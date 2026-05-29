#include "Backend.hpp"
#include "Command.hpp"
#include "Delay.hpp"
#include "ExitCode.hpp"
#include "Packet.hpp"
#include "Socket.hpp"

/* ************************************************************************* */

/**
 * @brief 
 */
Backend::Backend(void) :
        mNeedForceStop(false),
        mCommSock(skSocketPath)
{
}

/**
 * @brief 
 */
Backend::~Backend(void)
{
}

/**
 * @brief  
 * @return 
 */
int Backend::start(void)
{
    Packet::Info_t pkt;
    ResultCode::Index_t ret;
    uint8_t *pData = reinterpret_cast<uint8_t *>(&pkt);

    // Initialize the UNIX-socket to start incoming events processing from the
    // frontend side.
    ret = mCommSock.init();
    if (ret != ResultCode::Index::kNoError) {
        return ExitCode::skErrCannotStartSocket;
    }
    // Run the events processing to react on command and do measurements with
    // calculations on the received values.
    while (!mNeedForceStop) {
        // Run the sensors data measurements and calculations.
        /**
          TODO: place a code to get measured values from sensors, do calculations.
         */
        // Wait for the incoming amount of events/commands should be processed.
        int inEvtAmt = mCommSock.wait(skPollPeriodMs);
        if (inEvtAmt > 0) { ///< got something, process...
            // Process received amount of commands.
            for (int i = 0; i < inEvtAmt; i ++) {
                if (mCommSock.need2Accept()) { ///< check if need socket
                    mCommSock.connect();
                } else {                       ///< incoming data/command
                    int rxRet = mCommSock.receive(i, pData, sizeof(pkt));
                    if (rxRet < 0) {
                        mCommSock.disconnect();
                    } else {
                        if (Packet::Validate(pkt)) {
                            /**
                              TODO: place a code to process incoming commands
                             */
                        }
                    }
                }
            }
        } else {            ///< cooldown
            Delay::Ms(skProcessDelayMs);
        }
    }
    
    // Stop the communication with frontend, return different result based on
    // the socket disabling result.
    return ((mCommSock.uninit() == ResultCode::Index::kNoError) ?
            ExitCode::skNoError : ExitCode::skErrCannotStopSocket);
}

/**
 * @brief 
 */
void Backend::stop(void)
{
    mNeedForceStop = true;
}