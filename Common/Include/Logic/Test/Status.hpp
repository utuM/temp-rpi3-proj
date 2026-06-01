#ifndef __LOGIC_TEST_STATUS_HPP
#define __LOGIC_TEST_STATUS_HPP

#include <cstdint>
#include "Phase.hpp"
#include "State.hpp"

class Status
{
public:
    /**
     *
     */
    typedef struct __attribute__((packed)) Info
    {
        /// Current state in the testing processing sequence.
        State::Index_t state;
        /// Test sequence duration the application is already passed at this
        /// moment.
        uint32_t durMs;

        /**
         *
         */
        struct CurrentPhase
        {
            /// Current testing phase.
            Phase::Index_t idx;
            /// Current testing step.
            uint8_t step;
        } phase;
    } Info_t;
};

#endif // #ifndef __LOGIC_TEST_STATUS_HPP