#include "Temperature.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Temperature::configure(const void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
float Temperature::readF(void)
{
    return .0f;
}

/**
 * @brief 
 * @return 
 */
int32_t Temperature::read(void)
{
    return 0;
}