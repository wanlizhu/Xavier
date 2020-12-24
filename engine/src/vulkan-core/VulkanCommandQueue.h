#pragma once

#include "VulkanTools.h"
#include "VulkanCommandBuffer.h"

namespace Xavier
{
    class VulkanCommandQueue
    {
    public:
        VulkanCommandQueue(
            VkDevice device,
            uint32_t queueFamilyIndex,
            VkQueueFamilyProperties properties
        );
        VulkanCommandQueue(const VulkanCommandQueue&) = delete;
        VulkanCommandQueue& operator=(const VulkanCommandQueue&) = delete;
        virtual ~VulkanCommandQueue();

        void WaitIdle();
        VulkanCommandBuffer* GetCommandBuffer();
        
        uint32_t GetFamilyIndex() const { return mQueueFamilyIndex; }
        VkQueue  GetQueue() const { return mVkQueue; }
        VkQueueFamilyProperties GetProperties() const { return mProperties; }
        
    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkQueue  mVkQueue = VK_NULL_HANDLE;
        uint32_t mQueueFamilyIndex = UINT32_MAX;
        VkQueueFamilyProperties mProperties = {};

        VkCommandPool mVkCommandPool = VK_NULL_HANDLE;
        std::shared_ptr<VulkanCommandBuffer> mCommandBuffer;
    };
}