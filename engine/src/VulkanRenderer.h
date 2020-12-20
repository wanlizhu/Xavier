#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(__APPLE__)
#define VK_USE_PLATFORM_MACOS_MVK
#else
#error "unsupported platform"
#endif
#include "vulkan/vulkan.h"
#include "Xavier/IRenderer.h"

namespace Xavier
{
    class VulkanBuffer;
    class VulkanImage;
    class VulkanEffect;
    class VulkanDescriptorSet;
    class VulkanRenderPass;
    class VulkanCommandBuffer;
    class VulkanCommandManager;
    class VulkanSwapChain;

    class VulkanRenderer : public IRenderer
    {
    public:
        VulkanRenderer() = default;
        VulkanRenderer(const VulkanRenderer&) = delete;
        VulkanRenderer& operator=(const VulkanRenderer&) = delete;
        virtual ~VulkanRenderer();

        virtual bool Init(void* window) override;
        virtual void Deinit() override;

        virtual void CreateBuffer(const char* name, const VulkanBufferCreateInfo& info) override;
        virtual void CreateImage(const char* name, const VulkanImageCreateInfo& info) override;
        virtual void CreateRenderPass(const char* name, const VulkanRenderPassCreateInfo& info) override;
        virtual void CreateEffect(const char* name, const VulkanEffectCreateInfo& info) override;

        virtual void ClearColor(Color color) override;
        virtual void ClearDS(float depth, uint8_t stencil) override;
        virtual void BeginRenderPass(const char* name) override;
        virtual void BeginEffect(const char* name) override;
        virtual void EndRenderPass() override;
        virtual void EndEffect() override;
        virtual void UpdateEffectParameter(const char* name, void* data) override;

        virtual void Present() override;
        virtual void Resize() override;

    private:
        void CreateVulkanInstance();
        void CreateSurface(void* window);
        void CreateVulkanDevice();

    private:
        VkInstance mVkInstance = VK_NULL_HANDLE;
        VkSurfaceKHR mVkSurface = VK_NULL_HANDLE;
        VkPhysicalDevice mVkPhysicalDevice = VK_NULL_HANDLE;
        VkDevice mVkDevice = VK_NULL_HANDLE;
        VkPipelineCache mPipelineCache = VK_NULL_HANDLE;
        uint32_t mGraphicsQueueFamilyIndex = UINT32_MAX;
        uint32_t mTransferQueueFamilyIndex = UINT32_MAX;
        uint32_t mComputeQueueFamilyIndex = UINT32_MAX;
        uint32_t mPresentQueueFamilyIndex = UINT32_MAX;

        std::string mEffectName;
        std::string mRenderPassName;

        std::unordered_map<std::string, std::shared_ptr<VulkanEffect>> mEffects;
        std::unordered_map<std::string, std::shared_ptr<VulkanRenderPass>> mRenderPasses;
        std::unordered_map<std::string, std::shared_ptr<VulkanBuffer>> mBuffers;
        std::unordered_map<std::string, std::shared_ptr<VulkanImage>> mImages;
        std::unordered_map<std::string, std::shared_ptr<VulkanDescriptorSet>> mDescriptorSets;
        std::shared_ptr<VulkanSwapChain> mSwapChain;
        std::shared_ptr<VulkanCommandManager> mCommandManager;
    };
}
