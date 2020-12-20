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
        VulkanCommandManager(
            VkPhysicalDevice physicalDevice, 
            VkDevice device,
            uint32_t graphicsQueueFamilyIndex,
            uint32_t transferQueueFamilyIndex,
            uint32_t computeQueueFamilyIndex,
            uint32_t presentQueueFamilyIndex
        );
        VulkanCommandManager(const VulkanCommandManager&) = delete;
        VulkanCommandManager& operator=(const VulkanCommandManager&) = delete;
        virtual ~VulkanCommandManager();

        VulkanCommandBuffer* GetGraphicsCommandBuffer();
        void FlushGraphicsCommands();
        void WaitGraphicsIdle();

        VulkanCommandBuffer* GetTransferCommandBuffer();
        void FlushTransferCommands();
        void WaitTransferIdle();
        
        VulkanCommandBuffer* GetComputeCommandBuffer();
        void FlushComputeCommands();
        void WaitComputeIdle();

        VulkanQueue const& GetPresentQueue() const { return mPresentQueue; }

    private:
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;

        VulkanQueue   mGraphicsQueue = {};
        VkCommandPool mGraphicsCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mGraphicsCommandBuffer = nullptr;

        VulkanQueue   mTransferQueue = {};
        VkCommandPool mTransferCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mTransferCommandBuffer = nullptr;

        VulkanQueue   mComputeQueue = {};
        VkCommandPool mComputeCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mComputeCommandBuffer = nullptr;

        VulkanQueue mPresentQueue = {};
    };
}