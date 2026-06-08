#ifndef __LOGIC_MEASURED_DATA_HPP
#define __LOGIC_MEASURED_DATA_HPP

#include <cstdint>
#include "ResultCode.hpp"
#include "Sensor.hpp"

class Measurement
{
protected:
    ///
    Sensor &mrSensor;

public:
    /**
     * @brief 
     * @param rSensor 
     */
    Measurement(Sensor &rSensor) :
            mrSensor(rSensor)
    {}

    /**
     * @brief 
     */
    virtual ~Measurement(void)
    {}

    virtual ResultCode::Index_t configure(const void *) = 0;

    virtual float readF(void) = 0;

    virtual int32_t read(void) = 0;
};

#endif // #ifndef __LOGIC_MEASUREMENT_HPP