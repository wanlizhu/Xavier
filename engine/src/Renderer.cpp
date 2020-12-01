#include "Renderer.h"

namespace Xavier
{
    Renderer::~Renderer()
    {
        Deinit();
    }

    bool Renderer::Init()
    {
        return true;
    }

    void Renderer::Deinit()
    {
        
    }

    void Renderer::CreateSwapChain(void* window)
    {
        
    }

    void Renderer::ClearColor(Color color)
    {}

    void Renderer::ClearDS(float depth, uint8_t stencil)
    {}

    void Renderer::Present()
    {}

    void Renderer::Resize()
    {}
}
