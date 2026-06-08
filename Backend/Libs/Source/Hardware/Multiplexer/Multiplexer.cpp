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
        mPinA1.reset(mAttrA1);
        mPinA0.reset(mAttrA0);
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig1:
        mPinA1.reset(mAttrA1);
        mPinA0.set(mAttrA0);
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig2:
        mPinA1.set(mAttrA1);
        mPinA0.reset(mAttrA0);
        _muxEnableIfNot(kNeedIgnoreValid);
        break;

    case kMuxConfig3:
        mPinA1.set(mAttrA1);
        mPinA0.set(mAttrA0);
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