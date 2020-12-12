#include "VulkanCommandBuffer.h"

namespace Xavier
{
    VulkanCommandBuffer::VulkanCommandBuffer(
        VkDevice device,
        VkQueue queue,
        VkCommandPool pool,
        VkCommandBufferLevel level
    )
        : mVkDevice(device)
        , mVkQueue(queue)
        , mVkCommandPool(pool)
    {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = level;
        allocInfo.commandPool = pool;
        allocInfo.commandBufferCount = 1;

        VK_ASSERT(vkAllocateCommandBuffers(mVkDevice, &allocInfo, &mVkCommandBuffer));

        VkFenceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        VK_ASSERT(vkCreateFence(mVkDevice, &createInfo, nullptr, &mVkFence));
    }

    VulkanCommandBuffer::~VulkanCommandBuffer()
    {
        if (mVkFence)
        {
            vkDestroyFence(mVkDevice, mVkFence, nullptr);
            mVkFence = VK_NULL_HANDLE;
        }

        if (mVkCommandBuffer)
        {
            vkFreeCommandBuffers(mVkDevice, mVkCommandPool, 1, &mVkCommandBuffer);
            mVkCommandBuffer = VK_NULL_HANDLE;
        }
    }

    void VulkanCommandBuffer::CmdCopyBuffer(
        VkBuffer src, 
        size_t   srcOffset,
        VkBuffer dst,
        size_t   dstOffse,
        size_t size
    )
    {
        VkBufferCopy copy;
        copy.srcOffset = srcOffset;
        copy.dstOffset = dstOffse;
        copy.size = size;

        vkCmdCopyBuffer(mVkCommandBuffer, src, dst, 1, &copy);
    }

    void VulkanCommandBuffer::CmdCopyImage(
        VkImage    src, 
        VkOffset2D srcOffset,
        VkFormat   srcFormat,
        VkImage    dst, 
        VkOffset2D dstOffset,
        VkFormat   dstFormat,
        VkExtent2D extent
    )
    {
        VkImageCopy copy;
        copy.srcOffset.x = srcOffset.x;
        copy.srcOffset.y = srcOffset.y;
        copy.srcOffset.z = 0;
        copy.dstOffset.x = dstOffset.x;
        copy.dstOffset.y = dstOffset.y;
        copy.dstOffset.z = 0;
        copy.srcSubresource.aspectMask = GetImageAspectFlags(srcFormat);
        copy.srcSubresource.baseArrayLayer = 0;
        copy.srcSubresource.layerCount = 1;
        copy.srcSubresource.mipLevel = 0;
        copy.dstSubresource.aspectMask = GetImageAspectFlags(dstFormat);
        copy.dstSubresource.baseArrayLayer = 0;
        copy.dstSubresource.layerCount = 1;
        copy.dstSubresource.mipLevel = 0;
        copy.extent.width = extent.width;
        copy.extent.height = extent.height;
        copy.extent.depth = 1;

        vkCmdCopyImage(
            mVkCommandBuffer, 
            src, 
            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            dst,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &copy
        );
    }

    void VulkanCommandBuffer::CmdCopyBufferToImage(
        VkBuffer src, 
        size_t   srcOffset,
        VkImage    dst, 
        VkOffset2D dstOffset,
        VkFormat   dstFormat,
        VkExtent2D extent
    )
    {
        VkBufferImageCopy copy;
        copy.bufferOffset = srcOffset;
        copy.bufferRowLength = extent.width;
        copy.bufferImageHeight = extent.height;
        copy.imageOffset.x = dstOffset.x;
        copy.imageOffset.y = dstOffset.y;
        copy.imageOffset.z = 0;
        copy.imageExtent.width = extent.width;
        copy.imageExtent.height = extent.height;
        copy.imageExtent.depth = 1;
        copy.imageSubresource.aspectMask = GetImageAspectFlags(dstFormat);
        copy.imageSubresource.baseArrayLayer = 0;
        copy.imageSubresource.layerCount = 1;
        copy.imageSubresource.mipLevel = 0;

        vkCmdCopyBufferToImage(
            mVkCommandBuffer,
            src,
            dst,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &copy
        );
    }

    void VulkanCommandBuffer::CmdCopyImageToBuffer(
        VkImage    src, 
        VkOffset2D srcOffset, 
        VkFormat   srcFormat,
        VkBuffer dst, 
        size_t   dstOffse,
        VkExtent2D extent
    )
    {
        VkBufferImageCopy copy;
        copy.bufferOffset = dstOffse;
        copy.bufferRowLength = extent.width;
        copy.bufferImageHeight = extent.height;
        copy.imageOffset.x = srcOffset.x;
        copy.imageOffset.y = srcOffset.y;
        copy.imageOffset.z = 0;
        copy.imageExtent.width = extent.width;
        copy.imageExtent.height = extent.height;
        copy.imageExtent.depth = 1;
        copy.imageSubresource.aspectMask = GetImageAspectFlags(srcFormat);
        copy.imageSubresource.baseArrayLayer = 0;
        copy.imageSubresource.layerCount = 1;
        copy.imageSubresource.mipLevel = 0;

        vkCmdCopyImageToBuffer(
            mVkCommandBuffer,
            src,
            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            dst,
            1,
            &copy
        );
    }
}