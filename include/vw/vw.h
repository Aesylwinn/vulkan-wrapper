#ifndef VW_VW_H
#define VW_VW_H

#include <vw/exception.h>
#include <vw/instance.h>
#include <vw/physicaldevice.h>

namespace vw
{
    /*! @brief Returns the version major number.
     */
    int getVersionMajor();

    /*! @brief Returns the version minor number.
     */
    int getVersionMinor();

    /*! @brief Returns the version patch number.
     */
    int getVersionPatch();

    /*! @brief Returns the version string in the format "major.minor.patch"
     *      where major, minor, and patch are their respective numbers.
     */
    const std::string getVersionString();
}

#endif
