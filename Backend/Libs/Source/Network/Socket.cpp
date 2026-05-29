#include "Socket.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param kpPath 
 * @param evtAmt 
 */
Socket::Socket(const char *kpPath, int evtAmt) :
        mFdSock(skClosedFdIdx),
        mFdFrontSock(skClosedFdIdx),
        mFdEpoll(skClosedFdIdx),
        mPath(kpPath),
        mCliEvtAmt(evtAmt),
        mpCliEvt(nullptr)
{
    memset(&mEvent, 0x0, sizeof(epoll_event_t));
    mEvent.events = EPOLLIN;
}

/**
 * @brief 
 */
Socket::~Socket(void)
{
    // Close all of the occupied file descriptors with internal method does not
    // return any result back.
    _close();
}

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Socket::init(void)
{
    ResultCode::Index_t ret;
    saddru_t addr;

    // Check descriptiors information before continuing.
    if (mFdSock != skClosedFdIdx) {
        return ResultCode::Index::kErrSockOpenSockAlready;
    }
    if (mFdEpoll != skClosedFdIdx) {
        return ResultCode::Index::kErrSockOpenEpollAlready;
    }
    if (mPath.empty()) {
        return ResultCode::Index::kErrSockOpenSockNoPath;
    }

    // Unlink previous socket to be sure everything's clean.
    unlink(mPath.c_str());

    // UNIX-socket: initialize.
    mFdSock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (mFdSock < 0) {
        return ResultCode::Index::kErrSockOpenSockInvFd;
    }
    // UNIX-socket: bind.
    memset(&addr, 0x0, sizeof(saddru_t));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, mPath.c_str(), sizeof(addr.sun_path) - 1);
    if (bind(mFdSock, (saddr_t *) &addr, sizeof(addr)) < 0) {
        ret = ResultCode::Index::kErrSockOpenSockBind;
        goto exit_with_socket_cleanup;
    }
    // UNIX-socket: listen to incoming connections.
    if (listen(mFdSock, 5) < 0) {
        ret = ResultCode::Index::kErrSockOpenSockListen;
        goto exit_with_socket_cleanup;
    }

    // Initialize non-blocked listener for incoming I/O.
    mFdEpoll = epoll_create1(0);
    if (mFdEpoll < 0) {
        ret = ResultCode::Index::kErrSockOpenEpollInvFd;
        goto exit_with_socket_cleanup;
    }
    // Initialize controlling over the events.
    mpCliEvt = new epoll_event_t[mCliEvtAmt];
    if (!mpCliEvt) {
        ret = ResultCode::Index::kErrSockOpenEventsMem;
        goto exit_with_epoll_cleanup;
    }
    mEvent.data.fd = mFdSock;
    epoll_ctl(mFdEpoll, EPOLL_CTL_ADD, mFdSock, &mEvent);

    return ResultCode::Index::kNoError;

exit_with_epoll_cleanup:
    close(mFdEpoll);

exit_with_socket_cleanup:
    close(mFdSock);
    unlink(mPath.c_str());

    return ret;
}

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Socket::uninit(void)
{
    // Close events polling.
    if (mFdEpoll == skClosedFdIdx) {
        return ResultCode::Index::kErrSockCloseEpoll;
    } 
    close(mFdEpoll);
    mFdEpoll = skClosedFdIdx;
    // Close the connected client.
    if (mFdFrontSock != skClosedFdIdx) {
        close(mFdFrontSock);
        mFdFrontSock = skClosedFdIdx;
    }
    // Clean up the socket descriptor.
    if (mFdSock == skClosedFdIdx) {
        return ResultCode::Index::kErrSockCloseSock;
    }
    close(mFdSock);
    mFdSock = skClosedFdIdx;
    // Unlink socket.
    unlink(mPath.c_str());
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
int Socket::connect(void)
{
    if (mFdSock < 0) {
        return -(ResultCode::Index::kErrSockConnSockInvFd);
    }
    mFdFrontSock = accept(mFdSock, nullptr, nullptr);
    if (mFdFrontSock < 0) {
        return -(ResultCode::Index::kErrSockConnCliInvFd);
    }
    mEvent.data.fd = mFdFrontSock;
    epoll_ctl(mFdEpoll, EPOLL_CTL_ADD, mFdFrontSock, &mEvent);
    return mFdFrontSock;
}

/**
 * @brief 
 */
void Socket::disconnect(void)
{
    // Check that frontend socket is still valid before proceed.
    if (mFdFrontSock == skClosedFdIdx) {
        return;
    }
    epoll_ctl(mFdEpoll, EPOLL_CTL_DEL, mFdFrontSock, NULL);
    // Close the socket for the frontend.
    close(mFdFrontSock);
    mFdFrontSock = skClosedFdIdx;
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
        return 0;
    }
    if ((idx < 0) || (idx >= mCliEvtAmt)) {
        return -1;
    }
    if (_getCliFd(idx) != mFdFrontSock) {
        return -1;
    }
    return recv(mFdFrontSock, pData, length, 0);
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
        return 0;
    }
    if (mFdFrontSock == skClosedFdIdx) {
        return skClosedFdIdx;
    } 
    return send(mFdFrontSock, pData, length, 0);
}