#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class RaytracingRenderer : public IRaytracingRenderer
    {
    public:
        RaytracingRenderer() = default;
        RaytracingRenderer(const RaytracingRenderer&) = delete;
        RaytracingRenderer& operator=(const RaytracingRenderer&) = delete;
        virtual ~RaytracingRenderer();


    };
}