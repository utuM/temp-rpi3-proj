#ifndef __TOOLS_SYS_TICK_HPP
#define __TOOLS_SYS_TICK_HPP

#include <cstdint>
#include <ctime>

class SysTick
{
private:
    /// 
    static uint32_t sOffsetMs;

public:
    /**
     * @brief  
     * @return 
     */
    static inline uint32_t TicksMs(void)
    {
        return (TicksOsMs() - sOffsetMs);
    }

#ifdef MOTOR_FRONTEND

    /**
     * @brief 
     */
    static inline void UpdateOffset(void)
    {
        sOffsetMs = TicksOsMs();
    }

#else

    /**
     * @brief 
     * @param kTicksMs 
     */
    static inline void UpdateOffset(const uint32_t kTicksMs)
    {
        sOffsetMs = kTicksMs;
    }

#endif // #ifdef MOTOR_FRONTEND

    /**
     * @brief 
     * @return 
     */
    static uint32_t TicksOsMs(void)
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return static_cast<uint32_t>((ts.tv_sec * 1000ull) +
                (ts.tv_nsec / 1000000ull));
    } 
};

#endif // #ifndef __TOOLS_SYS_TICK_HPP