#include "vw/physicaldevice.h"

namespace vw
{
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice handle)
        : mValid(false)
    {
        if (handle != VK_NULL_HANDLE)
        {
            vkGetPhysicalDeviceProperties(handle, &mProperties);
            mValid = true;
        }
    }

    PhysicalDevice::operator bool() const
    {
        return mValid;
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
}
