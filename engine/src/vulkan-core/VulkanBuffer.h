#pragma once

#include "vulkan/vulkan.h"
#include "Xavier/Config.h"

namespace Xavier
{
    class VulkanImage;

    class VulkanBuffer
    {
    public:
        VulkanBuffer(
            VkDevice device,
            size_t size,
            VkBufferUsageFlags usageFlags,
            VkMemoryPropertyFlags memoryPropertyFlags
        );
        VulkanBuffer(const VulkanBuffer&) = delete;
        VulkanBuffer& operator=(const VulkanBuffer&) = delete;
        virtual ~VulkanBuffer();

        uint8_t* Map();
        void UnMap();
        void CopyFrom(const VulkanImage& image);
        void MakeTransition(
            VkAccessFlags newAccess,
            VkPipelineStageFlags newStage
        );

        VkBuffer GetHandle() const { return mVkBuffer; }
        size_t GetSizeInBytes() const { return mSizeInBytes; }
        VkBufferUsageFlags GetUsageFlags() const { mUsageFlags; }
        VkMemoryPropertyFlags GetMemoryPropertyFlags() const { return mMemoryPropertyFlags; }

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkBuffer mVkBuffer = VK_NULL_HANDLE;
        VkBufferUsageFlags mUsageFlags = 0;
        VkDeviceMemory mVkDeviceMemory = VK_NULL_HANDLE;
        VkMemoryPropertyFlags mMemoryPropertyFlags = 0;
        VkDeviceSize mSizeInBytes = 0;

        VkAccessFlags mAccessFlags = 0;
        VkPipelineStageFlags mPipelineStageFlags = 0;

        void* mMappedData = nullptr;
        uint32_t mNumMapped = 0;
    };

}