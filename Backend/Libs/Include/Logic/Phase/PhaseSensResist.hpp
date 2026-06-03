#ifndef __LOGIC_PHASE_PHASE_SENS_RESIST_HPP
#define __LOGIC_PHASE_PHASE_SENS_RESIST_HPP

#include <cstdint>
#include "Phase.hpp"
#include "ResultCode.hpp"

class PhaseSensResist : public Phase
{
private:
    /**
     * 
     */
    typedef enum Step : uint8_t
    {
        kStep01Setup        = 0x00,
        kStep02Setup,
        kStep03ZeroMult,
        kStep04PumpConn,
        kStep05PhaseVptoVn,
        kStep06PhaseSptoSn,
        kStep07PhaseVptoSn,
        kStep08PhaseVptoSp,
        kStep09PhaseSptoVn,
        kStep10PhaseVntoSn,
        kStepsAmt
    } Step_t;

public:
    /// 
    static const uint8_t skStepsAmt = Step::kStepsAmt;

    /**
     * @brief 
     */
    PhaseSensResist(void) :
            Phase(kSensorResist, skStepsAmt)
    {}

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void *) override;
    ResultCode::Index_t stop(void *) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENS_RESIST_HPP