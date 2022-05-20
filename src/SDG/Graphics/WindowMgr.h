/*!
 * @file WindowMgr.h -- SDG_Engine
 * 
 * @namespace SDG
 * @class WindowMgr
 * Manages the creation and destruction of Windows.
 * 
 */
#pragma once
#include "Color.h"
#include "Texture2D.h"
#include "SDG/Math/Rectangle.h"
#include "Window.h"

struct SDL_WindowEvent;

namespace SDG
{

    class WindowMgr
    {
        struct Impl;
    public:
        WindowMgr();
        ~WindowMgr();

        /// Create a window, returning the id of that window
        /// @returns the id of the window, or -1 on error.
        int CreateWindow(int width, int height, const char *title, unsigned flags = 0, Ref<Window> *out = nullptr);

        /// Closes every window
        void Close();

        void ProcessInput(SDL_WindowEvent &ev);
        void SwapBuffers();


        /// Gets Window ref
        Ref<Window> At(int id);
    private:
        // Private implementation to wrap GPU functions.
        Impl *impl;
    };
}
