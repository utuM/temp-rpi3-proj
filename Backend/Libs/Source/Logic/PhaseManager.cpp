#include <cstring>
#include "PhaseManager.hpp"
#include "SysTick.hpp"

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
        // Clean up the set of test instances.
        memset(spSelected, 0x00, Phase::skTotalAmt * sizeof(Phase *));
        // Process the incoming phase indexes should be processed by the
        // backend.
        sPhasesAmt = 0u;
        for (uint8_t i = 0u; i < Test::skMaxOrderSize; i++) {
            if (rOpts.order[i] < Phase::Index::kAmt) {
                spSelected[sPhasesAmt++] = spAllPhases[rOpts.order[i]];
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
    // Prevent to select phase by the Frontend if the Backend is running one of
    // the automatic modes.
    if (sConfig.mode <= Mode::Index::kAutoCustom) {
        // If the mode is "Auto" or "Auto Custom", then the phase selection is
        // not allowed, so return with the error code.
        return ResultCode::Index::kErrPhaseInvalidState;
    }
    // Do not allow to select the phase if the testing sequence is already running.
    if ((sStatus.state != State::Index::kIdle) &&
            (sStatus.state != State::Index::kPaused)) {
        return ResultCode::Index::kErrPhaseInvalidState;
    }
    // Do not select anything outside of the possible test indexes.
    if (phase >= sPhasesAmt) {
        return ResultCode::Index::kErrPhaseNotSelected;
    }
    // Update the current phase index and pointer to the current phase instance
    // based on the phase instances order.
    sPhaseIdx = phase;
    spCurrent = spSelected[phase];

    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  act 
 * @return 
 */
ResultCode::Index_t PhaseManager::Control(Action::Index_t act)
{
    // Process incoming action based on the current state of the testing
    // process.
    State::Index_t state = sStatus.state;
    switch (act) {
    case Action::Index::kStart:
        // Check the mode and select what to do based on its value.
        if (sConfig.mode <= Mode::Index::kAutoCustom) {
            // Check if the testing sequence is not awaiting for the start and
            // not paused.
            if (state != State::Index::kIdle) {
                return ResultCode::Index::kErrPhaseInvalidState;
            }
            // If the mode is "Auto" or "Auto Custom", then just start the
            // testing sequence based on the selected phases.
            if (!spSelected[0]) {
                return ResultCode::Index::kErrPhaseNotSelected;
            }
            sPhaseIdx = 0u;
            spCurrent = spSelected[0];
        } else {
            // Check if the testing sequence is not awaiting for the start and
            // not paused.
            if ((state != State::Index::kIdle) &&
                    (state != State::Index::kPaused)) {
                return ResultCode::Index::kErrPhaseInvalidState;
            }
            // Before staring the testing phase instance should be transmitted to the 
            if (!spCurrent) {
                return ResultCode::Index::kErrPhaseNotSelected;
            }
        }
        // Reset the fields before enabling the state machine.
        sStartTickMs  = SysTick::TicksMs();
        sStatus.state = State::Index::kStarting;
        break;
        
    case Action::Index::kContinue:
        // Check if the testing sequence is already starting itself, running
        // the processes or stopping/finishing the current actual test.
        if ((state <= State::Index::kStarting) ||
                (state == State::Index::kRunning) ||
                (state >= State::Index::kStopping)) {
            return ResultCode::Index::kErrPhaseInvalidState;
        }
        // Change the manager state to the "Running" one to continue the processing.
        sStatus.state = State::Index::kRunning;
        break;

    case Action::Index::kPause: 
        // Check if the testing sequence is not running at the moment, so
        // nothing to pause here.
        if ((state == State::Index::kIdle) ||
                (state == State::Index::kPaused) ||
                (state >= State::Index::kStopping)) {
            return ResultCode::Index::kErrPhaseInvalidState;
        }
        // Change the manager state to the "Paused" to prevent ticking of the
        // manager.
        sStatus.state = State::Index::kPaused;
        break;
    
    case Action::Index::kStop:
        // Check if the testing sequence is not running at the moment, so
        // nothing to stop here.
        if ((state == State::Index::kIdle) ||
                (state >= State::Index::kStopping)) {
            return ResultCode::Index::kErrPhaseInvalidState;
        }
        // Change the manager state to the "Stopping" to launch the stopping 
        // process for the current selected testing sequence.
        sStatus.state = State::Index::kStopping;
        break;
    
    case Action::Index::kRestart:
        // TODO: place a code to trigger the Backend to restart.
        break;  
    }
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t PhaseManager::Tick(void)
{
    // Allow to return positive result in a case when the manager is waiting
    // for incoming commands.
    if (sStatus.state == State::Index::kIdle) {
        return ResultCode::Index::kNoError;
    }
    // Check if the pointer to the current testing phase instance is null.
    if (!spCurrent) {
        // If so, then the testing phase is not selected yet, so return with
        // the error code.
        return ResultCode::Index::kErrPhaseNotSelected;
    }
    // Run the state machine.
    // TODO: 

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