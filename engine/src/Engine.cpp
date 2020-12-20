#include "Engine.h"
#include "Document.h"
#include "VulkanRenderer.h"
#include "Window.h"

namespace Xavier
{
    IEngine* AllocateEngine(int argc, char** argv)
    {
        return new Engine(argc, argv);
    }

    void FreeEngine(IEngine* engine)
    {
        delete engine;
    }

    Engine::Engine(int argc, char** argv)
        : mArguments(argc, argv)
    {
        mRenderer.reset(new VulkanRenderer());
    }

    Engine::~Engine()
    {
        for (auto& doc : mDocuments)
            doc = nullptr;
        mDocuments.clear();

        mRenderer->Deinit();
        mRenderer = nullptr;
    }

    bool Engine::IsRayTracingEnabled() const
    {
        return mArguments.IsOption("--raytracing");
    }

    IRenderer* Engine::GetRenderer()
    {
        return mRenderer.get();
    }

    IDocument* Engine::OpenDocument(const char* filename)
    {
        mDocuments.emplace_back(new Document(filename));
        return mDocuments.back().get();
    }

    void Engine::CloseDocument(IDocument* doc)
    {
        for (auto& docptr : mDocuments)
        {
            if (docptr.get() == doc)
            {
                std::swap(docptr, mDocuments.back());
                mDocuments.pop_back();
                break;
            }
        }
    }
}