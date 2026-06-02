#ifndef __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP
#define __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseMotorResist : public Phase
{
private:
    /**
     * 
     */
    typedef enum Index : uint8_t
    {
        kStep01Setup        = 0x00,
        kStep02Setup,
        kStep03ZeroMult,
        kStep04PumpConn,
        kStep05Phase1to2,
        kStep06Phase1to3,
        kStep07Phase2to3,
        kStep08Phase3toGND,
        kStepsAmt
    } Index_t;

public:
    /**
     * @brief 
     */
    PhaseMotorResist(void) :
            Phase(kPhaseResist)
    {}

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void *) override;
    ResultCode::Index_t stop(void *) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_MOTOR_RESIST_HPP