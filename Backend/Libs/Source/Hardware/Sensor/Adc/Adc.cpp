#include <climits>
#include <cstdlib>
#include <cstring>
#include "Adc.hpp"

constexpr const char *Adc::skRanges[];
constexpr const char *Adc::skAttrs[];

/* ************************************************************************* */

/**
 * @brief 
 * @param  kpOpts 
 * @return 
 */
ResultCode::Index_t Adc::configure(const void *kpOpts)
{
    if (!kpOpts) {
        return ResultCode::Index::kErrCommonNullPtr;
    }
    mConfig = *static_cast<const Config_t *>(kpOpts);
    // Setup the PGA range scale using the IIO attribute.
    if (openAttr(skRangeAttr) != ResultCode::Index::kNoError) {
        return ResultCode::Index::kErrNodeOpenAttrFailed;
    }
    const char *kpScale = skRanges[mConfig.range];
    ResultCode::Index_t ret = write(kpScale, strlen(kpScale));
    close();
    return ret;
}

/**
 * @brief  
 * @return 
 */
int32_t Adc::read(void)
{
    // Read raw ADC count for the configured input.
    const char *kpAttr = skAttrs[mConfig.input];
    if (openAttr(kpAttr) != ResultCode::Index::kNoError) {
        return INT32_MIN;
    }
    Node::read(mBufRaw, skBufRawSize - 1);
    close();
    // Read current scale factor, to calculate the measured voltage, in
    // milivots.
    if (openAttr(skRangeAttr) != ResultCode::Index::kNoError) {
        return INT32_MIN;
    }
    Node::read(mBufScale, skBufScaleSize - 1);
    close();
    // Make a calculation based on the read measurement and scale factor.
    const int32_t raw = static_cast<int32_t>(strtol(mBufRaw, nullptr, 10));
    const float scale = strtof(mBufScale, nullptr);

    return static_cast<int32_t>(static_cast<float>(raw) * scale);
}