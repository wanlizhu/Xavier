#include "Document.h"
#include "Window.h"
#include <filesystem>

namespace Xavier
{
    Document::Document(const std::string& path)
        : mFilePath(path)
    {
        
    }

    Document::~Document()
    {
        mWindow.reset();

    }

    void Document::OpenWindow()
    {
        CloseWindow();

        mWindow.reset(new Window());
        mWindow->SetRenderCallback([this]() { OnRender(); });
        mWindow->SetResizeCallback([this]() { OnResize(); });
        mWindow->Open(
            std::filesystem::path(mFilePath).stem().string(), 
            ScreenSizeInPixels()[0] * 0.707,
            ScreenSizeInPixels()[1] * 0.707,
            true,
            true,
            true
        );

        mRenderer->CreateSwapChain(mWindow->GetNativeHandle());
        mRenderer->ClearColor(Color(1, 0, 0));
    }

    void Document::CloseWindow()
    {
        if (!mWindow)
            return;

        mWindow->Close();
        mWindow.reset();
    }

    void Document::WaitUntilWindowClosed()
    {
        if (!mWindow)
            return;

        mWindow->MessageLoop();
    }

    void Document::SetRenderer(IRenderer* renderer)
    {
        mRenderer = renderer;
    }

    void Document::RunRayTracing(
        const char* outFile,
        PFN_OnProgress progressFunc,
        PFN_OnError errorFunc
    )
    {}

    void Document::OnRender()
    {
        printf("render\n");
        //TODO
        mRenderer->Present();
    }

    void Document::OnResize()
    {
        printf("resize\n");
        mRenderer->Resize();
    }
}