#include "SDG_Tests.h"
#include <Engine/Graphics/Camera2D.h>
#include <Engine/Graphics/RenderTarget.h>
#include <Engine/Graphics/Window.h>
#include <Engine/Math/Matrix4x4.h>

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

    SECTION("Rotate")
    {
        camera.Rotate(1);    // relative increment from zero
        REQUIRE(camera.Angle() == 1);
        camera.Rotate(10);   // relative increment
        REQUIRE(camera.Angle() == 11);
        camera.Rotate(360);  // wraps around
        REQUIRE(camera.Angle() == 11);
    }

    SECTION("Angle")
    {
        REQUIRE(camera.Angle() == 0);
        camera.Angle(10);  // absolute set
        REQUIRE(camera.Angle() == 10);
        camera.Angle(20);  // absolute set
        REQUIRE(camera.Angle() == 20);
        camera.Angle(375); // wrap around
        REQUIRE(camera.Angle() == 15);
    }

    SECTION("Zoom")
    {
        REQUIRE(camera.Scale() == Vector2::One());
        camera.Zoom({2.f, 2.f});
        REQUIRE(camera.Scale() == Vector2(2.f, 2.f));
        camera.Zoom(3.f);             // one float sets both
        REQUIRE(camera.Scale() == Vector2(6.f, 6.f));
        camera.Zoom(.5f, .5f);        // two floats sets each
        REQUIRE(camera.Scale() == Vector2(3.f, 3.f));
        camera.Zoom({ 4.f, 4.f });    // one Vector2 sets both
        REQUIRE(camera.Scale() == Vector2(12.f, 12.f));
    }

    SECTION("Scale")
    {
        REQUIRE(camera.Scale() == Vector2::One());
        camera.Scale(2.f);             // one float sets both
        REQUIRE(camera.Scale() == Vector2(2.f, 2.f));
        camera.Scale(5.f, 1.f);  // two floats sets each
        REQUIRE(camera.Scale() == Vector2(5.f, 1.f));
        camera.Scale({ 1.f, 2.4f });   // one Vector2 sets both
        REQUIRE(camera.Scale() == Vector2(1.f, 2.4f));
    }

    SECTION("PivotPoint")
    {
        REQUIRE(camera.PivotPoint() == Vector2::Zero());
        camera.PivotPoint(30, 30);
        REQUIRE(camera.PivotPoint() == Vector2(30, 30));
        camera.PivotPoint({ 45, 70 });
        REQUIRE(camera.PivotPoint() == Vector2(45, 70));
    }

    SECTION("Translate")
    {
        REQUIRE(camera.Position() == Vector2::Zero());
        camera.Translate({ 2.f, 2.f });    // Vector2 setter
        REQUIRE(camera.Position() == Vector2(2.f, 2.f));
        camera.Translate({ -10.f, -4.f }); // negative Vector2 setter
        REQUIRE(camera.Position() == Vector2(-8.f, -2.f));
        camera.Translate(5.f, 6.f);   // two floats sets each
        REQUIRE(camera.Position() == Vector2(-3.f, 4.f));
    }

    SECTION("ViewportSize")
    {
        camera.ViewportSize(200, 200);
        REQUIRE(camera.ViewportSize() == Point(200, 200));
        camera.ViewportSize(450, 180);  // two floats sets each
        REQUIRE(camera.ViewportSize() == Point(450, 180));
    }

    SECTION("Matrix")
    {
        REQUIRE(*camera.Matrix() == Matrix4x4::Identity());
    }
}