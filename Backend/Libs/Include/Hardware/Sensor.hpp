#ifndef __HARDWARE_SENSOR_HPP
#define __HARDWARE_SENSOR_HPP

#include <climits>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include "Node.hpp"
#include "ResultCode.hpp"

class Sensor : public Node
{
protected:
    ///
    static const uint8_t skBufRawSize = 24u;

    ///
    char mRaw[skBufRawSize];

public:
    /**
     * @brief 
     * @param 
     */
    Sensor(const char *kpPath) :
            Node(kpPath),
            mRaw{}
    {}

    /**
     * @brief 
     */
    virtual ~Sensor(void)
    {}

    /**
     * @brief  
     * @return 
     */
    virtual float readF(void)
    {
        return .0f;
    }

    virtual ResultCode::Index_t configure(const void *) = 0;

    virtual int32_t read(void) = 0;
};

#endif // #ifndef __HARDWARE_SENSOR_HPP