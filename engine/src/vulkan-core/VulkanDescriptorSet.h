#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanDescriptorSet
    {
    public:
        VulkanDescriptorSet(
            VkDevice device,
            VkDescriptorPool pool,
            VkDescriptorSetLayout layout
        );
        VulkanDescriptorSet(const VulkanDescriptorSet&) = delete;
        VulkanDescriptorSet& operator=(const VulkanDescriptorSet&) = delete;
        virtual ~VulkanDescriptorSet();

        void BindResource(const char* name, std::vector<VkBuffer> const& buffers);
        void BindResource(const char* name, std::vector<VkImage> const& images);
        void BindResource(const char* name, std::vector<VkSampler> const& samplers);

        VkDescriptorSet GetHandle() const { return mVkDescriptorSet; }
        VkDescriptorSetLayout GetLayoutHandle() const { return mVkDescriptorSetLayout; }

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkDescriptorPool mVkDescriptorPool = VK_NULL_HANDLE;
        VkDescriptorSet mVkDescriptorSet = VK_NULL_HANDLE;
        VkDescriptorSetLayout mVkDescriptorSetLayout = VK_NULL_HANDLE;

        std::unordered_set<std::shared_ptr<VulkanBuffer>> mBoundBuffers;
        std::unordered_set<std::shared_ptr<VulkanImage>>  mBoundImages;
    };
}