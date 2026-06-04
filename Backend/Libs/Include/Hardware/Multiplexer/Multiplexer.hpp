#ifndef __HARDWARE_MULTIPLEXER_TMUX1209_HPP
#define __HARDWARE_MULTIPLEXER_TMUX1209_HPP

#include "Gpio.hpp"
#include "ResultCode.hpp"

class Multiplexer
{
public:
    typedef enum Config : uint8_t
    {
        kMuxConfig0    = 0x00, ///< 0x00, EN = 1, A1 = 0, A0 = 0
        kMuxConfig1,           ///< 0x01, EN = 1, A1 = 0, A0 = 1
        kMuxConfig2,           ///< 0x02, EN = 1, A1 = 1, A0 = 0
        kMuxConfig3,           ///< 0x03, EN = 1, A1 = 1, A0 = 1
        kMuxOff = 0xFF,        ///< 0xFF, EN = 0
    } Config_t;

    ResultCode::Index_t select(const Config_t,
            const bool kNeedIgnoreValid = false);

private:
    ///
    static constexpr const char *skPath =
            "/sys/devices/platform/mtester-gpios/gpios/";

    /**
     * @brief  
     * @param  kIdx 
     * @return 
     */
    inline bool _configValidate(const uint8_t kIdx)
    {
        return ((kIdx == kMuxOff) || (kIdx <= kMuxConfig3));
    }

public:
    /// 
    Gpio mPinEn;
    ///
    Gpio mPinA1;
    ///
    Gpio mPinA0;

    /**
     * @brief 
     */
    Multiplexer(void) :
            mPinEn(skPath),
            mPinA1(skPath),
            mPinA0(skPath)
    {}

    /**
     * @brief 
     */
    ~Multiplexer(void)
    {
        mPinEn.close();
        mPinA1.close();
        mPinA0.close();
    }

    /**
     * @brief 
     * @param  kIdx 
     * @return 
     */
    inline ResultCode::Index_t select(const uint8_t kIdx)
    {
        // Validate the input unsigned decimal number if that one is applicable.
        if (!_configValidate(kIdx)) {
            return ResultCode::Index::kErrCommonInvArg;
        }
        // Continue with changing the commutation.
        return select(static_cast<Config_t>(kIdx));
    }

private:
    /**
     * @brief 
     * @param kShouldIgnore
     */
    inline void _muxEnableIfNot(const bool kShouldIgnore)
    {
        if (!kShouldIgnore && !mPinEn.get()) {
            mPinEn.set();
        }
    }
};

#endif // #ifndef __HARDWARE_MULTIPLEXER_TMUX1209_HPP