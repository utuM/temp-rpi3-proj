#ifndef __HARDWARE_SENSOR_HPP
#define __HARDWARE_SENSOR_HPP

#include <cstdint>
#include "Node.hpp"
#include "ResultCode.hpp"

class Sensor : public Node
{
public:
    /**
     * @brief 
     * @param 
     */
    Sensor(const char *kpPath) :
            Node(kpPath)
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