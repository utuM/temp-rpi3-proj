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
public:
    /**
     *
     */
    typedef enum Role : uint8_t
    {
        kServer  = 0x00, ///< 0x00, backend role which is a server role
        kClient          ///< 0x01, frontend role which is a client role
    } Role_t;

private:
    ///
    typedef struct sockaddr_un saddru_t;
    ///
    typedef struct sockaddr    saddr_t;
    ///
    typedef struct epoll_event epoll_event_t;

    ///
    static const int     skClosedFdIdx = -1;
    /// 
    static const uint8_t skEventsAmt   = 16u;

    /// Target path to the Unix-socket backend and frontend should to
    /// communicate thru.
    std::string mPath;

    /// Current role of the socket/application: backend(server) or
    /// frontend(client).
    Role_t mRole;

    /// Base file descriptor for the incoming/outgoing data between
    /// applications.
    int mFdConn;
    /// File descriptor for the events polling.
    int mFdEpoll;
    
#ifdef MOTOR_BACKEND
    /// Specific file descriptor to wait until the frontend application is
    /// trying to establish inter-communication between processes. 
    int mFdListen;
#endif // #ifdef MOTOR_BACKEND

    ///
    int           mCliEvtAmt;
    ///
    epoll_event_t *mpCliEvt;

    /// 
    epoll_event_t mEvent;

    /**
     * @brief 
     * @param rFd 
     */
    inline void _resetFd(int &rFd)
    {
        close(rFd);
        rFd = skClosedFdIdx;
    }

    /**
     * @brief 
     * @param  idx 
     * @return 
     */
    inline int _getEventFd(int idx)
    {
        return mpCliEvt[idx].data.fd;
    }

#ifdef MOTOR_BACKEND
    ResultCode::Index_t _initServer(void);
#endif // #ifdef MOTOR_BACKEND

    void _closeAll(void);

public: 
    /**
     * @brief 
     * @return 
     */
    inline bool isConnected(void) const
    {
        return (mFdConn != skClosedFdIdx);
    }

    /**
     * @brief  
     * @return 
     */
    inline bool need2Accept(void) const
    {
        return ((mRole == kServer) && (mFdConn == skClosedFdIdx));
    }

    Socket(const char *, int evtAmt = skEventsAmt);
    ~Socket(void);

    ResultCode::Index_t init(void);
    ResultCode::Index_t uninit(void);

    ResultCode::Index_t connect(void);
    void                disconnect(void);

    int wait(uint32_t);

    int receive(int, void *, int);
    int transmit(void *, int);
};

#endif // #ifndef __NETWORK_UNIX_SOCKET_HPP