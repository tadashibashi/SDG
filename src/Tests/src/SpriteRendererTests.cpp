#include "SDG_Tests.h"
#include <SDG/Graphics/SpriteRenderer.h>
#include <SDG/Graphics/Sprite.h>

TEST_CASE("SpriteRenderer tests", "[SpriteRenderer]")
{
    SpriteRenderer spr;

    SECTION("Paused")
    {
        spr.Paused(true);
        REQUIRE(spr.Paused());
        spr.Paused(false);
        REQUIRE(!spr.Paused());
    }

    SECTION("Position")
    {
        SECTION("two float overload")
        {
            REQUIRE(spr.Position() == Vector2::Zero());
            spr.Position(10, 20);
            REQUIRE(spr.Position() == Vector2(10, 20));
        }

        SECTION("Vector2 overload")
        {
            spr.Position({ 10.4f, 22.9f });
            REQUIRE(spr.Position() == Vector2(10.4f, 22.9f));
        }
    }

    SECTION("Scale")
    {
        SECTION("two float overload")
        {
            REQUIRE(spr.Scale() == Vector2::One());
            spr.Scale(1.5f, 20.f);
            REQUIRE(spr.Scale() == Vector2(1.5f, 20.f));
        }

        SECTION("Vector2 overload")
        {
            spr.Scale({ 10.4f, 22.9f });
            REQUIRE(spr.Scale() == Vector2(10.4f, 22.9f));
        }
    }

    SECTION("Angle")
    {
        // default value
        REQUIRE(spr.Angle() == 0);

        // normal value
        spr.Angle(19.f);
        REQUIRE(spr.Angle() == 19.f);

        // wrap tests
        spr.Angle(-10.f);
        REQUIRE(spr.Angle() == 350.f);
        spr.Angle(370.f);
        REQUIRE(spr.Angle() == 10.f);
    }

    SECTION("Speed")
    {
        REQUIRE(spr.Speed() == 1.f);
        spr.Speed(10.f);
        REQUIRE(spr.Speed() == 10.f);
    }

    SECTION("Fps")
    {
        REQUIRE(spr.Speed() == 1.f);
        spr.Speed(10.f);
        REQUIRE(spr.Speed() == 10.f);
    }

    SECTION("Flip")
    {
        REQUIRE(spr.Flip() == Flip::None);
        spr.Flip(Flip::Horizontal);
        REQUIRE(spr.Flip() == Flip::Horizontal);
    }

    SECTION("Sprite")
    {
        REQUIRE(!spr.Sprite());
        Sprite s("player-run", { {}, {} }, { 0, 0, 1, 1 });
        spr.Sprite(s);
        REQUIRE(spr.Sprite());
        REQUIRE(spr.Sprite()->Name() == "player-run");
        spr.Sprite(nullptr);
        REQUIRE(!spr.Sprite());
    }

    SECTION("Index")
    {
        // without sprite, index is set without limit
        REQUIRE(spr.Index() == 0);
        spr.Index(1004.f);
        REQUIRE(spr.Index() == 1004.f);
        spr.Index(-1234.f);
        REQUIRE(spr.Index() == -1234.f);

        // with a sprite, index must wrap about 0 and its length
        Sprite s("player-run", { {}, {} }, { 0, 0, 1, 1 });
        spr.Sprite(s);
        spr.Index(4.f);
        REQUIRE(spr.Index() == 0);
        spr.Index(-2.f);
        REQUIRE(spr.Index() == 2.f);
    }

    SECTION("Depth")
    {
        REQUIRE(spr.Depth() == 0);
        spr.Depth(10.f);
        REQUIRE(spr.Depth() == 10.f);
        spr.Depth(-123.f);
        REQUIRE(spr.Depth() == -123.f);
    }

    SECTION("Tint")
    {
        REQUIRE(spr.Tint() == Color::White());
        spr.Tint(Color::Amaranth());
        REQUIRE(spr.Tint() == Color::Amaranth());
        spr.Tint(Color::SeaBlue());
        REQUIRE(spr.Tint() == Color::SeaBlue());
    }
}