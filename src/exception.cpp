#include "vw/exception.h"

#include <sstream>

namespace vw
{
    Exception::Exception(const std::string& location, VkResult result)
        : mErrorCode(result)
    {
        setup(location, getVulkanResultString(result));
    }

    VkResult Exception::getErrorCode() const
    {
        return mErrorCode;
    }

    const std::string& Exception::getErrorMessage() const
    {
        return mErrorMsg;
    }

    void Exception::setup(const std::string& location, const std::string& msg)
    {
        std::stringstream ss;
        ss << "Unhandled event at " << location << ". " << msg;
        mErrorMsg = ss.str();
    }

    std::string Exception::getVulkanResultString(VkResult result) const
    {
        switch (result)
        {
            case VK_SUCCESS:
                return "Vulkan command completed successfully.";
            case VK_NOT_READY:
                return "Vulkan fence or query not ready.";
            case VK_TIMEOUT:
                return "Vulkan operation timed out.";
            case VK_EVENT_SET:
                return "Vulkan event is signaled.";
            case VK_EVENT_RESET:
                return "Vulkan event is unsignaled.";
            case VK_INCOMPLETE:
                return "Vulkan return array is too small for the result.";
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                return "Vulkan host failed to allocate memory.";
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return "Vulkan device failed to allocate memory.";
            case VK_ERROR_INITIALIZATION_FAILED:
                return "Vulkan failed to create object.";
            case VK_ERROR_DEVICE_LOST:
                return "Vulkan physical or logical device lost.";
            case VK_ERROR_MEMORY_MAP_FAILED:
                return "Vulkan mapping of memory object failed.";
            case VK_ERROR_LAYER_NOT_PRESENT:
                return "Vulkan layer that was requested not present.";
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                return "Vulkan extension that was requested not present.";
            case VK_ERROR_FEATURE_NOT_PRESENT:
                return "Vulkan feature that was requested not supported.";
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                return "Vulkan api compatible with requested version not available.";
            case VK_ERROR_TOO_MANY_OBJECTS:
                return "Vulkan exceeded maximum number of allowed objects for type.";
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                return "Vulkan format that was requested not supported by device.";
            case VK_ERROR_FRAGMENTED_POOL:
                return "Vulkan pool allocation failed due to memory fragmentation.";
            default:
                return "Vulkan unhandled error code.";
        }
    }
}

