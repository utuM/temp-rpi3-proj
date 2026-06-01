#include <cstring>
#include "Packet.hpp"
#include "SysTick.hpp"

constexpr const uint8_t Packet::skMagic[];

/* ************************************************************************* */

/**
 * @brief  
 * @param  kCmd 
 * @param  kpData 
 * @param  kLen 
 * @return 
 */
Packet::Info_t Packet::Build(const Command::Info_t kCmd, const uint8_t *kpRaw,
        const uint8_t kLen)
{
    Packet::Info_t pack { 0 };

    // Fill the header.
    memcpy(pack.head.magic, skMagic, skMagicSize);
    pack.head.cmd    = kCmd;
    pack.head.tstamp = SysTick::TicksMs();
    pack.head.len    = (kLen > skPayloadSize) ? skPayloadSize : kLen;
    
#ifdef MOTOR_BACKEND
    pack.head.src    = kBEnd;
#else
    pack.head.src    = kFEnd;
#endif // #ifndef MOTOR_BACKEND    
    
    // Copy the input data inside the package.
    if (kpRaw && pack.head.len) {
        memcpy(pack.data, kpRaw, pack.head.len);
    }

    // Calculate the checksum value based on the filled package.
    pack.csum = _CalculateChksum(pack);

    return pack;
}

/**
 * @brief  
 * @param  kpRaw 
 * @param  kLen  
 * @param  rPack  
 * @return 
 */
bool Packet::Unpack(const uint8_t *kpRaw, const uint8_t kLen, Info_t &rPack)
{
    if (!kpRaw || (kLen < sizeof(Info_t))) {
        return false;
    }
    memcpy(&rPack, kpRaw, sizeof(Info_t));
    return Validate(rPack);
}

/**
 * @brief  
 * @param  krPack 
 * @return 
 */
bool Packet::Validate(const Info_t &krPack)
{
    // Check the 'magic' array.
    if (memcmp(krPack.head.magic, skMagic, skMagicSize)) {
        return false;
    }
    
#ifdef MOTOR_BACKEND
    // Check the source: Backend might to get a package from the Frontend.
    if (krPack.head.src != kFEnd) {
        return false;
    }
#else
    // Check the source: Frontend might to get a package from the Backend.
    if (krPack.head.src != kBEnd) {
        return false;
    }
#endif // #ifdef MOTOR_BACKEND

    // Check the command.
    if (krPack.head.cmd >= Command::Info::kAmt) {
        return false;
    }
    // Check the payload length.
    if (krPack.head.len > skPayloadSize) {
        return false;
    }

    // Check the checksum value.
    return _ValidateChksum(krPack);
}