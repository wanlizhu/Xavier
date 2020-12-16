#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanCommandBuffer;

    struct VulkanQueue
    {
        VkQueue  queueHandle = VK_NULL_HANDLE;
        uint32_t queueFamilyIndex = UINT32_MAX;
        VkQueueFamilyProperties properties = {};
        bool supportsPresent = false;
    };

    class VulkanCommandManager
    {
    public:
        static VulkanCommandManager* Instance();

        void Init(
            VkPhysicalDevice physicalDevice, 
            VkDevice device,
            uint32_t graphicsQueueFamilyIndex,
            uint32_t computeQueueFamilyIndex
        );
        void Deinit();

        VulkanQueue const& GetGraphicsQueue() const;
        VulkanCommandBuffer* GetGraphicsCommandBuffer();
        void FlushGraphicsCommands();
        void WaitGraphicsIdle();
        
        VulkanQueue const& GetComputeQueue() const;
        VulkanCommandBuffer* GetComputeCommandBuffer();
        void FlushComputeCommands();
        void WaitComputeIdle();

    private:
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;

        VulkanQueue   mGraphicsQueue = {};
        VkCommandPool mGraphicsCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mGraphicsCommandBuffer = nullptr;

        VulkanQueue   mComputeQueue = {};
        VkCommandPool mComputeCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mComputeCommandBuffer = nullptr;
    };
}