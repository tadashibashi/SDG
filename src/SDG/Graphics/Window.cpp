#include "Window.h"
#include "Private/RendererType.h"
#include "Texture2D.h"

#include <SDG/Debug.hpp>
#include <SDL_gpu.h>
#include <SDL_ttf.h>

#ifdef GetWindow // Cancels some conflicts with MSVC defines
#undef GetWindow
#endif

/// Helper to retrieve underlying SDL_Window * from GPU_Target * for this impl file.
#define GetWindow(target) SDL_GetWindowFromID(target.Target().Get()->context->windowID)

namespace SDG
{
    struct Window::Impl {
        Impl() : target(), title(), icon() {}
        RenderTarget    target;
        std::string     title;
        CRef<Texture2D> icon;
    };

    size_t Window::windowCount;
    bool Window::manageGraphics;

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
        Close(); // Make sure to initialize cleanly

        GPU_Target *target;

        if (windowCount == 0)
        {
            target = GPU_InitRenderer(RendererType,
                     width,
                     height,
                     flags);
        }
        else
        {
            SDL_Window *window = SDL_CreateWindow(title,
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      width, height,
                      flags | SDL_WINDOW_OPENGL);
            if (!window)
            {
                SDG_Err("Failed to create window with error: {}", SDL_GetError());
                return false;
            }

            target = GPU_CreateTargetFromWindow(SDL_GetWindowID(window));
        }


        if (!target)
        {
            SDG_Err("Failed to initialize SDL_gpu GPU_Target: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
            return false;
        }

        impl->target.EmplaceTarget(Ref{target});
        if (title)
            Title(title);

        ++windowCount;
        return true;
    }

    void
    Window::Close()
    {
        if (impl->target.IsOpen())
        {
            // Sets active target to null if this was currently active
            if (GPU_GetActiveTarget() == impl->target.Target().Get())
                GPU_SetActiveTarget(nullptr);

            SDL_DestroyWindow(GetWindow(impl->target));
            impl->target.Close();

            --windowCount;
            if (manageGraphics && windowCount == 0)
            {
                TTF_Quit();
                GPU_Quit();
            }
        }
    }

