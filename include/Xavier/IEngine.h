#pragma once

#include "IDocument.h"
#include "IRenderer.h"

namespace Xavier
{
    class IEngine
    {
    public:
        virtual ~IEngine() = default;
        virtual bool Init() = 0;
        virtual void Deinit() = 0;

        virtual IRenderer* GetRenderer() = 0;
        virtual IDocument* OpenDocument(const char* filename) = 0;
        virtual void CloseDocument(IDocument* doc) = 0;
    };

    IEngine* AllocateEngine();
    void FreeEngine(IEngine* engine);
}
