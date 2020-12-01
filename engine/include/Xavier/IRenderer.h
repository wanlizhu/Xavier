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

        virtual void ClearColor(Color color) = 0;
        virtual void ClearDS(float depth, uint8_t stencil) = 0;

        virtual void Present() = 0;
        virtual void Resize() = 0;
    };

}
