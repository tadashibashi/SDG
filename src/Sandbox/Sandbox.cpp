#include <SDG/SDG.hpp>
#include <SDG/Graphics/Font.h>
using namespace SDG;

class Sandbox : public App 
{
public:
    Sandbox() : App(
        //{640, 480, true,
        //"SDG Engine Test",
        //"SDG Engine Test", "aaronishibashi"}
        "assets/config.sdgc"
    )
    {
        Texture::DefaultFilterMode(Texture::Filter::Nearest);
    }
private:
    // Test objects / members
    Ref<Window> window2;
    Texture kirby;
    Texture kirby2;
    Texture pixels;
    Shader shader;
    Font font;
    Camera2D camera;
    SpriteBatch spriteBatch;

    float angle = 0;
    Matrix4x4 mat = Matrix4x4::Identity();
    Vector2 pos;

    int Initialize() override
    {
        //Windows()->CreateWindow(300, 300, "Window2", 0, &window2);
        spriteBatch.Initialize(MainWindow());
        LoadContent();
        return 0;
    }


    void LoadContent()
    {
        //if (font.Load(BasePath("assets/fonts/CourierPrimeCode.sdgc"), 32))
        //{
        //    text = font.CreateTextSolid(MainWindow(), "Hello", Color::MediumPurple());
        //    if (text)
        //    {
        //        SDG_Core_Log("Loaded texture: dimensions: {}", text->Size());
        //        text->FilterMode(TexFilter::Linear).Blending(true).SnapMode(TexSnap::PositionAndDimensions);
        //    }
        //}
        //else
        //{
        //    SDG_Core_Warn("Failed to load font!\n");
        //}
        uint8_t pixs[] = {
            255, 255, 255, 255,
            0, 255, 0, 255,
            255, 0, 0, 255,
            0, 255, 255, 255
        };

        pixels.LoadPixels(MainWindow(), 2, 2, pixs);
        font.Load(MainWindow(), BasePath("assets/fonts/CourierPrimeCode.sdgc"), 32, FontStyle::Bold | FontStyle::Italic);
        camera.PivotPoint({320, 240});
        kirby.Load(MainWindow(), BasePath("assets/textures/DawSession.sdgc"));
        //kirby2.Load(window2, BasePath("assets/textures/DawSession.sdgc"));

        shader.Compile(BasePath("assets/shaders/v1.sdgc"), BasePath("assets/shaders/f1.sdgc"));

    }

    void Update() override
    {
        if (Input::KeyPressed(Key::Escape))
            Exit();

        if (MainWindow()->IsOpen())
        {
            Vector2 mouseWorld = camera.ScreenToWorld((Vector2)Input::MousePosition());
            MainWindow()->Title(mouseWorld.Str().Cstr());
        }


        if (Input::KeyPressed(Key::Space))
        {
            SDG_Core_Log("Seconds since game start: {}", Time()->As(TimeUnit::Seconds));
        }

        if (Input::KeyPressed(Key::S) && Input::KeyPress(Key::V))
        {
            // Save the game!!
            File file;
            file.Write("My saved game!");
            file.Write(Time()->As(TimeUnit::Seconds));
            file.SaveAs(PrefPath("game1.sdgc"));
        }

        if (Input::KeyPressed(Key::L) && Input::KeyPress(Key::V))
        {
            // Loaded the game!!
            File sav(PrefPath("game1.sdgc"));
            String str;
            sav.Read(str, 14);
            double i;
            sav.Read(i);
            SDG_Core_Log("Loaded save: \"{}\": {}", str, i);
        }

        if (Input::KeyPressed(Key::F))
        {
            MainWindow()->Fullscreen(!MainWindow()->Fullscreen());
        }

        if (Input::KeyPressed(Key::B))
        {
            MainWindow()->Bordered(!MainWindow()->Bordered());
        }

        if (Input::MousePressed(MButton::Left))
        {
            SDG_Core_Log("Pressing left mouse button.");
        }
        if (Input::MousePressed(MButton::Right))
        {
            SDG_Core_Log("Pressing right mouse button.");
        }
        if (Input::MouseWheelDidMove())
        {
            SDG_Core_Log(Input::MouseWheel().Str());
        }

        if (MainWindow()->IsOpen())
        {
            if (Input::KeyPress(Key::Right))
                camera.Translate(Vector2{ 10, 0 }), 
                pos.X(pos.X() - 100);
            if (Input::KeyPress(Key::Left))
                camera.Translate(Vector2{ -10, 0 }), 
                pos.X(pos.X() + 100);
            if (Input::KeyPress(Key::Up))
                camera.Translate({0, -10});
            if (Input::KeyPress(Key::Down))
                camera.Translate({0, 10});

            if (Input::KeyPress(Key::C))
                camera.Rotate(10);
            // Must be called after every alteration of the matrix has occured to update it to the gpu.

            if ((Input::KeyPress(Key::LeftShift) || Input::KeyPress(Key::RightShift)) &&
                Input::KeyPress(Key::Equals))
                camera.Zoom({1.1f, 1.1f});
            if ((Input::KeyPress(Key::LeftShift) || Input::KeyPress(Key::RightShift)) &&
                Input::KeyPress(Key::Minus))
                camera.Zoom({0.9f, 0.9f});
        }
        
        if (Input::MouseWheelDidMove())
        {
            angle = fmod(angle + Input::MouseWheel().Y(), 360.f);
        }
    }



