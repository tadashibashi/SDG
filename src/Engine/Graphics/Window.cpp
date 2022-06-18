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
#define GetWindow(target) SDL_GetWindowFromID(target->Target()->context->windowID)

namespace SDG
{
    // ===== Implementation ===================================================
    struct Window::Impl {
        Impl() : target(new RenderTarget), title(), icon() {}
        Unique<RenderTarget> target;
        String               title;
        Texture              icon;
    };

    // ===== Window static variables ==========================================

    size_t Window::windowCount = size_t{0};
    bool Window::manageGraphics = bool{false};
    Delegate<void()> Window::OnAllClosed = Delegate<void()>{};

    // ===== Window Initialization ============================================
    Window::Window() : impl(new Impl), On{}
    {

    }

    Window::~Window()
    {
        Close();
    }

    auto Window::Initialize(int width, int height, const char *title, unsigned flags)->bool
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
            auto window = SDL_CreateWindow(title,
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

        impl->target->EmplaceTarget(target);
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

    
    auto Window::Close()->void
    {
        if (impl->target->IsOpen())
        {
            // Sets active target to null if this was currently active
            if (GPU_GetActiveTarget() == impl->target->Target())
                GPU_SetActiveTarget(nullptr);

            SDL_DestroyWindow(GetWindow(impl->target));
            impl->target->Close();

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
    
    auto Window::ProcessInput(const SDL_WindowEvent &ev)->void
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
                    impl->target->SwapBuffers();
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


    auto Window::MakeCurrent()->void
    {
        GPU_MakeCurrent(Target()->Target().Get(), Id());
    }


    auto Window::SwapBuffers()->void
    {
        impl->target->SwapBuffers();
    }


    auto Window::Clear(Color color)->void
    {
       impl->target->Clear(color);
    }

    // ======= Setters ========================================================

   
    auto Window::Title(const char *title)->Window &
    {
        if (!title)
            title = "";

        impl->title = title;
        SDL_SetWindowTitle(GetWindow(impl->target), impl->title.Cstr());
        return *this;
    }

   
    auto Window::ClientSize(Point size)->Window &
    {
        SDL_SetWindowSize(GetWindow(impl->target), size.W(), size.H());
        On.SizeChange.TryInvoke(impl->target->Size().W(), impl->target->Size().H());
        return *this;
    }

   
    auto Window::Fullscreen(bool fullscreen)->Window &
    {
        bool lastFullscreen = GPU_GetFullscreen();
        GPU_SetFullscreen(fullscreen, SDG_TARGET_DESKTOP);
        if (lastFullscreen != fullscreen)
            On.SizeChange.TryInvoke(impl->target->Size().W(), impl->target->Size().H());
        return *this;
    }

   
    auto Window::Bordered(bool bordered)->Window &
    {
        SDL_SetWindowBordered(GetWindow(impl->target), (SDL_bool)bordered);
        return *this;
    }

   
    auto Window::Resizable(bool resizable)->Window &
    {
        SDL_SetWindowResizable(GetWindow(impl->target), (SDL_bool)resizable);
        return *this;
    }

   
    auto Window::Resolution(Point size)->Window &
    {
        if (size.X() < 1) size.X(1);
        if (size.Y() < 1) size.Y(1);

        GPU_SetWindowResolution(size.X(), size.Y());
        return *this;
    }

    auto Window::Position(Point position)->Window &
    {
        SDL_SetWindowPosition(GetWindow(impl->target), position.X(), position.Y());
        return *this;
    }

    auto Window::Minimized(bool minimized)->Window &
    {
        if (minimized)
            SDL_MinimizeWindow(GetWindow(impl->target));
        else
            SDL_RestoreWindow(GetWindow(impl->target));
        return *this;
    }

    auto Window::MinimumSize(Point size)->Window &
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

    auto Window::MaximumSize(Point size)->Window &
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

    auto Window::MouseGrabbed(bool mouseGrabbed)->Window &
    {
        SDL_SetWindowMouseGrab(GetWindow(impl->target), (SDL_bool)mouseGrabbed);
        return *this;
    }

    auto Window::AlwaysOnTop(bool alwaysOnTop)->Window &
    {
        SDL_SetWindowAlwaysOnTop(GetWindow(impl->target), (SDL_bool)alwaysOnTop);
        return *this;
    }

    auto Window::Hidden(bool hidden)->Window &
    {
        if (hidden)
            SDL_HideWindow(GetWindow(impl->target));
        else
            SDL_ShowWindow(GetWindow(impl->target));

        return *this;
    }

    auto Window::Icon(const Texture &texture)->Window &
    {
        SDL_Surface *surf = GPU_CopySurfaceFromImage((GPU_Image *)texture.Image());
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

    auto Window::Title() const->String
    {
        return impl->title;
    }

    auto Window::Size() const->Point
    {
        return impl->target->Size();
    }

    auto Window::Fullscreen() const->bool
    {
        return GPU_GetFullscreen();
    }

    auto Window::Bordered() const->bool
    {
        return (Flags() & SDL_WINDOW_BORDERLESS) != SDL_WINDOW_BORDERLESS;
    }

    auto Window::Target() const->Ref<const RenderTarget>
    {
        return impl->target.Get();
    }

    auto Window::Target()->Ref<RenderTarget>
    {
        return impl->target.Get();
    }

    bool
    Window::Resizable() const
    {
        return (Flags() & SDL_WINDOW_RESIZABLE);
    }

    auto
    Window::Resolution() const->Point
    {
        Uint16 x, y;
        GPU_GetVirtualResolution((GPU_Target *)impl->target->Target().Get(), &x, &y);
        return {x, y};
    }

    auto
    Window::Position() const->Point
    {
        int x, y;
        SDL_GetWindowPosition(GetWindow(impl->target), &x, &y);

        return {x, y};
    }

    auto
    Window::Minimized() const->bool
    {
        return (Flags() & SDL_WINDOW_MINIMIZED);
    }

    auto
    Window::Hidden() const->bool
    {
        return (Flags() & SDL_WINDOW_HIDDEN);
    }

    auto
    Window::Flags() const->uint32_t
    {
        return (uint32_t)SDL_GetWindowFlags(GetWindow(impl->target));
    }

    auto
    Window::Viewport() const->Rectangle
    {
        return impl->target->Viewport();
    }

    auto
    Window::Id() const->uint32_t
    {
        return impl->target->Target()->context->windowID;
    }

    auto
    Window::ClientSize() const->Point
    {
        int w, h;
        SDL_GL_GetDrawableSize(GetWindow(impl->target), &w, &h);
        return {w, h};
    }

    auto Window::MinimumSize() const->Point
    {
        int x, y;
        SDL_GetWindowMinimumSize(GetWindow(impl->target), &x, &y);
        return {x, y};
    }

    auto Window::MaximumSize() const->Point
    {
        int x, y;
        SDL_GetWindowMaximumSize(GetWindow(impl->target), &x, &y);
        return {x, y};
    }

    auto Window::MouseGrabbed() const->bool
    {
        return (Flags() & SDL_WINDOW_MOUSE_GRABBED);
    }

    auto Window::AlwaysOnTop() const->bool
    {
        return (Flags() & SDL_WINDOW_ALWAYS_ON_TOP);
    }

    auto Window::Icon() const->Ref<const Texture>
    {
        return impl->icon;
    }

    auto Window::IsOpen() const->bool
    {
        return impl->target->IsOpen();
    }

}
/* end namespace SDG*/
