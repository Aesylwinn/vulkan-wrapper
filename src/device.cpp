#include "vw/device.h"

#include <cassert>
#include <utility>

#include "vw/exception.h"
#include "vw/physicaldevice.h"
#include "vw/queuefamily.h"

namespace vw
{
    Device::QueueList::QueueList(Container container)
        : mContainer(std::move(container))
    {
    }

    Device::QueueList::QueueList(QueueList&& other)
        : mContainer(std::move(other.mContainer))
    {
    }

    Device::QueueList& Device::QueueList::operator=(QueueList&& other)
    {
        std::swap(mContainer, other.mContainer);
    }

    Device::QueueList::iterator Device::QueueList::begin()
    {
        return mContainer.begin();
    }

    Device::QueueList::const_iterator Device::QueueList::begin() const
    {
        return mContainer.begin();
    }

    Device::QueueList::iterator Device::QueueList::end()
    {
        return mContainer.end();
    }

    Device::QueueList::const_iterator Device::QueueList::end() const
    {
        return mContainer.end();
    }

    Device::QueueList::const_iterator Device::QueueList::cbegin() const
    {
        return mContainer.cbegin();
    }

    Device::QueueList::const_iterator Device::QueueList::cend() const
    {
        return mContainer.cend();
    }

    Device::QueueList::size_type Device::QueueList::size()
    {
        return mContainer.size();
    }

    Device::Device()
        : mHandle(VK_NULL_HANDLE)
        , mQueues(QueueList::Container())
    {
    }

    Device::Device(VkDevice handle, QueueList queues)
        : mHandle(handle)
        , mQueues(std::move(queues))
    {
    }

    Device::Device(Device&& other)
        : mHandle(other.mHandle)
        , mQueues(std::move(other.mQueues))
    {
        other.mHandle = VK_NULL_HANDLE;
    }

    Device::~Device()
    {
        if (*this)
            vkDestroyDevice(mHandle, nullptr);
    }

    Device& Device::operator=(Device&& other)
    {
        std::swap(mHandle, other.mHandle);
        std::swap(mQueues, other.mQueues);
    }

    Device::operator bool() const
    {
        return mHandle != VK_NULL_HANDLE;
    }

    Device::QueueList& Device::getQueues()
    {
        return mQueues;
    }

    const Device::QueueList& Device::getQueues() const
    {
        return mQueues;
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

        // Create device
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

        VkDevice deviceHandle = VK_NULL_HANDLE;
        VkResult result = vkCreateDevice(mPhysicalDevice, &deviceCInfo, nullptr, &deviceHandle);
        if (result != VK_SUCCESS)
        {
            throw Exception("vw::DeviceCreator::create", result);
        }

        // Retrieve queues
        Device::QueueList::Container queues;
        for (const VkDeviceQueueCreateInfo& info : mQueueInfos)
        {
            uint32_t family = info.queueFamilyIndex;
            for (uint32_t index = 0; index < info.queueCount; ++index)
            {

                VkQueue queueHandle = VK_NULL_HANDLE;
                vkGetDeviceQueue(deviceHandle, family, index, &queueHandle);
                queues.push_back(Queue(family, index, queueHandle));
            }
        }

        return Device(deviceHandle, Device::QueueList(queues));
    }
}
