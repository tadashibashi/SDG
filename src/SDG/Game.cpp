//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Game.h"
#include <SDG/Exceptions/AssertionException.h>
#include "Debug.hpp"
#include "Input.hpp"
#include <SDG/FileSys/XMLReader.h>
#include <SDG/FileSys/FileSys.h>

#include <SDG/Graphics/Window.h>

#include <SDL.h>

using std::string;

#if SDG_TARGET_WEBGL
static void EmMainLoop(void *arg)
{
    ((SDG::Game *)arg)->RunOneFrame();
}
#endif

struct SDG::Game::Impl {
    Impl() : window(), isRunning(), time() {}
    SDG::Window window;
    bool isRunning;
    SDG::GameTime time;
};

SDG::Game::Game() : impl(new Impl)
{

}

SDG::Game::~Game()
{
    Close_();
    delete impl;
}

int
SDG::Game::Initialize_()
{
    SDG_Log("Game initializing.");
    GameConfig config;

    // Get game settings from config file
    try {
        XMLReader::ParseGameConfig("assets/config.sdgc", &config);
    }
    catch(const std::exception &e)
    {
        SDG_Err("Failed to parse game config.");
        return -1;
    }

    FileSys::Initialize(config.appName, config.appOrg);

    impl->window.Initialize(config.width, config.height, config.title.c_str());
    impl->window.Fullscreen(config.fullscreen);

    Input::Initialize();

    impl->isRunning = true;

    return Initialize(); // Child class initialization;
}



void
SDG::Game::ProcessInput()
{
    Input::UpdateLastStates();

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
                impl->window.ProcessInput(&ev);
                break;
        }

        Input::ProcessInput(&ev);
    }
}

void
SDG::Game::RunOneFrame()
{
    try {
        ProcessInput();
        Update_();
        Render_();
    }
    catch(const AssertionException &e)
    {
        SDG_Err("{}", e.what());
        Exit();
    }
}


void
SDG::Game::Close_()
{
    Close(); // Child class clean up
    Input::Close();
    impl->window.Close();
    SDG_Log("Game shut down complete.");
}

void
SDG::Game::Run()
{
    if (int err = Initialize_() != 0)
    {
        SDG_Err("Problem occured during initialization: error code: {}", err);
        return;
    }
#if SDG_TARGET_WEBGL
    emscripten_set_main_loop_arg(EmMainLoop, this, -1, true);
#else
    while (impl->isRunning)
        RunOneFrame();
#endif
}

void
SDG::Game::Exit()
{
    impl->isRunning = false;
#if SDG_TARGET_WEBGL
    Close();
    emscripten_cancel_main_loop();
#endif
}

SDG::Ref<SDG::Window>
SDG::Game::Window()
{
    return Ref(impl->window);
}

void
SDG::Game::Update_()
{
    impl->time.Update();
    Update();
}

void
SDG::Game::Render_()
{
    Render();
    impl->window.SwapBuffers();
}

const SDG::CRef<SDG::GameTime>
SDG::Game::Time()
{
    return CRef(impl->time);
}
