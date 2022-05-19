//
// Created by Aaron Ishibashi on 4/29/22.
//

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
