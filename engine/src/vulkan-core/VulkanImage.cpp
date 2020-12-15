#include "VulkanImage.h"
#include "VulkanCommandBuffer.h"
#include "VulkanCommandManager.h"

namespace Xavier
{
    VulkanImage* VulkanImage::Instance(VkImage image)
    {
        if (smInstanceMap.find(image) == smInstanceMap.end())
            return nullptr;

        return smInstanceMap[image];
    }

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
        smInstanceMap[mVkImage] = this;

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
            smInstanceMap.erase(mVkImage);
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
        VkAccessFlags newAccess,
        VkPipelineStageFlags newStage,
        VkImageLayout newLayout,
        VkQueue newQueue
    )
    {
        VulkanCommandManager::Instance()->GetCommandBuffer()
        ->CmdPipelineBarrier(
            mPipelineStageFlags,
            newStage,
            mAccessFlags,
            newAccess,
            mQueue,
            newQueue,
            mImageLayout,
            newLayout,
            mVkImage
        );

        mAccessFlags = newAccess;
        mPipelineStageFlags = newStage;
        mImageLayout = newLayout;
        mQueue = newQueue;
    }
}