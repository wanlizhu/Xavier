#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class GPURaytracingRenderer : public IRenderer
    {
    public:
        GPURaytracingRenderer() = default;
        GPURaytracingRenderer(const GPURaytracingRenderer&) = delete;
        GPURaytracingRenderer& operator=(const GPURaytracingRenderer&) = delete;
        virtual ~GPURaytracingRenderer();


    };
}