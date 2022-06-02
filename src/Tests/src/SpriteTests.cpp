#include "SDG_Tests.h"
#include <SDG/Graphics/Sprite.h>

TEST_CASE("Sprite tests", "[Sprite]")
{
    SECTION("Default empty Sprite")
    {
        Sprite spr;
        REQUIRE(spr.Empty());
    }

    SECTION("Typical sprite")
    {
        Frame fr1({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame1", nullptr);
        Frame fr2({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame2", nullptr);
        Frame fr3({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame3", nullptr);
        Sprite spr("sprite", { fr1, fr2, fr3 }, {0, 1, 2});

        SECTION("Sprite has correct length")
        {
            REQUIRE(!spr.Empty());
            REQUIRE(spr.Length() == 3);
        }

        SECTION("Indexer reads correct frames")
        {
            REQUIRE(spr[0].Name() == "frame1");
            REQUIRE(spr[1].Name() == "frame2");
            REQUIRE(spr[2].Name() == "frame3");
        }

        SECTION("At reads correct frames")
        {
            REQUIRE(spr.At(0).Name() == "frame1");
            REQUIRE(spr.At(1).Name() == "frame2");
            REQUIRE(spr.At(2).Name() == "frame3");
        }

        SECTION("At throws exception when out of range")
        {
            bool didThrow = false;
            try {
                const Frame &f = spr.At(3);
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }

            REQUIRE(didThrow);
        }

        SECTION("Name")
        {
            REQUIRE(spr.Name() == "sprite");
        }
    }

    SECTION("Varying reel values targets correct frames")
    {
        Frame fr1({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame1", nullptr);
        Frame fr2({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame2", nullptr);
        Frame fr3({ 0, 0, 16, 16 }, { 0, 0, 16, 16 }, true, { 0, 0 }, "frame3", nullptr);
        Sprite spr("sprite", { fr1, fr2, fr3 }, {2, 1, 0, 1});

        REQUIRE(spr.Length() == 4);
        REQUIRE(spr[0].Name() == "frame3");
        REQUIRE(spr[1].Name() == "frame2");
        REQUIRE(spr[2].Name() == "frame1");
        REQUIRE(spr[3].Name() == "frame2");
    }

}