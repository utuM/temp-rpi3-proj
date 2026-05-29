#ifndef __LOGIC_TEST_ACTION_HPP
#define __LOGIC_TEST_ACTION_HPP

#include <cstdint>

class Action
{
public:
    typedef enum Index : uint8_t 
    {
        kStart    = 0x00, ///< 0x00, 
        kContinue,        ///< 0x01, 
        kPause,           ///< 0x02, 
        kStop,            ///< 0x03,
        kRestart          ///< 0x04,    
    } Index_t;
};

#endif // #ifndef __LOGIC_TEST_ACTION_HPP