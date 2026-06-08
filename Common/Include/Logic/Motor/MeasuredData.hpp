#ifndef __LOGIC_MOTOR_MEASURED_DATA_HPP
#define __LOGIC_MOTOR_MEASURED_DATA_HPP

#include <cstdint>

class MeasuredData
{
public:
    ///
    static const uint8_t skArraySize = 6u;

    /**
     *
     */
    typedef enum Type : uint8_t
    {
        kV_mV  = 0x00, ///< 0x00, voltage measurement, in milivolts
        kV_V,          ///< 0x01, voltage measurement, in volts
        kA_uA,         ///< 0x02, current measurement, in microamps
        kA_mA,         ///< 0x03, current measurement, in miliamps      
        kT_C,          ///< 0x04, temperature measurement, in degrees Celsius

        kNoUnits,      ///< 0x05, measurement without units
        kUnknown       ///< 0x06, something unknown
    } Type_t;

    /**
     *
     */
    typedef struct __attribute__((packed)) Info
    { 
        /// 
        Type_t   type;
        /// 
        uint32_t value;
        ///
        bool     isFloat;
    } Info_t;
};

#endif // #ifndef __LOGIC_MOTOR_MEASURED_DATA_HPP