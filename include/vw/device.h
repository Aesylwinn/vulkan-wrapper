#ifndef VW_DEVICE_H
#define VW_DEVICE_H

#include <vw/common.h>
#include <vector>

namespace vw
{
    class PhysicalDevice;
    class QueueFamily;

    /*! @brief A wrapper for a VkDevice.
     */
    class Device
    {
        public:

            /*! @brief Constructs an invalid Device.
             */
            Device();

            /*! @brief Constructs a Device with the specified handle. Ownership
             *      of the handle is assumed.
             */
            explicit Device(VkDevice handle);

            /*! @brief Move constructor that loots the other's VkDevice handle.
             */
            Device(Device&& other);

            /*! @brief Destroys the associated VkDevice.
             */
            ~Device();

            /*! @brief Move assignment operator that swaps VkDevice handles.
             */
            Device& operator=(Device&& other);

            /*! @brief Returns true if the underlying handle is valid.
             */
            operator bool() const;

            /*! @brief Retrieve the underlying VkDevice handle of the object.
             */
            VkDevice getHandle();

        private:

            Device(const Device& other) = delete;
            Device& operator=(const Device& other) = delete;

            VkDevice mHandle;
    };

    /*! @brief A convenience class for creating a Device.
     */
    class DeviceCreator
    {
        public:

            using PriorityList = std::vector<float>;

            /*! @brief Constructs a DeviceCreator.
             */
            DeviceCreator();

            /*! @brief Sets the PhysicalDevice to create the Device on. Also
             *      clears out any queues set to be added.
             */
            void setPhysicalDevice(const PhysicalDevice& device);

            /*! @brief Adds queues from the specified family.
             *  @param family The queue family. Each family has specific sets of
             *      operations they support.
             *  @param priority The priority of the work that will be submitted
             *      to each queue. The number of queues created will match the
             *      size of the PriorityList.
             */
            void addQueues(const QueueFamily& family, PriorityList priorities);

            /*! @brief Adds the specified device layer.
             *  @param name The name of the layer.
             *  @note The specification has deprecated this function. Layers
             *      should only need to be specified during instance creation.
             *      However, there may be some implementations that don't do
             *      this.
             */
            void addLayer(const std::string& name);

            /*! @brief Adds the specified extension.
             *  @param name The name of the extension.
             */
            void addExtension(const std::string& name);

            /*! @brief Some extra features can be enabled, though there may be
             *      performance implications.
             */
            void setEnabledFeatures(const VkPhysicalDeviceFeatures& features);

            /*! @brief Resets the DeviceCreator to a default state.
             */
            void reset();

            /*! @brief Creates a Device and its queues. The queues added will be
             *      cleared from the creator after creation.
             */
            Device create();

        private:

            bool mDefineEnabledFeatures;
            VkPhysicalDevice mPhysicalDevice;
            std::vector<VkDeviceQueueCreateInfo> mQueueInfos;
            PriorityList mQueuePriorities;
            std::vector<std::string> mLayers;
            std::vector<std::string> mExtensions;
            VkPhysicalDeviceFeatures mEnabledFeatures;
    };
}

#endif
