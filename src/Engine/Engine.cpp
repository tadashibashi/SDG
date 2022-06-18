/// App implementation file
#include "Engine.h"
#include <Engine/Exceptions/AssertionException.h>
#include <Engine/Debug/Assert.h>
#include <Engine/Debug/Log.h>
#include <Engine/Input/Input.h>
#include <Engine/Filesys/Filesys.h>
#include <Engine/Game/Datatypes/AppConfig.h>

#include <Engine/Graphics/WindowMgr.h>
#include <Engine/Platform.h>

#include <SDL.h>

#include <Engine/Filesys/Json.h>

#if (SDG_TARGET_WEBGL)
static void EmMainLoop(void *arg)
{
    ((SDG::Engine *)arg)->RunOneFrame();
}
#endif

namespace SDG
{
    // ===== App Implementation ===============================================
    struct Engine::Impl 
    {
        Impl() 
            : windows(new WindowMgr), mainWindow(), isRunning(), time(), 
            fileSys(), config() {}
        ~Impl();

        void Initialize(const AppConfig &config);

        Unique<WindowMgr> windows;
        Ref<Window> mainWindow;
        bool        isRunning;
        AppTime     time;
        Filesys     fileSys;
        AppConfig   config;
    };


    Engine::Engine(const String &configPath) : impl(new Impl)
    {
        // Get game settings from config file
        AppConfig config;
        config.LoadJson(BasePath(configPath));
        impl->Initialize(std::move(config));
    }

    Engine::~Engine()
    {
        Close_();
    }


    int
    Engine::Initialize_()
    {
        auto &config = impl->config;

        Ref<Window> window;
        for (auto i = size_t{0}; i < config.windows.size(); ++i)
        {
            auto &windata = config.windows[i];
            if (impl->windows->CreateWindow(windata.width, windata.height, 
                windata.title.Cstr(), windata.winFlags, i == 0 ? &window : nullptr) >= 0)
            {
                SDG_Core_Log("- window [{}] initialized", i);
            }
            else
            {
                SDG_Core_Err("- window [{}] init failed!", i);
                return -1;
            }
        }
        impl->mainWindow = window;

        // TODO: game config can specify input types through an array?
        InputDriver::Initialize(SDG_INPUTTYPE_DEFAULT);
        SDG_Core_Log("- input driver: ok");

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
                        impl->windows->ProcessInput(ev.window);
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
        impl->windows->Close();
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

    Ref<Window>
    Engine::MainWindow()
    {
        SDG_Assert(impl->mainWindow);
        return impl->mainWindow;
    }

    Ref<WindowMgr>
    Engine::Windows()
    {
        return impl->windows.Get();
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
        impl->windows->SwapBuffers();
    }

    Ref< const AppTime>
    Engine::Time()
    {
        return impl->time;
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

    json &Engine::Config()
    {
        return impl->config.Json();
    }

    const json &Engine::Config() const
    {
        return impl->config.Json();
    }
    
    void Engine::Impl::Initialize(const AppConfig &config)
    {
        std::stringstream ss;
        ss << String::Format("\n"
            "*===========================================================================*\n"
            "  SDG Engine v{}\n"
            "    Platform:   {}: {}\n"
            "    Debug mode: {}\n"
            "\n"
            "-----------------------------------------------------------------------------\n",
            Engine::Version(), TargetPlatformName(), SIZEOF_VOIDP == 8 ? "64-bit" : "32-bit", SDG_DEBUG ? "ON" : "OFF");
        ss << String::Format(
            "  {} [{}]\n"
            "     Window Count: {}\n", config.appName, config.orgName, config.windows.size());
        size_t winId = 0;
        for (auto &windata : config.windows)
        {
            ss << String::Format(
            "        [{}] Title: \"{}\", Size: {} x {}, Flags: {}\n",
            winId++, windata.title, windata.width, windata.height, windata.winFlags);
        }
        SDG_Core_Log("{}\n", ss.str());

        SDG_Core_Log("Initializing engine...");

        SDG_Assert(!config.appName.Empty());
        SDG_Assert(!config.orgName.Empty());
        fileSys.Initialize(config.appName, config.orgName);
        Path::PushFileSys(fileSys);

        SDG_Core_Log("- filesystem: ok");

        this->config = config;
    }
    
    Engine::Impl::~Impl()
    {
        Path::PopFileSys();
    }
}

