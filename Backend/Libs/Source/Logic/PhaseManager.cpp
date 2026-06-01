#include <cstring>
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

uint8_t PhaseManager::sPhaseIdx  = 0u;
uint8_t PhaseManager::sPhasesAmt = 0u;

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
    // Do not apply any configuration if the testing is already running, so
    // check the current state for that.
    if (sStatus.state != State::Index::kIdle) { ///< code should be stopped
        return ResultCode::Index::kErrPhaseAlreadyRunning;
    }

    // Check the passed mode to identify the order.
    switch (rOpts.mode) {
    case Mode::Index::kAuto:
        // Clean up the set of test instances.
        memset(spSelected, 0x00, Phase::skTotalAmt * sizeof(Phase *));
        // Copy the default pointers amount based on the passed flags.
        if (rOpts.hasTestedOnBench) {
            spSelected[0] = spAllPhases[Phase::Index::kPhaseResist];
            if (rOpts.hasOpticalSensor) { ///< make the Motor Leakage next
                spSelected[1] = spAllPhases[Phase::Index::kMotorLeak];
                sPhasesAmt = 2u;
            } else {                      ///< check flags further
                // Put with the default set of tests.
                spSelected[1] = spAllPhases[Phase::Index::kSensorResist];
                spSelected[2] = spAllPhases[Phase::Index::kMotorLeak];
                // Add the sensor leakage current measurements if the pressure
                // cap is not presented.
                if (!rOpts.hasPressureCap) {
                    spSelected[3] = spAllPhases[Phase::Index::kSensorLeak];
                    sPhasesAmt = Phase::kAmt;
                } else {
                    sPhasesAmt = 3u;
                }
            }
        } else {
            spSelected[0] = spAllPhases[Phase::Index::kMotorLeak];
            spSelected[1] = spAllPhases[Phase::Index::kPhaseResist];
            if (!rOpts.hasOpticalSensor) {
                spSelected[2] = spAllPhases[Phase::Index::kSensorResist];
                if (!rOpts.hasPressureCap) {
                    spSelected[3] = spAllPhases[Phase::Index::kSensorLeak];
                    sPhasesAmt = Phase::kAmt;
                } else {
                    sPhasesAmt = 3u;
                }
            } else {
                sPhasesAmt = 2u;
            }
        }
        break;
        
    case Mode::Index::kAutoCustom:
        // Process the incoming phase indexes should be processed by the
        // backend.
        sPhasesAmt = 0u;
        for (uint8_t i = 0u; i < Test::skMaxOrderSize; i++) {
            if (rOpts.order[i] < Phase::Index::kAmt) {
                spSelected[i] = spAllPhases[rOpts.order[i]];
                ++sPhasesAmt;
            }
        }
        if (!sPhasesAmt) {
            return ResultCode::Index::kErrPhaseNothingToRun;
        }
        break;

    default:
        // Nothing to do in a case of the "Semi-manual" or "Manual" modes
        // because Frontend should control the processing on the Backend side,
        // so just break the switch statement.
        break;
    }
    // Copy the input options instance to the internal one for the further
    // usage.
    sConfig = rOpts;

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