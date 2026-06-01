#ifndef __LOGIC_TEST_PHASE_HPP
#define __LOGIC_TEST_PHASE_HPP

#include <cstdint>
#include "ResultCode.hpp"

class Phase
{ 
protected:
    virtual ResultCode::Index_t configure(void *) = 0;

public:
    ///
    static const uint8_t skPhaseMotorResistStepsAmt = 8u;
    ///
    static const uint8_t skPhaseSensResistStepsAmt  = 10u;
    ///
    static const uint8_t skPhaseMotorLeakStepsAmt   = 12u;
    ///
    static const uint8_t skPhaseSensLeakStepsAmt    = 10u;

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

    virtual ResultCode::Index_t run(void)     = 0;
    virtual ResultCode::Index_t stop(void)    = 0;

    /**
     * @brief 
     */
    virtual ~Phase(void)
    {}

    /**
     * @brief 
     * @param kType 
     */
    Phase(Index_t kType) :
            mType(kType),
            mStep(0u),
            mStepsAmt(0u)
    {
        switch (kType) {
        case kPhaseResist:
            mStepsAmt = skPhaseMotorResistStepsAmt;
            break;
            
        case kSensorResist:
            mStepsAmt = skPhaseSensResistStepsAmt;
            break;
            
        case kMotorLeak:
            mStepsAmt = skPhaseMotorLeakStepsAmt;
            break;

        case kSensorLeak:
            mStepsAmt = skPhaseSensLeakStepsAmt;
            break;
        }
    }

    ResultCode::Index_t setup(void *pCfg)
    {
        // Reset the current step index for sure.
        mStep = 0u;
        // Call internal method for the setup of the testing phase.
        return configure(pCfg);  
    }

protected:
    /// Type of the testing phase this class is identified with.
    Index_t mType;

    /// Current testing step.
    uint8_t mStep;
    /// The amount of steps are applicable for the current testing phase.
    uint8_t mStepsAmt;

public:
    /**
     * @brief 
     * @param  idx 
     * @return 
     */
    static inline uint8_t Phase2StepsAmt(Index_t idx)
    {
        switch (idx) {
        case kPhaseResist:
            return skPhaseMotorResistStepsAmt;

        case kSensorResist:
            return skPhaseSensResistStepsAmt;

        case kMotorLeak:
            return skPhaseMotorLeakStepsAmt;

        default:
            return skPhaseSensLeakStepsAmt;
        }
        return 0u;
    }

    /**
     * @brief  
     * @return 
     */
    inline uint8_t getStepsAmt(void) const
    {
        return mStepsAmt;
    }
};

#endif // __LOGIC_TEST_PHASE_HPP