#ifndef __LOGIC_TEST_PHASE_HPP
#define __LOGIC_TEST_PHASE_HPP

#include <cstdint>

class Phase
{ 
public:
    ///
    static const uint8_t skPhase1MaxStep = 8u;
    ///
    static const uint8_t skPhase2MaxStep = 10u;
    ///
    static const uint8_t skPhase3MaxStep = 12u;
    ///
    static const uint8_t skPhase4MaxStep = 10u;

    /**
     *
     */
    typedef enum Index : uint8_t
    {
        kPhaseResist  = 0x00, ///< 0x00, Phase resistance measurement
        kSensorResist,        ///< 0x01, Sensor resistance meaurement
        kMotorLeak,           ///< 0x02, Motor leakage current measurement
        kSensorLeak           ///< 0x03, Sensor leakage current measurement
    } Index_t;

    virtual int setup(void *) = 0;
    virtual int run(void)   = 0;
    virtual int stop(void)  = 0;

    /**
     * @brief 
     * @param kIndex
     */
    Phase(Index_t kIndex) :
            mIndex(kIndex)
    {}

    /**
     * @brief 
     */
    virtual ~Phase(void)
    {}

protected:
    Index_t mIndex;
};

#endif // __LOGIC_TEST_PHASE_HPP