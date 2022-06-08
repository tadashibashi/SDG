#include "WindowMgr.h"

#include <SDG/Debug/Log.h>
#include <SDG/Math/Vector2.h>

#include <SDL_ttf.h>
#include <SDL_gpu.h>
#include <SDL.h>

#include <vector>

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace SDG
{
    struct WindowMgr::Impl 
    {
        Impl() : windows() { }
        std::vector<SDG::Window *> windows;
    };

    // Helpers
    static SDL_Window *
    GetTargetWindow(GPU_Target *target)
    {
        return SDL_GetWindowFromID(target->context->windowID);
    }

    WindowMgr::WindowMgr() : impl(new Impl)
    {
        Window::StandaloneMode(false); // WindowMgr will manage the graphics library.

        if (SDL_WasInit(0) == 0)
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
            {
                SDG_Core_Err("Failed to initialize SDL2: {}", SDL_GetError());
                exit(-1);
            }
            if (TTF_Init() != 0)
            {
                SDG_Core_Err("Failed to initialize SDL2_ttf: {}", TTF_GetError());
                SDL_Quit();
            }
        }
    }

    WindowMgr::~WindowMgr()
    {
        Close();
        for (Window *win : impl->windows)
            delete win;
        delete impl;

        TTF_Quit();
        GPU_Quit();
    }

    int
    WindowMgr::CreateWindow(int width, int height, const char *title, unsigned flags, Ref<Window> *out)
    {
        size_t id = impl->windows.size();
        Window *window = new Window;
        if (!window->Initialize(width, height, title, flags))
        {
            delete window;
            return -1;
        }

        impl->windows.emplace_back(window);
        if (out)
            *out = window;
        return id;
    }

    // Safely get Window at an id index
    Ref<Window>
    WindowMgr::At(int id)
    {
        if (id >= impl->windows.size() || id < 0)
            throw OutOfRangeException(id, "Window index is out of range");
        return Ref{impl->windows[id]};
    }

    void WindowMgr::Close()
    {
        for (Window *win : impl->windows)
            win->Close();
    }

    void WindowMgr::ProcessInput(SDL_WindowEvent &ev)
    {
        for (Window *win : impl->windows)
            if (win->IsOpen())
                win->ProcessInput(ev);
    }

    void WindowMgr::SwapBuffers()
    {
        for (Window *win : impl->windows)
        {
            if (win->IsOpen())
                win->SwapBuffers();
        }
    }
}