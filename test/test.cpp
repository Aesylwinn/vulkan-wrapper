#include "vw/vw.h"

#include <iostream>

int main(int argc, const char * const argv[])
{
    // Create instance
    std::cout << "Attempting to create an Instance.\n";

    vw::InstanceCreator instanceCtor;
    instanceCtor.setApplicationName("vwTest");
    instanceCtor.setApplicationVersion(1);

    try
    {
        vw::Instance instance = instanceCtor.create();
    }
    catch (const vw::Exception& ex)
    {
        std::cout << "Failed to create Instance.\n";
        std::cout << ex.getErrorMessage() << "\n";
        std::exit(0);
    }

    std::cout << "Successfully created an Instance.\n";

    std::exit(0);
}

