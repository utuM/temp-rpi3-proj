#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include "Node.hpp"

/* ************************************************************************* */

/**
 * @brief  
 * @param  pBuf 
 * @param  size 
 * @return 
 */
ResultCode::Index_t Node::read(void *pBuf, uint32_t size)
{
    return ((::read(mFd, pBuf, size) >= 0) ? ResultCode::Index::kNoError :
            ResultCode::Index::kErrNodeReadFailed);
}

/**
 * @brief  
 * @param  kpBuf 
 * @param  size 
 * @return 
 */
ResultCode::Index_t Node::write(const void *kpBuf, uint32_t size)
{
    return ((::write(mFd, kpBuf, size) >= 0) ? ResultCode::Index::kNoError :
            ResultCode::Index::kErrNodeWriteFailed);
}

/* ************************************************************************* */

/**
 * @brief 
 * @return 
 */
ResultCode::Index_t Node::open(void)
{
    mFd = ::open(mkPath, O_RDWR);
    return ((mFd != skInvalidFd) ? ResultCode::Index::kNoError :
            ResultCode::Index::kErrNodeOpenFailed);
}

/**
 * @brief 
 * @param  kpAttr 
 * @return 
 */
ResultCode::Index_t Node::openAttr(const char *kpAttr)
{
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", mkPath, kpAttr);
    mFd = ::open(path, O_RDWR);
    return ((mFd != skInvalidFd) ? ResultCode::Index::kNoError :
            ResultCode::Index::kErrNodeOpenAttrFailed);
}

/**
 * @brief 
 */
void Node::close(void)
{
    if (mFd != skInvalidFd) {
        ::close(mFd);
        mFd = skInvalidFd;
    }
}