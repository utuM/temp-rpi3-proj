#ifndef __TOOLS_UNITS_CHECKSUM_HPP
#define __TOOLS_UNITS_CHECKSUM_HPP

#include <cstdint>

class Checksum
{
public:
    /**
     * @brief  
     * @param  kpData 
     * @param  kLength 
     * @return 
     */
    static uint8_t Calculate(const uint8_t *kpData, const uint8_t kLength)
    {
        uint8_t cs = 0u;
        for (uint8_t i = 0u; i < kLength; i ++) {
            cs ^= kpData[i];
        }
        return cs;
    }

    /**
     * @brief  
     * @param  kpData
     * @param  kLength
     * @param  kOrigin
     * @return 
     */
    static inline bool Validate(const uint8_t *kpData, const uint8_t kLength,
            const uint8_t kOrigin)
    {
        return (Calculate(kpData, kLength) == kOrigin);
    }
};

#endif // #ifndef __TOOLS_UNITS_CHECKSUM_HPP