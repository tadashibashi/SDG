#include "GraphicsMgr.h"
#include <SDG/Platform.h>
#include <SDG/Math/Vector2.h>
#include <SDG/Debug.hpp>

#include <SDL_gpu.h>
#include <SDL.h>

static const unsigned DefaultInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;


namespace SDG
{
    struct GraphicsMgr::Impl {
        SDG::Window window;
    };

    // Helpers

    SDL_Window *
    GetTargetWindow(GPU_Target *target)
    {
        return SDL_GetWindowFromID(target->context->windowID);
    }

    GraphicsMgr::GraphicsMgr() : impl(new Impl)
    {

    }

    GraphicsMgr::~GraphicsMgr()
    {
        Close();
        delete impl;
    }

    bool
    GraphicsMgr::Initialize()
    {


        return true;
    }

    Ref<Window>
    GraphicsMgr::Window()
    {
        return Ref{impl->window};
    }


    void GraphicsMgr::Close()
    {
        impl->window.Close();
    }
}