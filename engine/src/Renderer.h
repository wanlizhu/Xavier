#pragma once

#include "Xavier/IRenderer.h"

namespace Xavier
{
    class Renderer : public IRenderer
    {
    public:
        Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        virtual ~Renderer();

        virtual bool Init() override;
        virtual void Deinit() override;

        virtual void CreateSwapChain(void* window) override;

        virtual void ClearColor(Color color) override;
        virtual void ClearDS(float depth, uint8_t stencil) override;

        virtual void Present() override;
        virtual void Resize() override;
    };
}
