//
// Created by Aaron Ishibashi on 4/29/22.
//

#include "Window.h"
#include "RendererType.h"

#include <SDG/Debug.h>
#include <SDL_gpu.h>

#ifdef GetWindow
#undef GetWindow
#endif
#define GetWindow(target) SDL_GetWindowFromID(target->context->windowID)
static const SDG::Vector2 DefaultWindowSize {1280, 720};

namespace SDG
{
    struct Window::Impl {
        GPU_Target *target;
    };

    Window::Window() : impl(new Impl)
    {

    }

    Window::~Window()
    {
        Close();
        delete impl;
    }

    bool
    Window::Initialize()
    {
        Close(); // Make sure to initialize cleanly

        GPU_Target *target = GPU_InitRenderer(RendererType,
                                              DefaultWindowSize.w,
                                              DefaultWindowSize.h,
                                              0);
        if (!target)
        {
            SDG_Err("Failed to initialize SDL_gpu GPU_Target: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
            return false;
        }

        // Will be using the camera feature
        GPU_EnableCamera(target, true);

        impl->target = target;
        return true;
    }

    void
    Window::Close()
    {
        if (impl->target)
        {
            GPU_FreeTarget(impl->target);
            impl->target = nullptr;
        }
    }

    void
    Window::SwapBuffers()
    {
        GPU_Flip(impl->target);
    }

    void
    Window::Clear(Color color)
    {
        GPU_ClearColor(impl->target, SDL_Color {color.r, color.g, color.b, color.a});
    }

    /// ======= SETTERS =========

    Window &
    Window::Title(const char *title)
    {
        SDL_SetWindowTitle(GetWindow(impl->target), title);
        return *this;
    }

    Window &
    Window::Size(Point size)
    {
        SDL_SetWindowSize(GetWindow(impl->target), size.w, size.h);
        return *this;
    }

    Window &Window::Fullscreen(bool fullscreen)
    {
        GPU_SetFullscreen(fullscreen, SDG_TARGET_DESKTOP);
        return *this;
    }

    Window &
    Window::SetCamera(const Camera &camera)
    {
        GPU_SetCamera(impl->target, camera.InnerCamera());
        return *this;
    }

    /// ========= GETTERS ========

    const char *
    Window::Title() const
    {
        return SDL_GetWindowTitle(GetWindow(impl->target));
    }

    Point
    Window::Size() const
    {
        return Point {
            impl->target->context->window_w,
            impl->target->context->window_h
        };
    }

    bool
    Window::Fullscreen() const
    {
        return GPU_GetFullscreen();
    }

    GPU_Target *
    Window::InnerWindow()
    {
        return impl->target;
    }


}