#include "Socket.hpp"

/* ************************************************************************* */

#ifdef MOTOR_BACKEND

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Socket::_initServer(void)
{
    saddru_t addr;

    // Check that the listening file descriptor is valid for continuing.
    if (mFdListen != skClosedFdIdx) {
        return ResultCode::Index::kErrSockOpenSockAlready;
    }

    // Unlink previous socket to be sure everything's clean.
    unlink(mPath.c_str());

    // UNIX-socket: initialize.
    mFdListen = socket(AF_UNIX, SOCK_STREAM, 0);
    if (mFdListen < 0) {
        return ResultCode::Index::kErrSockOpenSockInvFd;
    }
    // UNIX-socket: bind.
    memset(&addr, 0x0, sizeof(saddru_t));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, mPath.c_str(), sizeof(addr.sun_path) - 1);
    if (bind(mFdListen, (saddr_t *) &addr, sizeof(addr)) < 0) {
        _resetFd(mFdListen);
        unlink(mPath.c_str());
        return ResultCode::Index::kErrSockOpenSockBind;
    }
    // UNIX-socket: listen to incoming connections.
    if (listen(mFdListen, 5) < 0) {
        _resetFd(mFdListen);
        unlink(mPath.c_str());
        return ResultCode::Index::kErrSockOpenSockListen;
    }

    // Bind the file descriptor with the events.
    mEvent.data.fd = mFdListen;
    epoll_ctl(mFdEpoll, EPOLL_CTL_ADD, mFdListen, &mEvent);

    return ResultCode::Index::kNoError;
}

#endif // #ifdef MOTOR_BACKEND

/**
 * @brief 
 */
void Socket::_closeAll(void)
{
#ifdef MOTOR_BACKEND
    if (mFdListen != skClosedFdIdx) {
        close(mFdListen);
        mFdListen = skClosedFdIdx;
    }
#endif // #ifdef MOTOR_BACKEND

    if (mFdEpoll != skClosedFdIdx) {
        close(mFdEpoll);
        mFdEpoll = skClosedFdIdx;
    }
    if (mFdConn != skClosedFdIdx) {
        close(mFdConn);
        mFdConn = skClosedFdIdx;
    }

    // Remove the inter-communication socket only when the backend is stopping.
    if (mRole == kServer) {
        if (!mPath.empty()) {
            unlink(mPath.c_str());
        }
    }
    // De-allocate memory has been occupied for events.
    if (mpCliEvt) {
        delete[] mpCliEvt;
        mpCliEvt = nullptr;
    }
}

/* ************************************************************************* */

/**
 * @brief 
 * @param kpPath 
 * @param evtAmt 
 */
Socket::Socket(const char *kpPath, int evtAmt) :
        mPath(kpPath),
        mRole(kServer),
        mFdConn(skClosedFdIdx),
        mFdEpoll(skClosedFdIdx),

#ifdef MOTOR_BACKEND
        mFdListen(skClosedFdIdx),
#endif // #ifndef MOTOR_BACKEND

        mCliEvtAmt(evtAmt),
        mpCliEvt(nullptr)
{
    memset(&mEvent, 0x0, sizeof(epoll_event_t));
    mEvent.events = EPOLLIN;

#ifdef MOTOR_FRONTEND
    // Identify the role as "client".
    mRole = kClient;
#endif // #ifdef MOTOR_FRONTEND
}

/**
 * @brief 
 */
