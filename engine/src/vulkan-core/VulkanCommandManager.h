#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanCommandBuffer;

    class VulkanCommandManager
    {
    public:
        static VulkanCommandManager* Instance();

        void Init(VkPhysicalDevice physicalDevice, VkDevice device);
        void Deinit();

        uint32_t GetQueueFamilyIndex(VkQueue queue) const;
        VulkanCommandBuffer* GetCommandBuffer();
        void FlushCommands();
        void WaitIdle();

    private:
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;

        std::unordered_map<VkQueue, uint32_t> mQueueFamilyIndices;
        std::unordered_map<VkQueue, VkCommandPool> mCommandPools;
        std::vector<std::shared_ptr<VulkanCommandBuffer>> mAllocatedCommandBuffers;
        VulkanCommandBuffer* mCommandBuffer = nullptr;
    };
}