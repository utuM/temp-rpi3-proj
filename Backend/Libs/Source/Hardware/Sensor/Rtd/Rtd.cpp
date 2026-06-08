#include "Rtd.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param  kpOpts
 * @return 
 */
ResultCode::Index_t Rtd::configure(const void *kpOpts)
{
    return ResultCode::Index::kNoError;
}

/**
 * @brief  
 * @return Read temperature value, in milidegress Celsius.
 */
int32_t Rtd::read(void)
{
    // Try to open the related attribute to get the temperature value.
    if (openAttr("in_temp_input") != ResultCode::Index::kNoError) {
        return INT32_MIN;
    }
    // Read the temperature value in milidesgrees Celsius.
    Node::read(mRaw, skBufRawSize - 1);
    close();
    // Convert and return the value.
    return static_cast<int32_t>(strtol(mRaw, nullptr, 10));
}