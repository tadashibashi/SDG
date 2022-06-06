/// App implementation file
#include "App.h"
#include <SDG/Exceptions/AssertionException.h>
#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Log.h>
#include <SDG/Input/Input.h>
#include <SDG/FileSys/FileSys.h>
#include <SDG/Game/Datatypes/AppConfig.h>

#include <SDG/Graphics/WindowMgr.h>
#include <SDG/Lib/Platform.h>

#include <SDL.h>

#if (SDG_TARGET_WEBGL)
static void EmMainLoop(void *arg)
{
    ((SDG::App *)arg)->RunOneFrame();
}
#endif

namespace SDG
{
    // ===== App Implementation ===============================================
    struct App::Impl 
    {
        Impl() 
            : windows(), mainWindow(), isRunning(), time(), 
            fileSys(), version(SDG_VERSION_MAJOR, SDG_VERSION_MINOR, SDG_VERSION_PATCH) {}
        void Initialize(const AppConfig &config) 
        { 
            this->config = config;
            SDG_Assert(!config.appName.Empty());
            SDG_Assert(!config.orgName.Empty());
            fileSys.Initialize(config.appName, config.orgName);
            Path::PushFileSys(fileSys);

            SDG_Core_Log("\n"
            "*===========================================================================*\n"
            "  SDG Engine v{}\n"
            "    Platform:   {}: {}\n"
            "    Debug mode: {}\n"
            "\n"
            "*===========================================================================*",
                version, TargetPlatformName(), SIZEOF_VOIDP == 8 ? "64-bit" : "32-bit", SDG_DEBUG ? "ON" : "OFF");
        }

        ~Impl()
        {
            Path::PopFileSys();
        }

        WindowMgr   windows;
        Ref<Window> mainWindow;
        bool        isRunning;
        AppTime     time;
        FileSys     fileSys;
        AppConfig   config;
        Version     version;
    };


    App::App(const String &configPath) : impl(new Impl)
    {

        // Get game settings from config file
        AppConfig config;
        config.Load(BasePath(configPath));
        impl->Initialize(config);
    }

    App::App(const AppConfig &config) : impl(new Impl)
    {
        impl->Initialize(config);
    }


    App::~App()
    {
        Close_();
        delete impl;
    }


    int
    App::Initialize_()
    {
        AppConfig &config = impl->config;
        SDG_Core_Log("Initializing {}", config.appName);
        
        Ref<Window> window;
        if (impl->windows.CreateWindow(config.width, config.height, 
            config.title.Cstr(), impl->config.winFlags, &window) >= 0)
        {
            impl->mainWindow = window;
            SDG_Core_Log("- graphics library and window. ok.");
        }
        else
        {
            SDG_Core_Err("- graphics library and window. failed!");
            return -1;
        }

        // TODO: game config can specify input types through an array?
        InputDriver::Initialize(SDG_INPUTTYPE_DEFAULT);
        SDG_Core_Log("- input driver. ok.");

        impl->isRunning = true;
        return Initialize(); // Child class initialization;
    }


    void
    App::ProcessInput()
    {
        InputDriver::UpdateLastStates();

        // Event polling
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch(ev.type)
            {
                case SDL_QUIT:
                    Exit();
                    break;
                case SDL_WINDOWEVENT:
                        impl->windows.ProcessInput(ev.window);
                    break;
            }

            InputDriver::ProcessInput(ev);
        }
    }


    void
    App::RunOneFrame()
    {
        try {
            ProcessInput();
            Update_();
            Render_();
        }
        catch(const Exception &e)
        {
            SDG_Core_Err("{}", e.what());
            Exit();
        }
    }


    void
    App::Close_()
    {
        Close(); // Child class clean up
        InputDriver::Close();
        Path::PopFileSys();
        impl->windows.Close();
        SDG_Core_Log("App shutdown complete.");
    }


    void
    App::Run()
    {
        if (int err = Initialize_() != 0)
        {
            SDG_Core_Err("App failed to initialize: error code: {}", err);
            return;
        }
        SDG_Core_Log("Initialization complete! Entering application loop.");

    #if (SDG_TARGET_WEBGL)
        emscripten_set_main_loop_arg(EmMainLoop, this, -1, true);
    #else
        while (impl->isRunning)
            RunOneFrame();
    #endif
    }

    void
    SDG::App::Exit()
    {
        impl->isRunning = false;
    #if (SDG_TARGET_WEBGL) // since emscripten's main loop is infinite, we need to immediately exit.
        Close();
        emscripten_cancel_main_loop();
    #endif
    }

    Ref<SDG::Window>
    App::MainWindow()
    {
        SDG_Assert(impl->mainWindow);
        return impl->mainWindow;
    }

    Ref<SDG::WindowMgr>
    App::Windows()
    {
        return Ref(impl->windows);
    }

    void
    App::Update_()
    {
        impl->time.Update();
        Update();
    }

    void
    App::Render_()
    {
        Render();
        impl->windows.SwapBuffers();
    }

    CRef<AppTime>
    App::Time()
    {
        return CRef(impl->time);
    }

    const Version &App::EngineVersion() const
    {
        return impl->version;
    }

    const String &
    SDG::App::Name() const
    {
        return impl->config.appName;
    }
}

