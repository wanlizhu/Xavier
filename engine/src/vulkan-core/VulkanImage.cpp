#include "VulkanImage.h"

namespace Xavier
{
    VulkanImage::VulkanImage(
        VkDevice device,
        VkExtent2D extent,
        VkFormat format,
        uint32_t mipLevels,
        uint32_t arrayLayers,
        VkSampleCountFlagBits samples,
        VkImageUsageFlags usageFlags,
        VkMemoryPropertyFlags memoryPropertyFlags
    )
        : mVkDevice(device)
        , mUsageFlags(usageFlags)
        , mExtent(extent)
        , mMipLevels(mipLevels)
        , mArrayLayers(arrayLayers)
        , mSampleCount(samples)
    {
        VkImageCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        createInfo.imageType = VK_IMAGE_TYPE_2D;
        createInfo.format = format;
        createInfo.extent.width = mExtent.width;
        createInfo.extent.height = mExtent.height;
        createInfo.extent.depth = 1;
        createInfo.arrayLayers = mArrayLayers;
        createInfo.mipLevels = mipLevels;
        createInfo.samples = mSampleCount;
        createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        createInfo.usage = mUsageFlags;
        createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        VK_ASSERT(vkCreateImage(
            mVkDevice, 
            &createInfo,
            nullptr,
            &mVkImage
        ));

        VkMemoryRequirements memoryReq = {};
        vkGetImageMemoryRequirements(mVkDevice, mVkImage, &memoryReq);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memoryReq.size;
        allocInfo.memoryTypeIndex = GetMemoryTypeIndex(
            mVkDevice,
            memoryReq.memoryTypeBits | memoryPropertyFlags,
            &mMemoryPropertyFlags
        );

        VK_ASSERT(vkAllocateMemory(
            mVkDevice, 
            &allocInfo,
            nullptr,
            &mVkDeviceMemory
        ));
        VK_ASSERT(vkBindImageMemory(
            mVkDevice, 
            mVkImage,
            mVkDeviceMemory, 
            0
        ));
    }
    
    VulkanImage::~VulkanImage()
    {
        if (mVkImage)
        {
            vkDestroyImage(mVkDevice, mVkImage, nullptr);
            mVkImage = VK_NULL_HANDLE;
        }

        if (mVkDeviceMemory)
        {
            vkFreeMemory(mVkDevice, mVkDeviceMemory, nullptr);
            mVkDeviceMemory = VK_NULL_HANDLE;
        }
    }

    void VulkanImage::InsertMemoryBarrier(
        VkCommandBuffer commandBuffer,
        VkAccessFlags newAccess,
        VkPipelineStageFlags newStage,
        VkImageLayout newLayout
    )
    {
        VkImageMemoryBarrier barrier = {};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = mVkImage;
        barrier.subresourceRange.aspectMask = mImageAspectFlags;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.layerCount = 1;
        barrier.subresourceRange.levelCount = 1;
        barrier.srcAccessMask = mAccessFlags;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstAccessMask = newAccess;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.oldLayout = mImageLayout;
        barrier.newLayout = newLayout;

        vkCmdPipelineBarrier(
            commandBuffer,
            mPipelineStageFlags,
            newStage,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrier
        );

        mAccessFlags = newAccess;
        mPipelineStageFlags = newStage;
        mImageLayout = newLayout;
    }
}