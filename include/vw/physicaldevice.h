#ifndef VW_PHYSICALDEVICE_H
#define VW_PHYSICALDEVICE_H

#include <vw/common.h>
#include <array>
#include <vector>

namespace vw
{
    class QueueFamily;

    /*! @brief A wrapper for a VkPhysicalDevice object. */
    class PhysicalDevice
    {
        public:

            enum Type
            {
                Type_Other          = VK_PHYSICAL_DEVICE_TYPE_OTHER,
                Type_IntegratedGpu  = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
                Type_DiscreteGpu    = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
                Type_VirtualGpu     = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
                Type_Cpu            = VK_PHYSICAL_DEVICE_TYPE_CPU
            };

            using Uuid = std::array<uint8_t, VK_UUID_SIZE>;
            using QueueFamilyList = std::vector<QueueFamily>;

            /*! @brief Constructs a PhysicalDevice that is valid only during the
             *      lifetime of the Instance it was obtained from.
             *  @note It is possible for a physical device to be dropped when
              *     there is faulty hardware.
             */
            explicit PhysicalDevice(VkPhysicalDevice handle);

            /*! @brief Returns true if the data contained is valid.
             */
            operator bool() const;

            /*! @brief Retrieves the Vulkan version, encoded in the special
             *      format specified by the Vulkan specification.
             */
            uint32_t getApiVersion() const;

            /*! @brief Retrieves the vendor specified version of the driver.
             */
            uint32_t getDriverVersion() const;

            /*! @brief Retrieves an identifier which uniquely identifies the
             *      device vendor.
             */
            uint32_t getVendorId() const;

            /*! @brief Retrieves an identifier which uniquely identifies the
             *      physical device type in combination with the vendor id.
             */
            uint32_t getDeviceId() const;

            /*! @brief Retrieves the type of the physical device.
             */
            Type getDeviceType() const;

            /*! @brief Retrieves a user friendly name for the physical device,
             *      specified in UTF-8.
             */
            std::string getDeviceName() const;

            /*! @brief Retrieves a universally unique identifier for the device.
             */
            Uuid getPipelineCacheUuid() const;

            /*! @brief Retrieves the reported device limits. See the Vulkan API
             *      specification for more details.
             */
            const VkPhysicalDeviceLimits& getDeviceLimits() const;

            /*! @brief Retrieves the reported device sparse memory ablities,
             *      which essentially reduce memory rules. See the Vulkan API
             *      specification for more details.
             */
            const VkPhysicalDeviceSparseProperties& getDeviceSparseProperties() const;

            /*! @brief Returns a list of descriptions for each queue on the
             *      device.
             */
            QueueFamilyList getDeviceQueueFamilies() const;

            /*! @brief Retrieves the underlying VkPhysicalDevice handle. The
             *      lifetime of the handle does not change.
             */
            VkPhysicalDevice getHandle() const;

        private:

            VkPhysicalDevice mHandle;
            VkPhysicalDeviceProperties mProperties;
    };
}

#endif
