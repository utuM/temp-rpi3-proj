#ifndef __NETWORK_PACKET_COMMAND_HPP
#define __NETWORK_PACKET_COMMAND_HPP

class Command
{
public:
    /**
     * 
     */
    typedef enum Info : uint8_t
    {
        kHandshake = 0x00, ///< 0x00, 
        kConfig,           ///< 0x01, 
        kSelect,           ///< 0x02, 
        kStart,            ///< 0x03, 
        kStatus,           ///< 0x04, 
        kMeasure,          ///< 0x05, 
        kPause,            ///< 0x06, 
        kStop,             ///< 0x07, 
        kRestart,          ///< 0x08, 
        kAmt,              ///< 0x09,
        kInvalid   = 0xFF
    } Info_t;

    /**
     * @brief 
     * @param  kIdx 
     * @return 
     */
    static inline Info_t IdxToCmd(const uint8_t kIdx)
    {
        if (kIdx > CmdToIdx(kAmt)) {
            return static_cast<Info_t>(kInvalid);
        }
        return static_cast<Info_t>(kIdx);
    }

    /**
     * @brief 
     * @param  kCmd 
     * @return 
     */
    static inline uint8_t CmdToIdx(const Info_t kCmd)
    {
        return static_cast<uint8_t>(kCmd);
    }
};

#endif // #ifndef __NETWORK_PACKET_COMMAND_HPP