#include "Voltage.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Voltage::configure(const void *)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief 
 * @return 
 */
float Voltage::readF(void)
{
    return .0f;
}

/**
 * @brief 
 * @return 
 */
int32_t Voltage::read(void)
{
    return 0;
}