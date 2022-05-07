//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include "Camera2D.h"
#include "Color.h"

#include <SDG/Math/Vector2.h>
#include <SDG/Templates/Delegate.h>
#include <SDG/Ref.h>
#include <SDG/ClassAttr.h>
#include <string>

namespace SDG
{
    class RenderTarget;

    class Window
    {
        struct Impl;
    public:
        Window();
        ~Window();

        bool Initialize(int width, int height, const char *title, unsigned flags = 0);
        void Close();

        void Clear(Color color = Color::CornflowerBlue());
        void SwapBuffers();

        void ProcessInput(void *evt);

        // === Setters ===
        Window &Title(const char *title);
        Window &Size(Point size);
        Window &Resolution(Point size);
        Window &Fullscreen(bool fullscreen);
        Window &Bordered(bool bordered);
        Window &Resizable(bool resizable);

        // === Getters ===

        std::string Title() const;
        Point Size() const;
        bool Fullscreen() const;
        bool Bordered() const;
        bool Resizable() const;
        Point Resolution() const;
        uint32_t Flags() const;
        Rectangle Viewport() const;
        Ref<RenderTarget> Target() const;

        /// Window Events
        class Events {
            SDG_NOCOPY(Events)
        private:
            Events() = default; // Instantiable by window only
        public:
            Delegate<>         Show;
            Delegate<>         Hide;
            Delegate<>         Expose;

            /// Occurs when the Window is moved.
            /// Parameters: (X, Y) Window position
            Delegate<int, int> Move;
            Delegate<int, int> Resize;
            Delegate<int, int> SizeChange;
            Delegate<>         Minimize;
            Delegate<>         Fullscreen;
            Delegate<>         Restore;
            Delegate<>         MouseEnter;
            Delegate<>         MouseLeave;
            Delegate<>         Focus;
            Delegate<>         FocusLost;
            Delegate<>         Close;
        } On;

        uint32_t Id() const;
    private:
        Impl *impl;
    };
}
