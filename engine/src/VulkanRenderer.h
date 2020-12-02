#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#else
#error "unsupported platform"
#endif
#include "vulkan/vulkan.h"
#include "Xavier/IRenderer.h"

namespace Xavier
{
    class VulkanRenderer : public IRenderer
    {
    public:
        VulkanRenderer() = default;
        VulkanRenderer(const VulkanRenderer&) = delete;
        VulkanRenderer& operator=(const VulkanRenderer&) = delete;
        virtual ~VulkanRenderer();

        virtual bool Init() override;
        virtual void Deinit() override;

        virtual void CreateSwapChain(void* window) override;

        virtual void ClearColor(Color color) override;
        virtual void ClearDS(float depth, uint8_t stencil) override;

        virtual void Present() override;
        virtual void Resize() override;

    private:
        void CreateVulkanInstance();
        void CreateVulkanDevice();

    private:
        VkInstance mVkInstance = VK_NULL_HANDLE;
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;
        uint32_t mGraphicsQueueFamilyIndex = UINT32_MAX;
        uint32_t mTransferQueueFamilyIndex = UINT32_MAX;
        uint32_t mComputeQueueFamilyIndex = UINT32_MAX;
        uint32_t mPresentQueueFamilyIndex = UINT32_MAX;

        void* mSwapchainWindow = nullptr;
        VkSurfaceKHR   mVkSurface = VK_NULL_HANDLE;
        VkSwapchainKHR mVkSwapchain = VK_NULL_HANDLE;
        uint32_t mSwapchainImageIndex = UINT32_MAX;
        std::vector<VkImage>     mSwapchainImages;
        std::vector<VkImageView> mSwapchainImageViews;


    };
}
