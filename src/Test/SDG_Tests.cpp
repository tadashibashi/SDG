#include "DelegateTests.h"
#include "MatrixTests.h"
#include <SDG/SDG.hpp>
#include <SDL_gpu.h>
#include <SDG/Graphics/SpriteBatch.h>

using namespace SDG;

static SpriteBatch spriteBatch;

class TestGame : public Game {
private:
    int Initialize() override
    {
        // Initialization logic here
        TestDelegate();
        TestMatrix();
        // Temp content
        kirby = new Texture2D(FileSys::MakePath("assets/textures/kirby.sdgc", FileSys::Base::Root));
        shader = new Shader;
        shader->Compile("assets/shaders/v1.sdgc", "assets/shaders/f1.sdgc");

        return 0;
    }

    void Update() override
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
float angle = 0;
    void Render() override
    {
        angle = fmod(angle + 1, 360.f);

        // Render
        Window &window = GetWindow();
        window.Clear(Color::Cerulean());

        shader->Activate();
        shader->SetUniform("time", (float) SDL_GetTicks());

        GPU_BlitScale(kirby->Image(), nullptr, window.InnerWindow(), (float)window.Size().w / 2,
                      (window.Size().h/2) + kirby->Image()->h * 0.1f * .5f, 0.1f, 0.1f);
        shader->Deactivate();

        GPU_BlitScale(kirby->Image(), nullptr, window.InnerWindow(), (float)window.Size().w / 2,
                      window.Size().h/2, 0.1f, 0.1f);
        spriteBatch.Begin(window.InnerWindow());
        spriteBatch.DrawTexture(kirby, {0, 0, kirby->Image()->base_w, kirby->Image()->base_h},
                                {10, 10, (float) kirby->Image()->base_w / 100, (float) kirby->Image()->base_h / 100},
                                100, Vector2(.5, .5), Flip::Vertical, Color::White(), 1.f);
        spriteBatch.DrawTexture(kirby, {0, 0, kirby->Image()->base_w, kirby->Image()->base_h},
                                {100, 100, (float) kirby->Image()->base_w / 100, (float) kirby->Image()->base_h / 100},
                                angle, Vector2(kirby->Image()->base_w / 2.f, kirby->Image()->base_h / 2.f),
                                Flip::None, Color::White(), 1.f);
        spriteBatch.DrawTexture(kirby, {angle, angle}, {angle/180.f, angle/180.f},
                                {.5f,.5f}, angle*2, angle, Color{(uint8_t)(angle/360.f * 255.f), 255});
        spriteBatch.End();
    }

    void Close() override
    {
        delete kirby;
        delete shader;
    }

    // Test Objects
    Shader *shader;
    Texture2D *kirby;
    GPU_Camera cam;
};

/// Entry-point
Game *CreateGame()
{
    return new TestGame;
}
