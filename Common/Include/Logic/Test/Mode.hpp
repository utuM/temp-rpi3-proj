#ifndef __LOGIC_TEST_MODE_HPP
#define __LOGIC_TEST_MODE_HPP

#include <cstdint>

class Mode
{
public:
    /**
     *
     */
    typedef enum Index : uint8_t
    {
        kAuto       = 0x00, ///< 0x00, automatic mode with default order
        kAutoCustom,        ///< 0x01, automatic mode with custom order
        kSemiManual,        ///< 0x02, semi-manual mode to select mode-by-mode
        kManual             ///< 0x03, manual mode to apply every step
    } Index_t;  
};

#endif // #ifndef __LOGIC_TEST_MODE_HPP