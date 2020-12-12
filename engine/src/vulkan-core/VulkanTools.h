#pragma once

#include "vulkan/vulkan.h"
#include "Xavier/Config.h"

#define VK_ASSERT(result) if (result != VK_SUCCESS) throw std::runtime_error("vulkan call failed")

namespace Xavier
{
    template<typename T>
    class REF
    {
    public:
        REF() = default;
        REF(VkDevice device, T handle) : mDevice(device), mHandle(handle) { AddRef(); }
        REF(std::nullopt_t) { DelRef(); }
        virtual ~REF() { DelRef(); }

        operator T() const { return mHandle; }

    private:
        void AddRef()
        {
            if (mHandle != VK_NULL_HANDLE)
            {

            }
        }

        void DelRef()
        {
            if (mHandle != VK_NULL_HANDLE)
            {

            }
        }

    private:
        VkDevice mDevice = VK_NULL_HANDLE;
        T mHandle = VK_NULL_HANDLE;

        static inline std::unordered_map<T, uint32_t> smReferences;
    };

    uint32_t GetMemoryTypeIndex(
        VkDevice device,
        VkMemoryPropertyFlags requiredFlags,
        VkMemoryPropertyFlags* finalFlags
    );

    VkImageAspectFlags GetImageAspectFlags(VkFormat format);
}