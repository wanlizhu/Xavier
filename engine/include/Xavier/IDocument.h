#pragma once

#include "Xavier/Config.h"
#include "Xavier/IRenderer.h"

namespace Xavier
{
    class IDocument
    {
    public:
        virtual ~IDocument() = default;
        virtual void OpenWindow() = 0;
        virtual void CloseWindow() = 0;
        virtual void WaitUntilWindowClosed() = 0;
        virtual void SetRenderer(IRenderer* renderer) = 0;
        virtual void RunRayTracing(
            const char* outFile,
            PFN_OnProgress progressFunc, 
            PFN_OnError errorFunc
        ) = 0;
    };
}
