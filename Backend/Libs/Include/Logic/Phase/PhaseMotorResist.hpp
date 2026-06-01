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

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void) override;
    ResultCode::Index_t stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP