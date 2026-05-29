#ifndef __NETWORK_SOCKET_HPP
#define __NETWORK_SOCKET_HPP

#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "ResultCode.hpp"

class Socket
{
private:
    ///
    typedef struct sockaddr_un saddru_t;
    ///
    typedef struct sockaddr saddr_t;

    ///
    typedef struct epoll_event epoll_event_t;

    ///
    static const int skClosedFdIdx = -1;

    /// 
    static const uint8_t skEventsAmt = 10u;

    /// 
    int mFdSock;
    ///
    int mFdFrontSock;
    ///
    int mFdEpoll;

    /// 
    std::string mPath;

    ///
    int           mCliEvtAmt;
    ///
    epoll_event_t *mpCliEvt;

    ///
    epoll_event_t mEvent;

    /**
     * @brief 
     * @param  idx 
     * @return 
     */
    inline int _getCliFd(int idx)
    {
        return mpCliEvt[idx].data.fd;
    }

    /**
     * @brief 
     */
    inline void _close(void)
    {
        if (mFdEpoll != skClosedFdIdx) {
            close(mFdEpoll);
        }
        if (mFdFrontSock != skClosedFdIdx) {
            close(mFdFrontSock);
        }
        if (mFdSock != skClosedFdIdx) {
            close(mFdSock);
        }
        if (!mPath.empty()) {
            unlink(mPath.c_str());
        }
        // De-allocate memory has been occupied for events.
        if (mpCliEvt) {
            delete[] mpCliEvt;
            mpCliEvt = nullptr;
        }
    }

public: 
    /**
     * @brief  
     * @return 
     */
    inline bool need2Accept(void)
    {
        return (mFdFrontSock == skClosedFdIdx);
    }

    Socket(const char *, int evtAmt = skEventsAmt);
    ~Socket(void);

    ResultCode::Index_t init(void);
    ResultCode::Index_t uninit(void);

    int  connect(void);
    void disconnect(void);

    int wait(uint32_t);

    int receive(int, void *, int);
    int transmit(void *, int);
};

#endif // #ifndef __NETWORK_UNIX_SOCKET_HPP