#ifndef __LOGIC_PHASE_PHASE_MANAGER_HPP
#define __LOGIC_PHASE_PHASE_MANAGER_HPP

#include <cstdint>
#include "Action.hpp"
#include "Phase.hpp"
#include "ResultCode.hpp"
#include "State.hpp"
#include "Test.hpp"

class PhaseManager
{
public:
    static ResultCode::Index_t Configure(const Test::Option_t &);
    static ResultCode::Index_t Select(Phase::Index_t);
    static ResultCode::Index_t Control(Action::Index_t);
    static ResultCode::Index_t Tick(void);

private: 
    /// Array of pointers with the selected phases ordering.
    static Phase *spSelected[Phase::skTotalAmt];
    /// Pointer to the current testing phase is running at this moment.
    static Phase *spCurrent;

    /// Current processing state.
    static State::Index_t sState;

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
        return sState;
    }
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MANAGER_HPP