#include "Pressure.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Pressure::configure(const void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
float Pressure::readF(void)
{
    return .0f;
}

/**
 * @brief 
 * @return 
 */
int32_t Pressure::read(void)
{
    return 0;
}