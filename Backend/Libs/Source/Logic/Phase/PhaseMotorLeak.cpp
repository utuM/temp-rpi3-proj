#include "PhaseMotorLeak.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::setup(void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::run(void *)
{
    // Stoip
    if (isCompleted()) {
        return ResultCode::Index::kNoError;
    }
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorLeak::stop(void *)
{
    return ResultCode::Index::kNoError;
}