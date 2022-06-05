/*!
 * @file App.h
 * @namespace SDG
 * @class App
 * Main application object base class
 * 
 */
#pragma once
#include <SDG/FileSys/Path.h>
#include <SDG/Game/AppConfig.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/String.h>
#include <SDG/Time/AppTime.h>


namespace SDG
{
    /// Provides the basic ammenities to run an app
    class App 
    {
        struct Impl;
    public:
        /// @param appName - name of the app
        /// @param orgName - company / organization name
        /// @param configPath - path relative to the base executable directory
        explicit App(const String &configPath);
        /// @param appName - name of the app
        /// @param 
        explicit App(const AppConfig &config);
        virtual ~App();

        /// Executes one game frame. Intended for use by platforms that require the
        /// use of the main loop, such as Emscripten-WebGL.
        void RunOneFrame();

        /// Triggers the main loop to run until Exit is called.
        void Run();

        /// Shuts down the game before the next frame.
        void Exit();

        const String &Name() const;

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
