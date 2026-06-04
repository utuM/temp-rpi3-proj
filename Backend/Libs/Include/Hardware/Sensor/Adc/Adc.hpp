#ifndef __HARDWARE_SENSOR_ADC_HPP
#define __HARDWARE_SENSOR_ADC_HPP

#include "Sensor.hpp"

class Adc : public Sensor
{
public:
    /**
     *
     */
    typedef struct Config
    {
        
    } Config_t;

    /**
     * @brief 
     * @param 
     */
    Adc(const char *kpPath) :
            Sensor(kpPath)
    {}

    ResultCode::Index_t configure(const void *) override;

    int32_t read(void) override;
};

#endif // #ifndef __HARDWARE_SENSOR_ADC_HPP