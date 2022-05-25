#include "SDG_Tests.h"
#include <SDG/Graphics/Camera2D.h>
#include <SDG/Graphics/RenderTarget.h>
#include <SDG/Graphics/Window.h>

TEST_CASE("Camera2D tests", "[Camera2D]")
{
    Camera2D camera;
    camera.ViewportSize(640, 480);
    
    SECTION("Window to World") // screen space view port not implemented...
    {
        REQUIRE(camera.ScreenToWorld({ 0, 0 }) == Vector2::Zero());
        camera.Position({ 100, 200 });
        REQUIRE(camera.ScreenToWorld({ 0, 0 }) == Vector2(100, 200));
        camera.Zoom({ 2.f, 2.f });
        camera.Position({0, 0});
        REQUIRE(camera.ScreenToWorld({ 100, 200 }) == Vector2(50, 100));
    }

    SECTION("World to Window")
    {
        REQUIRE(camera.WorldToScreen({ 0, 0 }) == Vector2::Zero());
        camera.Position({ 100, 100 });
        REQUIRE(camera.WorldToScreen({ 0, 0 }) == Vector2(-100, -100));
        camera.Zoom({ 2, 2 });
        REQUIRE(camera.WorldToScreen({ 0, 0 }) == Vector2(-200, -200));
    }

    SECTION("Rotation")
    {
        
    }
}