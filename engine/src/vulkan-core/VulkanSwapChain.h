#pragma once

#include "VulkanTools.h"

namespace Xavier
{
    class VulkanSwapChain
    {
    public:
        VulkanSwapChain(
            VkDevice device,
            void* window
        );
        VulkanSwapChain(const VulkanSwapChain&) = delete;
        VulkanSwapChain& operator=(const VulkanSwapChain&) = delete;
        virtual ~VulkanSwapChain();

        void Resize();
        void Present();

        VkSurfaceKHR GetSurface() const { return mVkSurface; }
        VkSwapchainKHR GetHandle() const { return mVkSwapchain; }
        VkExtent2D GetExtent() const { return mImageExtent; }
        VkImage GetBackImage() const { assert(mImageIndex != UINT32_MAX); return mImages[mImageIndex]; }
        VkImageView GetBackImageView() const { assert(mImageIndex != UINT32_MAX); return mImageViews[mImageIndex]; }
        VkSemaphore GetBackImageSemaphore() const { assert(mImageIndex != UINT32_MAX); return mImageSemaphores[mImageIndex]; }

    private:
        void Destroy();
        void Recreate();
        void AcquireNextImage();
        void SyncedPresent(const VkSemaphore* semaphores, uint32_t count);

    private:
        void* mWindowHandle = nullptr;
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkSurfaceKHR   mVkSurface = VK_NULL_HANDLE;
        VkSwapchainKHR mVkSwapchain = VK_NULL_HANDLE;

        uint32_t   mMinImageCount = 3;
        VkExtent2D mImageExtent = { UINT32_MAX, UINT32_MAX };

        uint32_t mImageIndex = UINT32_MAX;
        Array<VkImage>     mImages;
        Array<VkImageView> mImageViews;
        Array<VkSemaphore> mImageSemaphores;
    };
}