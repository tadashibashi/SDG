#include "SDG_Tests.h"
#include <Engine/Graphics/Color.h>

TEST_CASE("Color tests", "[Color]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            Color color;
            REQUIRE(color.R() == Color::COLOR_MAX);
            REQUIRE(color.G() == Color::COLOR_MAX);
            REQUIRE(color.B() == Color::COLOR_MAX);
            REQUIRE(color.A() == Color::COLOR_MAX);
        }

        SECTION("From StringView")
        {
            SECTION("Standard Case")
            {
                String str = "FFa0b0c0";
                Color color;
                bool didThrow = false;
                try {
                    color = Color(str, Color::Format::ARGB8888);
                }
                catch (const std::exception &e)
                {
                    didThrow = true;
                }

                REQUIRE(!didThrow);
                REQUIRE(color.A() == 0xFF);
                REQUIRE(color.R() == 0xA0);
                REQUIRE(color.G() == 0xB0);
                REQUIRE(color.B() == 0xC0);
            }

            SECTION("Prepended symbol")
            {
                String str = "#FFa0b0c0";
                Color color = Color(str, Color::Format::ARGB8888);

                REQUIRE(color.A() == 0xFF);
                REQUIRE(color.R() == 0xA0);
                REQUIRE(color.G() == 0xB0);
                REQUIRE(color.B() == 0xC0);
            }

        }

        SECTION("Parameters")
        {
            SECTION("Full")
            {
                Color color(0, 186, 243, 255);
                REQUIRE(color.R() == 0);
                REQUIRE(color.G() == 186);
                REQUIRE(color.B() == 243);
                REQUIRE(color.A() == 255);
            }
            SECTION("With default alpha")
            {
                Color color(0, 186, 243);
                REQUIRE(color.R() == 0);
                REQUIRE(color.G() == 186);
                REQUIRE(color.B() == 243);
                REQUIRE(color.A() == Color::COLOR_MAX);
            }
        }
        SECTION("Setters")
        {
            Color color;
            color.Set(0, 1, 2, 3);
            REQUIRE(color.R() == 0);
            REQUIRE(color.G() == 1);
            REQUIRE(color.B() == 2);
            REQUIRE(color.A() == 3);

            color.R(10).G(9).B(8).A(7);
            REQUIRE(color.R() == 10);
            REQUIRE(color.G() == 9);
            REQUIRE(color.B() == 8);
            REQUIRE(color.A() == 7);
        }
    }
}