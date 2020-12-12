#pragma once

#include "vulkan/vulkan.h"
#include "Xavier/Config.h"

#define VK_ASSERT(result) if (result != VK_SUCCESS) throw std::runtime_error("vulkan call failed")

namespace Xavier
{
    uint32_t GetMemoryTypeIndex(
        VkDevice device,
        VkMemoryPropertyFlags requiredFlags,
        VkMemoryPropertyFlags* finalFlags
    );

    VkImageAspectFlags GetImageAspectFlags(VkFormat format);
}