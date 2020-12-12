#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanCommandBuffer
    {
    public:
        VulkanCommandBuffer(
            VkDevice device,
            VkQueue queue, 
            VkCommandPool pool,
            VkCommandBufferLevel level
        );
        VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
        VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
        virtual ~VulkanCommandBuffer();       

        void CmdCopyBuffer(
            VkBuffer src, 
            size_t   srcOffset, 
            VkBuffer dst, 
            size_t   dstOffse, 
            size_t size
        );
        void CmdCopyImage(
            VkImage    src, 
            VkOffset2D srcOffset, 
            VkFormat   srcFormat,
            VkImage    dst,
            VkOffset2D dstOffset,
            VkFormat   dstFormat,
            VkExtent2D extent
        );
        void CmdCopyBufferToImage(
            VkBuffer src,
            size_t   srcOffset, 
            VkImage    dst, 
            VkOffset2D dstOffset, 
            VkFormat   dstFormat,
            VkExtent2D extent
        );
        void CmdCopyImageToBuffer(
            VkImage    src,
            VkOffset2D srcOffset, 
            VkFormat   srcFormat,
            VkBuffer dst,
            size_t   dstOffse,
            VkExtent2D extent
        );

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkQueue  mVkQueue = VK_NULL_HANDLE;
        VkCommandPool mVkCommandPool = VK_NULL_HANDLE;
        VkCommandBuffer mVkCommandBuffer = VK_NULL_HANDLE;
        VkFence mVkFence = VK_NULL_HANDLE;
    };
}