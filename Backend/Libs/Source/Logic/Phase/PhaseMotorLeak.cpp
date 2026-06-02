#include "PhaseMotorLeak.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::setup(void *)
{
    /**
     * TODO: make an initialization before starting to drive motor leakage
     *       current measurement.
     */
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::run(void *)
{
    ResultCode::Index_t ret = ResultCode::Index::kErrPhaseStepInProgress;
    // Drive steps applicable for this phase.
    switch (mStep) {
    case kStep01Setup:
        break;

    case kStep02Setup:
        break;

    case kStep03Setup:
        break;

    case kStep04Setup:
        break;

    case kStep05Setup:
        break;

    case kStep06Setup:
        break;

    case kStep07PreTest:
        break;

    case kStep08Air:
        break;

    case kStep09Air20V:
        break;

    case kStep10AirN20V:
        break;

    case kStep11WaterN20V:
        break;

    case kStep12Water20V:
        break;

    default:
        ret = ResultCode::Index::kErrPhaseInvalidStepIdx;
        break;
    }
    return ret;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::stop(void *)
{
    return ResultCode::Index::kNoError;
}