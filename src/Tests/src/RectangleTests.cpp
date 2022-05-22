#include "SDG_Tests.h"
#include <SDG/Math/Rectangle.h>
#include <sstream>

TEST_CASE("FRectangle tests", "[FRectangle]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            FRectangle rect;
            REQUIRE(rect.X() == 0);
            REQUIRE(rect.Y() == 0);
            REQUIRE(rect.Width() == 0);
            REQUIRE(rect.Height() == 0);
        }
        SECTION("With setters")
        {
            FRectangle rect(1.f, 2.f, 3.f, 4.f);
            REQUIRE(rect.X() == 1.f);
            REQUIRE(rect.Y() == 2.f);
            REQUIRE(rect.Width() == 3.f);
            REQUIRE(rect.Height() == 4.f);
        }
    }

    SECTION("Setters")
    {
        FRectangle rect;

        SECTION("Direct to members")
        {
            rect.X(2.f).Y(3.f).Width(2.5f).Height(78.f);
            REQUIRE(rect.X() == 2.f);
            REQUIRE(rect.Y() == 3.f);
            REQUIRE(rect.Width() == 2.5f);
            REQUIRE(rect.Height() == 78.f);
        }
        SECTION("Set")
        {
            rect.Set(10.f, 20.f, 30.f, 40.f);
            REQUIRE(rect.X() == 10.f);
            REQUIRE(rect.Y() == 20.f);
            REQUIRE(rect.Width() == 30.f);
            REQUIRE(rect.Height() == 40.f);
        }
    }

    SECTION("Empty")
    {
        FRectangle rect;
        REQUIRE(rect.Empty());

        rect.Set(0, 0, 20.f, 20.f);
        REQUIRE(!rect.Empty());
    }

    SECTION("Area")
    {
        FRectangle rect;
        REQUIRE(rect.Area() == 0);
        rect.Width(10.f).Height(10.f);
        REQUIRE(rect.Area() == 100.f);

        rect.Width(20.f).Height(2);
        REQUIRE(rect.Area() == 40.f);

        rect.Width(100).Height(.5f);
        REQUIRE(rect.Area() == 50.f);
    }

    SECTION("Side Getters")
    {
        FRectangle rect;
        SECTION("Left")
        {
            REQUIRE(rect.Left() == 0);
            rect.X(100);
            REQUIRE(rect.Left() == 100);
            rect.X(-400.5f);
            REQUIRE(rect.Left() == -400.5f);
            rect.X(5000.00123f);
            REQUIRE(rect.Left() == 5000.00123f);
        }
        SECTION("Top")
        {
            REQUIRE(rect.Top() == 0);
            rect.Y(100);
            REQUIRE(rect.Top() == 100);
            rect.Y(-400.5f);
            REQUIRE(rect.Top() == -400.5f);
            rect.Y(5000.00123f);
            REQUIRE(rect.Top() == 5000.00123f);
        }
        SECTION("Right")
        {
            REQUIRE(rect.Right() == 0);
            rect.X(100);
            REQUIRE(rect.Right() == 100);
            rect.X(-400.5f).Width(400.5f);
            REQUIRE(rect.Right() == 0);
            rect.X(20.f).Width(15.f);
            REQUIRE(rect.Right() == 35.f);
        }
        SECTION("Bottom")
        {
            REQUIRE(rect.Bottom() == 0);
            rect.Y(10);
            REQUIRE(rect.Bottom() == 10);
            rect.Height(20.f);
            REQUIRE(rect.Bottom() == 30.f);
            rect.Y(20.f).Height(50.5f);
            REQUIRE(rect.Bottom() == 70.5f);
        }
    }


    SECTION("String")
    {
        // using normal Rectangle here since it's hard to predict floating point results
        Rectangle rect;
        REQUIRE(rect.Str() == "{0, 0, 0, 0}");
        rect.Set(1, 2, 3, 4);
        REQUIRE(rect.Str() == "{1, 2, 3, 4}");
        rect.Set(-44, -25, 499, 459);
        REQUIRE(rect.Str() == "{-44, -25, 499, 459}");
    }

    SECTION("operator == (const FRectangle &)")
    {
        FRectangle rect1;
        FRectangle rect2;
        REQUIRE((rect1 == rect2));
        rect1.Set(1, 2, 3, 4);
        rect2.Set(1, 2, 3, 4);
        REQUIRE((rect1 == rect2));
        rect1.Set(1, 2, 3, 4);
        rect2.Set(-1, -2, -3, -4);
        REQUIRE(!(rect1 == rect2));
        rect1.Set(100, 200, 300, 400);
        rect2.Set(100, 200, 300, 400);
        REQUIRE((rect1 == rect2));
    }

    SECTION("operator != (const FRectangle &)")
    {
        FRectangle rect1;
        FRectangle rect2;
        REQUIRE(!(rect1 != rect2));
        rect1.Set(1, 2, 3, 4);
        rect2.Set(-1, 2, 3, -4);
        REQUIRE((rect1 != rect2));
        rect1.Set(1, 2, 3, -4);
        rect2.Set(1, 2, 3, 4);
        REQUIRE((rect1 != rect2));
        rect1.Set(100, 200, 300, 400);
        rect2.Set(100, 200, 300, 400);
        REQUIRE(!(rect1 != rect2));
    }

    SECTION("operator << (ostream &, const FRectangle &)")
    {
        std::stringstream ss;
        Rectangle rect;
        ss << rect;
        REQUIRE(ss.str() == "{0, 0, 0, 0}");
        ss.str(std::string());

        rect.Set(1, 2, 3, 4);
        ss << rect;
        REQUIRE(ss.str() == "{1, 2, 3, 4}");
        ss.str(std::string());

        rect.Set(-200, 300, 24, 25);
        ss << rect;
        REQUIRE(ss.str() == "{-200, 300, 24, 25}");
        ss.str(std::string());

        rect.Set(-20041, -3004124, 241243, 2512355);
        ss << rect;
        REQUIRE(ss.str() == "{-20041, -3004124, 241243, 2512355}");
    }
}

