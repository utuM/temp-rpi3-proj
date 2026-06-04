#include "Adc.hpp"

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
    const Config_t *kpCfg = reinterpret_cast<const Config_t *>(kpOpts);
    mConfig = *kpCfg;
    // TODO: run configuring here.
    return ResultCode::Index::kNoError;
}

/**
 * @brief  
 * @return 
 */
int32_t Adc::read(void)
{
    return 0;
}