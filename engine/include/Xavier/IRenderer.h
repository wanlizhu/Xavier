#pragma once

#include "XavierConfig.h"

namespace Xavier
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual bool Init() = 0;
        virtual void Deinit() = 0;
    };

}
