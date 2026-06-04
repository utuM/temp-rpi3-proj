#ifndef __HARDWARE_SENSOR_ADC_HPP
#define __HARDWARE_SENSOR_ADC_HPP

#include "Sensor.hpp"

class Adc : public Sensor
{
public:
    /**
     * @brief 
     */
    typedef enum Range : uint8_t
    {
        kFsr0256V = 0x00, ///< 0x00, range of -0.256V..0.256V
        kFsr0512V,        ///< 0x01, range of -0.512V..0.512V
        kFsr1V,           ///< 0x02, range of -1.024V..1.024V
        kFsr2V,           ///< 0x03, range of -2.048V..2.048V
        kFsr4V,           ///< 0x04, range of -4.096V..4.096V
        kFsr6V            ///< 0x05, range of -6.144V..6.144V
    } Range_t;

    /**
     * @brief 
     */
    typedef enum Input : uint8_t
    {
        kSingleAIN0  = 0x00, ///< 0x00, measurement between AIN0 and GND
        kSingleAIN1,         ///< 0x01, measurement between AIN1 and GND
        kDifferAIN23         ///< 0x02, differencial measurement between
                             ///        AIN2(+) and AIN3(-)
    } Input_t;

    /**
     * @brief 
     */
    typedef struct __attribute__((packed)) Config
    {
        /// 
        Range_t range;
        /// 
        Input_t input;
    } Config_t;

private:
    /// 
    static constexpr char *skPath =
            "/sys/bus/iio/devices/iio\:device1";

    /// 
    Config_t mConfig;

public:
    /**
     * @brief 
     * @param 
     */
    Adc(const char *kpPath) :
            Sensor(kpPath),
            mConfig{}
    {}

    ResultCode::Index_t configure(const void *) override;

    int32_t read(void) override;
};

#endif // #ifndef __HARDWARE_SENSOR_ADC_HPP