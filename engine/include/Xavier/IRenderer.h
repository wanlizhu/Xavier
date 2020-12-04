#pragma once

#include "Xavier/Config.h"

namespace Xavier
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual bool Init() = 0;
        virtual void Deinit() = 0;

        virtual void CreateSwapChain(void* window) = 0;
        virtual void CreateBuffer(const char* name, const VulkanBufferCreateInfo& info) = 0;
        virtual void CreateImage(const char* name, const VulkanImageCreateInfo& info) = 0;
        virtual void CreateRenderPass(const char* name, const VulkanRenderPassCreateInfo& info) = 0;
        virtual void CreateEffect(const char* name, const VulkanEffectCreateInfo& info) = 0;

        virtual void ClearColor(Color color) = 0;
        virtual void ClearDS(float depth, uint8_t stencil) = 0;
        virtual void BeginRenderPass(const char* name) = 0;
        virtual void BeginEffect(const char* name) = 0;
        virtual void EndRenderPass() = 0;
        virtual void EndEffect() = 0;
        virtual void UpdateEffectParameter(const char* name, void* data) = 0;

        virtual void Present() = 0;
        virtual void Resize() = 0;
    };

}
