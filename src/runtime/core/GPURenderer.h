#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class GPURenderer : public IRenderer
    {
    public:
        GPURenderer() = default;
        GPURenderer(const GPURenderer&) = delete;
        GPURenderer& operator=(const GPURenderer&) = delete;
        virtual ~GPURenderer();


    };
}
