/* =============================================================================
 * WindowTests
 * 
 * 
 * ===========================================================================*/
#include <catch2/catch_test_macros.hpp>
#include <SDG/Graphics/Window.h>
#include <SDG/Graphics/RenderTarget.h>

using namespace SDG;

TEST_CASE("Window tests", "[Window]")
{
    Window window;

    SECTION("Initialize")
    {
        bool result = window.Initialize(100, 100, "TestWindow", 2);

        REQUIRE(result == true);
        REQUIRE(window.Size().X() == 100);
        REQUIRE(window.Size().Y() == 100);
        REQUIRE(window.Resolution().X() == 100);
        REQUIRE(window.Resolution().Y() == 100);
        REQUIRE(window.Viewport().X() == 0);
        REQUIRE(window.Viewport().Y() == 0);
        REQUIRE(window.Viewport().Width() == window.ClientSize().X());
        REQUIRE(window.Viewport().Height() == window.ClientSize().Y());
        REQUIRE((window.Flags() & 2) == 2);
        REQUIRE(window.Title() == "TestWindow");
    }

    SECTION("Initializing twice opens successfully")
    {
        bool result = window.Initialize(100, 100, "FirstWindow");
        REQUIRE(result == true);
        REQUIRE(window.Title() == "FirstWindow");

        result = window.Initialize(200, 200, "SecondWindow");
        REQUIRE(result == true);
        REQUIRE(window.Title() == "SecondWindow");
    }

    SECTION("Set Window properties")
    {
        bool result = window.Initialize(100, 100, "TestWindow");
        REQUIRE(result);

        SECTION("Position")
        {
            REQUIRE(&window == &window.Position({1234, 114}));
            REQUIRE(window.Position().X() == 1234);
            REQUIRE(window.Position().Y() == 114);

            REQUIRE(&window == &window.Position({100, 499}));
            REQUIRE(window.Position().X() == 100);
            REQUIRE(window.Position().Y() == 499);

            // For some reason, on my Mac, the lowest x position is -60,
            // and the lowest y position is 28. Anything lower than this gets
            // clamped out. Windows does not have this
            REQUIRE(&window == &window.Position({-60, 28}));
            REQUIRE(window.Position().X() == -60);
            REQUIRE(window.Position().Y() == 28);
        }

        SECTION("Resizable")
        {
            REQUIRE(!window.Resizable()); // default
            REQUIRE(&window == &window.Resizable(true)); // check returned ref
            REQUIRE(window.Resizable());  // check mutated
            window.Resizable(false);
            REQUIRE(!window.Resizable());
        }

        SECTION("Bordered")
        {
            REQUIRE(window.Bordered()); // default
            REQUIRE(&window == &window.Bordered(false));
            REQUIRE(!window.Bordered());
            window.Bordered(true);
            REQUIRE(window.Bordered());
        }

        SECTION("Fullscreen")
        {
            REQUIRE(!window.Fullscreen());
            REQUIRE(&window == &window.Fullscreen(true));
            REQUIRE(window.Fullscreen());
            window.Fullscreen(false);
            REQUIRE(!window.Fullscreen());
        }

        SECTION("Title")
        {
            SECTION("Nullptr results in blank title")
            {
                REQUIRE(&window == &window.Title(nullptr));
                REQUIRE(window.Title().empty());
            }

            SECTION("Title with chars sets correctly")
            {
                window.Title("Test title 1234567890");
                REQUIRE(window.Title() == "Test title 1234567890");
            }

            SECTION("Empty string results in empty string title")
            {
                REQUIRE(&window == &window.Title(""));
                REQUIRE(window.Title().empty());
            }
        }

        SECTION("Minimized")
        {
            REQUIRE(!window.Minimized());
            REQUIRE(&window == &window.Minimized(true));
            REQUIRE(window.Minimized());
            window.Minimized(false);
            REQUIRE(!window.Minimized());
        }

        SECTION("Hidden")
        {
            REQUIRE(!window.Hidden());
            REQUIRE(&window == &window.Hidden(true));
            REQUIRE(window.Hidden());
            window.Hidden(false);
            REQUIRE(!window.Hidden());
        }

        SECTION("MinimumSize can get/set")
        {
            window.MinimumSize({200, 200});
            REQUIRE(window.MinimumSize().X() == 200);
            REQUIRE(window.MinimumSize().Y() == 200);

            // zero or less is an illegal value, min size set to 1
            window.MinimumSize({0, 0});
            REQUIRE(window.MinimumSize().X() == 1);
            REQUIRE(window.MinimumSize().Y() == 1);

            window.MinimumSize({1080, 920});
            REQUIRE(window.MinimumSize().X() == 1080);
            REQUIRE(window.MinimumSize().Y() == 920);
        }

        SECTION("MinimumSize clamps size")
        {
            window.MinimumSize({200, 200});

            // prevent too small size
            window.ClientSize({1, 50});
            REQUIRE(window.ClientSize().X() == 200);
            REQUIRE(window.ClientSize().Y() == 200);

            // mutates smaller size: X
            window.MinimumSize({400, 25});
            REQUIRE(window.ClientSize().X() == 400);
            REQUIRE(window.ClientSize().Y() == 200);

            // mutates smaller size: Y
            window.MinimumSize({25, 500});
            REQUIRE(window.ClientSize().X() == 400);
            REQUIRE(window.ClientSize().Y() == 500);

            // mutates smaller size X and Y
            window.MinimumSize({800, 800});
            REQUIRE(window.ClientSize().X() == 800);
            REQUIRE(window.ClientSize().Y() == 800);
        }

        SECTION("MaximumSize can get/set")
        {
            window.MaximumSize({200, 200});
            REQUIRE(window.MaximumSize().X() == 200);
            REQUIRE(window.MaximumSize().Y() == 200);

            // zero or less is an illegal value, min size set to 1
            window.MaximumSize({0, 0});
            REQUIRE(window.MaximumSize().X() == 1);
            REQUIRE(window.MaximumSize().Y() == 1);

            window.MaximumSize({1080, 920});
            REQUIRE(window.MaximumSize().X() == 1080);
            REQUIRE(window.MaximumSize().Y() == 920);
        }

        SECTION("MaximumSize clamps size")
        {
            window.MaximumSize({200, 200});

            // prevent too big size
            window.ClientSize({2000, 2000});
            REQUIRE(window.ClientSize().X() == 200);
            REQUIRE(window.ClientSize().Y() == 200);

            // mutates bigger size: X
            window.MaximumSize({175, 25});
            REQUIRE(window.ClientSize().X() == 175);
            REQUIRE(window.ClientSize().Y() == 25);

            // mutates bigger size: Y
            window.MaximumSize({200, 175});
            REQUIRE(window.ClientSize().X() == 175);
            REQUIRE(window.ClientSize().Y() == 25);

            // mutates bigger size X and Y
            window.MaximumSize({125, 1});
            REQUIRE(window.ClientSize().X() == 125);
            REQUIRE(window.ClientSize().Y() == 1);
        }

        SECTION("MouseGrabbed")
        {
            REQUIRE(!window.MouseGrabbed());
            REQUIRE(&window == &window.MouseGrabbed(true));
            REQUIRE(window.MouseGrabbed());
            window.MouseGrabbed(false);
            REQUIRE(!window.MouseGrabbed());
        }

        SECTION("AlwaysOnTop")
        {
            REQUIRE(!window.AlwaysOnTop());
            REQUIRE(&window == &window.AlwaysOnTop(true));
            REQUIRE(window.AlwaysOnTop());
            window.AlwaysOnTop(false);
            REQUIRE(!window.AlwaysOnTop());
        }

        SECTION("Resolution")
        {
            // Resolution get/set basic
            REQUIRE(&window == &window.Resolution(window.ClientSize() * 2));
            REQUIRE(window.Resolution().X() == window.ClientSize().X());
            REQUIRE(window.Resolution().Y() == window.ClientSize().Y());

            // Resolution cannot be set to 0; clamped to 1
            window.Resolution(Point());
            REQUIRE(window.Resolution().X() == 1);
            REQUIRE(window.Resolution().Y() == 1);
        }
    }

    SECTION("Events process correctly")
    {
        window.Initialize(100, 100, "Event Processing");

        SECTION("On Close")
        {
            // Set up test callback
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Close.AddListener(&func);
            REQUIRE(window.On.Close.Size() == 1);

            // Create callback data
            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_CLOSE;
            ev.window.windowID = window.Id();

            // Pass to event handler
            window.ProcessInput(&ev);

            // Check that data was mutated via callback,
            // which means that this callback is working.
            REQUIRE(i == 1);
        }

        SECTION("On Show")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Show.AddListener(&func);
            REQUIRE(window.On.Show.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_SHOWN;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Hide")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Hide.AddListener(&func);
            REQUIRE(window.On.Hide.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_HIDDEN;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Expose")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Expose.AddListener(&func);
            REQUIRE(window.On.Expose.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_EXPOSED;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Move")
        {
            int x = 0, y = 0;
            std::function<void(int, int)> func = [&x, &y](int pX, int pY)->void {
                x = pX;
                y = pY;
            };

            window.On.Move.AddListener(&func);
            REQUIRE(window.On.Move.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_MOVED;
            ev.window.windowID = window.Id();
            ev.window.data1 = 143;
            ev.window.data2 = 245;
            window.ProcessInput(&ev);

            REQUIRE(x == 143);
            REQUIRE(y == 245);
        }

        SECTION("On Resize")
        {
            int x = 0, y = 0;
            std::function<void(int, int)> func = [&x, &y](int pX, int pY)->void {
                x = pX;
                y = pY;
            };

            window.On.Resize.AddListener(&func);
            REQUIRE(window.On.Resize.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_RESIZED;
            ev.window.windowID = window.Id();
            ev.window.data1 = 14;
            ev.window.data2 = 24;
            window.ProcessInput(&ev);

            REQUIRE(x == 14);
            REQUIRE(y == 24);
        }

        SECTION("On SizeChange")
        {
            int x = 0, y = 0;
            std::function<void(int, int)> func = [&x, &y](int pX, int pY)->void {
                x = pX;
                y = pY;
            };

            window.On.SizeChange.AddListener(&func);
            REQUIRE(window.On.SizeChange.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
            ev.window.windowID = window.Id();
            ev.window.data1 = 14;
            ev.window.data2 = 24;
            window.ProcessInput(&ev);

            REQUIRE(x == 14);
            REQUIRE(y == 24);
        }

        SECTION("On Minimize")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Minimize.AddListener(&func);
            REQUIRE(window.On.Minimize.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_MINIMIZED;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Fullscreen")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Fullscreen.AddListener(&func);
            REQUIRE(window.On.Fullscreen.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_MAXIMIZED;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Restore")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Restore.AddListener(&func);
            REQUIRE(window.On.Restore.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_RESTORED;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On MouseEnter")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.MouseEnter.AddListener(&func);
            REQUIRE(window.On.MouseEnter.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_ENTER;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On MouseLeave")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.MouseLeave.AddListener(&func);
            REQUIRE(window.On.MouseLeave.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_LEAVE;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Focus")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.Focus.AddListener(&func);
            REQUIRE(window.On.Focus.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }

        SECTION("On Focus Lost")
        {
            int i = 0;
            std::function<void()> func = [&i]()->void {
                i = 1;
            };

            window.On.FocusLost.AddListener(&func);
            REQUIRE(window.On.FocusLost.Size() == 1);

            SDL_Event ev;
            ev.type = SDL_WINDOWEVENT;
            ev.window.event = SDL_WINDOWEVENT_FOCUS_LOST;
            ev.window.windowID = window.Id();
            window.ProcessInput(&ev);

            REQUIRE(i == 1);
        }
    }


}
