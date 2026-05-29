#ifndef __LOGIC_TEST_TEST_HPP
#define __LOGIC_TEST_TEST_HPP

#include "Mode.hpp"
#include "Phase.hpp"

class Test
{
public:
    /**
     *
     */
    typedef struct __attribute__((packed)) Option
    {
        /// Mode setting.
        Mode_t         mode;
        /// Phases order.
        Phase::Index_t order[skMaxOrderSize];

        /// Conditional check: pump tested on test bench?
        bool hasTestedOnBench;
        /// Conditional check: is optical sensor present?
        bool hasOpticalSensor;
        /// Conditional check: is pressure port in end cap present?
        bool hasPressureCap;

        /// Loop setting: define the test duration all the steps should be done
        /// within.
        uint32_t loopDurMs;
        /// Loop setting: amount of test sequences might to be done.
        uint32_t loopAmt;
    } Option_t;

private:
    /// 
    static constexpr const uint8_t skDfltOrder[] = { kPhaseResist,
            kSensorResist, kMotorLeak, kSensorLeak };

    /// 
    static const uint8_t skMaxOrderSize = sizeof(skDfltOrder);
};

#endif // #ifndef __LOGIC_TEST_TEST_HPP