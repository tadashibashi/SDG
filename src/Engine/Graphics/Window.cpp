#include "Window.h"
#include "Private/RendererType.h"
#include "RenderTarget.h"
#include "Texture.h"

#include <Engine/Debug/Log.h>
#include <Engine/Exceptions/Fwd.h>

#include <SDL_gpu.h>
#include <SDL_ttf.h>

#ifdef GetWindow // Cancels some conflicts with MSVC defines
#undef GetWindow
#endif

/// Helper to retrieve underlying SDL_Window * from GPU_Target * for this impl file.
#define GetWindow(target) SDL_GetWindowFromID(target.Target().Get()->context->windowID)

namespace SDG
{
    // ===== Implementation ===================================================
    struct Window::Impl {
        Impl() : target(), title(), icon() {}
        RenderTarget    target;
        String          title;
        CRef<Texture> icon;
    };

    // ===== Window static variables ==========================================
    size_t Window::windowCount;
    bool Window::manageGraphics;
    Delegate<void()> Window::OnAllClosed;

    // ===== Window Initialization ============================================
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
                     0);
            if (!target)
            {
                SDG_Core_Err("Window::Initialize: GPU_Target initialization failed: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
                return false;
            }
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
                SDG_Core_Err("Window::Initialize: SDL_CreateWindow failed: {}", SDL_GetError());
                return false;
            }

            target = GPU_CreateTargetFromWindow(SDL_GetWindowID(window));
            if (!target)
            {
                SDG_Core_Err("Window::Initialize: GPU_CreateTargetFromWindow failed: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
                return false;
            }
        }


        impl->target.EmplaceTarget(Ref{target});
        if (title)
            Title(title);

        // TODO: add the rest of the flags here or see why SDL_gpu sets a weird fullscreen when setting flags directly.
        // Currently emscripten's fullscreen zooms in, strangely.
        if (flags & SDL_WINDOW_FULLSCREEN || flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
            Fullscreen(true);
        if (flags & SDL_WINDOW_BORDERLESS)
            Bordered(false);
        if (flags & SDL_WINDOW_HIDDEN)
            Hidden(true);

        ++windowCount;
        return true;
    }
    /* end Window::Initialize */

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
            if (windowCount == 0)
            {
                OnAllClosed.TryInvoke();

                if (manageGraphics)
                {
                    GPU_Quit();
                }

            }
        }
    }
    /* end Window::Close */

    // ===== Driver-related ===================================================
    void
    Window::ProcessInput(const SDL_WindowEvent &ev)
    {
        if (ev.windowID == Id())
        {
            switch(ev.event)
            {
                case SDL_WINDOWEVENT_SHOWN:
                    // SDG_Core_Log("Window was shown");
                    On.Show.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    // SDG_Core_Log("Window was hidden");
                    On.Hide.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    // SDG_Core_Log("Window was exposed");
                    On.Expose.TryInvoke();
                    impl->target.SwapBuffers();
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    // SDG_Core_Log("Window moved: {}, {}",
                    //        ev.data1,
                    //        ev.data2);
                    On.Move.TryInvoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    On.Resize.TryInvoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    //Resolution({event.ev.data1, event.ev.data2});
                    // SDG_Core_Log("Window size changed: {}, {}",
                    //        ev.data1,
                    //        ev.data2);
                    On.SizeChange.TryInvoke(ev.data1, ev.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    // SDG_Core_Log("Window was minimized");
                    On.Minimize.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    // SDG_Core_Log("Window was maximized");
                    On.Fullscreen.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    // SDG_Core_Log("Window was restored");
                    On.Restore.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_ENTER: // Mouse entered the window
                    // SDG_Core_Log("Mouse entered window");
                    On.MouseEnter.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_LEAVE: // Mouse left the window
                    // SDG_Core_Log("Mouse left window");
                    On.MouseLeave.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    // SDG_Core_Log("Window gained keyboard focus");
                    On.Focus.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    // SDG_Core_Log("Window lost keyboard focus");
                    On.FocusLost.TryInvoke();
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    // SDG_Core_Log("Window closed");
                    On.Close.TryInvoke();
                    Close();
                    break;
            }
        }
    }
    /* end Window::ProcessInput */

    void
    Window::MakeCurrent()
    {
        GPU_MakeCurrent(Target()->Target().Get(), Id());
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

    // ======= Setters ========================================================

    Window &
    Window::Title(const char *title)
    {
        if (!title)
            title = "";

        impl->title = title;
        SDL_SetWindowTitle(GetWindow(impl->target), impl->title.Cstr());
        return *this;
    }

    Window &
    Window::ClientSize(Point size)
    {
        SDL_SetWindowSize(GetWindow(impl->target), size.W(), size.H());
        On.SizeChange.TryInvoke(impl->target.Size().W(), impl->target.Size().H());
        return *this;
    }

    Window &
    Window::Fullscreen(bool fullscreen)
    {
        bool lastFullscreen = GPU_GetFullscreen();
        GPU_SetFullscreen(fullscreen, SDG_TARGET_DESKTOP);
        if (lastFullscreen != fullscreen)
            On.SizeChange.TryInvoke(impl->target.Size().W(), impl->target.Size().H());
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

    Window &
    Window::Minimized(bool minimized)
    {
        if (minimized)
            SDL_MinimizeWindow(GetWindow(impl->target));
        else
            SDL_RestoreWindow(GetWindow(impl->target));
        return *this;
    }

    Window &
    Window::MinimumSize(Point size)
    {
        if (size.X() < 1)
        {
            //SDG_Core_Warn("Window::MinimumSize size.X() must be > 0; setting it to 1");
            size.X(1);
        }
        if (size.Y() < 1)
        {
            //SDG_Core_Warn("Window::MinimumSize size.Y() must be > 0; setting it to 1");
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

    Window &
    Window::MaximumSize(Point size)
    {
        if (size.X() < 1)
        {
            //SDG_Core_Warn("Window::MaximumSize size.X() must be > 0; setting it to 1");
            size.X(1);
        }
        if (size.Y() < 1)
        {
            //SDG_Core_Warn("Window::MaximumSize size.Y() must be > 0; setting it to 1");
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
    /* end Window::MaximumSize */

    Window &
    Window::MouseGrabbed(bool mouseGrabbed)
    {
        SDL_SetWindowMouseGrab(GetWindow(impl->target), (SDL_bool)mouseGrabbed);
        return *this;
    }

    Window &
    Window::AlwaysOnTop(bool alwaysOnTop)
    {
        SDL_SetWindowAlwaysOnTop(GetWindow(impl->target), (SDL_bool)alwaysOnTop);
        return *this;
    }

    Window &
    Window::Hidden(bool hidden)
    {
        if (hidden)
            SDL_HideWindow(GetWindow(impl->target));
        else
            SDL_ShowWindow(GetWindow(impl->target));

        return *this;
    }

    Window &
    Window::Icon(CRef<Texture> texture)
    {
        if (!texture)
            ThrowNullReferenceException("Texture");

        SDL_Surface *surf = GPU_CopySurfaceFromImage(texture->Image().Get());
        if (!surf)
        {
            SDG_Core_Err("Failed to copy SDL_Surface from GPU_Image: {}",
                    GPU_GetErrorString(GPU_PopErrorCode().error));
        }

        SDL_SetWindowIcon(GetWindow(impl->target), surf);
        SDL_FreeSurface(surf);

        impl->icon = texture;
        return *this;
    }

    // ========= Getters ======================================================

    String
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
        return (Flags() & SDL_WINDOW_RESIZABLE);
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
        return (Flags() & SDL_WINDOW_MINIMIZED);
    }

    bool
    Window::Hidden() const
    {
        return (Flags() & SDL_WINDOW_HIDDEN);
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
        return (Flags() & SDL_WINDOW_MOUSE_GRABBED);
    }

    bool
    Window::AlwaysOnTop() const
    {
        return (Flags() & SDL_WINDOW_ALWAYS_ON_TOP);
    }

    CRef<Texture>
    Window::Icon() const
    {
        return impl->icon;
    }

    bool
    Window::IsOpen() const
    {
        return impl->target.IsOpen();
    }

}
/* end namespace SDG*/