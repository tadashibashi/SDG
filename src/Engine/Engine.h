/* ====================================================================================================================
 * @file    Engine.h – SDG_Engine
 * @author  Aaron Ishibashi
 *
 * @class   SDG::Engine
 * Main base class that provdes basic Window and input for an application.
 *
 * ==================================================================================================================*/
#pragma once
#include <Engine/Filesys/Path.h>
#include <Engine/Game/Datatypes/AppConfig.h>
#include <Engine/Lib/Ref.h>
#include <Engine/Lib/String.h>
#include <Engine/Lib/Version.h>
#include <Engine/Time/AppTime.h>

namespace SDG
{
    /// Provides the basic ammenities to run an app
    class Engine 
    {
        struct Impl;
    public:
        /// @param appName - name of the app
        /// @param orgName - company / organization name
        /// @param configPath - path to an AppConfig json file.
        explicit Engine(const String &configPath);
        /// @param appName - name of the app
        /// @param 
        explicit Engine(const AppConfig &config);
        virtual ~Engine();

        /// Executes one game frame. Intended for use by platforms that require the
        /// use of the main loop, such as Emscripten-WebGL.
        void RunOneFrame();

        /// Triggers the main loop to run until Exit is called.
        void Run();

        /// Shuts down the game before the next frame.
        void Exit();

        const String &Name() const;

        CRef<AppTime> Time();

        static Version Version();
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
