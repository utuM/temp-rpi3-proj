#ifndef __LOGIC_PHASE_PHASE_SENSOR_RESIST_HPP
#define __LOGIC_PHASE_PHASE_SENSOR_RESIST_HPP

#include <cstdint>
#include "Phase.hpp"

class PhaseSensResist : public Phase
{
public:
    /**
     * @brief 
     */
    PhaseSensResist(void) :
            Phase(kSensorResist)
    {}

    int setup(void *) override;
    int run(void) override;
    int stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENSOR_RESIST_HPP