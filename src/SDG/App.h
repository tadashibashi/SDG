/*!
 * @file App.h
 * @namespace SDG
 * @class App
 * Main application object base class
 * 
 */
#pragma once
#include <SDG/FileSys/Path.h>
#include <SDG/Platform.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/String.h>
#include "SDG/Time/AppTime.h"

namespace SDG
{
    class App 
    {
        struct Impl;
    public:
        App(const String &appName, const String &orgName,
            const Path &configPath = BasePath("assets/config.sdgc"));
        virtual ~App();

        /// Executes one game frame. Intended for use by platforms that require the
        /// use of the main loop, such as Emscripten-WebGL.
        void RunOneFrame();

        /// Triggers the main loop to run until Exit is called.
        void Run();

        /// Shuts down the game before the next frame.
        void Exit();

        CRef<AppTime> Time();
    protected:
        // Access for base classes
        Ref<class Window> MainWindow();
        Ref<class WindowMgr> Windows();

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
