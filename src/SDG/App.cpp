/// App implementation file
#include "App.h"
#include <SDG/Exceptions/AssertionException.h>
#include "Debug.hpp"
#include "Input.hpp"
#include <SDG/FileSys/FileSys.h>
#include <SDG/FileSys/XMLReader.h>
#include <SDG/Graphics/WindowMgr.h>

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
        Impl(const String &appName, const String &orgName) 
            : windows(), mainWindow(), isRunning(), time(), 
            fileSys(appName, orgName) {}

        WindowMgr   windows;
        Ref<Window> mainWindow;
        bool        isRunning;
        class AppTime  time;
        FileSys     fileSys;
        GameConfig  config;
    };


    App::App(const String &appName, const String &orgName, 
        const Path &configPath) : impl(new Impl(appName, orgName))
    {
        // Make our app's FileSys current
        Path::PushFileSys(Ref(impl->fileSys));

        // Get game settings from config file
        GameConfig config;
        try {
            XMLReader::ParseGameConfig(configPath.Str(), &config);
            impl->config = config;
        }
        catch(const std::exception &e)
        {
            SDG_Core_Err("Failed to parse game config.");
        }
    }


    App::~App()
    {
        Close_();
        delete impl;
    }


    int
    App::Initialize_()
    {
        SDG_Core_Log("Game initializing.");
        GameConfig &config = impl->config;
        Ref<Window> window;
        if (impl->windows.CreateWindow(config.width, config.height, 
            config.title.c_str(), 0, &window) >= 0)
        {
            impl->mainWindow = window;
            impl->mainWindow->Fullscreen(config.fullscreen);
        }

        // TODO: game config can specify input types through an array?
        InputDriver::Initialize(SDG_INPUTTYPE_DEFAULT);

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
        impl->windows.Close();
        SDG_Core_Log("Game shut down complete.");
    }


    void
    App::Run()
    {
        if (int err = Initialize_() != 0)
        {
            SDG_Core_Err("App failed to initialize: error code: {}", err);
            return;
        }

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
}

