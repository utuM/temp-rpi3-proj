#ifndef __LOGIC_MEASUREMENT_RESISTANCE_HPP
#define __LOGIC_MEASUREMENT_RESISTANCE_HPP

#include "Adc.hpp"
#include "Measurement.hpp"

class Resistance : public Measurement
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
    Resistance(Adc &rAdc) :
            Measurement(rAdc)
    {}

    ResultCode::Index_t configure(const void *) override;

    float readF(void) override;

    int32_t read(void) override;
};

#endif // #ifndef __LOGIC_MEASUREMENT_RESISTANCE_HPP