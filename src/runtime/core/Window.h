#pragma once

#include "XavierConfig.h"

struct GLFWwindow;

namespace Xavier
{
    class ImageRenderer;

    class Window
    {
    public:
        Window();
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
        void  ClearFramebuffer(float r, float g, float b);
        void  UpdateFramebuffer(
            unsigned char* pixels,
            int width,
            int height,
            EPixelFormat format
        );

    private:
        GLFWwindow* mWindow = nullptr;
        std::unique_ptr<ImageRenderer> mImageRenderer;
    };
};