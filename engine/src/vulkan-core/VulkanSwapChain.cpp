#include "VulkanSwapChain.h"

namespace Xavier
{
    VulkanSwapChain::VulkanSwapChain(
        VkDevice device,
        void* window
    )
        : mVkDevice(device)
        , mWindowHandle(window)
    {

    }

    VulkanSwapChain::~VulkanSwapChain()
    {}

    void VulkanSwapChain::Resize()
    {}

    void VulkanSwapChain::Present()
    {}

    void VulkanSwapChain::Destroy()
    {}

    void AdjustSwapchainCreateInfo(
        VkSurfaceKHR surface,
        VkSwapchainCreateInfoKHR* createInfo
    )
    {}

    void VulkanSwapChain::Recreate()
    {
        Destroy();

#ifdef _WIN32
        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
        surfaceCreateInfo.hwnd = (HWND)mSwapchainWindow;

        VK_ASSERT(vkCreateWin32SurfaceKHR(
            mVkInstance,
            &surfaceCreateInfo,
            nullptr,
            &mVkSurface
        ));
#elif defined(__APPLE__)

#endif

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = mVkSurface;
        swapchainCreateInfo.minImageCount = 3;
        swapchainCreateInfo.imageExtent = {};
        swapchainCreateInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
        swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        swapchainCreateInfo.clipped = VK_FALSE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        AdjustSwapchainCreateInfo(
            mVkSurface,
            &swapchainCreateInfo
        );

        VK_ASSERT(vkCreateSwapchainKHR(
            mVkDevice,
            &swapchainCreateInfo,
            nullptr,
            &mVkSwapchain
        ));

        uint32_t imageCount = 0;
        VK_ASSERT(vkGetSwapchainImagesKHR(
            mVkDevice,
            mVkSwapchain,
            &imageCount,
            nullptr
        ));

        mImages.resize(imageCount);
        mImageViews.resize(imageCount);
        mImageSemaphores.resize(imageCount);
        VK_ASSERT(vkGetSwapchainImagesKHR(
            mVkDevice,
            mVkSwapchain,
            &imageCount,
            mImages.data()
        ));

        for (uint32_t i = 0; i < imageCount; i++)
        {
            VkImageViewCreateInfo imageViewCreateInfo = {};
            imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.image = mImages[i];
            imageViewCreateInfo.format = swapchainCreateInfo.imageFormat;
            imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
            imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
            imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
            imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
            imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
            imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
            imageViewCreateInfo.subresourceRange.layerCount = 1;
            imageViewCreateInfo.subresourceRange.levelCount = 1;

            VK_ASSERT(vkCreateImageView(
                mVkDevice,
                &imageViewCreateInfo,
                nullptr,
                &mImageViews[i]
            ));

            VkSemaphoreCreateInfo semaphoreCreateInfo = {};
            semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            VK_ASSERT(vkCreateSemaphore(
                mVkDevice,
                &semaphoreCreateInfo,
                nullptr,
                &mImageSemaphores[i]
            ));
        }

        AcquireNextImage();
    }

    void VulkanSwapChain::AcquireNextImage()
    {}

    void VulkanSwapChain::SyncedPresent(const VkSemaphore* semaphores, uint32_t count)
    {}
}