#ifndef VW_QUEUE_H
#define VW_QUEUE_H

#include <vw/common.h>

namespace vw
{
    /*! @brief A wrapper for a VkQueue.
     */
    class Queue
    {
        public:

            /*! @brief Constructs a queue with the given details.
             */
            Queue(uint32_t family, uint32_t index, VkQueue handle);

            /*! @brief Returns true if the queue is valid.
             */
            operator bool();

            /*! @brief Returns the family index of the queue.
             */
            uint32_t getFamilyIndex() const;

            /*! @brief Returns the queue's index in its family.
             */
            uint32_t getQueueIndex() const;

            /*! @brief Returns the VkQueue handle for the underlying object.
             */
            VkQueue getHandle();

        private:

            uint32_t mFamily;
            uint32_t mIndex;
            VkQueue mHandle;
    };
}

#endif
