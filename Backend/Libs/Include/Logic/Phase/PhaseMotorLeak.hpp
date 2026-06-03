#ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP
#define __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP

#include <cstdint>
#include "Phase.hpp"
#include "ResultCode.hpp"

class PhaseMotorLeak : public Phase
{
private:
    /**
     * 
     */
    typedef enum Step : uint8_t
    {
        kStep01Setup      = 0x00,
        kStep02Setup,
        kStep03Setup,
        kStep04Setup,
        kStep05Setup,
        kStep06Setup,
        kStep07PreTest,
        kStep08Air,
        kStep09Air20V,
        kStep10AirN20V,
        kStep11WaterN20V,
        kStep12Water20V,
        kStepsAmt
    } Step_t;

public:
    /// 
    static const uint8_t skStepsAmt = Step::kStepsAmt;

    /**
     * @brief 
     */
    PhaseMotorLeak(void) :
            Phase(kMotorLeak, skStepsAmt)
    {}

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void *) override;
    ResultCode::Index_t stop(void *) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_LEAK_HPP