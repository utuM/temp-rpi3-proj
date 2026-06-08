#ifndef __LOGIC_MEASUREMENT_VOLTAGE_HPP
#define __LOGIC_MEASUREMENT_VOLTAGE_HPP

#include "Adc.hpp"
#include "Measurement.hpp"

class Voltage : public Measurement
{
public:
    /**
     *
     */
    typedef struct __attribute__((packed)) Config
    {
        /// 
        Adc::Config_t adc;
    } Config_t;

    /**
     * @brief 
     * @param rAdc 
     */
    Voltage(Adc &rAdc) :
            Measurement(rAdc)
    {}

    ResultCode::Index_t configure(const void *) override;

    float readF(void) override;

    int32_t read(void) override;
    int32_t readUv(void);
};

#endif // #ifndef __LOGIC_MEASUREMENT_VOLTAGE_HPP