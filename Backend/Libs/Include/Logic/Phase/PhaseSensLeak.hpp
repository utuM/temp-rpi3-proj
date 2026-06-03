#ifndef __LOGIC_PHASE_PHASE_SENS_LEAK_HPP
#define __LOGIC_PHASE_PHASE_SENS_LEAK_HPP

#include <cstdint>
#include "Phase.hpp"
#include "ResultCode.hpp"

class PhaseSensLeak : public Phase
{
private:
    /**
     * 
     */
    typedef enum Step : uint8_t
    {
        kStep01Setup   = 0x00,
        kStep02Setup,
        kStep03Setup,
        kStep04Setup,
        kStep05Setup,
        kStep06PreTest,
        kStep07LeakVp,
        kStep08LeakSn,
        kStep09LeakSp,
        kStep10LeakVn,
        kStepsAmt
    } Step_t;

public:
    /// 
    static const uint8_t skStepsAmt = Step::kStepsAmt;

    /**
     * @brief 
     */
    PhaseSensLeak(void) :
            Phase(Phase::Index::kSensorLeak, skStepsAmt)
    {}

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void *) override;
    ResultCode::Index_t stop(void *) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENS_LEAK_HPP