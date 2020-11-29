#pragma once

#include "XavierConfig.h"

struct GLFWwindow;

namespace Xavier
{
    class Window
    {
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        virtual ~Window();

        bool Open(
            const char* title,
            int posx,
            int posy,
            int width,
            int height,
            bool resizable,
            bool interactive
        );
        void Close();

        void* GetNativeHandle() const;

    private:
        static void OnFramebufferSize(GLFWwindow* handle, int w, int h);
        static void OnMouseButton(GLFWwindow* handle, int button, int action, int mods);
        static void OnMousePos(GLFWwindow* handle, double xpos, double ypos);
        static void OnKey(GLFWwindow* handle, int key, int scancode, int action, int mods);

    private:
        GLFWwindow* mWindow = nullptr;
    };
};