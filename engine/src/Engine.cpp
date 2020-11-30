#include "Engine.h"

namespace Xavier
{
    IEngine* AllocateEngine()
    {
        return new Engine();
    }

    void FreeEngine(IEngine* engine)
    {
        if (engine)
            delete engine;
    }

    Engine::~Engine()
    {}

    bool Engine::Init()
    {
        return true;
    }

    void Engine::Deinit()
    {}

    IRenderer* Engine::GetRenderer()
    {
        return nullptr;
    }

    IDocument* Engine::OpenDocument(const char* filename)
    {
        return nullptr;
    }

    void Engine::CloseDocument(IDocument* doc)
    {}
}