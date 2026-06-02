#ifndef __NETWORK_PACKET_PACKET_HPP
#define __NETWORK_PACKET_PACKET_HPP

#include <cstdint>
#include "Command.hpp"
#include "Checksum.hpp"
#include "Payload.hpp"
#include "SysTick.hpp"

class Packet
{
private:
    ///
    static constexpr const uint8_t skMagic[] =
    {
        0xBE, 0xAF
    };

    ///
    static const uint8_t skMagicSize = sizeof(skMagic);

    ///
    static const uint8_t skPayloadSize = 40u;

    /* ******************************************************************* */

public:
    /// 
    static const uint8_t skVersion = 1u;

    /**
     *
     */
    typedef enum Source : uint8_t 
    {
        kFEnd = 0x00, ///< 0x00, package from the Frontend (request)
        kBEnd         ///< 0x01, package from the Backend (response)
    } Src_t;

    /**
     * 
     */
    typedef struct __attribute__((packed)) Header
    {
        /// Magic for a header.
        uint8_t         magic[skMagicSize];
        /// Transmitting source.
        Src_t           src;
        /// Target command should be transmitted and processed.
        Command::Info_t cmd;
        /// Package timestamp (application time).
        uint32_t        tstamp;
        /// Length of the payload.
        uint8_t         len;
    } Header_t;

    /**
     * 
     */
    typedef struct __attribute__((packed)) Info
    {
        /// Package header.
        Header_t head;
        /// Data payload.
        uint8_t  data[skPayloadSize];
        /// Package checksum.
        uint8_t  csum;
    } Info_t;

    static Info_t Build(const Command::Info_t, const uint8_t *, const uint8_t);
    static bool   Unpack(const uint8_t *, const uint8_t, Info_t &);

    static bool   Validate(const Info_t &);

private:
    /// 
    static const uint8_t skHeaderSize = sizeof(Header_t);

    ///
    static const uint8_t skPackSize = sizeof(Info_t);

    /**
     * @brief 
     * @param  krPack 
     * @return 
     */
    static inline uint8_t _CalculateChksum(const Info_t &krPack)
    {
        const uint8_t *pRaw = reinterpret_cast<const uint8_t *>(&krPack);
        const uint8_t len   = skHeaderSize + krPack.head.len;
        return (Checksum::Calculate(pRaw, len));
    }

    /**
     * @brief 
     * @param  krPack 
     * @return 
     */
    static inline bool _ValidateChksum(const Info_t &krPack)
    {
        const uint8_t *pRaw = reinterpret_cast<const uint8_t *>(&krPack);
        const uint8_t len   = skHeaderSize + krPack.head.len;
        return (Checksum::Validate(pRaw, len, krPack.csum));
    }

    /* ******************************************************************* */

public:
    ///
    static const uint8_t skFullSize = sizeof(Info_t);
 
    /**
     * @brief  
     * @return 
     */
    static inline Info_t BuildHandshake(void)
    {
        Payload::Handshake_t payload { skVersion, SysTick::TicksMs(), 0u };
        return Build(Command::Info::kHandshake, 
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetHandshakeSize());
    }

    /**
     * @brief  
     * @param  krOpts 
     * @return 
     */
    static inline Info_t BuildConfig(const Test::Option_t &krOpts)
    {
        Payload::Config_t payload { krOpts };
        return Build(Command::Info::kConfig,
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetConfigSize());
    }

    /**
     * @brief 
     * @param  phase   
     * @return 
     */
    static inline Info_t BuildSelect(Phase::Index_t phase)
    {
        Payload::Select_t payload { phase };
        return Build(Command::Info::kSelect,
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetSelectSize());
    }

    /**
     * @brief 
     * @param  act  
     * @return 
     */
    static inline Info_t BuildControl(Action::Index_t act)
    {
        Payload::Control_t payload { act };
        return Build(Command::Info::kControl,
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetControlSize());
    }

    /**
     * @brief 
     * @param  krStatus 
     * @return 
     */
    static inline Info_t BuildStatus(const Status::Info_t &krStatus)
    {
        Payload::Status_t payload { krStatus };
        return Build(Command::Info::kStatus,
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetStatusSize());
    }

    /**
     * @brief 
     * @param  pkValues 
     * @param  amt 
     * @return 
     */
    static inline Info_t BuildMeasure(const Measurement::Info_t *pkValues,
            uint8_t amt)
    {
        Payload::Measure_t payload { };
        uint8_t size = ((amt > Measurement::skArraySize) ?
                Measurement::skArraySize : amt);
        for (uint8_t i = 0; i < size; i ++) {
            payload.value[i] = pkValues[i];
        }
        return Build(Command::Info::kMeasure,
                reinterpret_cast<const uint8_t *>(&payload),
                Payload::GetMeasureSize());
    }

    /**
     * @brief  
     * @param  rPack 
     * @return 
     */
    static inline const uint8_t * GetPayload(const Info_t &rPack)
    {
        return (rPack.head.len ? rPack.data : nullptr);
    }
};

#endif // #ifndef __NETWORK_PACKET_PACKET_HPP