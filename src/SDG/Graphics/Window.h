/*!
 * @file Window.h
 * @class Window
 * Manages an application Window.
 * 
 * It may also manage graphics library by calling 
 * Window::StandaloneMode(true). With this behavior enabled, the
 * graphcis library will automatically shutdown when the last Window
 * has been closed.
 */
#pragma once
#include "Color.h"

#include <SDG/Math/Vector2.h>
#include <SDG/Lib/ClassMacros.h>
#include <SDG/Lib/Delegate.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/String.h>
#include <SDG/Math/Rectangle.h>

// forward declaration
struct SDL_WindowEvent;

namespace SDG
{
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

        /// Close the window if it is open, and shut down the graphics library.
        void Close();

        /// Clears the window with a blank screen of a specified color
        /// @param color the color to clear with. Default: Cornflower Blue
        void Clear(Color color = Color::CornflowerBlue());

        /// Makes Window's context current to load images with.
        void MakeCurrent();

        /// Drives the displays of the graphics that were rendered to the Window.
        /// Called at the end of rendering to display what was drawn.
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
        Window &Icon(CRef<class Texture> texture);

        /// Hide or show window
        /// @param hidden true: hide window; false: show window
        Window &Hidden(bool hidden);
        /// Set the Window's minimum size
        Window &MinimumSize(Point size);
        /// Set the Window's maximum size
        Window &MaximumSize(Point size);

        /// Sets the Window's mouse grab mode. Mouse grab mode confines the
        /// mouse cursor within the window.
        Window &MouseGrabbed(bool mouseGrab);
        Window &AlwaysOnTop(bool alwaysOnTop);



        // === Getters ===
        bool IsOpen() const;
        String Title() const;
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
        CRef<class Texture> Icon() const;

        uint32_t Flags() const;
        Rectangle Viewport() const;
        Ref<class RenderTarget> Target() const;

        static size_t Count() { return windowCount; }

        /// Window Events
        class Events {
            SDG_NOCOPY(Events);
        private:
            Events() = default; // Instantiable by window only
        public:
            /// Occurs when the Window is shown in view.
            /// @callback void callback()
            Delegate<void()>         Show;

            /// Occurs when the Window is hidden out of view.
            /// @callback void callback()
            Delegate<void()>         Hide;

            /// Occurs when the Window has been exposed.
            /// Window will automatically be redrawn right after this callback
            /// @callback void callback()
            Delegate<void()>         Expose;

            /// Occurs when the Window is moved.
            /// @callback void callback(int x, int y)
            /// @param x - Window x-coordinate in user's environment
            /// @param y - Window y-coordinate in user's environment
            Delegate<void(int, int)> Move;

            /// Occurs when the user resizes the Window.
            /// @callback void callback(int width, int height)
            /// @param width - updated Window width
            /// @param height - updated Window height
            Delegate<void(int, int)> Resize;

            /// Occurs any time the window's size changes.
            /// @callback void callback(int width, int height)
            /// @param width - updated Window width
            /// @param height - updated Window height
            Delegate<void(int, int)> SizeChange;

            /// Occurs when the Window is minimized.
            /// @callback void callback()
            Delegate<void()>         Minimize;

            /// Occurs when the Window is maximized to fullscreen.
            /// @callback void callback()
            Delegate<void()>         Fullscreen;

            /// Not sure when this occurs...
            /// @callback void callback()
            Delegate<void()>         Restore;

            /// Occurs when the mouse enters the Window (not including the tab at the top)
            /// @callback void callback()
            Delegate<void()>         MouseEnter;

            /// Occurs when the mouse leaves the Window (not including the tab at the top)
            /// @callback void callback()
            Delegate<void()>         MouseLeave;

            /// Occurs when the Window gains user focus. On Desktop platforms, this happens
            /// when the user clicks on an unfocused Window. In a web browser, this may happen
            /// when the user activates the tab or clicks on the window.
            /// Keyboard / Gamepad input will now be in effect after this event.
            /// @callback void callback()
            Delegate<void()>         Focus;

            /// Occurs when the Window loses user focus. On Desktop platforms, this happens
            /// when the user clicks outside of a focused Window. In a web browser, this may happen
            /// when the user activates another tab or clicks outside of the browser.
            /// Keyboard / Gamepad input will now be in effect after this event.
            /// @callback void callback()
            Delegate<void()>         FocusLost;

            /// Occurs when the Window closes, usually on app shutdown.
            Delegate<void()>         Close;
        } On;

        uint32_t Id() const;

        /// Tells Window class whether to handle the graphics library cleanup on its own.
        /// If set to true, cleanup will automatically happen right when the last Window is closed.
        /// Default: false
        /// This behavior was made for programs not using a graphics/window manager-type object
        /// to handle this. When set to true, a listener should be added to Window::OnAllClosed to
        /// shutdown the rest of the application that may otherwise depend on the graphics library
        /// for shutdown logic, such as receiving the SDL_QUIT event just before the last Window is closed.
        /// Even if set to true, please make sure to shutdown any auxilliary libraries like SDL_ttf, mix, net, etc.
        /// on your own.
        static void StandaloneMode(bool manage) { manageGraphics = manage; }

        static Delegate<void()> OnAllClosed;

    private:
        Impl *impl;
        static size_t windowCount;
        static bool manageGraphics;
    };
}
