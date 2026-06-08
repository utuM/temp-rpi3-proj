#ifndef __LOGIC_MEASUREMENT_PRESSURE_HPP
#define __LOGIC_MEASUREMENT_PRESSURE_HPP

#include "Adc.hpp"
#include "Measurement.hpp"

class Pressure : public Measurement
{
public:
    /**
     *
     */
    typedef struct __attribute__((packed)) Config
    {
        /// 
        Adc::Config_t adc;
        
        /**
         * 
         */
        struct
        {
            ///
            uint32_t highOhm;
            ///
            uint32_t lowOhm;
        } divider;
        
        /**
         *
         */
        struct
        {
            ///
            uint32_t min;
            ///
            uint32_t max;
        } sensMv;

        /**
         *
         */
        struct
        {
            ///
            uint32_t min;
            ///
            uint32_t max;
        } range;
    } Config_t;
    
    /**
     * @brief 
     * @param rAdc 
     */
    Pressure(Adc &rAdc) :
            Measurement(rAdc)
    {}

    ResultCode::Index_t configure(const void *) override;

    float readF(void) override;

    int32_t read(void) override;
};

#endif // #ifndef __LOGIC_MEASUREMENT_PRESSURE_HPP