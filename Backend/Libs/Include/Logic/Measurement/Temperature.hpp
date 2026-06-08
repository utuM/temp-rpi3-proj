#ifndef __LOGIC_MEASUREMENT_TEMPERATURE_HPP
#define __LOGIC_MEASUREMENT_TEMPERATURE_HPP

#include "Measurement.hpp"
#include "Rtd.hpp"

class Temperature : public Measurement
{
public:
    /**
     * @brief 
     * @param rRtd 
     */
    Temperature(Rtd &rRtd) :
            Measurement(rRtd)
    {}

    ResultCode::Index_t configure(const void *);

    float readF(void) override;

    int32_t read(void) override;
};

#endif // #ifndef __LOGIC_MEASUREMENT_TEMPERATURE_HPP