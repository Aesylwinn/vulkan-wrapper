#include "vw/instance.h"

#include <cassert>

#include "vw/exception.h"
#include "vw/physicaldevice.h"

namespace vw
{
    Instance::Instance()
        : mHandle(VK_NULL_HANDLE)
    {
    }

    Instance::Instance(VkInstance handle)
        : mHandle(handle)
    {
    }

    Instance::Instance(Instance&& other)
    {
        mHandle = other.mHandle;
        other.mHandle = VK_NULL_HANDLE;
    }

    Instance::~Instance()
    {
        if (*this)
            vkDestroyInstance(mHandle, nullptr);
    }

    Instance& Instance::operator=(Instance&& other)
    {
        VkInstance temp = mHandle;
        mHandle = other.mHandle;
        other.mHandle = temp;
    }

    Instance::operator bool() const
    {
        return mHandle != VK_NULL_HANDLE;
    }

    VkInstance Instance::getHandle()
    {
        return mHandle;
    }

    Instance::PhysicalDeviceList Instance::enumeratePhysicalDevices()
    {
        assert(*this);

        // Retrieve handles
        uint32_t deviceCount = 0;
        VkResult result = VK_SUCCESS;
        std::vector<VkPhysicalDevice> handles;

        result = vkEnumeratePhysicalDevices(mHandle, &deviceCount, nullptr);
        if (result != VK_SUCCESS)
            throw Exception("vw::Instance::enumeratePhysicalDevices", result);

        handles.resize(deviceCount, VK_NULL_HANDLE);
        result = vkEnumeratePhysicalDevices(mHandle, &deviceCount, handles.data());
        if (result != VK_SUCCESS)
            throw Exception("vw::Instance::enumeratePhysicalDevices", result);

        // Construct and return result
        PhysicalDeviceList devices;
        for (VkPhysicalDevice handle : handles)
        {
            devices.push_back(PhysicalDevice(handle));
        }

        return devices;
    }

    InstanceCreator::InstanceCreator()
    {
        reset();
    }

    void InstanceCreator::setApplicationName(const std::string& name)
    {
        mUseAppInfo = true;
        mAppName = name;
    }

    void InstanceCreator::setApplicationVersion(uint32_t version)
    {
        mUseAppInfo = true;
        mAppVersion = version;
    }

    void InstanceCreator::setEngineName(const std::string& name)
    {
        mUseAppInfo = true;
        mEngineName = name;
    }

    void InstanceCreator::setEngineVersion(uint32_t version)
    {
        mUseAppInfo = true;
        mEngineVersion = version;
    }

    void InstanceCreator::setApiVersion(uint32_t major, uint32_t minor,
        uint32_t patch)
    {
        mUseAppInfo = true;
        mApiVersion = VK_MAKE_VERSION(major, minor, patch);
    }

    void InstanceCreator::addLayer(const std::string& name)
    {
        mLayers.push_back(name);
    }

    void InstanceCreator::addExtension(const std::string& name)
    {
        mExtensions.push_back(name);
    }

    void InstanceCreator::reset()
    {
        mUseAppInfo = false;
        mAppName.clear();
        mAppVersion = 0;
        mEngineName.clear();
        mEngineVersion = 0;
        mApiVersion = 0;
        mLayers.clear();
        mExtensions.clear();
    }

    Instance InstanceCreator::create()
    {
        // Application specific info
        VkApplicationInfo appInfo;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = mAppName.c_str();
        appInfo.applicationVersion = mAppVersion;
        appInfo.pEngineName = mEngineName.c_str();
        appInfo.engineVersion = mEngineVersion;
        appInfo.apiVersion = mApiVersion;

        // Extensions and layers
        std::vector<const char *> rawLayers;
        for (const std::string& str : mLayers)
            rawLayers.push_back(str.c_str());

        std::vector<const char *> rawExtensions;
        for (const std::string& str : mExtensions)
            rawExtensions.push_back(str.c_str());

        // Instance specific info
        VkInstanceCreateInfo createInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.pApplicationInfo = (mUseAppInfo) ? &appInfo : nullptr;
        createInfo.enabledLayerCount = rawLayers.size();
        createInfo.ppEnabledLayerNames = rawLayers.data();
        createInfo.enabledExtensionCount = rawExtensions.size();
        createInfo.ppEnabledExtensionNames = rawExtensions.data();

        // Actually create the instance now
        VkInstance handle = VK_NULL_HANDLE;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &handle);
        if (result != VK_SUCCESS)
        {
            throw Exception("vw::InstanceCreator::create", result);
        }

        return Instance(handle);
    }
}

