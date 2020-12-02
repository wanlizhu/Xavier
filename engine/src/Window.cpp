#include "Window.h"
#include "VulkanRenderer.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace Xavier
{
    Window::Window()
    {
        smNumWindow += 1;
    }

    Window::~Window()
    {
        Close();
        
        smNumWindow -= 1;
        if (smNumWindow == 0)
        {
            glfwTerminate();
        }
    }

    bool Window::Open(
        const std::string& title,
        int width,
        int height,
        bool centralize,
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
            title.c_str(),
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
            glfwSetWindowRefreshCallback(mWindow, &Window::OnRefresh);
            glfwSetMouseButtonCallback(mWindow, &Window::OnMouseButton);
            glfwSetCursorPosCallback(mWindow, &Window::OnMousePos);
            glfwSetKeyCallback(mWindow, &Window::OnKey);
        }

        if (centralize)
        {
            std::array<int, 2> size = ScreenSizeInPixels();
            int posx = (size[0] - width) * 0.5;
            int posy = (size[1] - height) * 0.5;
            glfwSetWindowPos(mWindow, posx, posy);
        }

        return true;
    }

    void Window::Close()
    {
        if (mWindow)
        {
            glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
            glfwDestroyWindow(mWindow);
            mWindow = nullptr;
        }
    }

    void Window::MessageLoop()
    {
        assert(mResizeCallback != nullptr);
        assert(mRenderCallback != nullptr);

        while (!glfwWindowShouldClose(mWindow))
        {
            glfwPollEvents();
        }

        Close();
    }

    void Window::SetRenderCallback(PFN_OnRender renderFunc)
    {
        mRenderCallback = renderFunc;
    }

    void Window::SetResizeCallback(PFN_OnResize resizeFunc)
    {
        mResizeCallback = resizeFunc;
    }

    void* Window::GetNativeHandle() const
    {
#ifdef _WIN32
        return (void*)glfwGetWin32Window(mWindow);
#else
        return (void*)glfwGetCocoaWindow(mWindow);
#endif
    }

    void Window::OnRefresh(GLFWwindow* handle)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        win->mRenderCallback();
    }

    void Window::OnFramebufferSize(GLFWwindow* handle, int w, int h)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
        win->mResizeCallback();
    }

    void Window::OnMouseButton(GLFWwindow* handle, int button, int action, int mods)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
    }

    void Window::OnMousePos(GLFWwindow* handle, double xpos, double ypos)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
    }

    void Window::OnKey(GLFWwindow* handle, int key, int scancode, int action, int mods)
    {
        auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
    }

    std::array<int, 2> ScreenSizeInPixels()
    {
        assert(glfwInit() == GLFW_TRUE);

        auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        return {videoMode->width, videoMode->height};
    }
}
