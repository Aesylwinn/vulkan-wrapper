#include "vw/vw.h"

#include <sstream>

#include <vw/version.h>

namespace vw
{
    int getVersionMajor()
    {
        return MajorVersion;
    }

    int getVersionMinor()
    {
        return MinorVersion;
    }

    int getVersionPatch()
    {
        return PatchVersion;
    }

    const std::string getVersionString()
    {
        std::stringstream ss;
        ss << getVersionMajor() << '.';
        ss << getVersionMinor() << '.';
        ss << getVersionPatch();
        return ss.str();
    }
}

