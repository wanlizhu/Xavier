#pragma once

#include "XavierConfig.h"

namespace Xavier
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
    };

    class IRasterRenderer : public IRenderer
    {
    public:
        virtual ~IRasterRenderer() = default;
    };

    class IRaytracingRenderer : public IRenderer
    {
    public:
        virtual ~IRaytracingRenderer() = default;
    };
}
