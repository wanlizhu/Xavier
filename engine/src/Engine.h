#pragma once

#include "Xavier/Config.h"
#include "Xavier/IEngine.h"
#include "Xavier/IDocument.h"
#include "Xavier/IRenderer.h"
#include "tools/CommandArguments.h"

namespace Xavier
{
    class Engine : public IEngine
    {
    public:
        Engine(int argc, char** argv);
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        virtual ~Engine();

        virtual bool IsRayTracingEnabled() const override;

        virtual IRenderer* GetRenderer() override;
        virtual IDocument* OpenDocument(const char* filename) override;
        virtual void CloseDocument(IDocument* doc) override;

    private:
        CommandArguments mArguments;
        std::unique_ptr<IRenderer> mRenderer;
        std::vector<std::unique_ptr<IDocument>> mDocuments;
    };
}