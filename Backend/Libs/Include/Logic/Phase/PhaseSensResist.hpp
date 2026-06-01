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

    ResultCode::Index_t setup(void *) override;
    ResultCode::Index_t run(void) override;
    ResultCode::Index_t stop(void) override;
};

#endif // #ifndef __LOGIC_PHASE_PHASE_SENSOR_RESIST_HPP