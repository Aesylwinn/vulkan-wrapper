#ifndef VW_EXCEPTION_H
#define VW_EXCEPTION_H

#include <vw/common.h>

namespace vw
{
    /*! @brief An exception thrown whenever an unhandled Vulkan event occurs.
     */
    class Exception
    {
        public:

            /*! @brief Constructs an exception using the provided details.
             *  @param location Preferably a function name. For example,
             *      vw::InstanceCreator::create.
             *  @param errorCode The result returned from a vulkan function
             *      call.
             */
            Exception(const std::string& location, VkResult errorCode);

            /*! @brief Returns the error code returned by Vulkan, allowing an
             *      implementation to recover when possible.
             */
            VkResult getErrorCode() const;

            /*! @brief Returns a human readable error message providing details
             *      of the offending error.
             */
            const std::string& getErrorMessage() const;

        private:

            void setup(const std::string& location, const std::string& msg);
            std::string getVulkanResultString(VkResult result) const;

            std::string mErrorMsg;
            VkResult mErrorCode;
    };
}

#endif
