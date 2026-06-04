#include "Gpio.hpp"

constexpr const char *Gpio::skHigh;
constexpr const char *Gpio::skLow;

/* ************************************************************************* */

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Gpio::set(void)
{
    return _update(true);
}

/**
 * @brief  
 * @return 
 */
ResultCode::Index_t Gpio::reset(void)
{
    return _update(false);
}

/**
 * @brief  
 * @return 
 */
bool Gpio::get(void)
{
    char buf[2] = {};
    // Do not continue with processing if cannot open the file descriptor.
    if (open() != ResultCode::Index::kNoError) {
        return false;
    }
    // Get the state and process the output.
    read(buf, sizeof(buf));
    close();
    return (buf[0] == '1');
}