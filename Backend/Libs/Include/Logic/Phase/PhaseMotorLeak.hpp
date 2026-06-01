#ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP
#define __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseMotorLeak : public Phase
{
protected:
    ResultCode::Index_t configure(void *) override;

public:
    /**
     * @brief 
     */
    PhaseMotorLeak(void) :
            Phase(kMotorLeak)
    {}

    ResultCode::Index_t run(void) override;
    ResultCode::Index_t stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP