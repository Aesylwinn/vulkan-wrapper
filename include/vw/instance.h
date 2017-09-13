#ifndef VW_INSTANCE_H
#define VW_INSTANCE_H

#include <vw/common.h>
#include <vector>

namespace vw
{
    /*! @brief A wrapper for a VkInstance object. */
    class Instance
    {
        public:

            /*! @brief Constructs an Instance.
             *  @param handle The Instance object created will assume ownership
             *      of the passed handle.
             */
            explicit Instance(VkInstance handle);

            /*! @brief Constructs an Instance using the looted VkInstance found
             *      in the passed parameter.
             *  @param other The Instance to be looted.
             */
            Instance(Instance&& other);

            /*! @brief Cleans up allocated resources, including the VkInstance
             *      owned by the Instance.
             */
            ~Instance();

            /*! @brief Swaps the two associated VkInstance handles.
             *  @param other The Instance to be looted.
             */
            Instance& operator=(Instance&& other);

            /*! @brief Returns true if the VkInstance handle is not null.
             */
            operator bool();

            /*! @brief Retrieves the handle to the underlying VkInstance.
             *      Ownership is still maintained. It is not transferred!
             */
            VkInstance getHandle() const;

        private:

            Instance(const Instance&) = delete;
            Instance& operator=(const Instance&) = delete;

            VkInstance mHandle;
    };

    /*! @brief A convenience class for creating an Instance.
     */
    class InstanceCreator
    {
        public:

            /*! @brief Constructs a ready to use InstanceCreator.
             */
            InstanceCreator();

            /*! @brief Sets the application name that will be passed on to the
             *      implementation.
             */
            void setApplicationName(const std::string& name);

            /*! @brief Sets the application version that will be passed on to
             *      the implementation.
             */
            void setApplicationVersion(uint32_t version);

            /*! @brief Sets the engine name that will be passed on to the
             *      implementation.
             */
            void setEngineName(const std::string& name);

            /*! @brief Sets the engine version that will be passed on to the
             *      implementation.
             */
            void setEngineVersion(uint32_t version);

            /*! @brief Sets the api version that the application is expecting
             *      to use.
             *  @param major The major number of the Vulkan API being targeted.
             *  @param minor The minor number of the Vulkan API being targeted.
             *  @param patch The patch number of the Vulkan API being targeted.
             */
            void setApiVersion(uint32_t major, uint32_t minor, uint32_t patch);

            /*! @brief Adds the specified global layer to be enabled by the
             *      implementation.
             *  @param name The name of the global layer.
             */
            void addLayer(const std::string& name);

            /*! @brief Adds the specified extension to be enabled by the
             *      implementation.
             *  @param name The name of the extension.
             */
            void addExtension(const std::string& name);

            /*! @brief Resets the creator to its default state.
             */
            void reset();

            /*! @brief Attempts to create an Instance with the properties
             *      specified. On failure, an exception is thrown.
             */
            Instance create();

        private:

            bool mUseAppInfo;
            std::string mAppName;
            uint32_t mAppVersion;
            std::string mEngineName;
            uint32_t mEngineVersion;
            uint32_t mApiVersion;
            std::vector<std::string> mLayers;
            std::vector<std::string> mExtensions;
    };
}

#endif