Socket::~Socket(void)
{
    // Close all of the occupied file descriptors with internal method does not
    // return any result back.
    _closeAll();
}

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Socket::init(void)
{
    // Check descriptors indexes before continuing.
    if (mFdConn != skClosedFdIdx) {
        return ResultCode::Index::kErrSockOpenSockAlready;
    }
    if (mFdEpoll != skClosedFdIdx) {
        return ResultCode::Index::kErrSockOpenEpollAlready;
    }
    if (mPath.empty()) {
        return ResultCode::Index::kErrSockOpenSockNoPath;
    }

    // Initialize non-blocked listener for incoming I/O.
    mFdEpoll = epoll_create1(0);
    if (mFdEpoll < 0) {
        return ResultCode::Index::kErrSockOpenEpollInvFd;
    }
    // Initialize controlling over the events.
    if (!mpCliEvt) { ///< if the "uninit()" has been called before
        mpCliEvt = new epoll_event_t[mCliEvtAmt];
        if (!mpCliEvt) { /// to be sure that memory has been allocated
            _resetFd(mFdEpoll);
            return ResultCode::Index::kErrSockOpenEventsMem;
        }
    }

    // Launch different initialization/processing based on the role.
    if (mRole == kServer) {
        return _initServer();
    }
    return connect();
}

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Socket::uninit(void)
{
    // Check that all of the 
    if (mFdEpoll == skClosedFdIdx) {
        return ResultCode::Index::kErrSockCloseEpoll;
    }
    _resetFd(mFdEpoll);

#ifdef MOTOR_BACKEND
    // Close the connected frontend if this application is backend.
    if (mFdListen == skClosedFdIdx) {
        return ResultCode::Index::kErrSockCloseListen;
    }
    _resetFd(mFdListen);
#endif // #ifdef MOTOR_BACKEND

    // Clean up the socket descriptor.
    if (mFdConn == skClosedFdIdx) {
        return ResultCode::Index::kErrSockCloseSock;
    }
    _resetFd(mFdConn);

    // Unlink socket in a case of the "server" role.
    if (mRole == kServer) {
        if (!mPath.empty()) {
            unlink(mPath.c_str());
        }
    }
    // De-allocate memory if need to do that.
    if (mpCliEvt) {
        delete[] mpCliEvt;
        mpCliEvt = nullptr;
    }

    return ResultCode::Index::kNoError;
}

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Socket::connect(void)
{
    // Process/prepare file descriptor based on the current role.
    if (mRole == kServer) {
        if (mFdListen < 0) {
            return ResultCode::Index::kErrSockConnSockInvFd;
        }
        mFdConn = accept(mFdListen, nullptr, nullptr);
        if (mFdConn < 0) {
            mFdConn = skClosedFdIdx;
            return ResultCode::Index::kErrSockConnCliInvFd;
        }
    } else {
        // Reset current connectivity if there is an active one.
        if (mFdConn != skClosedFdIdx) {
            disconnect();
        }

        saddru_t addr;
        memset(&addr, 0x0, sizeof(saddru_t));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, mPath.c_str(), sizeof(addr.sun_path) - 1);

        mFdConn = socket(AF_UNIX, SOCK_STREAM, 0);
        if (mFdConn < 0) {
            mFdConn = skClosedFdIdx;
            return ResultCode::Index::kErrSockConnSockInvFd;
        }
        if (::connect(mFdConn, (saddr_t *) &addr, sizeof(addr)) < 0) {
            close(mFdConn);
            mFdConn = skClosedFdIdx;
            return ResultCode::Index::kErrSockConnCliInvFd;
        }
    }

    // Bind the processed file descriptor with events observing mechanism.
    mEvent.data.fd = mFdConn;
    epoll_ctl(mFdEpoll, EPOLL_CTL_ADD, mFdConn, &mEvent);

    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 */
void Socket::disconnect(void)
{
    // Check that frontend socket is still valid before proceed.
    if (mFdConn == skClosedFdIdx) {
        return;
    }
    epoll_ctl(mFdEpoll, EPOLL_CTL_DEL, mFdConn, nullptr);
    // Close the socket for the frontend.
    _resetFd(mFdConn);
}

/**
 * @brief 
 * @param  kWaitMs 
 * @return 
 */
int Socket::wait(uint32_t kWaitMs)
{
    return epoll_wait(mFdEpoll, mpCliEvt, mCliEvtAmt, kWaitMs);
}

/**
 * @brief 
 * @param  idx 
 * @param  pData 
 * @param  length 
 * @return 
 */
int Socket::receive(int idx, void *pData, int length)
{
    if (!pData || (length <= 0)) {
        return -1;
    }
    if ((idx < 0) || (idx >= mCliEvtAmt)) {
        return -1;
    }
    if (_getEventFd(idx) != mFdConn) {
        return -1;
    }
    // Get the received amount of data, or an error code to be passed to the 
    // outside and for error processing.
    int ret = recv(mFdConn, pData, length, 0);
    return (ret <= 0 ? -1 : ret);
}

/**
 * @brief  
 * @param  pData 
 * @param  length 
 * @return 
 */
int Socket::transmit(void *pData, int length)
{
    if (!pData || (length <= 0)) {
        return -1;
    }
    if (mFdConn == skClosedFdIdx) {
        return skClosedFdIdx;
    } 
    return send(mFdConn, pData, length, 0);
}