#pragma once

#include "vulkan/vulkan.h"
#include "Xavier/Config.h"

namespace Xavier
{
    class VulkanBuffer;

    class VulkanImage
    {
    public:
        VulkanImage(
            VkDevice device,
            VkExtent2D extent,
            uint32_t mipLevels,
            uint32_t arrayLayers,
            uint32_t samples,
            VkImageUsageFlags usageFlags,
            VkMemoryPropertyFlags memoryPropertyFlags
        );
        VulkanImage(const VulkanImage&) = delete;
        VulkanImage& operator=(const VulkanImage&) = delete;
        virtual ~VulkanImage();

        void CopyFrom(const VulkanBuffer& buffer);
        void MakeTransition(
            VkAccessFlags newAccess,
            VkPipelineStageFlags newStage,
            VkImageLayout newLayout
        );

        VkImage GetHandle() const { return mVkImage; }
        VkExtent2D GetExtent() const { return mExtent; }
        uint32_t GetMipLevels() const { return mMipLevels; }
        uint32_t GetArrayLayers() const { return mArrayLayers; }
        uint32_t GetSampleCount() const { return mSampleCount; }
        VkBufferUsageFlags GetUsageFlags() const { mUsageFlags; }
        VkMemoryPropertyFlags GetMemoryPropertyFlags() const { return mMemoryPropertyFlags; }

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkImage mVkImage = VK_NULL_HANDLE;
        VkImageUsageFlags mUsageFlags = 0;
        VkDeviceMemory mVkDeviceMemory = VK_NULL_HANDLE;
        VkMemoryPropertyFlags mMemoryPropertyFlags = 0;
        VkExtent2D mExtent = {};
        uint32_t mMipLevels = 1;
        uint32_t mArrayLayers = 1;
        uint32_t mSampleCount = 1;

        VkAccessFlags mAccessFlags = 0;
        VkPipelineStageFlags mPipelineStageFlags = 0;
    };
}