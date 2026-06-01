#ifndef __GLOBAL_RESULT_CODE_HPP
#define __GLOBAL_RESULT_CODE_HPP

class ResultCode
{
public:
    /**
     *
     */
    typedef enum Index : int
    {
        kNoError = 0,

        kErrSockOpenSockAlready,
        kErrSockOpenEpollAlready,
        kErrSockOpenSockNoPath,
        kErrSockOpenSockInvFd,
        kErrSockOpenSockBind,
        kErrSockOpenSockListen,
        kErrSockOpenEpollInvFd,
        kErrSockOpenEventsMem,
        kErrSockConnSockInvFd,
        kErrSockConnCliInvFd,
        kErrSockConnEpollBind,
        kErrSockCloseEpoll,
        kErrSockCloseListen,
        kErrSockCloseSock,
    } Index_t;
};

#endif // #ifndef __GLOBAL_RESULT_CODE_HPP