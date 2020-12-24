#include "VulkanCommandQueue.h"

namespace Xavier
{
    VulkanCommandQueue::VulkanCommandQueue(
        VkDevice device,
        uint32_t queueFamilyIndex,
        VkQueueFamilyProperties properties
    )
        : mVkDevice(device)
        , mQueueFamilyIndex(queueFamilyIndex)
        , mProperties(properties)
    {
        vkGetDeviceQueue(mVkDevice, mQueueFamilyIndex, 0, &mVkQueue);
        assert(mVkQueue != VK_NULL_HANDLE);

        VkCommandPoolCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.queueFamilyIndex = mQueueFamilyIndex;

        VK_ASSERT(vkCreateCommandPool(mVkDevice, &createInfo, nullptr, &mVkCommandPool));
    }

    VulkanCommandQueue::~VulkanCommandQueue()
    {
        WaitIdle();

        if (mVkCommandPool)
        {
            vkDestroyCommandPool(mVkDevice, mVkCommandPool, nullptr);
            mVkCommandPool = VK_NULL_HANDLE;
        }
    }

    void VulkanCommandQueue::WaitIdle()
    {
        vkQueueWaitIdle(mVkQueue);
    }

    VulkanCommandBuffer* VulkanCommandQueue::GetCommandBuffer()
    {
        if (mCommandBuffer == nullptr)
        {
            mCommandBuffer = std::make_shared<VulkanCommandBuffer>(
                mVkDevice,
                mVkQueue,
                mVkCommandPool,
                VK_COMMAND_BUFFER_LEVEL_PRIMARY
            );
        }

        return mCommandBuffer.get();
    }
}