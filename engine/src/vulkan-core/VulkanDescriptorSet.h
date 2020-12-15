#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanDescriptorSet
    {
    public:
        VulkanDescriptorSet();
        VulkanDescriptorSet(const VulkanDescriptorSet&) = delete;
        VulkanDescriptorSet& operator=(const VulkanDescriptorSet&) = delete;
        virtual ~VulkanDescriptorSet();

        void BindResource(const char* name, std::vector<VkBuffer> const& buffers);
        void BindResource(const char* name, std::vector<VkImage> const& images);
        void BindResource(const char* name, std::vector<VkSampler> const& samplers);

    private:

    };
}