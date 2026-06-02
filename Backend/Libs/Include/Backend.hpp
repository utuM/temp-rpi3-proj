#ifndef __BACKEND_HPP
#define __BACKEND_HPP

#include "Command.hpp"
#include "Packet.hpp"
#include "Socket.hpp"

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
    Socket mSocket;

    void _processCommand(const Packet::Info_t &);

public:
    Backend(void);
    ~Backend(void);

    int  start(void);
    void stop(void);
};

#endif // #ifndef __BACKEND_HPP