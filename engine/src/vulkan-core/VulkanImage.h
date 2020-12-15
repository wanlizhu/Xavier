#pragma once

#include "VulkanTools.h"
#include "VulkanResource.h"

namespace Xavier
{
    class VulkanImage : public std::enable_shared_from_this<VulkanImage>
    {
    public:
        static VulkanImage* Instance(VkImage handle);

        VulkanImage(
            VkDevice device,
            VkExtent2D extent,
            VkFormat format,
            uint32_t mipLevels,
            uint32_t arrayLayers,
            VkSampleCountFlagBits samples,
            VkImageUsageFlags usageFlags,
            VkMemoryPropertyFlags memoryPropertyFlags
        );
        VulkanImage(const VulkanImage&) = delete;
        VulkanImage& operator=(const VulkanImage&) = delete;
        virtual ~VulkanImage();

        void InsertMemoryBarrier(
            VkAccessFlags newAccess,
            VkPipelineStageFlags newStage,
            VkImageLayout newLayout,
            VkQueue newQueue
        );

        VkImage GetHandle() const { return mVkImage; }
        VkExtent2D GetExtent() const { return mExtent; }
        uint32_t GetMipLevels() const { return mMipLevels; }
        uint32_t GetArrayLayers() const { return mArrayLayers; }
        VkSampleCountFlagBits GetSampleCount() const { return mSampleCount; }
        VkImageAspectFlags GetImageAspectFlags() const { return mImageAspectFlags; }
        VkBufferUsageFlags GetUsageFlags() const { return mUsageFlags; }
        VkMemoryPropertyFlags GetMemoryPropertyFlags() const { return mMemoryPropertyFlags; }

    private:
        static inline std::unordered_map<VkImage, VulkanImage*> smInstanceMap;

        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkImage mVkImage = VK_NULL_HANDLE;
        VkImageUsageFlags mUsageFlags = 0;
        VkDeviceMemory mVkDeviceMemory = VK_NULL_HANDLE;
        VkMemoryPropertyFlags mMemoryPropertyFlags = 0;
        VkImageAspectFlags mImageAspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
        VkExtent2D mExtent = {};
        VkFormat mFormat = VK_FORMAT_UNDEFINED;
        uint32_t mMipLevels = 1;
        uint32_t mArrayLayers = 1;
        VkSampleCountFlagBits mSampleCount = VK_SAMPLE_COUNT_1_BIT;

        VkAccessFlags mAccessFlags = 0;
        VkPipelineStageFlags mPipelineStageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        VkImageLayout mImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkQueue mQueue = VK_NULL_HANDLE;
    };
}