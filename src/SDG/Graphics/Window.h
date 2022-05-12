//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include "Camera2D.h"
#include "Color.h"

#include <SDG/Math/Vector2.h>
#include <SDG/Templates/Delegate.h>
#include <SDG/Ref.h>
#include <SDG/ClassMacros.h>
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
            /// Occurs when the Window is shown in view.
            /// @callback void callback()
            Delegate<>         Show;

            /// Occurs when the Window is hidden out of view.
            /// @callback void callback()
            Delegate<>         Hide;

            /// Occurs when the Window is first created.
            /// @callback void callback()
            Delegate<>         Expose;

            /// Occurs when the Window is moved.
            /// @callback void callback(int x, int y)
            /// @param x - Window x-coordinate in user's environment
            /// @param y - Window y-coordinate in user's environment
            Delegate<int, int> Move;

            /// Occurs when the user resizes the Window.
            /// @callback void callback(int width, int height)
            /// @param width - updated Window width
            /// @param height - updated Window height
            Delegate<int, int> Resize;

            /// Occurs any time the window's size changes.
            /// @callback void callback(int width, int height)
            /// @param width - updated Window width
            /// @param height - updated Window height
            Delegate<int, int> SizeChange;

            /// Occurs when the Window is minimized.
            /// @callback void callback()
            Delegate<>         Minimize;

            /// Occurs when the Window is maximized to fullscreen.
            /// @callback void callback()
            Delegate<>         Fullscreen;

            /// Not sure when this occurs...
            /// @callback void callback()
            Delegate<>         Restore;

            /// Occurs when the mouse enters the Window (not including the tab at the top)
            /// @callback void callback()
            Delegate<>         MouseEnter;

            /// Occurs when the mouse leaves the Window (not including the tab at the top)
            /// @callback void callback()
            Delegate<>         MouseLeave;

            /// Occurs when the Window gains user focus. On Desktop platforms, this happens
            /// when the user clicks on an unfocused Window. In a web browser, this may happen
            /// when the user activates the tab or clicks on the window.
            /// Keyboard / Gamepad input will now be in effect after this event.
            /// @callback void callback()
            Delegate<>         Focus;

            /// Occurs when the Window loses user focus. On Desktop platforms, this happens
            /// when the user clicks outside of a focused Window. In a web browser, this may happen
            /// when the user activates another tab or clicks outside of the browser.
            /// Keyboard / Gamepad input will now be in effect after this event.
            /// @callback void callback()
            Delegate<>         FocusLost;

            /// Occurs when the Window closes, usually on app shutdown.
            Delegate<>         Close;
        } On;

        uint32_t Id() const;
    private:
        Impl *impl;
    };
}
