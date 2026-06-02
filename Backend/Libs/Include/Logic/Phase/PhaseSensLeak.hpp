#ifndef __LOGIC_PHASE_PHASE_SENS_LEAK_HPP
#define __LOGIC_PHASE_PHASE_SENS_LEAK_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseSensLeak : public Phase
{
public:
    /**
     * @brief 
     */
    PhaseSensLeak(void) :
            Phase(kSensorLeak)
    {}

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void *) override;
    ResultCode::Index_t stop(void *) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENS_LEAK_HPP