/// Main application object
#pragma once
#include <SDG/Platform.h>
#include <SDG/Time/Time.h>
#include "Ref.h"

namespace SDG
{
    class Window;

    class App {
        struct Impl;
    public:
        App();
        virtual ~App();

        /// Executes one game frame. Intended for use by platforms that require the
        /// use of the main loop, such as Emscripten-WebGL.
        void RunOneFrame();

        /// Triggers the main loop to run until Exit is called.
        void Run();

        /// Shuts down the game before the next frame.
        void Exit();

        const CRef<Time> Time();
    protected:
        // Access for base classes
        Ref<Window> Window();

    private:
        int Initialize_();
        void ProcessInput();
        void Update_();
        void Render_();
        void Close_();

        // ===== Functions to be overriden by sub-classes =====
        virtual int Initialize() { return 0; }
        virtual void Update() {}
        virtual void Render() {}
        virtual void Close() {}
        Impl *impl;
    };
}
