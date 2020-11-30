#include "Window.h"
#include "Renderer.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace Xavier
{
    Window::~Window()
    {
        Close();
    }

    bool Window::Open(
        const char* title,
        int posx,
        int posy,
        int width,
        int height,
        bool resizable,
        bool interactive
    )
    {
        assert(mWindow == nullptr);
        assert(glfwInit() == GLFW_TRUE);
        assert(glfwVulkanSupported() == GLFW_TRUE);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

        mWindow = glfwCreateWindow(
            width,
            height,
            title,
            nullptr,
            nullptr
        );

        assert(mWindow != nullptr);
        glfwSetWindowUserPointer(mWindow, this);
        
        if (interactive)
        {
            if (resizable)
            {
                glfwSetFramebufferSizeCallback(mWindow, &Window::OnFramebufferSize);
            }
            glfwSetMouseButtonCallback(mWindow, &Window::OnMouseButton);
            glfwSetCursorPosCallback(mWindow, &Window::OnMousePos);
            glfwSetKeyCallback(mWindow, &Window::OnKey);
        }

        return true;
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
    }

    void* Window::GetNativeHandle() const
    {
#ifdef _WIN32
        return (void*)glfwGetWin32Window(mWindow);
#else
        return (void*)glfwGetCocoaWindow(mWindow);
#endif
    }
}
