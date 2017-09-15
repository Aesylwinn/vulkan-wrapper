#ifndef VW_DEBUGCALLBACK_H
#define VW_DEBUGCALLBACK_H

namespace vw
{
    /*! @brief A convenience class for recieving debug messages from Vulkan.
     */
    struct DebugCallback
    {
        struct CallbackData
        {
            VkDebugReportFlagsEXT flags;
            VkDebugReportObjectTypeEXT objectType;
            uint64_t object;
            size_t location;
            int32_t messageCode;
            const char* layerPrefix;
            const char* message;
        };

        /*! @brief When set up correctly, this function will be called every
         *      time there is a message from the Vulkan validation layers.
         *  @return Returning true will abort the offending call. The
         *      specification suggests not doing this to prevent debug builds
         *      from behaving differently.
         */
        virtual bool operator()(const CallbackData& data) = 0;
    };
}

#endif
