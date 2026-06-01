#ifndef __LOGIC_PHASE_PHASE_MANAGER_HPP
#define __LOGIC_PHASE_PHASE_MANAGER_HPP

#include <cstdint>
#include "Action.hpp"
#include "Phase.hpp"
#include "PhasesList.hpp"
#include "ResultCode.hpp"
#include "State.hpp"
#include "Status.hpp"
#include "Test.hpp"

class PhaseManager
{
public:
    static ResultCode::Index_t Configure(const Test::Option_t &);
    static ResultCode::Index_t Select(Phase::Index_t);
    static ResultCode::Index_t Control(Action::Index_t);
    static ResultCode::Index_t Tick(void);

    static Status::Info_t GetStatus(void);

private: 
    /// Array of pointers to the available/possible phase instances.
    static Phase *spAllPhases[Phase::skTotalAmt];

    /// Array of pointers with the selected phases ordering.
    static Phase *spSelected[Phase::skTotalAmt];
    /// Pointer to the current testing phase is running at this moment.
    static Phase *spCurrent;

    /// Current index of running test referenced to the selected phases array.
    static uint8_t sPhaseIdx;
    /// Amount of tests should be run and completed.
    static uint8_t sPhasesAmt;

    /// Current status instance.
    static Status::Info_t sStatus;

    /// Instance of the testing settings.
    static Test::Option_t sConfig;

    /// Start tick in milliseconds for the current testing phase.
    static uint32_t sStartTickMs;

public:
    /**
     * @brief 
     * @return 
     */
    static inline State::Index_t GetState(void)
    {
        return sStatus.state;
    }
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MANAGER_HPP