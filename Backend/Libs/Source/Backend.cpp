#include "Backend.hpp"
#include "Delay.hpp"
#include "ExitCode.hpp"
#include "PhaseManager.hpp"
#include "Socket.hpp"

/* ************************************************************************* */

/**
 * @brief 
 * @param krPacket 
 */
void Backend::_processCommand(const Packet::Info_t &krPacket)
{
    const uint8_t *kpPayload = Packet::GetPayload(krPacket);

    switch (krPacket.head.cmd) {
    case Command::Info::kHandshake: {
        // Synchronize the application timestamp with the Frontend.
        if (kpPayload) {
            const Payload::Handshake_t *kpHsPack =
                    reinterpret_cast<const Payload::Handshake_t *>(kpPayload);
            SysTick::UpdateOffset(kpHsPack->tstampMs);
        }
        // Send a response back.
        Packet::Info_t info = Packet::BuildHandshake();
        void *pData = reinterpret_cast<void *>(&info);
        mSocket.transmit(pData, Packet::skFullSize);
    } break;

    case Command::Info::kConfig: {
        if (kpPayload) {
            const Payload::Config_t *kpConfig =
                    reinterpret_cast<const Payload::Config_t *>(kpPayload);
            PhaseManager::Configure(kpConfig->config);
        }
    } break;

    case Command::Info::kSelect: {
        if (kpPayload) {
            const Payload::Select_t *kpSelect =
                    reinterpret_cast<const Payload::Select_t *>(kpPayload);
            PhaseManager::Select(kpSelect->phase); 
        }
    } break;

    case Command::Info::kControl: {
        if (kpPayload) {
            const Payload::Control_t *kpCtrl =
                    reinterpret_cast<const Payload::Control_t *>(kpPayload);
            PhaseManager::Control(kpCtrl->act);        
        }
    } break;

    case Command::Info::kStatus: {
        Packet::Info_t info = Packet::BuildStatus(PhaseManager::GetStatus());
        void *pData = reinterpret_cast<void *>(&info);
        mSocket.transmit(pData, Packet::skFullSize);
    } break;

    case Command::Info::kMeasure:
        // TODO: 
        break;

    default:
        break;
    }
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
        PhaseManager::Tick();
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
                            _processCommand(pkt);
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