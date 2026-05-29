#ifndef __TOOLS_UNITS_CONVERTER_HPP
#define __TOOLS_UNITS_CONVERTER_HPP

#include <unistd.h>

class UnitsConverter
{
    class Time
    {
    public:
        /**
         * @brief  
         * @param  min 
         * @return 
         */
        static inline uint32_t Min2Sec(uint32_t min)
        {
            return (min * 60ul);
        }

        /**
         * @brief 
         * @param  min 
         * @return 
         */
        static inline uint32_t Min2Ms(uint32_t min)
        {
            return (min * 60000ul);
        }

        /**
         * @brief 
         * @param  min 
         * @return 
         */
        static inline uint64_t Min2Us(uint32_t min)
        {
            return (min * 60000000ull);
        }

        /**
         * @brief  
         * @param  sec 
         * @return 
         */
        static inline uint32_t Sec2Ms(uint32_t sec)
        {
            return (sec * 1000ul);
        }

        /**
         * @brief  
         * @param  sec 
         * @return 
         */
        static inline uint64_t Sec2Us(uint32_t sec)
        {
            return (sec * 1000000ul);
        }

        /**
         * @brief  
         * @param  ms 
         * @return 
         */
        static inline uint32_t Ms2Us(uint32_t ms)
        {
            return (ms * 1000ul);
        }
    };
};

#endif // #ifndef __TOOLS_UNITS_CONVERTER_HPP