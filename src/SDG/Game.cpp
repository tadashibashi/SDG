//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "Platform.h"
#include "Game.h"

// TODO: abstract SDL_gpu into a GraphicsDevice class
#include <SDL_gpu.h>
#include <SDL.h>
#include <SDG/Exceptions/AssertionException.h>
#include <iostream>

#include "Platform.h"
#include "Debug.h"

#include "Input.h"
#include "XMLReader.h"
#include "SDG/Graphics/Texture2D.h"
#include <SDG/FileSys.h>


#include "SDG/Graphics/Shader.h"

using std::string;

#if defined (SDG_TARGET_HTML5) || defined (SDG_TARGET_ANDROID) || defined (SDG_TARGET_IPHONE)
    const GPU_RendererEnum RendererType = GPU_RENDERER_GLES_3;
#elif defined (SDG_TARGET_MAC) || defined (SDG_TARGET_LINUX) || defined (SDG_TARGET_WINDOWS)
    const GPU_RendererEnum RendererType = GPU_RENDERER_OPENGL_3;
#endif

const unsigned DefaultInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;

SDG::Game::Game() : window{}, isRunning{}
{
    Initialize();
}

// temporary test
SDG::Shader *shader = nullptr;
SDG::Texture2D *kirby = nullptr;

int
SDG::Game::Initialize()
{
    int winWidth = 1920, winHeight = 1080;
    bool fullscreen = false;
    string appName;
    string appOrg;
    string title = "";

    // Get Window information from config file
    try {
        XMLReader::ParseGameConfig("assets/config.sdgc", &appName, &appOrg, &title, &winWidth, &winHeight, &fullscreen);
    }
    catch(const std::exception &e)
    {
        std::cout << "Failed to parse config.\n";
        return -1;

    }
    FileSys::Initialize(appName, appOrg);


    GPU_Target *target = GPU_InitRenderer(RendererType, winWidth, winHeight, 0);
    if (!target)
    {
        std::cout << "Failed to init gpu target/sdl_gpu.\n";
        SDG_Err("Failed to initialize SDL_gpu GPU_Target: {}", GPU_GetErrorString(GPU_PopErrorCode().error));
        return -2;
    }

    SDL_Window *win = SDL_GetWindowFromID(target->context->windowID);
    SDL_SetWindowTitle(win, title.c_str());

    GPU_SetFullscreen(fullscreen, true);


    Input::Initialize();

    // Temp content
    kirby = new Texture2D("assets/textures/kirby.sdgc");
    shader = new Shader;
    shader->Compile("assets/shaders/v1.sdgc", "assets/shaders/f1.sdgc");


    window = target;
    isRunning = true;
    return 0;
}

SDG::Game::~Game()
{
    Close();
}

void
SDG::Game::RunOneFrame()
{
    try {
        ProcessInput();
        Update();
        Render();
    }
    catch(const AssertionException &e)
    {
        SDG_Err("{}", e.what());
        Exit();
    }

}

void
SDG::Game::ProcessInput()
{
    // Called before events are pumped to update all internal last* variables.
    Input::Update();

    // Event polling
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
            Exit();
    }
}

void
SDG::Game::Update()
{
    if (Input::KeyPressed(Key::Escape))
        Exit();
    // TODO: Test GPU_Camera

    if (Input::KeyPressed(Key::S) && Input::KeyPress(Key::V))
    {
        // Save the game!!
        FileSys::EncryptFile("game1.sav", {'m', 'y', ' ', 's', 'a', 'v', 'e'});
    }

    if (Input::KeyPressed(Key::L) && Input::KeyPress(Key::V))
    {
        // Loaded the game!!
        auto loadedSave = FileSys::DecryptFileStr("game1.sav", FileSys::Base::Pref);
        SDG_Log("Loaded save: \"{}\"", loadedSave.memory);
        loadedSave.Free();
    }


}

void
SDG::Game::Render()
{
    // Render
    GPU_ClearRGBA(window, 128, 128, 128, 255);

    shader->Activate();
    shader->SetVariable("time", (float)SDL_GetTicks());

    GPU_BlitScale(kirby->GetImage(), nullptr, window, (float)window->base_w/2,
            (window->base_h/2) + kirby->GetImage()->h * 0.1f * .5f, 0.1f, 0.1f);
    shader->Deactivate();

    GPU_BlitScale(kirby->GetImage(), nullptr, window, (float)window->base_w/2,
            window->base_h/2, 0.1f, 0.1f);

    GPU_Flip(window);
}

void
SDG::Game::Close()
{
    delete shader; // temp test
    delete kirby;

    Input::Close();
    GPU_Quit();
    SDL_Quit();
}

void
SDG::Game::Run()
{
    while (isRunning)
        RunOneFrame();
}

void
SDG::Game::Exit()
{
    isRunning = false;
}
