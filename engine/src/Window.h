#pragma once

#include "Xavier/Config.h"

#define CENTER_POS_X -1
#define CENTER_POS_Y -1

struct GLFWwindow;

namespace Xavier
{
    class Window
    {
    public:
        Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        virtual ~Window();

        bool Open(
            const std::string& title,
            int width,
            int height,
            bool centralize,
            bool resizable,
            bool interactive
        );
        void Close();
        void MessageLoop();

        void SetRenderCallback(PFN_OnRender renderFunc);
        void SetResizeCallback(PFN_OnResize resizeFunc);
        void* GetNativeHandle() const;

    private:
        static void OnRefresh(GLFWwindow* handle);
        static void OnFramebufferSize(GLFWwindow* handle, int w, int h);
        static void OnMouseButton(GLFWwindow* handle, int button, int action, int mods);
        static void OnMousePos(GLFWwindow* handle, double xpos, double ypos);
        static void OnKey(GLFWwindow* handle, int key, int scancode, int action, int mods);

    private:
        static inline uint32_t smNumWindow = 0;
        GLFWwindow* mWindow = nullptr;

        PFN_OnRender mRenderCallback = nullptr;
        PFN_OnResize mResizeCallback = nullptr;
    };

    std::array<int, 2> ScreenSizeInPixels();
};