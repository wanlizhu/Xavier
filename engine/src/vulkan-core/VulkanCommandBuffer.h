#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanBuffer;
    class VulkanImage;

    class VulkanCommandBuffer
    {
        friend class VulkanCommandManager;
    public:
        enum class Status
        {
            Initial,
            Recording,
            Executable,
            Pending,
            Invalid
        };

        VulkanCommandBuffer(
            VkDevice device,
            VkQueue queue, 
            VkCommandPool pool,
            VkCommandBufferLevel level
        );
        VulkanCommandBuffer(const VulkanCommandBuffer&) = delete;
        VulkanCommandBuffer& operator=(const VulkanCommandBuffer&) = delete;
        virtual ~VulkanCommandBuffer(); 

        void CmdClearColorImage(
            VkImage image,
            VkClearColorValue clearColor
        );
        void CmdClearDepthStencilImage(
            VkImage image,
            VkClearDepthStencilValue clearDS
        );

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

        void CmdPipelineBarrier(
            VkPipelineStageFlags oldStageFlags,
            VkPipelineStageFlags newStageFlags,
            VkAccessFlags oldAccessFlags,
            VkAccessFlags newAccessFlags
        );
        void CmdPipelineBarrier(
            VkPipelineStageFlags oldStageFlags,
            VkPipelineStageFlags newStageFlags,
            VkAccessFlags oldAccessFlags,
            VkAccessFlags newAccessFlags,
            VkQueue  oldQueue,
            VkQueue  newQueue,
            VkBuffer buffer
        );
        void CmdPipelineBarrier(
            VkPipelineStageFlags oldStageFlags,
            VkPipelineStageFlags newStageFlags,
            VkAccessFlags oldAccessFlags,
            VkAccessFlags newAccessFlags,
            VkQueue oldQueue,
            VkQueue newQueue,
            VkImageLayout oldLayout,
            VkImageLayout newLayout,
            VkImage image
        );

        void CmdBeginRenderPass(
            VkFramebuffer framebuffer,
            VkRenderPass renderPass,
            std::vector<VkClearColorValue> const& clearColors,
            std::optional<VkClearDepthStencilValue> clearDS
        );
        void CmdEndRenderPass();
        void CmdBindPipeline(
            VkPipelineBindPoint bindPoint,
            VkPipeline pipeline
        );
        void CmdBindDescriptorSets(
            VkPipelineBindPoint bindPoint,
            std::unordered_map<uint32_t, VkDescriptorSet> const& descriptorSets
        );
        void CmdBindVertexBuffers(
            std::unordered_map<uint32_t, VkBuffer> const& vertexBuffers,
            std::unordered_map<uint32_t, size_t> const&   vertexOffsets
        );
        void CmdBindIndexBuffer(
            VkBuffer indexBuffer,
            size_t   offset,
            VkIndexType indexType
        );
        void CmdSetViewport(
            std::vector<VkViewport> const& viewport
        );
        void CmdSetScissors(
            std::vector<VkRect2D> const& scissor
        );
        void CmdDraw(
            uint32_t vertexCount,
            uint32_t instanceCount,
            uint32_t firstVertex,
            uint32_t firstInstance
        );
        void CmdDrawIndexed(
            uint32_t indexCount,
            uint32_t instanceCount,
            uint32_t firstIndex,
            uint32_t firstVertex,
            uint32_t firstInstance
        );

    private:
        void Begin();
        void End();
        void Reset();
        void Submit(
            VkSemaphore  waitSemaphore,
            VkSemaphore* signalSemaphore
        );

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkQueue  mVkQueue = VK_NULL_HANDLE;
        VkCommandPool   mVkCommandPool = VK_NULL_HANDLE;
        VkCommandBuffer mVkCommandBuffer = VK_NULL_HANDLE;
        VkSemaphore mVkSemaphore = VK_NULL_HANDLE;
        VkFence mVkFence = VK_NULL_HANDLE;

        Status mStatus = Status::Initial;

        std::unordered_set<std::shared_ptr<VulkanBuffer>> mBoundBuffers;
        std::unordered_set<std::shared_ptr<VulkanImage>>  mBoundImages;
    };
}