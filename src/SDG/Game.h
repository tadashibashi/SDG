/// Main application object
#pragma once

#include <SDG/Graphics/Window.h>

class GPU_Target;

namespace SDG
{
    class Game {
        struct Impl;
    public:
        Game();
        ~Game();

        /// Executes one game frame. Intended for use by platforms that require the
        /// use of the main loop, such as Emscripten-WebGL.
        void RunOneFrame();

        /// Triggers the main loop to run until Exit is called.
        void Run();

        /// Shuts down the game before the next frame.
        void Exit();
    protected:
        /// Gets the SDL_gpu Target object. TODO: Wrap in a GraphicsMgr object.
        Window &GetWindow() { return window; }

        virtual int Initialize();
        virtual void ProcessInput();
        virtual void Update();
        virtual void Render();
        virtual void Close();

    private:
        Window window;
        bool isRunning;
    };
}
