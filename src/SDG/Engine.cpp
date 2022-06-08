/// App implementation file
#include "Engine.h"
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
    struct Engine::Impl 
    {
        Impl() 
            : windows(), mainWindow(), isRunning(), time(), 
            fileSys(), config() {}
        ~Impl();

        void Initialize(const AppConfig &config);

        WindowMgr   windows;
        Ref<Window> mainWindow;
        bool        isRunning;
        AppTime     time;
        FileSys     fileSys;
        AppConfig   config;
    };


    Engine::Engine(const String &configPath) : impl(new Impl)
    {

        // Get game settings from config file
        AppConfig config;
        config.Load(BasePath(configPath));
        impl->Initialize(config);
    }

    Engine::Engine(const AppConfig &config) : impl(new Impl)
    {
        impl->Initialize(config);
    }


    Engine::~Engine()
    {
        Close_();
        delete impl;
    }


    int
    Engine::Initialize_()
    {
        AppConfig &config = impl->config;
        Ref<Window> window;
        if (impl->windows.CreateWindow(config.width, config.height, 
            config.title.Cstr(), impl->config.winFlags, &window) >= 0)
        {
            impl->mainWindow = window;
            SDG_Core_Log("- graphics library and window: ok!");
        }
        else
        {
            SDG_Core_Err("- graphics library and window: failed!");
            return -1;
        }

        // TODO: game config can specify input types through an array?
        InputDriver::Initialize(SDG_INPUTTYPE_DEFAULT);
        SDG_Core_Log("- input driver. ok!");

        impl->isRunning = true;
        return Initialize(); // Child class initialization;
    }


    void
    Engine::ProcessInput()
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
    Engine::RunOneFrame()
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
    Engine::Close_()
    {
        Close(); // Child class clean up
        InputDriver::Close();
        Path::PopFileSys();
        impl->windows.Close();
        SDG_Core_Log("Engine shutdown complete.");
    }


    void
    Engine::Run()
    {
        if (int err = Initialize_() != 0)
        {
            SDG_Core_Err("Engine failed to initialize: error code: {}", err);
            return;
        }
        SDG_Core_Log("Done! Entering application loop...");

    #if (SDG_TARGET_WEBGL)
        emscripten_set_main_loop_arg(EmMainLoop, this, -1, true);
    #else
        while (impl->isRunning)
            RunOneFrame();
    #endif
    }

    void
    SDG::Engine::Exit()
    {
        impl->isRunning = false;
    #if (SDG_TARGET_WEBGL) // since emscripten's main loop is infinite, we need to immediately exit.
        Close();
        emscripten_cancel_main_loop();
    #endif
    }

    Ref<SDG::Window>
    Engine::MainWindow()
    {
        SDG_Assert(impl->mainWindow);
        return impl->mainWindow;
    }

    Ref<SDG::WindowMgr>
    Engine::Windows()
    {
        return Ref(impl->windows);
    }

    void
    Engine::Update_()
    {
        impl->time.Update();
        Update();
    }

    void
    Engine::Render_()
    {
        Render();
        impl->windows.SwapBuffers();
    }

    CRef<AppTime>
    Engine::Time()
    {
        return CRef(impl->time);
    }

    const String &
    Engine::Name() const
    {
        return impl->config.appName;
    }

    // static
    Version Engine::Version()
    {
        static SDG::Version v(SDG_VERSION_MAJOR, SDG_VERSION_MINOR, SDG_VERSION_PATCH);
        return v;
    }
    
    void Engine::Impl::Initialize(const AppConfig &config)
    {
        SDG_Core_Log("\n"
            "*===========================================================================*\n"
            "  SDG Engine v{}\n"
            "    Platform:   {}: {}\n"
            "    Debug mode: {}\n"
            "\n"
            "-----------------------------------------------------------------------------\n"
            "  {} [{}]\n"
            "     Window\n"
            "        Title: \"{}\"\n"
            "        Size : {} x {}\n"
            "        Flags: {}"
            "\n"
            "*===========================================================================*\n",
            Engine::Version(), TargetPlatformName(), SIZEOF_VOIDP == 8 ? "64-bit" : "32-bit", SDG_DEBUG ? "ON" : "OFF",
            config.appName, config.orgName, config.title, config.width, config.height, config.winFlags);

        SDG_Core_Log("Initializing engine...");

        SDG_Assert(!config.appName.Empty());
        SDG_Assert(!config.orgName.Empty());
        fileSys.Initialize(config.appName, config.orgName);
        Path::PushFileSys(fileSys);

        SDG_Core_Log("- filesystem. ok!");

        this->config = config;
    }
    
    Engine::Impl::~Impl()
    {
        Path::PopFileSys();
    }
}

