#include "vw/physicaldevice.h"

#include <cassert>

#include "vw/queuefamily.h"

namespace vw
{
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice handle)
        : mHandle(handle)
    {
        if (*this)
            vkGetPhysicalDeviceProperties(mHandle, &mProperties);
    }

    PhysicalDevice::operator bool() const
    {
        return mHandle != VK_NULL_HANDLE;
    }

    uint32_t PhysicalDevice::getApiVersion() const
    {
        return mProperties.apiVersion;
    }

    uint32_t PhysicalDevice::getDriverVersion() const
    {
        return mProperties.driverVersion;
    }

    uint32_t PhysicalDevice::getVendorId() const
    {
        return mProperties.vendorID;
    }

    uint32_t PhysicalDevice::getDeviceId() const
    {
        return mProperties.deviceID;
    }

    PhysicalDevice::Type PhysicalDevice::getDeviceType() const
    {
        return static_cast<Type>(mProperties.deviceType);
    }

    std::string PhysicalDevice::getDeviceName() const
    {
        const char* name = &mProperties.deviceName[0];
        return std::string(name, VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
    }

    PhysicalDevice::Uuid PhysicalDevice::getPipelineCacheUuid() const
    {
        Uuid id;
        for (size_t i = 0; i < VK_UUID_SIZE; ++i)
        {
            id[i] = mProperties.pipelineCacheUUID[i];
        }

        return id;
    }

    const VkPhysicalDeviceLimits& PhysicalDevice::getDeviceLimits() const
    {
        return mProperties.limits;
    }

    const VkPhysicalDeviceSparseProperties& PhysicalDevice::getDeviceSparseProperties() const
    {
        return mProperties.sparseProperties;
    }

    PhysicalDevice::QueueFamilyList PhysicalDevice::getDeviceQueueFamilies() const
    {
        assert(*this);

        // Read properties from device
        uint32_t count = 0;
        std::vector<VkQueueFamilyProperties> properties;

        vkGetPhysicalDeviceQueueFamilyProperties(mHandle, &count, nullptr);
        properties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(mHandle, &count, properties.data());

        // Return list
        size_t index = 0;
        QueueFamilyList list;
        for (auto it : properties)
        {
            list.push_back(QueueFamily(index++, it));
        }
        return list;
    }

    VkPhysicalDevice PhysicalDevice::getHandle() const
    {
        return mHandle;
    }
}
