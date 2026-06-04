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

        kErrCommonNullPtr,

        kErrNodeOpenFailed,
        kErrNodeOpenAttrFailed,
        kErrNodeReadFailed,
        kErrNodeWriteFailed,

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

        kErrPhaseNotSelected,
        kErrPhaseInvalidState,
        kErrPhaseAlreadyRunning,
        kErrPhaseNothingToRun,
        kErrPhaseStepInProgress,
        kErrPhaseInvalidStepIdx,
        kErrPhaseIsCompleted
    } Index_t;
};

#endif // #ifndef __GLOBAL_RESULT_CODE_HPP