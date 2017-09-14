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
        std::cout << "Successfully created an Instance.\n";
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
        std::cout << "Device Type: " << dev.getDeviceType() << "\n\n";
    }

    std::exit(0);
}

