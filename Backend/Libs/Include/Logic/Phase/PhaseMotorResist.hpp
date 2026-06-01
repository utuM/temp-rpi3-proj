#ifndef __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP
#define __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseMotorResist : public Phase
{
public:
    /**
     * @brief 
     */
    PhaseMotorResist(void) :
            Phase(kPhaseResist)
    {}

    int setup(void *);
    int run(void);
    int stop(void);
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP