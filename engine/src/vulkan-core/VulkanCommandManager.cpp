#include "VulkanCommandManager.h"
#include "VulkanCommandBuffer.h"

namespace Xavier
{
    VulkanCommandManager* VulkanCommandManager::Instance()
    {
        static VulkanCommandManager instance;
        return &instance;
    }

    void VulkanCommandManager::Init(
        VkPhysicalDevice physicalDevice,
        VkDevice device,
        uint32_t graphicsQueueFamilyIndex,
        uint32_t computeQueueFamilyIndex
    )
    {
        Deinit();

        uint32_t count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
        
        std::vector<VkQueueFamilyProperties> properties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, properties.data());
        
        mGraphicsQueueFamilyIndex = graphicsQueueFamilyIndex;
        vkGetDeviceQueue(device, mGraphicsQueueFamilyIndex, 0, &mGraphicsQueue);

        VkCommandPoolCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.queueFamilyIndex = mGraphicsQueueFamilyIndex;

        VK_ASSERT(vkCreateCommandPool(
            device,
            &createInfo,
            nullptr,
            &mGraphicsCommandPool
        ));

        if (computeQueueFamilyIndex != UINT32_MAX)
        {
            mComputeQueueFamilyIndex = computeQueueFamilyIndex;
            vkGetDeviceQueue(device, mComputeQueueFamilyIndex, 0, &mComputeQueue);

            VkCommandPoolCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            createInfo.pNext = nullptr;
            createInfo.flags = 0;
            createInfo.queueFamilyIndex = mComputeQueueFamilyIndex;

            VK_ASSERT(vkCreateCommandPool(
                device,
                &createInfo,
                nullptr,
                &mComputeCommandPool
            ));
        }
    }

    void VulkanCommandManager::Deinit()
    {
        if (mGraphicsCommandBuffer)
        {
            mGraphicsCommandBuffer->WaitUntilCompleted();
            delete mGraphicsCommandBuffer;
            mGraphicsCommandBuffer = nullptr;
        }

        if (mGraphicsCommandPool)
        {
            vkDestroyCommandPool(
                mVkDevice,
                mGraphicsCommandPool,
                nullptr
            );
            mGraphicsCommandPool = VK_NULL_HANDLE;
        }

        mGraphicsQueueFamilyIndex = UINT32_MAX;
        mGraphicsQueue = VK_NULL_HANDLE;
        mGraphicsQueueFamilyProperties = {};

        if (mComputeCommandBuffer)
        {
            mComputeCommandBuffer->WaitUntilCompleted();
            delete mComputeCommandBuffer;
            mComputeCommandBuffer = nullptr;
        }

        if (mComputeCommandPool)
        {
            vkDestroyCommandPool(
                mVkDevice,
                mComputeCommandPool,
                nullptr
            );
            mComputeCommandPool = VK_NULL_HANDLE;
        }

        mComputeQueueFamilyIndex = UINT32_MAX;
        mComputeQueue = VK_NULL_HANDLE;
        mComputeQueueFamilyProperties = {};
    }

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
}