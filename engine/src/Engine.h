#pragma once

#include "Xavier/Config.h"
#include "Xavier/IEngine.h"
#include "Xavier/IDocument.h"
#include "Xavier/IRenderer.h"

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

        virtual IRenderer* GetRenderer() override;
        virtual IDocument* OpenDocument(const char* filename) override;
        virtual void CloseDocument(IDocument* doc) override;

    private:
        std::unique_ptr<IRenderer> mRenderer;
        std::vector<std::unique_ptr<IDocument>> mDocuments;
    };
}