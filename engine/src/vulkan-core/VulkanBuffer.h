#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanBuffer : public std::enable_shared_from_this<VulkanBuffer>
    {
    public:
        static VulkanBuffer* Instance(VkBuffer handle);

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

        VkBuffer GetHandle() const { return mVkBuffer; }
        size_t GetSizeInBytes() const { return mSizeInBytes; }
        VkBufferUsageFlags GetUsageFlags() const { return mUsageFlags; }
        VkMemoryPropertyFlags GetMemoryPropertyFlags() const { return mMemoryPropertyFlags; }
        
    private:
        static inline std::unordered_map<VkBuffer, VulkanBuffer*> smInstanceMap;

        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkBuffer mVkBuffer = VK_NULL_HANDLE;
        VkBufferUsageFlags mUsageFlags = 0;
        VkDeviceMemory mVkDeviceMemory = VK_NULL_HANDLE;
        VkMemoryPropertyFlags mMemoryPropertyFlags = 0;
        VkDeviceSize mSizeInBytes = 0;

        VkAccessFlags mAccessFlags = 0;
        VkPipelineStageFlags mPipelineStageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        VkQueue mQueue = VK_NULL_HANDLE;

        void* mMappedData = nullptr;
        uint32_t mNumMapped = 0;
    };
}