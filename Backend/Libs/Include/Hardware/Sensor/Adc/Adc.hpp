#ifndef __HARDWARE_SENSOR_ADC_HPP
#define __HARDWARE_SENSOR_ADC_HPP

#include "Sensor.hpp"

class Adc : public Sensor
{
private:
    ///
    static constexpr const char *skRangeAttr = "in_voltage_scale";

    ///
    static constexpr const char *skRanges[] =
    {
        "0.0078125", ///< +-(256mV / 32768)
        "0.015625",  ///< +-(512mV / 32768)
        "0.03125",   ///< +-(1024mV / 32768)
        "0.0625",    ///< +-(2048mV / 32768)
        "0.125",     ///< +-(4096mV / 32768)
        "0.1875",    ///< +-(6144mV / 32768)
    };

    ///
    static constexpr const char *skAttrs[] =
    {
        "in_voltage0_raw",         ///< AIN0 to GND
        "in_voltage1_raw",         ///< AIN1 to GND
        "in_voltage2_raw",         ///< AIN2 to GND
        "in_voltage3_raw",         ///< AIN3 to GND
        "in_voltage2-voltage3_raw" ///< AIN2 to AIN3
    };

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
        kSingleAIN2,         ///< 0x02, measurement between AIN2 and GND
        kSingleAIN3,         ///< 0x03, measurement between AIN3 and GND
        kDifferAIN23         ///< 0x04, differencial measurement between
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
    static const uint8_t skBufRawSize  = 16u;
    ///
    static const uint8_t skBufScaleSize = 16u;

    /// 
    Config_t mConfig;

    ///
    char mBufRaw[skBufRawSize];
    ///
    char mBufScale[skBufScaleSize];

public:
    /**
     * @brief 
     * @param 
     */
    Adc(const char *kpPath) :
            Sensor(kpPath),
            mConfig{},
            mBufRaw{},
            mBufScale{}
    {}

    ResultCode::Index_t configure(const void *) override;

    int32_t read(void) override;
};

#endif // #ifndef __HARDWARE_SENSOR_ADC_HPP