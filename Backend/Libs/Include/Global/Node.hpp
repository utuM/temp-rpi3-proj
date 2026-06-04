#ifndef __GLOBAL_NODE_HPP
#define __GLOBAL_NODE_HPP

#include <cstdint>
#include "ResultCode.hpp"

class Node
{
private:
    // 
    const char *mkPath;
    // 
    int        mFd;

public:
    ///
    static const int skInvalidFd = -1;

    /**
     * @brief 
     * @param kpPath
     */
    Node(const char *kpPath) :
            mkPath(kpPath),
            mFd(skInvalidFd)
    {}

    /**
     * @brief 
     */
    virtual ~Node(void)
    {
        close();
    }

    ResultCode::Index_t open(void);
    ResultCode::Index_t openAttr(const char *);

    void close(void);

protected:
    ResultCode::Index_t read(void *, uint32_t);
    ResultCode::Index_t write(const void *, uint32_t);
};

#endif // #ifndef __GLOBAL_NODE_HPP