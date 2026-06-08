#include "Gpio.hpp"

constexpr const char *Gpio::skHigh;
constexpr const char *Gpio::skLow;

/* ************************************************************************* */

/**
 * @brief  
 * @param  kpAttr 
 * @return 
 */
ResultCode::Index_t Gpio::set(const char *kpAttr)
{
    if (kpAttr && kpAttr[0]) {
        return _update(kpAttr, true);
    }
    return _update(true);
}

/**
 * @brief  
 * @param  kpAttr 
 * @return 
 */
ResultCode::Index_t Gpio::reset(const char *kpAttr)
{
    if (kpAttr && kpAttr[0]) {
        return _update(kpAttr, false);
    }
    return _update(false);
}

/**
 * @brief  
 * @param  kpAttr 
 * @return 
 */
bool Gpio::get(const char *kpAttr)
{
    char buf[2] = {};
    // Do not continue with processing if cannot open the file descriptor.
    if (kpAttr && kpAttr[0]) {
        if (openAttr(kpAttr) != ResultCode::Index::kNoError) {
            return false;
        }
    } else if (open() != ResultCode::Index::kNoError) {
        return false;
    }
    // Get the state and process the output.
    read(buf, sizeof(buf));
    close();
    return (buf[0] == '1');
}