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
        SDG::Rectangle rect;
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
        SDG::Rectangle rect;
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

    SECTION("Side tests")
    {
        SECTION("Left")
        {
            SECTION("Increasing left decreases width")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Left(10);
                REQUIRE(rect.Left() == 10);
                REQUIRE(rect.X() == 10);
                REQUIRE(rect.Width() == 90);
            }

            SECTION("Smaller left position increases width")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Left(-10);
                REQUIRE(rect.Left() == -10);
                REQUIRE(rect.X() == -10);
                REQUIRE(rect.Width() == 110);
            }

            SECTION("Left further than right is limited by right")
            {
                Rectangle rect(0, 0, 100, 100);
                rect.Left(200);
                REQUIRE(rect.Left() == 100);
                REQUIRE(rect.X() == 100);
                REQUIRE(rect.Width() == 0);
            }
        }

        SECTION("Right")
        {
            SECTION("Increasing right increases width")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Right(110);
                REQUIRE(rect.Right() == 110);
                REQUIRE(rect.Width() == 110);
            }

            SECTION("Smaller right position decreases width")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Right(90);
                REQUIRE(rect.Right() == 90);
                REQUIRE(rect.Width() == 90);
            }

            SECTION("Right lower than left is limited by left")
            {
                Rectangle rect(0, 0, 100, 100);
                rect.Right(-10);
                REQUIRE(rect.Right() == 0);
                REQUIRE(rect.X() == 0);
                REQUIRE(rect.Width() == 0);
            }
        }

        SECTION("Top")
        {
            SECTION("Increasing top decreases height")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Top(10);
                REQUIRE(rect.Top() == 10);
                REQUIRE(rect.Y() == 10);
                REQUIRE(rect.Height() == 90);
            }

            SECTION("Smaller top position increases height")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Top(-10);
                REQUIRE(rect.Top() == -10);
                REQUIRE(rect.Y() == -10);
                REQUIRE(rect.Height() == 110);
            }

            SECTION("Right lower than left is limited by left")
            {
                Rectangle rect(0, 0, 100, 100);
                rect.Top(110);
                REQUIRE(rect.Top() == 100);
                REQUIRE(rect.Y() == 100);
                REQUIRE(rect.Height() == 0);
            }
        }

        SECTION("Bottom")
        {
            SECTION("Increasing bottom increases height")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Bottom(110);
                REQUIRE(rect.Bottom() == 110);
                REQUIRE(rect.Height() == 110);
            }

            SECTION("Smaller bottom position decreases height")
            {
                FRectangle rect(0, 0, 100, 100);
                rect.Bottom(90);
                REQUIRE(rect.Bottom() == 90);
                REQUIRE(rect.Height() == 90);
            }

            SECTION("bottom lower than top is limited by top")
            {
                Rectangle rect(0, 0, 100, 100);
                rect.Bottom(-10);
                REQUIRE(rect.Bottom() == 0);
                REQUIRE(rect.Y() == 0);
                REQUIRE(rect.Height() == 0);
            }
        }
    }

    SECTION("Corners")
    {
        SECTION("LeftTop")
        {
            Rectangle rect(0, 0, 100, 100);
            rect.LeftTop({10, 10});
            REQUIRE(rect.LeftTop() == Point{10, 10});
            REQUIRE(rect.Top() == 10);
            REQUIRE(rect.Left() == 10);
        }
        SECTION("RightTop")
        {
            Rectangle rect(0, 0, 100, 100);
            rect.RightTop({110, 10});
            REQUIRE(rect.RightTop() == Point{110, 10});
            REQUIRE(rect.Top() == 10);
            REQUIRE(rect.Right() == 110);
        }
        SECTION("LeftBottom")
        {
            Rectangle rect(0, 0, 100, 100);
            rect.LeftBottom({-10, 90});
            REQUIRE(rect.LeftBottom() == Point{-10, 90});
            REQUIRE(rect.Bottom() == 90);
            REQUIRE(rect.Left() == -10);
        }
        SECTION("RightBottom")
        {
            Rectangle rect(0, 0, 100, 100);
            rect.RightBottom({90, 90});
            REQUIRE(rect.RightBottom() == Point{90, 90});
            REQUIRE(rect.Bottom() == 90);
            REQUIRE(rect.Right() == 90);
        }
    }
}

