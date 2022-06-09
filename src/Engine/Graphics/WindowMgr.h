/*!
 * @file WindowMgr.h -- SDG_Engine
 * @namespace SDG
 * @class WindowMgr
 * Manages the creation and closure of Windows.
 */
#pragma once
#include "Color.h"
#include "Texture.h"
#include "Window.h"

#include <Engine/Math/Rectangle.h>

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace SDG
{

    class WindowMgr
    {
        struct Impl;
    public:
        WindowMgr();
        ~WindowMgr();

        /// Create a window, returning the id of that window.
        /// @returns the id of the window, or -1 on error.
        int CreateWindow(int width, int height, const char *title, 
            unsigned flags = 0, Ref<Window> *out = nullptr);

        /// Closes every window
        void Close();

        /// Drives input processing to every managed Window object.
        /// Called before game updates take place.
        void ProcessInput(struct SDL_WindowEvent &ev);

        /// Drives render buffering of the Window objects.
        /// To be called at the end of drawn frame.
        void SwapBuffers();

        /// Gets Window ref from id number.
        Ref<Window> At(int id);
    private:
        Impl *impl;
    };
}
