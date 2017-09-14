#include "vw/vw.h"

#include <iostream>

int main(int argc, const char * const argv[])
{
    // Create instance
    vw::InstanceCreator instanceCtor;
    instanceCtor.setApplicationName("vwTest");
    instanceCtor.setApplicationVersion(1);

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

    std::exit(0);
}

