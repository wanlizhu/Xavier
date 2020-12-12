#include "VulkanBuffer.h"
#include "VulkanImage.h"

namespace Xavier
{
    VulkanBuffer::VulkanBuffer(
        VkDevice device,
        size_t size,
        VkBufferUsageFlags usageFlags,
        VkMemoryPropertyFlags memoryPropertyFlags
    )
        : mVkDevice(device)
        , mSizeInBytes(size)
        , mUsageFlags(usageFlags)
    {
        VkBufferCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createInfo.usage = mUsageFlags;
        createInfo.size = mSizeInBytes;
        createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VK_ASSERT(vkCreateBuffer(
            mVkDevice, 
            &createInfo,
            nullptr, 
            &mVkBuffer
        ));

        VkMemoryRequirements memoryReq = {};
        vkGetBufferMemoryRequirements(mVkDevice, mVkBuffer, &memoryReq);

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
        VK_ASSERT(vkBindBufferMemory(
            mVkDevice, 
            mVkBuffer,
            mVkDeviceMemory, 
            0
        ));
    }
    
    VulkanBuffer::~VulkanBuffer()
    {
        UnMap();

        if (mVkDeviceMemory)
        {
            vkFreeMemory(mVkDevice, mVkDeviceMemory, nullptr);
            mVkDeviceMemory = VK_NULL_HANDLE;
        }

        if (mVkBuffer)
        {
            vkDestroyBuffer(mVkDevice, mVkBuffer, nullptr);
            mVkBuffer = VK_NULL_HANDLE;
        }
    }

    uint8_t* VulkanBuffer::Map()
    {
        if (mMappedData)
        {
            mNumMapped += 1;
            return reinterpret_cast<uint8_t*>(mMappedData);
        }

        VK_ASSERT(vkMapMemory(
            mVkDevice, 
            mVkDeviceMemory,
            0, 
            VK_WHOLE_SIZE,
            0,
            &mMappedData
        ));
        assert(mMappedData != nullptr);

        mNumMapped = 1;
        return reinterpret_cast<uint8_t*>(mMappedData);
    }

    void VulkanBuffer::UnMap()
    {
        if (--mNumMapped == 0)
        {
            vkUnmapMemory(mVkDevice, mVkDeviceMemory);
            mMappedData = nullptr;
        }
    }

    void VulkanBuffer::InsertMemoryBarrier(
        VkCommandBuffer commandBuffer,
        VkAccessFlags newAccess,
        VkPipelineStageFlags newStage
    )
    {
        VkBufferMemoryBarrier bufferBarrier = {};
        bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
        bufferBarrier.buffer = mVkBuffer;
        bufferBarrier.offset = 0;
        bufferBarrier.size = VK_WHOLE_SIZE;
        bufferBarrier.srcAccessMask = mAccessFlags;
        bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        bufferBarrier.dstAccessMask = newAccess;
        bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

        vkCmdPipelineBarrier(
            commandBuffer,
            mPipelineStageFlags, 
            newStage,
            0,                  // VkDependencyFlags
            0, nullptr,         // VkMemoryBarrier
            1, &bufferBarrier,  // VkBufferMemoryBarrier
            0, nullptr          // VkImageMemoryBarrier
        );

        mAccessFlags = newAccess;
        mPipelineStageFlags = newStage;
    }
}