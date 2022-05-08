//
// Created by Aaron Ishibashi on 4/29/22.
//

#include "Window.h"
#include "RendererType.h"
#include "RenderTarget.h"

#include <SDG/Debug.hpp>
#include <SDL_gpu.h>
#include <SDL_ttf.h>

#ifdef GetWindow // Cancels some conflicts with some MSVC defines
#undef GetWindow
#endif

#define GetWindow(target) SDL_GetWindowFromID(target.Target().Get()->context->windowID)

namespace SDG
{
    struct Window::Impl {
        Impl() : target(), title() {}
        RenderTarget target;
        std::string title;
    };

    Window::Window() : impl(new Impl), On{}
    {

    }

    Window::~Window()
    {
        Close();
        delete impl;
    }

    bool
    Window::Initialize(int width, int height, const char *title, unsigned flags)
    {
        SDG_Assert(width > 0 && height > 0);
        Close(); // Make sure to initialize cleanly

        GPU_Target *target = GPU_InitRenderer(RendererType,
                                              width,
                                              height,
                                              flags);

        if (!target)
        {
            SDG_Err("Failed to initialize SDL_gpu GPU_Target: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
            return false;
        }

//        if (!TTF_WasInit())
//        {
            if (TTF_Init() != 0)
            {
                SDG_Err("Failed to initialize SDL2_ttf: {}", TTF_GetError());
                GPU_FreeTarget(target);
                GPU_Quit();
                return false;
            }
//        }

        impl->target.EmplaceTarget(Ref{target});
        if (title)
            Title(title);

        return true;
    }

    void
    Window::Close()
    {
        if (impl->target)
        {
            impl->target.Close();
            TTF_Quit();
            GPU_Quit();
        }
    }

    void
    Window::ProcessInput(void *evt)
    {
        SDL_WindowEvent &window = (*static_cast<SDL_Event *>(evt)).window;
        if (window.windowID == Id())
        {
            switch(window.event)
            {
                case SDL_WINDOWEVENT_SHOWN:
                    SDG_Log("Window was shown");
                    On.Show.Invoke();
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    SDG_Log("Window was hidden");
                    On.Hide.Invoke();
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    SDG_Log("Window was exposed");
                    On.Expose.Invoke();
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    SDG_Log("Window moved: {}, {}",
                            window.data1,
                            window.data2);
                    On.Move.Invoke(window.data1, window.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    On.Resize.Invoke(window.data1, window.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    //Resolution({event.window.data1, event.window.data2});
                    SDG_Log("Window size changed: {}, {}",
                            window.data1,
                            window.data2);
                    On.SizeChange.Invoke(window.data1, window.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    SDG_Log("Window was minimized");
                    On.Minimize.Invoke();
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    SDG_Log("Window was maximized");
                    On.Fullscreen.Invoke();
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    SDG_Log("Window was restored");
                    On.Restore.Invoke();
                    break;
                case SDL_WINDOWEVENT_ENTER: // Mouse entered the window
                    SDG_Log("Mouse entered window");
                    On.MouseEnter.Invoke();
                    break;
                case SDL_WINDOWEVENT_LEAVE: // Mouse left the window
                    SDG_Log("Mouse left window");
                    On.MouseLeave.Invoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    SDG_Log("Window gained keyboard focus");
                    On.Focus.Invoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    SDG_Log("Window lost keyboard focus");
                    On.FocusLost.Invoke();
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    SDG_Log("Window closed");
                    On.Close.Invoke();
                    break;
            }
        }
    }

    void
    Window::SwapBuffers()
    {
        impl->target.SwapBuffers();
    }

    void
    Window::Clear(Color color)
    {
       impl->target.Clear(color);
    }

    /// ======= SETTERS =========

    Window &
    Window::Title(const char *title)
    {
        impl->title = title;
        SDL_SetWindowTitle(GetWindow(impl->target), impl->title.c_str());
        return *this;
    }

    Window &
    Window::Size(Point size)
    {
        SDL_SetWindowSize(GetWindow(impl->target), size.W(), size.H());
        return *this;
    }

    Window &
    Window::Fullscreen(bool fullscreen)
    {
        bool lastFullscreen = GPU_GetFullscreen();
        GPU_SetFullscreen(fullscreen, SDG_TARGET_DESKTOP);
        if (lastFullscreen != fullscreen)
            On.SizeChange(impl->target.Size().W(), impl->target.Size().H());
        return *this;
    }

    Window &
    Window::Bordered(bool bordered)
    {
        SDL_SetWindowBordered(GetWindow(impl->target), (SDL_bool)bordered);
        return *this;
    }

    Window &
    Window::Resizable(bool resizable)
    {
        SDL_SetWindowResizable(GetWindow(impl->target), (SDL_bool)resizable);
        return *this;
    }

    Window &
    Window::Resolution(Point size)
    {
        GPU_SetWindowResolution(size.X(), size.Y());
        return *this;
    }


    /// ========= GETTERS ========

    std::string
    Window::Title() const
    {
        return impl->title;
    }

    Point
    Window::Size() const
    {
        return impl->target.Size();
    }

    bool
    Window::Fullscreen() const
    {
        return GPU_GetFullscreen();
    }

    bool
    Window::Bordered() const
    {
        return (Flags() & SDL_WINDOW_BORDERLESS) != SDL_WINDOW_BORDERLESS;
    }

    Ref<RenderTarget>
    Window::Target() const
    {
        return Ref{impl->target};
    }

    bool
    Window::Resizable() const
    {
        return (Flags() & SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE;
    }

    Point
    Window::Resolution() const
    {
        Uint16 x, y;
        GPU_GetVirtualResolution(impl->target.Target().Get(), &x, &y);
        return {x, y};
    }

    uint32_t
    Window::Flags() const
    {
        return (uint32_t)SDL_GetWindowFlags(GetWindow(impl->target));
    }

    Rectangle
    Window::Viewport() const
    {
        return impl->target.Viewport();
    }

    uint32_t
    Window::Id() const
    {
        return impl->target.Target()->context->windowID;
    }
}