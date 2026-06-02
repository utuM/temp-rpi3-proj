#ifndef __LOGIC_TEST_PHASE_HPP
#define __LOGIC_TEST_PHASE_HPP

#include <cstdint>
#include <string>
#include "ResultCode.hpp"
#include "State.hpp"

class Phase
{ 
protected:
    virtual ResultCode::Index_t setup(void *) = 0;
    virtual ResultCode::Index_t run(void *)   = 0;
    virtual ResultCode::Index_t stop(void *)  = 0;

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
        kSensorLeak,          ///< 0x03, Sensor leakage current measurement
        kAmt
    } Index_t;

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
            mState(State::Index::kIdle),
            mStep(0u),
            mStepsAmt(0u)
    {
        switch (kType) {
        case kPhaseResist:
            mStepsAmt    = skPhaseMotorResistStepsAmt;
            mDescription = "Motor Phase Resistance Measurement";
            break;
            
        case kSensorResist:
            mStepsAmt    = skPhaseSensResistStepsAmt;
            mDescription = "Sensor Resistance Measurement";
            break;
            
        case kMotorLeak:
            mStepsAmt    = skPhaseMotorLeakStepsAmt;
            mDescription = "Motor Leakage Current Measurement";
            break;

        case kSensorLeak:
            mStepsAmt    = skPhaseSensLeakStepsAmt;
            mDescription = "Sensor Leakage Current Measurement";
            break;

        default:
            mStepsAmt = 0;
            mDescription = "Unknown Phase";
            break;
        }
    }

    /**
     * @brief 
     * @param  pConfig 
     * @return  
     */
    ResultCode::Index_t configure(void *pConfig = nullptr)
    {
        // Reset the current step index for sure.
        mStep = 0u;
        // Call internal method for the setup of the testing phase.
        return setup(pConfig);
    }

    /**
     * @brief 
     * @param  pData 
     * @return  
     */
    ResultCode::Index_t process(void *pData = nullptr)
    {
        // Stop to running the phase if the current step index is reached the
        // total amount of steps.
        if (isCompleted()) {
            return ResultCode::Index::kNoError;
        }
        
        return ResultCode::Index::kNoError;
    }

    /**
     * @brief 
     * @param  pData 
     * @return  
     */
    ResultCode::Index finish(void *pData = nullptr)
    {
        return ResultCode::Index::kNoError;
    }

protected:
    /// Type of the testing phase this class is identified with.
    Index_t mType;

    /// Description of the testing phase, might be used for debugging and
    /// other purposes.
    std::string mDescription;

    /// Current processing state index.
    State::Index_t mState;

    /// Current testing step.
    uint8_t mStep;
    /// The amount of steps are applicable for the current testing phase.
    uint8_t mStepsAmt;

public:
    /// Amount of possible/available testing phases for usage.
    static const uint8_t skTotalAmt = kAmt;

    /**
     * @brief Converts a phase index to a phase type.
     * @param idx The index of the phase.
     * @return The phase type corresponding to the index.
     */
    static inline Index_t Idx2Phase(uint8_t idx)
    {
        return ((idx <= skTotalAmt) ? static_cast<Index_t>(idx) : kAmt);
    }

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
    inline const char * getDescription(void) const
    {
        return mDescription.c_str();
    }

    /**
     * @brief 
     * @return 
     */
    inline uint8_t getStep(void) const
    {
        return mStep;
    }

    /**
     * @brief  
     * @return 
     */
    inline uint8_t getStepsAmt(void) const
    {
        return mStepsAmt;
    }

    /**
     * @brief  
     * @return 
     */
    inline bool isCompleted(void) const
    {
        return (mStep >= mStepsAmt);
    }
};

#endif // __LOGIC_TEST_PHASE_HPP