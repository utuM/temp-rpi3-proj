#ifndef __LOGIC_TEST_STATE_HPP
#define __LOGIC_TEST_STATE_HPP

#include <cstdint>

class State
{
public:
    /**
     *
     */
    typedef enum Index : uint8_t
    {
        kIdle     = 0x00, ///< 0x00, application is waiting for commands
        kStarting,        ///< 0x01, application starting the test sequence
        kRunning,         ///< 0x02, application is running tests
        kPaused,          ///< 0x03, application has been paused temporarily
        kStopping,        ///< 0x04, application is stopping every processing
        kFinishing        ///< 0x05, application has completed tests and
                          ///<       finishing processing
    } Index_t;
};

#endif // #ifndef __LOGIC_TEST_STATE_HPP