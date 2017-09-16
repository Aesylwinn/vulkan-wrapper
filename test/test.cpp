#include "vw/vw.h"

#include <algorithm>
#include <iostream>

struct DebugCallback : public vw::DebugCallback
{
    bool operator()(const CallbackData& data) override
    {
        std::cout << "Validation layers: " << data.message << "\n";
        return false;
    }
};

struct DevicePriority
{
    bool operator()(const vw::PhysicalDevice& a, const vw::PhysicalDevice& b)
    {
        return getPriority(a.getDeviceType()) < getPriority(b.getDeviceType());
    }

    int getPriority(vw::PhysicalDevice::Type type)
    {
        switch (type)
        {
            case vw::PhysicalDevice::Type_DiscreteGpu:      return 0;
            case vw::PhysicalDevice::Type_VirtualGpu:       return 1;
            case vw::PhysicalDevice::Type_IntegratedGpu:    return 2;
            case vw::PhysicalDevice::Type_Cpu:              return 3;
            case vw::PhysicalDevice::Type_Other:            return 4;
            default:                                        return 5;
        }
    }
};

int main(int argc, const char * const argv[])
{
    // Create instance
    vw::InstanceCreator instanceCtor;
    instanceCtor.setApplicationName("vwTest");
    instanceCtor.setApplicationVersion(1);
    instanceCtor.addLayer("VK_LAYER_LUNARG_standard_validation");
    instanceCtor.addExtension(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    vw::Instance instance;

    try
    {
        std::cout << "Attempting to create an Instance.\n";
        instance = instanceCtor.create();
        std::cout << "Successfully created an Instance.\n\n";
    }
    catch (const vw::Exception& ex)
    {
        std::cout << "Failed to create Instance.\n";
        std::cout << ex.getErrorMessage() << "\n";
        std::exit(0);
    }

    instance.setDebugCallback(std::make_shared<DebugCallback>());

    vw::Instance::PhysicalDeviceList physicalDevices;
    physicalDevices = instance.enumeratePhysicalDevices();

    for (auto dev : physicalDevices)
    {
        std::cout << "Device " << dev.getDeviceName() << "\n";
        std::cout << "API version: " << dev.getApiVersion() << "\n";
        std::cout << "Driver version: " << dev.getDriverVersion() << "\n";
        std::cout << "Vendor ID: " << dev.getVendorId() << "\n";
        std::cout << "Device ID: " << dev.getDeviceId() << "\n";
        std::cout << "Device type: " << dev.getDeviceType() << "\n\n";

        for (auto family : dev.getDeviceQueueFamilies())
        {
            std::cout << "Queue family " << family.getIndex() << "\n";
            if (family.hasGraphicsSupport())
                std::cout << "Supports graphics operations\n";
            if (family.hasComputeSupport())
                std::cout << "Supports compute operations\n";
            if (family.hasTransferSupport())
                std::cout << "Supports transfer operations\n";
            if (family.hasSparseBindingSupport())
                std::cout << "Supports sparse memory operations\n";
            std::cout << "Queue count: " << family.getQueueCount() << "\n";
            std::cout << "Queue time stamp precision: " <<
                family.getTimeStampPrecision() << " bits\n";
            std::cout << "Minimum transfer granularity: (" <<
                family.getMinImageTransferGranularity().width << ", " <<
                family.getMinImageTransferGranularity().height << ", " <<
                family.getMinImageTransferGranularity().depth << ")\n\n";
        }
    }

    // Create a device.
    vw::DeviceCreator deviceCtor;
    deviceCtor.addLayer("VK_LAYER_LUNARG_standard_validation");
    deviceCtor.addExtension(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    std::sort(physicalDevices.begin(), physicalDevices.end(), DevicePriority());
    bool devSelected = false;

    for (auto dev : physicalDevices)
    {
        deviceCtor.setPhysicalDevice(dev);

        for (auto family : dev.getDeviceQueueFamilies())
        {
            if (family.hasGraphicsSupport())
            {
                vw::DeviceCreator::PriorityList priorityList;
                priorityList.resize(family.getQueueCount(), 1.0f);

                deviceCtor.addQueues(family, priorityList);
                devSelected = true;
            }
        }

        if (devSelected)
            break;
    }

    if (!devSelected)
    {
        std::cout << "No device with vulkan graphics support was found.\n";
        std::exit(0);
    }

    vw::Device device;

    try
    {
        std::cout << "Attempting to create a Device.\n";
        device = deviceCtor.create();
        std::cout << "Successfully created a Device.\n";
    }
    catch (const vw::Exception& ex)
    {
        std::cout << "Failed to create a Device.\n";
        std::cout << ex.getErrorMessage() << "\n";
        std::exit(0);
    }

    std::cout << "Created queues:\n\n";
    for (auto& queue : device.getQueues())
    {
        std::cout << "Queue family: " << queue.getFamilyIndex() << "\n";
        std::cout << "Queue index: " << queue.getQueueIndex() << "\n\n";
    }

    std::exit(0);
}

