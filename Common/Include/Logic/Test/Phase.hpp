#ifndef __LOGIC_TEST_PHASE_HPP
#define __LOGIC_TEST_PHASE_HPP

#include <cstdint>
#include <string>
#include "ResultCode.hpp"
#include "State.hpp"

class Phase
{
    /// The amount of steps are applicable for the current testing phase.
    const uint8_t mkStepsAmt;

protected:
    virtual ResultCode::Index_t setup(void *) = 0;
    virtual ResultCode::Index_t run(void *)   = 0;
    virtual ResultCode::Index_t stop(void *)  = 0;

public:
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
     * @param type  
     * @param stepsAmt 
     */
    Phase(Index_t type, const uint8_t stepsAmt) :
            mkStepsAmt(stepsAmt),
            mType(type),
            mState(State::Index::kIdle),
            mStep(0u)
    {
        switch (type) {
        case kPhaseResist:
            mDescription = "Motor Phase Resistance Measurement";
            break;
            
        case kSensorResist:
            mDescription = "Sensor Resistance Measurement";
            break;
            
        case kMotorLeak:
            mDescription = "Motor Leakage Current Measurement";
            break;

        case kSensorLeak:
            mDescription = "Sensor Leakage Current Measurement";
            break;

        default:
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
            return ResultCode::Index::kErrPhaseIsCompleted;
        }
        // Run the internal phase instance processing code for a result.
        ResultCode::Index_t ret = run(pData);
        if (ret == ResultCode::Index::kNoError) {
            ++mStep;
        }
        return ret;
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
        return mkStepsAmt;
    }

    /**
     * @brief  
     * @return 
     */
    inline bool isCompleted(void) const
    {
        return (mStep >= mkStepsAmt);
    }
};

#endif // __LOGIC_TEST_PHASE_HPP