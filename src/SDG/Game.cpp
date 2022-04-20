//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "Game.h"
#include <SDL_gpu.h>
#include <SDL.h>
#include <tinyxml2.h>

#include "Platform.h"
#include "Logging.h"
#include "Input.h"
#include "XMLReader.h"

#include "Shader.h"

using namespace tinyxml2;

#if defined (SDG_TARGET_HTML5) || defined (SDG_TARGET_ANDROID) || defined (SDG_TARGET_IPHONE)
    const GPU_RendererEnum RendererType = GPU_RENDERER_GLES_2;
#elif defined (SDG_TARGET_MAC) || defined (SDG_TARGET_LINUX) || defined (SDG_TARGET_WINDOWS)
    const GPU_RendererEnum RendererType = GPU_RENDERER_OPENGL_3;
#endif

const unsigned DefaultInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;

SDG::Game::Game() : window()
{
    Initialize();
}

// temporary test
Shader *shader = nullptr;
GPU_Image *kirby = nullptr;

// temporary, make content manager to handle this
bool LoadImage(const char *path, GPU_Image **out)
{
    GPU_Image *img = GPU_LoadImage(path);

    if (img)
    {
        GPU_SetSnapMode(img, GPU_SNAP_NONE);
        GPU_SetWrapMode(img, GPU_WRAP_NONE, GPU_WRAP_NONE);
        *out = img;
        return true;
    }
    else
    {
        *out = nullptr;
        SDG_Err("Failed to load image from path: \"{}\"", path);
        return false;
    }
}



int
SDG::Game::Initialize()
{
    if (!SDL_WasInit(DefaultInitFlags))
    {
        if (SDL_Init(DefaultInitFlags) != 0)
        {
            SDG_Err("Problem initializing SDL2: {}", SDL_GetError());
            return -1;
        }
    }

    int winWidth = 1920, winHeight = 1080;
    bool fullscreen = false;
    std::string title = "";

    // Get Window information from config file
    XMLReader::ParseGameConfig("assets/config.xml", &title, &winWidth, &winHeight, &fullscreen);

    GPU_Target *target = GPU_InitRenderer(RendererType, winWidth, winHeight, 0);
    if (!target)
    {
        SDG_Err("Failed to initialize SDL_gpu GPU_Target: {}", GPU_GetErrorString(GPU_PopErrorCode().error));
        return -2;
    }

    GPU_SetFullscreen(fullscreen, true);

    Input::Initialize();

    // Temp content
    LoadImage("assets/kirby.png", &kirby);
    shader = new Shader;
    shader->Compile("assets/v1.vert", "assets/f1.frag");


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
    ProcessInput();
    Update();
    Render();
}

void
SDG::Game::ProcessInput()
{
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
    if (Input::KeyPressed(SDL_SCANCODE_ESCAPE))
        Exit();
}

void
SDG::Game::Render()
{
    // Render
    GPU_ClearRGBA(window, 128, 128, 128, 255);

    shader->Activate();
    float time = (float)SDL_GetTicks();
    shader->SetVariable("time", time);

    //shader->SetVariable("resolution", {100, 100}, 2);

    GPU_BlitScale(kirby, NULL, window, window->base_w/2, (window->base_h/2) + kirby->h * 0.1f * .5f, 0.1f, 0.1f);

    GPU_DeactivateShaderProgram();
    GPU_BlitScale(kirby, NULL, window, window->base_w/2, window->base_h/2, 0.1f, 0.1f);

    GPU_Flip(window);
}

void
SDG::Game::Close()
{

    delete shader; // temp test
    GPU_FreeImage(kirby); // temp test

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
