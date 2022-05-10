#include <SDG/SDG.hpp>
#include <SDL_gpu.h>
#include <SDG/Graphics/SpriteBatch.h>
#include <SDG/Math.hpp>
#include <SDG/Graphics/Camera2D.h>
#include <SDG/FileSys/Private/IO.h>

#include <catch2/catch_session.hpp>

using namespace SDG;

static SpriteBatch spriteBatch;
static Camera2D camera;

class TestGame : public App {
private:
    int Initialize() override
    {
        // Must run tests during initialization to test Input and FileSys functions,
        // which are initialized by App prior to this function call.
        Catch::Session().run();

        // Temp content
        kirby = new Texture2D(FileSys::MakePath("assets/textures/kirby.sdgc", FileSys::Base::Root));
        shader = new Shader;
        shader->Compile("assets/shaders/v1.sdgc", "assets/shaders/f1.sdgc");
        camera.Initialize(Window());
        camera.MakeCurrent();
        return 0;
    }

    void Update() override
    {
        if (Input::KeyPressed(Key::Escape))
            Exit();

        Vector2 mouseWorld = camera.ScreenToWorld((Vector2)Input::MousePosition());
        Window()->Title(mouseWorld.String().c_str());

        if (Input::KeyPressed(Key::Space))
        {
            SDG_Log("Seconds since game start: {}", Time()->Ticks() * 0.001f);
        }

        if (Input::KeyPressed(Key::S) && Input::KeyPress(Key::V))
        {
            // Save the game!!
            IO::WriteEncryptedFile(PrefPath("game1.sdgc").String().c_str(), {'m', 'y', ' ', 's', 'a', 'v', 'e'});
        }

        if (Input::KeyPressed(Key::L) && Input::KeyPress(Key::V))
        {
            // Loaded the game!!
            FileSys::File sav(PrefPath("game1.sdgc"));

            SDG_Log("Loaded save: \"{}\"", sav.Data());
        }

        if (Input::KeyPressed(Key::F))
        {
            Window()->Fullscreen(!Window()->Fullscreen());
        }

        if (Input::KeyPressed(Key::B))
        {
            Window()->Bordered(!Window()->Bordered());
        }

        if (Input::MousePressed(MButton::Left))
        {
            SDG_Log("Pressing left mouse button.");
        }
        if (Input::MousePressed(MButton::Right))
        {
            SDG_Log("Pressing right mouse button.");
        }
        if (Input::MouseWheelDidMove())
        {
            SDG_Log(Input::MouseWheel().String());
        }

        if (Input::KeyPress(Key::Right))
            camera.Translate({10, 0}), pos.X(pos.X() - 100);
        if (Input::KeyPress(Key::Left))
            camera.Translate({-10, 0}), pos.X(pos.X() + 100);
        if (Input::KeyPress(Key::Up))
            camera.Translate({0, -10});
        if (Input::KeyPress(Key::Down))
            camera.Translate({0, 10});

        if (Input::KeyPress(Key::C))
            camera.Rotate(10, camera.ScreenToWorld(camera.ScreenSize()/2));
        // Must be called after every alteration of the matrix has occured to update it to the gpu.

        if ((Input::KeyPress(Key::LeftShift) || Input::KeyPress(Key::RightShift)) &&
                Input::KeyPressed(Key::Equals))
            camera.Zoom(camera.Zoom() + Vector2(.1, .1));
        if ((Input::KeyPress(Key::LeftShift) || Input::KeyPress(Key::RightShift)) &&
                Input::KeyPressed(Key::Minus))
            camera.Zoom(camera.Zoom() - Vector2(.1, .1));

        camera.MakeCurrent();
    }

    float angle = 0;
    Matrix4x4 mat = Matrix4x4::Identity();
    Vector2 pos;

    void Render() override
    {
        if (Input::MouseWheelDidMove())
        {
            angle = fmod(angle + Input::MouseWheel().Y(), 360.f);
        }


        // Render
        auto window = Window();
        window->Clear(Color::BlueScreenOfDeath());

        shader->Activate();
        shader->SetUniform("time", (float) Time()->Ticks());

        //GPU_BlitScale(kirby->Image(), nullptr, window->InnerWindow().Get(), (float)window->Size().W() / 2,
        //              (window->Size().H()/2) + kirby->Image()->base_h * 0.1f * .5f, 0.1f, 0.1f);
        shader->Deactivate();

        //GPU_BlitScale(kirby->Image(), nullptr, window->InnerWindow().Get(), (float)window->Size().W() / 2,
         //             window->Size().H()/2, 0.1f, 0.1f);
        spriteBatch.Begin(window->Target());
        spriteBatch.DrawTexture(kirby, {0, 0, kirby->Image()->base_w, kirby->Image()->base_h},
                                {10, 10, (float) kirby->Image()->base_w / 100, (float) kirby->Image()->base_h / 100},
                                100, Vector2(0, 0), Flip::Both, Color::White(), 1.f);
        spriteBatch.DrawTexture(kirby, {0, 0, kirby->Image()->base_w, kirby->Image()->base_h},
                                {100, 100, (float) kirby->Image()->base_w / 100, (float) kirby->Image()->base_h / 100},
                                angle, Vector2(kirby->Image()->base_w / 2.f, kirby->Image()->base_h / 2.f),
                                Flip::None, Color::White(), 1.f);
        spriteBatch.DrawTexture(kirby,  Math::Transform(pos, mat), Vector2::One(),
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
};

/// Entry-point
App *CreateApp()
{
    return new TestGame;
}
