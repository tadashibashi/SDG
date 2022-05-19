//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include "Color.h"

#include <SDG/Math/Vector2.h>
#include <SDG/Templates/Delegate.h>
#include <SDG/Ref.h>
#include <SDG/ClassMacros.h>
#include <SDG/Math/Rectangle.h>
#include "RenderTarget.h"
#include <string>

// forward declaration
struct SDL_WindowEvent;

namespace SDG
{
    // forward declaration
    class Texture2D;

    /// Manages one application window.
    class Window
    {
        struct Impl;
    public:
        Window();
        ~Window();

        /// Opens the Window and initializes the internal graphics library.
        /// If called a second time, it will close the existing window, and re-open a new one.
        /// @param width  window width, must be 0 or larger
        /// @param height window height, must be 0 or larger
        /// @param title  window title
        /// @param flags  SDL2 Window flags
        bool Initialize(int width, int height, const char *title, unsigned flags = 0);

        /// Closes the window and shuts down the graphics library.
        void Close();

        void Clear(Color color = Color::CornflowerBlue());

        /// Displays the graphics that were drawn to the Window.
        void SwapBuffers();

        /// Drives event input to the window.
        /// Please pass all window events to this function. It automatically
        /// detects which window events pertain to this Window by id.
        void ProcessInput(const SDL_WindowEvent &ev);

        // === Setters ===
        Window &Title(const char *title);
        Window &ClientSize(Point size);
        Window &Resolution(Point size);
        Window &Fullscreen(bool fullscreen);
        Window &Bordered(bool bordered);
        Window &Resizable(bool resizable);
        Window &Position(Point position);
        Window &Minimized(bool minimized);
        Window &Icon(CRef<Texture2D> texture);

        /// Hide or show window
        /// @param hidden true: hide window; false: show window
        Window &Hidden(bool hidden);
        /// Set the Window's minimum size
        Window &MinimumSize(Point size);
        Window &MaximumSize(Point size);
        Window &MouseGrabbed(bool mouseGrab);
        Window &AlwaysOnTop(bool alwaysOnTop);



        // === Getters ===
        bool IsOpen() const;
        std::string Title() const;
        Point Size() const;

        /// Underlying Window size
        Point ClientSize() const;
        bool Fullscreen() const;
        bool Bordered() const;
        bool Resizable() const;
        Point Resolution() const;
        Point Position() const;
        bool Minimized() const;
        bool Hidden() const;
        Point MinimumSize() const;
        Point MaximumSize() const;
        bool MouseGrabbed() const;
        bool AlwaysOnTop() const;
        CRef<Texture2D> Icon() const;

        uint32_t Flags() const;
        Rectangle Viewport() const;
        Ref<RenderTarget> Target() const;

        static size_t Count() { return windowCount; }

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

            /// Occurs when the Window has been exposed.
            /// Window will automatically be redrawn right after this callback
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

        /// Tells Window whether to handle the graphics library cleanup on its own.
        /// Cleanup would happen right when the last Window is closed.
        /// Default: false, does not manage the library cleanup.
        /// Useful for programs not using a GraphicsMgr-type object to handle this.
        /// In this case, a listener should be set to close the application
        /// just before the last Window is closed.
        static void StandaloneMode(bool manage) { manageGraphics = manage; }
    private:
        Impl *impl;
        static size_t windowCount;
        static bool manageGraphics;
    };
}
