#include "Multiplexer.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  kConfig 
 * @return 
 */
ResultCode::Index_t Multiplexer::select(const Config_t kConfig,
        const bool kNeedIgnoreValid)
{
    switch (kConfig) {
    case kMuxConfig0:
        mPinA1.reset();
        mPinA0.reset();
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig1:
        mPinA1.reset();
        mPinA0.set();
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig2:
        mPinA1.set();
        mPinA0.reset();
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig3:
        mPinA1.set();
        mPinA0.set();
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxOff:
        mPinEn.reset();
        break;

    default:
        return ResultCode::Index::kErrCommonInvArg;
    }
    return ResultCode::Index::kNoError;
}