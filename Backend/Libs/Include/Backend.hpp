#ifndef __BACKEND_HPP
#define __BACKEND_HPP

#include <thread>
#include "Socket.hpp"
#include "UnitsConverter.hpp"

class Backend
{
private:
    /// 
    static constexpr const char *skSocketPath = "/tmp/motortester.sock";

    /// 
    static const uint32_t skProcessDelayMs = 10ul;
    ///
    static const uint32_t skPollPeriodMs   = 50ul;

    /// 
    volatile bool mNeedForceStop;

    /// 
    Socket mCommSock;

public:
    Backend(void);
    ~Backend(void);

    int  start(void);
    void stop(void);
};

#endif // #ifndef __BACKEND_HPP