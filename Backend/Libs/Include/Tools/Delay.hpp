#ifndef __TOOLS_DELAY_HPP
#define __TOOLS_DELAY_HPP

#include <unistd.h>

class Delay
{
public: 
    /**
     * @brief
     * @param kMs 
     */
    static inline void S(const uint32_t kS)
    {
        usleep(kS * 1000000ull);
    }

    /**
     * @brief
     * @param kMs 
     */
    static inline void Ms(const uint32_t kMs)
    {
        usleep(kMs * 1000ull);
    }

    /**
     * @brief
     * @param kUs 
     */
    static inline void Us(const uint64_t kUs)
    {
        usleep(kUs);
    }
};

#endif // #ifndef __TOOLS_DELAY_HPP