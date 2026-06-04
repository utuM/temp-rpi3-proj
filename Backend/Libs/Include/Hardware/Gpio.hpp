#ifndef __HARDWARE_GPIO_HPP
#define __HARDWARE_GPIO_HPP

#include "Node.hpp"
#include "ResultCode.hpp"

class Gpio : public Node
{
private:
    /// 
    static constexpr const char *skHigh = "1";
    ///
    static constexpr const char *skLow  = "0";

    /**
     * @brief 
     * @param  kNeedHigh 
     * @return 
     */
    inline ResultCode::Index_t _update(bool kNeedHigh)
    {
        // Do not continue with processing if cannot open the file descriptor.
        ResultCode::Index_t ret = open();
        if (ret != ResultCode::Index::kNoError) {
            return ret;
        }
        // Change the level based on the required one.
        ret = write(kNeedHigh ? skHigh : skLow, 1);
        close();
        return ret;
    }

public:
    /**
     * @brief  
     * @param kpPath 
     */
    Gpio(const char *kpPath) :
            Node(kpPath)
    {}

    ResultCode::Index_t set(void);
    ResultCode::Index_t reset(void);

    bool get(void);
};

#endif // #ifndef __HARDWARE_GPIO_HPP