#include "vw/queuefamily.h"

namespace vw
{
    QueueFamily::QueueFamily(size_t index, const VkQueueFamilyProperties& props)
        : mIndex(index)
        , mProperties(props)
    {
    }

    bool QueueFamily::hasGraphicsSupport() const
    {
        return mProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    }

    bool QueueFamily::hasComputeSupport() const
    {
        return mProperties.queueFlags & VK_QUEUE_COMPUTE_BIT;
    }

    bool QueueFamily::hasTransferSupport() const
    {
        // According to the spec, graphics and compute families are not required
        // to also report transfer support even though they inherently do.
        VkQueueFlags flag = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT |
            VK_QUEUE_TRANSFER_BIT;
        return mProperties.queueFlags & flag;
    }

    bool QueueFamily::hasSparseBindingSupport() const
    {
        return mProperties.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT;
    }

    size_t QueueFamily::getQueueCount() const
    {
        return mProperties.queueCount;
    }

    size_t QueueFamily::getTimeStampPrecision() const
    {
        return mProperties.timestampValidBits;
    }

    VkExtent3D QueueFamily::getMinImageTransferGranularity() const
    {
        return mProperties.minImageTransferGranularity;
    }

    size_t QueueFamily::getIndex() const
    {
        return mIndex;
    }
}
