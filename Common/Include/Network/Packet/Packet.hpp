#ifndef __NETWORK_PACKET_PACKET_HPP
#define __NETWORK_PACKET_PACKET_HPP

#include <cstdint>
#include "Command.hpp"
#include "Checksum.hpp"

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

    /* ******************************************************************* */

private:
    /// 
    static const uint8_t skHeaderSize = sizeof(Header_t);

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
    /**
     * @brief  
     * @param  rPack 
     * @return 
     */
    static inline const uint8_t * GetPayload(const Info_t &rPack)
    {
        return (rPack.head.len ? rPack.data : nullptr);
    }

    static Info_t Build(const Command::Info_t, const uint8_t *, const uint8_t);
    static bool   Unpack(const uint8_t *, const uint8_t, Info_t &);

    static bool   Validate(const Info_t &);

};

#endif // #ifndef __NETWORK_PACKET_PACKET_HPP