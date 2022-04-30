//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "Game.h"
#include "Platform.h"
// TODO: abstract SDL_gpu into a GraphicsDevice class
#include <SDL_gpu.h>
#include <SDL.h>
#include <SDG/Exceptions/AssertionException.h>
#include <iostream>

#include "Debug.h"

#include "Input.h"
#include "XMLReader.h"
#include <SDG/Graphics/Texture2D.h>
#include "SDG/FileSys/FileSys.h"
#include <SDG/FileSys/IO.h>


#include "SDG/Graphics/Shader.h"
#include "SDG/FileSys/File.h"

using std::string;

#if defined (SDG_TARGET_WEBGL) || defined (SDG_TARGET_ANDROID) || defined (SDG_TARGET_IPHONE)
    const GPU_RendererEnum RendererType = GPU_RENDERER_GLES_3;
#elif SDG_TARGET_DESKTOP
    const GPU_RendererEnum RendererType = GPU_RENDERER_OPENGL_3;
#endif

const unsigned DefaultInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;

SDG::Game::Game() : window{}, isRunning{}
{

}

// TODO: Put these objects into a ContentManager
SDG::Shader *shader = nullptr;
SDG::Texture2D *kirby = nullptr;

// TODO: Finish implementing Camera wrapper
GPU_Camera cam;

int
SDG::Game::Initialize()
{
    SDG_Log("Game initializing.");
    int winWidth = 1920, winHeight = 1080;
    bool fullscreen = false;
    string appName;
    string appOrg;
    string title;

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

    window.Initialize();
    window
        .Fullscreen(fullscreen)
        .Size(Point{winWidth, winHeight})
        .Title(title.c_str());



    GPU_SetFullscreen(fullscreen, true);

    Input::Initialize();

    // Temp content
    kirby = new Texture2D(FileSys::MakePath("assets/textures/kirby.sdgc", FileSys::Base::Root));
    shader = new Shader;
    shader->Compile("assets/shaders/v1.sdgc", "assets/shaders/f1.sdgc");

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
    // Called before events are pumped to update all internal last state variables.
    Input::Update();

    // Event polling
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
            Exit();
        Input::ProcessInput(&ev);
    }
}

void
SDG::Game::Update()
{
    if (Input::KeyPressed(Key::Escape))
        Exit();
    // TODO: Test GPU_Camera

    if (Input::KeyPress(Key::Left))
        cam.x -= 8;
    if (Input::KeyPress(Key::Right))
        cam.x += 8;
    if (Input::KeyPress(Key::Up))
        cam.y -= 8;
    if (Input::KeyPress(Key::Down))
        cam.y += 8;
    if (Input::KeyPress(Key::Return))
        //cam.zoom_x += .1, cam.zoom_y += .1;
        cam.angle -= 8;
    if (Input::KeyPress(Key::RightShift))
        //cam.zoom_x -= .1, cam.zoom_y -= .1;
        cam.angle += 8;
    if (Input::KeyPressed(Key::C))
        cam.use_centered_origin = !cam.use_centered_origin, SDG_Log("Pressed C");



    if (Input::KeyPressed(Key::S) && Input::KeyPress(Key::V))
    {
        // Save the game!!
        IO::WriteEncryptedFile("game1.sav", {'m', 'y', ' ', 's', 'a', 'v', 'e'});
    }

    if (Input::KeyPressed(Key::L) && Input::KeyPress(Key::V))
    {
        // Loaded the game!!
        FileSys::File sav(FileSys::MakePath("game1.sav", FileSys::Base::Pref));

        SDG_Log("Loaded save: \"{}\"", sav.Data());
    }


}

void
SDG::Game::Render()
{
    // Render
    window.Clear(Color::DarkKhaki());

    shader->Activate();
    shader->SetUniform("time", (float) SDL_GetTicks());

    GPU_BlitScale(kirby->Image(), nullptr, window.InnerWindow(), (float)window.Size().w / 2,
            (window.Size().h/2) + kirby->Image()->h * 0.1f * .5f, 0.1f, 0.1f);
    shader->Deactivate();

    GPU_BlitScale(kirby->Image(), nullptr, window.InnerWindow(), (float)window.Size().w / 2,
            window.Size().h/2, 0.1f, 0.1f);

    window.SwapBuffers();
}

void
SDG::Game::Close()
{
    SDG_Log("Closing Game Object");
    delete shader; // temp test
    delete kirby;

    Input::Close();
    GPU_Quit();

}

void
SDG::Game::Run()
{
    Initialize();
    while (isRunning)
        RunOneFrame();
}

void
SDG::Game::Exit()
{
    isRunning = false;
#if SDG_TARGET_WEBGL
    emscripten_cancel_main_loop();
#endif
}
