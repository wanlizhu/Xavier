#pragma once

#include "Xavier/IDocument.h"

namespace Xavier
{
    class Window;

    class Document : public IDocument
    {
    public:
        Document(const std::string& path);
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;
        virtual ~Document();

        virtual void OpenWindow() override;
        virtual void CloseWindow() override;
        virtual void WaitUntilWindowClosed() override;
        virtual void SetRenderer(IRenderer* renderer) override;
        virtual void RunRayTracing(
            const char* outFile,
            PFN_OnProgress progressFunc,
            PFN_OnError errorFunc
        ) override;

    private:
        void OnRender();
        void OnResize();

    private:
        std::string mFilePath;
        std::unique_ptr<Window> mWindow;
        IRenderer* mRenderer = nullptr;
    };
}