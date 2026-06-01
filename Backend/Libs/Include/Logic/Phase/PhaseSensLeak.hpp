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

    int setup(void *) override;
    int run(void) override;
    int stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENS_LEAK_HPP