    void
    Window::ProcessInput(const SDL_WindowEvent &ev)
    {
        if (ev.windowID == Id())
        {
            switch(ev.event)
            {
                case SDL_WINDOWEVENT_SHOWN:
                    // SDG_Log("Window was shown");
                    On.Show.Invoke();
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    // SDG_Log("Window was hidden");
                    On.Hide.Invoke();
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    // SDG_Log("Window was exposed");
                    On.Expose.Invoke();
                    impl->target.SwapBuffers(); // TODO: test this behavior...
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    // SDG_Log("Window moved: {}, {}",
                    //        ev.data1,
                    //        ev.data2);
                    On.Move.Invoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    On.Resize.Invoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    //Resolution({event.ev.data1, event.ev.data2});
                    // SDG_Log("Window size changed: {}, {}",
                    //        ev.data1,
                    //        ev.data2);
                    On.SizeChange.Invoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    // SDG_Log("Window was minimized");
                    On.Minimize.Invoke();
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    // SDG_Log("Window was maximized");
                    On.Fullscreen.Invoke();
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    // SDG_Log("Window was restored");
                    On.Restore.Invoke();
                    break;
                case SDL_WINDOWEVENT_ENTER: // Mouse entered the window
                    // SDG_Log("Mouse entered window");
                    On.MouseEnter.Invoke();
                    break;
                case SDL_WINDOWEVENT_LEAVE: // Mouse left the window
                    // SDG_Log("Mouse left window");
                    On.MouseLeave.Invoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    // SDG_Log("Window gained keyboard focus");
                    On.Focus.Invoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    // SDG_Log("Window lost keyboard focus");
                    On.FocusLost.Invoke();
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    // SDG_Log("Window closed");
                    On.Close.Invoke();
                    Close();
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
        if (!title)
            title = "";

        impl->title = title;
        SDL_SetWindowTitle(GetWindow(impl->target), impl->title.c_str());
        return *this;
    }

    Window &
    Window::ClientSize(Point size)
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
        if (size.X() < 1) size.X(1);
        if (size.Y() < 1) size.Y(1);

        GPU_SetWindowResolution(size.X(), size.Y());
        return *this;
    }

    Window &
    Window::Position(Point position)
    {
        SDL_SetWindowPosition(GetWindow(impl->target), position.X(), position.Y());
        return *this;
    }

    Window &Window::Minimized(bool minimized)
    {
        if (minimized)
            SDL_MinimizeWindow(GetWindow(impl->target));
        else
            SDL_RestoreWindow(GetWindow(impl->target));
        return *this;
    }

    Window &Window::MinimumSize(Point size)
    {
        if (size.X() < 0)
        {
            SDG_Warn("Window::MinimumSize size.X() must be > 0; setting it to 0");
            size.X(1);
        }
        if (size.Y() < 0)
        {
            SDG_Warn("Window::MinimumSize size.Y() must be > 0; setting it to 0");
            size.Y(1);
        }

        SDL_SetWindowMinimumSize(GetWindow(impl->target), size.X(), size.Y());
        Point clientSize = ClientSize();
        if (clientSize.X() < size.X() || clientSize.Y() < size.Y())
        {
            size.X(size.X() < clientSize.X() ? clientSize.X() : size.X());
            size.Y(size.Y() < clientSize.Y() ? clientSize.Y() : size.Y());
            ClientSize(size);
        }

        return *this;
    }

    Window &Window::MaximumSize(Point size)
    {
        if (size.X() < 1)
        {
            SDG_Warn("Window::MaximumSize size.X() must be greater than 0; setting it to 1");
            size.X(1);
        }
        if (size.Y() < 1)
        {
            SDG_Warn("Window::MaximumSize size.Y() must be greater than 0; setting it to 1");
            size.Y(1);
        }

        SDL_SetWindowMaximumSize(GetWindow(impl->target), size.X(), size.Y());
        Point clientSize = ClientSize();
        if (clientSize.X() > size.X() || clientSize.Y() > size.Y())
        {
            size.X(size.X() > clientSize.X() ? clientSize.X() : size.X());
            size.Y(size.Y() > clientSize.Y() ? clientSize.Y() : size.Y());
            ClientSize(size);
        }
        return *this;
    }

    Window &Window::MouseGrabbed(bool mouseGrabbed)
    {
        SDL_SetWindowMouseGrab(GetWindow(impl->target), (SDL_bool)mouseGrabbed);
        return *this;
    }

    Window &Window::AlwaysOnTop(bool alwaysOnTop)
    {
        SDL_SetWindowAlwaysOnTop(GetWindow(impl->target), (SDL_bool)alwaysOnTop);
        return *this;
    }

    Window &Window::Hidden(bool hidden)
    {
        if (hidden)
            SDL_HideWindow(GetWindow(impl->target));
        else
            SDL_ShowWindow(GetWindow(impl->target));

        return *this;
    }

    Window &Window::Icon(CRef<Texture2D> texture)
    {
        if (!texture)
            throw NullReferenceException("Texture2D");

        SDL_Surface *surf = GPU_CopySurfaceFromImage(texture->Image().Get());
        if (!surf)
        {
            SDG_Err("Failed to copy SDL_Surface from GPU_Image: {}", GPU_GetErrorString(GPU_PopErrorCode().error));
        }

        SDL_SetWindowIcon(GetWindow(impl->target), surf);
        SDL_FreeSurface(surf);

        impl->icon = texture;
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

    Point
    Window::Position() const
    {
        int x, y;
        SDL_GetWindowPosition(GetWindow(impl->target), &x, &y);

        return {x, y};
    }

    bool
    Window::Minimized() const
    {
        return (Flags() & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED;
    }

    bool
    Window::Hidden() const
    {
        return (Flags() & SDL_WINDOW_HIDDEN) == SDL_WINDOW_HIDDEN;
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

    Point Window::ClientSize() const
    {
        int w, h;
        SDL_GL_GetDrawableSize(GetWindow(impl->target), &w, &h);
        return {w, h};
    }

    Point Window::MinimumSize() const
    {
        int x, y;
        SDL_GetWindowMinimumSize(GetWindow(impl->target), &x, &y);
        return {x, y};
    }

    Point Window::MaximumSize() const
    {
        int x, y;
        SDL_GetWindowMaximumSize(GetWindow(impl->target), &x, &y);
        return {x, y};
    }

    bool
    Window::MouseGrabbed() const
    {
        return (Flags() & SDL_WINDOW_MOUSE_GRABBED) == SDL_WINDOW_MOUSE_GRABBED;
    }

    bool
    Window::AlwaysOnTop() const
    {
        return (Flags() & SDL_WINDOW_ALWAYS_ON_TOP) == SDL_WINDOW_ALWAYS_ON_TOP;
    }

    CRef<Texture2D>
    Window::Icon() const
    {
        return impl->icon;
    }

    bool Window::IsOpen() const
    {
        return impl->target.IsOpen();
    }

}