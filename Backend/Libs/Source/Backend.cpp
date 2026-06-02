#include "Backend.hpp"
#include "Delay.hpp"
#include "ExitCode.hpp"
#include "Socket.hpp"
#include "UnitsConverter.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param krPacket 
 */
void Backend::_processCommand(const Packet::Info_t &krPacket)
{
    const uint8_t *pPayload = Packet::GetPayload(krPacket);

    switch (krPacket.head.cmd) {
    case Command::Info::kHandshake:
        // Synchronize the application timestamp with the Frontend.
        if (pPayload) {
            const Payload::Handshake_t *kpHsPack =
                    reinterpret_cast<const Payload::Handshake_t *>(pPayload);
            SysTick::UpdateOffset(kpHsPack->tstampMs);
        }
        // 
        break;

    case Command::Info::kConfig:
        
        break;

    case Command::Info::kSelect:
        
        break;

    case Command::Info::kControl:
        
        break;

    case Command::Info::kStatus:
        
        break;

    case Command::Info::kMeasure:
        
        break;

    default:
        break;
    }
}

/**
 * @brief 
 * @param cmd 
 * @param kpData
 * @param len 
 */
void Backend::_processResponse(Command::Info_t cmd, const void *kpData,
        uint8_t len)
{
    Packet::Info_t response = Packet::Build(cmd,
            reinterpret_cast<const uint8_t *>(kpData), len);
    mSocket.transmit(reinterpret_cast<void *>(&response), Packet::skFullSize);
}

/* ************************************************************************* */

/**
 * @brief 
 */
Backend::Backend(void) :
        mNeedForceStop(false),
        mSocket(skSocketPath)
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
    ret = mSocket.init();
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
        int inEvtAmt = mSocket.wait(skPollPeriodMs);
        if (inEvtAmt > 0) { ///< got something, process...
            // Process received amount of commands.
            for (int i = 0; i < inEvtAmt; i ++) {
                if (mSocket.need2Accept()) { ///< check if need socket
                    mSocket.connect();
                } else {                       ///< incoming data/command
                    int rxRet = mSocket.receive(i, pData, sizeof(pkt));
                    if (rxRet < 0) {
                        mSocket.disconnect();
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
    return ((mSocket.uninit() == ResultCode::Index::kNoError) ?
            ExitCode::skNoError : ExitCode::skErrCannotStopSocket);
}

/**
 * @brief 
 */
void Backend::stop(void)
{
    mNeedForceStop = true;
}