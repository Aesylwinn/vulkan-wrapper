#ifndef VW_QUEUEFAMILY_H
#define VW_QUEUEFAMILY_H

#include <vw/common.h>

namespace vw
{
    /*! @brief A wrapper for VkQueueFamilyProperties.
     */
    class QueueFamily
    {
        public:

            /*! @brief Constructs a QueueFamily.
             *  @param index The index of the family on the PhysicalDevice.
             */
            explicit QueueFamily(size_t index, const VkQueueFamilyProperties& props);

            /*! @brief Returns true if the family supports graphics operations.
             */
            bool hasGraphicsSupport() const;

            /*! @brief Returns true if the family supports compute operations.
             */
            bool hasComputeSupport() const;

            /*! @brief Returns true if the family supports transfer operations.
             */
            bool hasTransferSupport() const;

            /*! @brief Returns true if the family supports sparse memory
             *      operations.
             */
            bool hasSparseBindingSupport() const;

            /*! @brief Returns the number of queues in the family.
             */
            size_t getQueueCount() const;

            /*! @brief Returns the number of bits of precision used when writing
             *      time stamps. If 0, the family does not support time stamps.
             */
            size_t getTimeStampPrecision() const;

            /*! @brief A return value of (0,0,0) means only whole mip levels can
             *      be transferred.
             */
            VkExtent3D getMinImageTransferGranularity() const;

            /*! @brief Returns the index of the family on the PhysicalDevice.
             */
            size_t getIndex() const;

        private:

            size_t mIndex;
            VkQueueFamilyProperties mProperties;
    };
}

#endif
