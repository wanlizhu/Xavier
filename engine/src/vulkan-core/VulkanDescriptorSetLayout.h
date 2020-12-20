#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanDescriptorSetLayout
    {
    public:
        static VulkanDescriptorSetLayout* Instance(VkDescriptorSetLayout handle);

        VulkanDescriptorSetLayout(
            VkDevice device,
            std::unordered_map<std::string, VkDescriptorSetLayoutBinding> const& bindings
        );
        VulkanDescriptorSetLayout(const VulkanDescriptorSetLayout&) = delete;
        VulkanDescriptorSetLayout& operator=(const VulkanDescriptorSetLayout&) = delete;
        virtual ~VulkanDescriptorSetLayout();

        VkDescriptorSetLayout GetHandle() const { return mVkDescriptorSetLayout; }
        VkDescriptorSetLayoutBinding const& GetBinding(const char* name) const { return mBindings.at(name); }

    private:
        static inline std::unordered_map<VkDescriptorSetLayout, VulkanDescriptorSetLayout> smInstanceMap;

        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkDescriptorSetLayout mVkDescriptorSetLayout = VK_NULL_HANDLE;

        std::unordered_map<std::string, VkDescriptorSetLayoutBinding> mBindings;
    };
}