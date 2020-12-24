#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanSwapChain
    {
    public:
        VulkanSwapChain(
            VkDevice device,
            VkSurfaceKHR surface
        );
        VulkanSwapChain(const VulkanSwapChain&) = delete;
        VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
        virtual ~VulkanSwapChain();

        void Resize();
        void Present(std::vector<VkSemaphore> const& semaphoresToWait);

        VkSwapchainKHR GetHandle() const { return mVkSwapchain; }
        VkExtent2D GetExtent() const { return mImageExtent; }
        VkImage GetBackImage() const { assert(mImageIndex != UINT32_MAX); return mImages[mImageIndex]; }
        VkImageView GetBackImageView() const { assert(mImageIndex != UINT32_MAX); return mImageViews[mImageIndex]; }
        VkSemaphore GetImageAvailableSemaphore() const { assert(mImageIndex != UINT32_MAX); return mImageSemaphores[mImageIndex]; }

    private:
        void Destroy();
        void Recreate();
        void AcquireNextImage();

    private:
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkSurfaceKHR mVkSurface = VK_NULL_HANDLE;
        VkSwapchainKHR mVkSwapchain = VK_NULL_HANDLE;

        uint32_t   mMinImageCount = 3;
        VkExtent2D mImageExtent = { UINT32_MAX, UINT32_MAX };

        uint32_t mImageIndex = UINT32_MAX;
        std::vector<VkImage>     mImages;
        std::vector<VkImageView> mImageViews;
        std::vector<VkSemaphore> mImageSemaphores;
    };
}