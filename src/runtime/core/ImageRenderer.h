#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class ImageRenderer : public IRenderer
    {
    public:
        ImageRenderer() = default;
        ImageRenderer(const ImageRenderer&) = delete;
        ImageRenderer& operator=(const ImageRenderer&) = delete;
        virtual ~ImageRenderer();


    };
}