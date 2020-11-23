#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class RasterRenderer : public IRasterRenderer
    {
    public:
        RasterRenderer() = default;
        RasterRenderer(const RasterRenderer&) = delete;
        RasterRenderer& operator=(const RasterRenderer&) = delete;
        virtual ~RasterRenderer();


    };
}