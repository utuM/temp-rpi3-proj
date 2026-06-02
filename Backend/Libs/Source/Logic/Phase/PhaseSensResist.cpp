#include "PhaseSensResist.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseSensResist::setup(void *)
{
    /**
     * TODO: make an initialization before starting to drive sensor resistance
     *       measurement.
     */
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseSensResist::run(void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @param  
 * @return 
 */
ResultCode::Index_t PhaseSensResist::stop(void *)
{
    return ResultCode::Index::kNoError;
}