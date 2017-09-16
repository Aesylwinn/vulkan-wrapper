#include "vw/queue.h"

namespace vw
{
    Queue::Queue(uint32_t family, uint32_t index, VkQueue handle)
        : mFamily(family)
        , mIndex(index)
        , mHandle(handle)
    {
    }

    Queue::operator bool()
    {
        return mHandle != VK_NULL_HANDLE;
    }

    uint32_t Queue::getFamilyIndex() const
    {
        return mFamily;
    }

    uint32_t Queue::getQueueIndex() const
    {
        return mIndex;
    }

    VkQueue Queue::getHandle()
    {
        return mHandle;
    }
}
