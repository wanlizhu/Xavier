#pragma once

#include "XavierConfig.h"
#include "IEngine.h"
#include "IDocument.h"
#include "IRenderer.h"

namespace Xavier
{
    class Engine : public IEngine
    {
    public:
        Engine() = default;
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        virtual ~Engine();

        virtual bool Init() override;
        virtual void Deinit() override;

        virtual IRenderer* GetRenderer(const char* name) override;
        virtual IDocument* OpenDocument(const char* filename) override;
        virtual void CloseDocument(IDocument* doc) override;
    };
}