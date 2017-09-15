#include "vw/device.h"

#include <cassert>

#include "vw/exception.h"
#include "vw/physicaldevice.h"
#include "vw/queuefamily.h"

namespace vw
{
    Device::Device()
        : mHandle(VK_NULL_HANDLE)
    {
    }

    Device::Device(VkDevice handle)
        : mHandle(handle)
    {
    }

    Device::Device(Device&& other)
    {
        mHandle = other.mHandle;
        other.mHandle = VK_NULL_HANDLE;
    }

    Device::~Device()
    {
        if (*this)
            vkDestroyDevice(mHandle, nullptr);
    }

    Device& Device::operator=(Device&& other)
    {
        VkDevice temp = mHandle;
        mHandle = other.mHandle;
        other.mHandle = temp;
    }

    Device::operator bool() const
    {
        return mHandle != VK_NULL_HANDLE;
    }

    VkDevice Device::getHandle()
    {
        return mHandle;
    }

    DeviceCreator::DeviceCreator()
    {
        reset();
    }

    void DeviceCreator::setPhysicalDevice(const PhysicalDevice& device)
    {
        assert(device);

        mQueueInfos.clear();
        mQueuePriorities.clear();
        mPhysicalDevice = device.getHandle();
    }

    void DeviceCreator::addQueues(const QueueFamily& family, PriorityList priorities)
    {
        if (priorities.empty())
            return;

        size_t offset = mQueuePriorities.size();
        mQueuePriorities.insert(mQueuePriorities.end(), priorities.begin(), priorities.end());

        VkDeviceQueueCreateInfo cinfo;
        cinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        cinfo.pNext = nullptr;
        cinfo.flags = 0;
        cinfo.queueFamilyIndex = family.getIndex();
        cinfo.queueCount = priorities.size();
        cinfo.pQueuePriorities = &mQueuePriorities[offset];
        mQueueInfos.push_back(cinfo);
    }

    void DeviceCreator::addLayer(const std::string& name)
    {
        mLayers.push_back(name);
    }

    void DeviceCreator::addExtension(const std::string& name)
    {
        mExtensions.push_back(name);
    }

    void DeviceCreator::setEnabledFeatures(const VkPhysicalDeviceFeatures& features)
    {
        mDefineEnabledFeatures = true;
        mEnabledFeatures = features;
    }

    void DeviceCreator::reset()
    {
        mDefineEnabledFeatures = false;
        mPhysicalDevice = VK_NULL_HANDLE;
        mQueueInfos.clear();
        mQueuePriorities.clear();
        mLayers.clear();
        mExtensions.clear();
    }

    Device DeviceCreator::create()
    {
        assert(mPhysicalDevice != VK_NULL_HANDLE);
        assert(!mQueuePriorities.empty());

        std::vector<const char*> layers;
        for (const std::string& layer : mLayers)
            layers.push_back(layer.c_str());

        std::vector<const char*> extensions;
        for (const std::string& ext : extensions)
            extensions.push_back(ext.c_str());

        VkDeviceCreateInfo deviceCInfo;
        deviceCInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCInfo.pNext = nullptr;
        deviceCInfo.flags = 0;
        deviceCInfo.queueCreateInfoCount = mQueueInfos.size();
        deviceCInfo.pQueueCreateInfos = mQueueInfos.data();
        deviceCInfo.enabledLayerCount = layers.size();
        deviceCInfo.ppEnabledLayerNames = layers.data();
        deviceCInfo.enabledExtensionCount = extensions.size();
        deviceCInfo.ppEnabledExtensionNames = extensions.data();
        deviceCInfo.pEnabledFeatures = (mDefineEnabledFeatures) ? &mEnabledFeatures : nullptr;

        VkDevice handle = VK_NULL_HANDLE;
        VkResult result = vkCreateDevice(mPhysicalDevice, &deviceCInfo, nullptr, &handle);
        if (result != VK_SUCCESS)
        {
            throw Exception("vw::DeviceCreator::create", result);
        }

        return Device(handle);
    }
}
