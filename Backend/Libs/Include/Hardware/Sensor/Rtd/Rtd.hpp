#ifndef __HARDWARE_SENSOR_RTD_HPP
#define __HARDWARE_SENSOR_RTD_HPP

#include "Sensor.hpp"

class Rtd : public Sensor
{
private:
    /// 


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
    Rtd(const char *kpPath) :
            Sensor(kpPath)
    {}

    ResultCode::Index_t configure(const void *) override;

    int32_t read(void) override;
};

#endif // #ifndef __HARDWARE_SENSOR_RTD_HPP