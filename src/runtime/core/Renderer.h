#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class Renderer : public IRenderer
    {
    public:
        Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        virtual ~Renderer();


    };
}