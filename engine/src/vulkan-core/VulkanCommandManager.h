#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanCommandBuffer;

    class VulkanCommandManager
    {
    public:
        static VulkanCommandManager* Instance();

        void Init(
            VkPhysicalDevice physicalDevice, 
            VkDevice device,
            uint32_t presentQueueFamilyIndex,
            uint32_t graphicsQueueFamilyIndex,
            uint32_t computeQueueFamilyIndex
        );
        void Deinit();

        uint32_t GetPresentQueueFamilyIndex() const;
        VkQueue  GetPresentQueue() const;

        uint32_t GetGraphicsQueueFamilyIndex() const;
        VkQueue  GetGraphicsQueue() const;
        VulkanCommandBuffer* GetGraphicsCommandBuffer();
        void FlushGraphicsCommands();
        void WaitGraphicsIdle();
        
        uint32_t GetComputeQueueFamilyIndex() const;
        VkQueue  GetComputeQueue() const;
        VulkanCommandBuffer* GetComputeCommandBuffer();
        void FlushComputeCommands();
        void WaitComputeIdle();

    private:
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;

        uint32_t mPresentQueueFamilyIndex = UINT32_MAX;
        VkQueue  mPresentQueue = VK_NULL_HANDLE;
       
        uint32_t mGraphicsQueueFamilyIndex = UINT32_MAX;    
        VkQueue  mGraphicsQueue = VK_NULL_HANDLE;
        VkQueueFamilyProperties mGraphicsQueueFamilyProperties = {};
        VkCommandPool mGraphicsCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mGraphicsCommandBuffer = nullptr;

        uint32_t mComputeQueueFamilyIndex = UINT32_MAX;
        VkQueue  mComputeQueue = VK_NULL_HANDLE;
        VkQueueFamilyProperties mComputeQueueFamilyProperties = {};
        VkCommandPool mComputeCommandPool = VK_NULL_HANDLE;
        VulkanCommandBuffer* mComputeCommandBuffer = nullptr;
    };
}