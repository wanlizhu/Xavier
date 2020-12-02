#include "VulkanRenderer.h"

namespace Xavier
{
    VulkanRenderer::~VulkanRenderer()
    {
        Deinit();
    }

    bool VulkanRenderer::Init()
    {

        return true;
    }

    void VulkanRenderer::Deinit()
    {
        
    }

    void VulkanRenderer::CreateSwapChain(void* window)
    {
        
    }

    void VulkanRenderer::ClearColor(Color color)
    {}

    void VulkanRenderer::ClearDS(float depth, uint8_t stencil)
    {}

    void VulkanRenderer::Present()
    {}

    void VulkanRenderer::Resize()
    {}
}
