#include "PhaseMotorResist.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorResist::setup(void *)
{
    /**
     * TODO: make an initialization before starting to drive motor phase
     *       resistance measurement.
     */
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorResist::run(void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseMotorResist::stop(void *)
{
    return ResultCode::Index::kNoError;
}