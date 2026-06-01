#ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP
#define __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseMotorLeak : public Phase
{
public:
    /**
     * @brief 
     */
    PhaseMotorLeak(void) :
            Phase(kMotorLeak)
    {}

    int setup(void *) override;
    int run(void) override;
    int stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP