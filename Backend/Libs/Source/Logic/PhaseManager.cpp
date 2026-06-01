#include "PhaseManager.hpp"

static PhaseMotorResist sPhaseMotorResist;
static PhaseSensResist  sPhaseSensResist;
static PhaseMotorLeak   sPhaseMotorLeak;
static PhaseSensLeak    sPhaseSensLeak;

/* ************************************************************************* */

Phase *PhaseManager::spAllPhases[Phase::skTotalAmt] =
{
    &sPhaseMotorResist, ///< this is the 'kPhaseResist'
    &sPhaseSensResist,  ///< this is the 'kSensResist'
    &sPhaseMotorLeak,   ///< this is the 'kMotorLeak'
    &sPhaseSensLeak     ///< this is the 'kSensLeak'
};

Phase *PhaseManager::spSelected[Phase::skTotalAmt] = { nullptr };
Phase *PhaseManager::spCurrent                     = nullptr;

Status::Info_t PhaseManager::sStatus;

Test::Option_t PhaseManager::sConfig;

uint32_t PhaseManager::sStartTickMs = 0ul;

/* ************************************************************************* */

/**
 * @brief 
 * @param  rOpts
 * @return 
 */
ResultCode::Index_t PhaseManager::Configure(const Test::Option_t & rOpts)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  phase
 * @return 
 */
ResultCode::Index_t PhaseManager::Select(Phase::Index_t phase)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  act
 * @return 
 */
ResultCode::Index_t PhaseManager::Control(Action::Index_t act)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t PhaseManager::Tick(void)
{
    // Check if the pointer to the current testing phase instance is null.
    if (!spCurrent) {
        // If so, then the testing phase is not selected yet, so return with
        // the error code.
        return ResultCode::Index::kErrPhaseNotSelected;
    }

    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
Status::Info_t PhaseManager::GetStatus(void)
{
    return sStatus;
}