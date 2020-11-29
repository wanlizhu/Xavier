#pragma once

#include "IRenderer.h"

namespace Xavier
{
    class IDocument
    {
    public:
        virtual ~IDocument() = default;
        virtual bool IsValid() const = 0;
        virtual void OpenWindow() = 0;
        virtual void CloseWindow() = 0;
        virtual void Render(
            const char* outFile,
            IRenderer* renderer, 
            PFN_OnProgress progressFunc, 
            PFN_OnError errorFunc
        ) = 0;
    };
}