    void Render() override
    {
        auto window = MainWindow();
        if (window->IsOpen())
        {
            window->Clear(Color::BlueScreenOfDeath());

            shader.Activate();
            shader.SetUniform("time", (float) Time()->Ticks());

            //GPU_BlitScale(kirby->Image(), nullptr, window->InnerWindow().Get(), (float)window->Size().W() / 2,
            //              (window->Size().H()/2) + kirby->Image()->base_h * 0.1f * .5f, 0.1f, 0.1f);
            shader.Deactivate();

            //GPU_BlitScale(kirby->Image(), nullptr, window->InnerWindow().Get(), (float)window->Size().W() / 2,
            //             window->Size().H()/2, 0.1f, 0.1f);

            spriteBatch.Begin(window->Target(), camera.Matrix());
            Point imgSize = kirby.Size();
            
           
            spriteBatch.DrawTexture(kirby, {0, 0, (int)imgSize.X(), (int)imgSize.Y()},
                                    {0.f, 0.f, (float) imgSize.X() / 100.f, (float) imgSize.Y() / 100.f},
                                    0, Vector2(110, 110), Flip::None, Color::White(), 1.f);

            spriteBatch.DrawTexture(pixels, { 100, 100 });
            spriteBatch.DrawTexture(pixels, { 102, 100 });
            spriteBatch.DrawTexture(kirby, {0, 0, (int)imgSize.X(), (int)imgSize.Y()},
                                    {100.f, 100.f, (float)imgSize.X() / 100.f, (float)imgSize.Y() / 100.f},
                                    angle, Vector2(imgSize.X() / 2.f, imgSize.Y() / 2.f), Flip::None, Color::White(), 1.f);
            spriteBatch.DrawTexture(kirby,  Math::Transform(pos, mat), Vector2::One(),
                                    {.5f,.5f}, angle*2, angle, Color{(uint8_t)(angle/360.f * 255.f), 255});
            spriteBatch.DrawRectangle(FRectangle{ 0, 0, 100, 100 }, Vector2{ .5f, .5f }, Color(Math::ModF(angle, 255.f), 0, 128, 255), angle, 0);
            spriteBatch.DrawLines({ {0, 0}, {2.f, 4.f}, {100.f, 100.f}, {350.f, 10.f}, {0, 0} }, 10, Color::HalloweenOrange(), 0);
            spriteBatch.DrawLine(Vector2{ 300.f, 300.f }, 100, angle, 3, Color( ((Math::Sin(Math::RadsPerDeg*angle) + 1.0) * .5) * 255, 255, 128, 255 ), 0);

            spriteBatch.End();
            font.Draw(window->Target(), { 10, 20 }, { 1.f, 1.f }, FontAlign::Center, Color::MonarchOrange(128),
                "Mouse position: {} {}", Input::MousePosition().Y(), Input::MousePosition().X());

        }

        //if (window2->IsOpen())
        //{
        //    window2->Clear(Color::OrangeRed());
        //    spriteBatch.Begin(window2->Target(), camera.Matrix());
        //    Point imgSize = kirby2.Size();
        //    spriteBatch.DrawTexture(&kirby2, {0, 0, imgSize.X(), imgSize.Y()},
        //                            {100, 100, (float)  imgSize.X()/ 20.f, (float) imgSize.Y() / 20.f},
        //                            0, Vector2(0, 0), Flip::None, Color::White(), 1.f);
        //    spriteBatch.End();
        //}


    }

    void Close() override
    {
        kirby.Close();
        kirby2.Close();
        shader.Close();
    }
};

/// Entry-point
App *CreateApp()
{
    return new Sandbox;
}
