#include "SDG_Tests.h"
#include <SDG/Math/Intersection.h>
#include <SDG/Math/MathShape.h>

TEST_CASE("Shape.h")
{
    SECTION("Vector2 Lerp")
    {
        SECTION("half")
        {
            Vector2 start;
            Vector2 target(100, 100);
            REQUIRE(Math::Lerp(start, target, .5) == Vector2(50, 50));
        }

        SECTION("moved start point")
        {
            Vector2 start(-50, -50);
            Vector2 target(50, 50);
            REQUIRE(Math::Lerp(start, target, .5) == Vector2(0, 0));
        }

        SECTION("zero amt remains at starting point")
        {
            Vector2 start(-50, -50);
            Vector2 target(50, 50);
            REQUIRE(Math::Lerp(start, target, 0) == start);
        }

        SECTION("one amt reaches target")
        {
            Vector2 start(-50, -50);
            Vector2 target(50, 50);
            REQUIRE(Math::Lerp(start, target, 1) == target);
        }
    }

    SECTION("FRectangle Lerp")
    {
        SECTION("halfway")
        {
            FRectangle start;
            FRectangle target(100, 100, 100, 100);
            REQUIRE(Math::Lerp(start, target, .5) == FRectangle(50, 50, 50, 50));
        }

        SECTION("moved start point")
        {
            FRectangle start(-50, -50, 50, 50);
            FRectangle target(50, 50, 100, 100);
            REQUIRE(Math::Lerp(start, target, .5) == FRectangle(0, 0, 75, 75));
        }

        SECTION("zero amt remains at starting point")
        {
            FRectangle start(-50, -50, 50, 50);
            FRectangle target(50, 50, 1000, 1000);
            REQUIRE(Math::Lerp(start, target, 0) == start);
        }

        SECTION("one amt reaches target")
        {
            FRectangle start(-50, -50, 100, 100);
            FRectangle target(50, 50, 1000, 2000);
            REQUIRE(Math::Lerp(start, target, 1) == target);
        }
    }

    SECTION("Circle Lerp")
    {
        SECTION("half")
        {
            Circle start;
            Circle target(100, 100, 100);
            REQUIRE(Math::Lerp(start, target, .5) == Circle(50, 50, 50));
        }

        SECTION("moved start point")
        {
            Circle start(-50, -50, 50);
            Circle target(50, 50, 100);
            REQUIRE(Math::Lerp(start, target, .5) == Circle(0, 0, 75));
        }

        SECTION("zero amt remains at starting point")
        {
            Circle start(-50, -50, 50);
            Circle target(50, 50, 100);
            REQUIRE(Math::Lerp(start, target, 0) == start);
        }

        SECTION("one amt reaches target")
        {
            Circle start(-50, -50, 50);
            Circle target(50, 50, 100);
            REQUIRE(Math::Lerp(start, target, 1) == target);
        }
    }

    SECTION("Round")
    {
        SECTION("Round Vector2")
        {
            REQUIRE(Math::Round(Vector2(1.111111f, 0.9999999f)) == Vector2::One());
            REQUIRE(Math::Round(Vector2(-0.5f, -1.4f)) == -Vector2::One());
            REQUIRE(Math::Round(Vector2::Zero()) == Vector2::Zero());
        }

        SECTION("Round Vector3")
        {
            REQUIRE(Math::Round(Vector3(1.111111f, 0.5f, 0.99999f)) == Vector3::One());
            REQUIRE(Math::Round(Vector3(-0.5f, -1.0001f, -1.487f)) == -Vector3::One());
            REQUIRE(Math::Round(Vector3::Zero()) == Vector3::Zero());
        }

        SECTION("Round FRectangle")
        {
            REQUIRE(Math::Round(FRectangle(0.0001f, -9.9999f, .5f, 22.1f)) == FRectangle(0, -10, 1, 22));
            REQUIRE(Math::Round(FRectangle(0.4f, -9.4f, .4f, 10.4f)) == FRectangle(0, -9, 0, 10));
            REQUIRE(Math::Round(FRectangle(1, 2, 3, 4)) == FRectangle(1, 2, 3, 4));
        }

        SECTION("Round Circle")
        {
            REQUIRE(Math::Round(Circle(14.4f, 14.5f, 16.4f)) == Circle(14, 15, 16));
            REQUIRE(Math::Round(Circle(-13.999f, -15.14f, -15.99f)) == Circle(-14, -15, -16));
            REQUIRE(Math::Round(Circle(14, 15, 16)) == Circle(14, 15, 16));
        }
    }

    SECTION("RoundN")
    {
        SECTION("Vector2")
        {
            SECTION("hundreths place")
            {
                Vector2 v(0.005f, -0.014f);
                REQUIRE(Math::RoundN(v, -2) == Vector2(0.01f, -0.01f));
            }
            SECTION("hundreds place")
            {
                Vector2 v(1850, -1840);
                REQUIRE(Math::RoundN(v, 2) == Vector2(1900, -1800));
            }
            SECTION("zero places")
            {
                Vector2 v(108.423f, -192.412f);
                REQUIRE(Math::RoundN(v, 0) == Vector2(108, -192));
            }
        }
        SECTION("Vector3")
        {
            SECTION("hundreths place")
            {
                Vector3 v(0.005f, -0.014f, 923.123f);
                REQUIRE(Math::RoundN(v, -2) == Vector3(0.01f, -0.01f, 923.12f));
            }
            SECTION("hundreds place")
            {
                Vector3 v(1850, -1840, 18493);
                REQUIRE(Math::RoundN(v, 2) == Vector3(1900, -1800, 18500));
            }
            SECTION("zero places")
            {
                Vector3 v(108.423f, -192.412f, 1234.523f);
                REQUIRE(Math::RoundN(v, 0) == Vector3(108, -192, 1235));
            }
        }
        SECTION("Circle")
        {
            SECTION("hundreths place")
            {
                Circle c(0.005f, -0.014f, 923.123f);
                REQUIRE(Math::RoundN(c, -2) == Circle(0.01f, -0.01f, 923.12f));
            }
            SECTION("hundreds place")
            {
                Circle c(1850, -1840, 18493);
                REQUIRE(Math::RoundN(c, 2) == Circle(1900, -1800, 18500));
            }
            SECTION("zero places")
            {
                Circle c(108.423f, -192.412f, 1234.523f);
                REQUIRE(Math::RoundN(c, 0) == Circle(108, -192, 1235));
            }
        }
        SECTION("FRectangle")
        {
            SECTION("hundreths place")
            {
                FRectangle r(0.005f, -0.014f, 923.123f, 13.145f);
                REQUIRE(Math::RoundN(r, -2) == FRectangle(0.01f, -0.01f, 923.12f, 13.15f));
            }
            SECTION("hundreds place")
            {
                FRectangle r(1850, -1840, 18493, 2432);
                REQUIRE(Math::RoundN(r, 2) == FRectangle(1900, -1800, 18500, 2400));
            }
            SECTION("zero places")
            {
                FRectangle r(108.423f, -192.412f, 1234.523f, 143.123f);
                REQUIRE(Math::RoundN(r, 0) == FRectangle(108, -192, 1235, 143));
            }
        }
    }

    SECTION("Clamp")
    {
        SECTION("Vector2 within two Vector2")
        {
            SECTION("Transparently pass vec within limits")
            {
                Vector2 pnt(10, 20);
                Vector2 min(0, 0);
                Vector2 max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Vector2(10, 20));
            }
            SECTION("Lower limit clamped x")
            {
                Vector2 pnt(10, 20);
                Vector2 min(50, 0);
                Vector2 max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Vector2(50, 20));
            }
            SECTION("Lower limit clamped y")
            {
                Vector2 pnt(10, 20);
                Vector2 min(0, 50);
                Vector2 max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Vector2(10, 50));
            }
            SECTION("Lower limit clamped")
            {
                Vector2 pnt(10, 20);
                Vector2 min(50, 50);
                Vector2 max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == min);
            }
            SECTION("Upper limit clamped x")
            {
                Vector2 pnt(10, 20);
                Vector2 min(0, 0);
                Vector2 max(5, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Vector2(5, 20));
            }
            SECTION("Upper limit clamped y")
            {
                Vector2 pnt(10, 20);
                Vector2 min(0, 0);
                Vector2 max(100, 10);
                REQUIRE(Math::Clamp(pnt, min, max) == Vector2(10, 10));
            }
            SECTION("Upper limit clamped")
            {
                Vector2 pnt(10, 20);
                Vector2 min(0, 0);
                Vector2 max(5, 5);
                REQUIRE(Math::Clamp(pnt, min, max) == max);
            }
        }

        SECTION("Vector2 within an FRectangle")
        {
            SECTION("Transparent if not crossing limits")
            {
                Vector2 point(50, 50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == point);
            }

            SECTION("Clamped on right side")
            {
                Vector2 point(250, 50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(100, 50));
            }
            SECTION("Clamped on left side")
            {
                Vector2 point(-100, 50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(0, 50));
            }
            SECTION("Clamped on top side")
            {
                Vector2 point(50, -50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(50, 0));
            }
            SECTION("Clamped on bottom")
            {
                Vector2 point(50, 250);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(50, 100));
            }
            SECTION("Clamped on top-left corner")
            {
                Vector2 point(-50, -50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2::Zero());
            }
            SECTION("Clamped on top-right corner")
            {
                Vector2 point(250, -50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(100, 0));
            }
            SECTION("Clamped on bottom-left corner")
            {
                Vector2 point(-50, 250);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(0, 100));
            }
            SECTION("Clamped on bottom-right corner")
            {
                Vector2 point(250, 250);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Vector2(100, 100));
            }
        }

        SECTION("Point within two Points")
        {
            SECTION("Transparently pass vec within limits")
            {
                Point pnt(10, 20);
                Point min(0, 0);
                Point max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Point(10, 20));
            }
            SECTION("Lower limit clamped x")
            {
                Point pnt(10, 20);
                Point min(50, 0);
                Point max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Point(50, 20));
            }
            SECTION("Lower limit clamped y")
            {
                Point pnt(10, 20);
                Point min(0, 50);
                Point max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Point(10, 50));
            }
            SECTION("Lower limit clamped")
            {
                Point pnt(10, 20);
                Point min(50, 50);
                Point max(100, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == min);
            }
            SECTION("Upper limit clamped x")
            {
                Point pnt(10, 20);
                Point min(0, 0);
                Point max(5, 100);
                REQUIRE(Math::Clamp(pnt, min, max) == Point(5, 20));
            }
            SECTION("Upper limit clamped y")
            {
                Point pnt(10, 20);
                Point min(0, 0);
                Point max(100, 10);
                REQUIRE(Math::Clamp(pnt, min, max) == Point(10, 10));
            }
            SECTION("Upper limit clamped")
            {
                Point pnt(10, 20);
                Point min(0, 0);
                Point max(5, 5);
                REQUIRE(Math::Clamp(pnt, min, max) == max);
            }
        }

        SECTION("Point within an Rectangle")
        {
            SECTION("Transparent if not crossing limits")
            {
                Point point(50, 50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == point);
            }

            SECTION("Clamped on right side")
            {
                Point point(250, 50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(100, 50));
            }
            SECTION("Clamped on left side")
            {
                Point point(-100, 50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(0, 50));
            }
            SECTION("Clamped on top side")
            {
                Point point(50, -50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(50, 0));
            }
            SECTION("Clamped on bottom")
            {
                Point point(50, 250);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(50, 100));
            }
            SECTION("Clamped on top-left corner")
            {
                Point point(-50, -50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point::Zero());
            }
            SECTION("Clamped on top-right corner")
            {
                Point point(250, -50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(100, 0));
            }
            SECTION("Clamped on bottom-left corner")
            {
                Point point(-50, 250);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(0, 100));
            }
            SECTION("Clamped on bottom-right corner")
            {
                Point point(250, 250);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(point, rect) == Point(100, 100));
            }
        }


        SECTION("Circle within an FRectangle")
        {
            SECTION("Transparent if not crossing limits")
            {
                Circle circ(50, 50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == circ);
            }

            SECTION("zero-sized Circle behaves like a point")
            {
                Circle circ(1000, 50, 0);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(100, 50, 0));
            }

            SECTION("Clamped on right side")
            {
                Circle circ(250, 50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(90, 50, 10));
            }
            SECTION("Clamped on left side")
            {
                Circle circ(-100, 50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(10, 50, 10));
            }
            SECTION("Clamped on top side")
            {
                Circle circ(50, -50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(50, 10, 10));
            }
            SECTION("Clamped on bottom")
            {
                Circle circ(50, 250, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(50, 90, 10));
            }
            SECTION("Clamped on top-left corner")
            {
                Circle circ(-50, -50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(10, 10, 10));
            }
            SECTION("Clamped on top-right corner")
            {
                Circle circ(250, -50, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(90, 10, 10));
            }
            SECTION("Clamped on bottom-left corner")
            {
                Circle circ(-50, 250, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(10, 90, 10));
            }
            SECTION("Clamped on bottom-right corner")
            {
                Circle circ(250, 250, 10);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Clamp(circ, rect) == Circle(90, 90, 10));
            }
        }
    }

    SECTION("Wrap")
    {
        SECTION("Vector2 inside of FRectangle")
        {
            SECTION("Transparent when inside limits")
            {
                Vector2 point(50, 50);
                FRectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Wrap(point, rect) == point);
            }
            SECTION("Right side")
            {
                SECTION("Once over")
                {
                    Vector2 point(100, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(0, 50));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(10000, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(0, 50));
                }
                SECTION("One hundred times over")
                {
                    Vector2 point(10000, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(0, 50));
                }
            }
            SECTION("Left side")
            {
                SECTION("Once over")
                {
                    Vector2 point(-1, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(99, 50));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(-1001, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(99, 50));
                }
                SECTION("One-hundred times over")
                {
                    Vector2 point(-10001, 50);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(99, 50));
                }
            }
            SECTION("Bottom side")
            {
                SECTION("Once over")
                {
                    Vector2 point(50, 100);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 0));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(50, 1000);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 0));
                }
                SECTION("One-hundred times over")
                {
                    Vector2 point(50, 10000);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 0));
                }
            }
            SECTION("Top side")
            {
                SECTION("Once over")
                {
                    Vector2 point(50, -1);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 99));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(50, -1001);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 99));
                }
                SECTION("One hundred times over")
                {
                    Vector2 point(50, -10001);
                    FRectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Vector2(50, 99));
                }
            }
        }

        SECTION("Vector2 inside of FRectangle + margin")
        {
            SECTION("Transparent when inside limits")
            {
                Vector2 point(50, 50);
                FRectangle rect(10, 10, 80, 80);
                REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == point);
            }
            SECTION("Right side")
            {
                SECTION("Once over")
                {
                    Vector2 point(100, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(0, 50));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(10000, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(0, 50));
                }
                SECTION("One hundred times over")
                {
                    Vector2 point(10000, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(0, 50));
                }
            }
            SECTION("Left side")
            {
                SECTION("Once over")
                {
                    Vector2 point(-1, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(99, 50));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(-1001, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(99, 50));
                }
                SECTION("One-hundred times over")
                {
                    Vector2 point(-10001, 50);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(99, 50));
                }
            }
            SECTION("Bottom side")
            {
                SECTION("Once over")
                {
                    Vector2 point(50, 100);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 0));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(50, 1000);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 0));
                }
                SECTION("One-hundred times over")
                {
                    Vector2 point(50, 10000);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 0));
                }
            }
            SECTION("Top side")
            {
                SECTION("Once over")
                {
                    Vector2 point(50, -1);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 99));
                }
                SECTION("Ten times over")
                {
                    Vector2 point(50, -1001);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 99));
                }
                SECTION("One hundred times over")
                {
                    Vector2 point(50, -10001);
                    FRectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Vector2(50, 99));
                }
            }
        }

        SECTION("Point inside of Rectangle")
        {
            SECTION("Transparent when inside limits")
            {
                Point point(50, 50);
                Rectangle rect(0, 0, 100, 100);
                REQUIRE(Math::Wrap(point, rect) == point);
            }
            SECTION("Right side")
            {
                SECTION("Once over")
                {
                    Point point(100, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(0, 50));
                }
                SECTION("Ten times over")
                {
                    Point point(10000, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(0, 50));
                }
                SECTION("One hundred times over")
                {
                    Point point(10000, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(0, 50));
                }
            }
            SECTION("Left side")
            {
                SECTION("Once over")
                {
                    Point point(-1, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(99, 50));
                }
                SECTION("Ten times over")
                {
                    Point point(-1001, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(99, 50));
                }
                SECTION("One-hundred times over")
                {
                    Point point(-10001, 50);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(99, 50));
                }
            }
            SECTION("Bottom side")
            {
                SECTION("Once over")
                {
                    Point point(50, 100);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 0));
                }
                SECTION("Ten times over")
                {
                    Point point(50, 1000);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 0));
                }
                SECTION("One-hundred times over")
                {
                    Point point(50, 10000);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 0));
                }
            }
            SECTION("Top side")
            {
                SECTION("Once over")
                {
                    Point point(50, -1);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 99));
                }
                SECTION("Ten times over")
                {
                    Point point(50, -1001);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 99));
                }
                SECTION("One hundred times over")
                {
                    Point point(50, -10001);
                    Rectangle rect(0, 0, 100, 100);
                    REQUIRE(Math::Wrap(point, rect) == Point(50, 99));
                }
            }
        }

        SECTION("Point inside of Rectangle + margin")
        {
            SECTION("Transparent when inside limits")
            {
                Point point(50, 50);
                Rectangle rect(10, 10, 80, 80);
                REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == point);
            }
            SECTION("Right side")
            {
                SECTION("Once over")
                {
                    Point point(100, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(0, 50));
                }
                SECTION("Ten times over")
                {
                    Point point(10000, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(0, 50));
                }
                SECTION("One hundred times over")
                {
                    Point point(10000, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(0, 50));
                }
            }
            SECTION("Left side")
            {
                SECTION("Once over")
                {
                    Point point(-1, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(99, 50));
                }
                SECTION("Ten times over")
                {
                    Point point(-1001, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(99, 50));
                }
                SECTION("One-hundred times over")
                {
                    Point point(-10001, 50);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(99, 50));
                }
            }
            SECTION("Bottom side")
            {
                SECTION("Once over")
                {
                    Point point(50, 100);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 0));
                }
                SECTION("Ten times over")
                {
                    Point point(50, 1000);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 0));
                }
                SECTION("One-hundred times over")
                {
                    Point point(50, 10000);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 0));
                }
            }
            SECTION("Top side")
            {
                SECTION("Once over")
                {
                    Point point(50, -1);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 99));
                }
                SECTION("Ten times over")
                {
                    Point point(50, -1001);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 99));
                }
                SECTION("One hundred times over")
                {
                    Point point(50, -10001);
                    Rectangle rect(10, 10, 80, 80);
                    REQUIRE(Math::Wrap(point, rect, { 10, 10 }) == Point(50, 99));
                }
            }
        }
    }



    SECTION("Transform")
    {
        Matrix4x4 transform(1);
        Vector2 position;
        SECTION("Translated position")
        {
            transform.Translate({ 10, 10, 0 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -6) == Math::RoundN(Vector2(10, 10), -6));
            transform.Translate({ 100, -100, 0 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -6) == Math::RoundN(Vector2(110, -90), -6));
        }
        SECTION("Rotated position")
        {
            position.Set(10, 0);
            transform.Rotate(90, { 0, 0, 1 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -5) == Math::RoundN(Vector2(0, 10), -5));
            transform.Rotate(90, { 0, 0, 1 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -5) == Math::RoundN(Vector2(-10, 0), -5));
        }
        SECTION("Scaled position")
        {
            position.Set(10, 10);
            transform.Scale(2);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -6) == Math::RoundN(Vector2(20, 20), -6));
            transform.Scale(2);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -6) == Math::RoundN(Vector2(40, 40), -6));
            transform.Scale(.25);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), -6) == Math::RoundN(Vector2(10, 10), -6));
        }
    }
     

    SECTION("Trajectory Vector2")
    {
        const double SqrtOfHalf = Math::RoundN(std::sqrt(.5), -6);

        SECTION("Trajectory")
        {
            REQUIRE(Math::RoundN(Math::Trajectory(0, 1), -5) == 
                Math::RoundN(Vector2(1, 0), -5));
            REQUIRE(Math::RoundN(Math::Trajectory(45, 1), -6) == 
                Math::RoundN(Vector2(SqrtOfHalf,-SqrtOfHalf), -6));
            REQUIRE(Math::RoundN(Math::Trajectory(90, 1), -5) == 
                Math::RoundN(Vector2(0, -1), -5));
            REQUIRE(Math::RoundN(Math::Trajectory(135, 1), -6) == 
                Math::RoundN(Vector2(-SqrtOfHalf, -SqrtOfHalf), -6));
            REQUIRE(Math::RoundN(Math::Trajectory(180, 1), -5) == 
                Math::RoundN(Vector2(-1, 0), -5));
            REQUIRE(Math::RoundN(Math::Trajectory(225, 1), -6) == 
                Math::RoundN(Vector2(-SqrtOfHalf, SqrtOfHalf), -6));
            REQUIRE(Math::RoundN(Math::Trajectory(270, 1), -5) == 
                Math::RoundN(Vector2(0, 1), -5));
            REQUIRE(Math::RoundN(Math::Trajectory(315, 1), -6) == 
                Math::RoundN(Vector2(SqrtOfHalf, SqrtOfHalf), -6));
            REQUIRE(Math::RoundN(Math::Trajectory(360, 1), -5) == 
                Math::RoundN(Vector2(1, 0), -5));
        }
    }
}

TEST_CASE("Point Direction")
{
    SECTION("Vector2")
    {
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ 1, 0 }) == 0);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ 1, 1 }) == 315);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ 0, 1 }) == 270);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ -1, 1 }) == 225);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ -1, 0 }) == 180);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ -1, -1 }) == 135);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ 0, -1 }) == 90);
        REQUIRE(Math::PointDirection(Vector2{ 0, 0 }, Vector2{ 1, -1 }) == 45);
    }
    SECTION("Point")
    {
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ 1, 0 }) == 0);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ 1, 1 }) == 315);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ 0, 1 }) == 270);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ -1, 1 }) == 225);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ -1, 0 }) == 180);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ -1, -1 }) == 135);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ 0, -1 }) == 90);
        REQUIRE(Math::PointDirection(Point{ 0, 0 }, Point{ 1, -1 }) == 45);
    }
}

TEST_CASE("Point Distance") // more extensive tests of underlying function in MathTests
{
    SECTION("Vector2")
    {
        REQUIRE(Math::PointDistance(Vector2{ 0, 0 }, Vector2{ 0, 0 }) == 0);
        REQUIRE(Math::PointDistance(Vector2{ 0, 0 }, Vector2{ 1, 0 }) == 1);
        REQUIRE(Math::PointDistance(Vector2{ 0, 0 }, Vector2{ 3, 4 }) == 5);
    }
    SECTION("Point")
    {
        REQUIRE(Math::PointDistance(Point{ 0, 0 }, Point{ 0, 0 }) == 0);
        REQUIRE(Math::PointDistance(Point{ 0, 0 }, Point{ 1, 0 }) == 1);
        REQUIRE(Math::PointDistance(Point{ 0, 0 }, Point{ 3, 4 }) == 5);
    }
}

TEST_CASE("Intersects")
{
    SECTION("Rectangle - Rectangle")
    {
        FRectangle rect1;
        FRectangle rect2;

        SECTION("Overlapping while empty")
        {
            REQUIRE(Math::Intersects(rect1, rect2));
            rect1.X(100).Y(100);
            rect2.X(100).Y(100);
            REQUIRE(Math::Intersects(rect1, rect2));
        }

        SECTION("Perfect Overlap")
        {
            rect1.Set(10, 10, 10, 10);
            rect2.Set(10, 10, 10, 10);
            REQUIRE(Math::Intersects(rect1, rect2));
            rect1.Set(10.45f, 10124.21f, 10.124f, 1247.12f);
            rect2.Set(10.45f, 10124.21f, 10.124f, 1247.12f);
            REQUIRE(Math::Intersects(rect1, rect2));
        }

        SECTION("Partial Overlap")
        {
            rect1.Set(0, 0, 10, 10);
            rect2.Set(5, 5, 10, 10);
            REQUIRE(Math::Intersects(rect1, rect2));
            rect1.Set(0, 0, 100000, 10);
            rect2.Set(10, 0, 10, 100000);
            REQUIRE(Math::Intersects(rect1, rect2));
        }

        SECTION("Overlapping on corners")
        {
            // Top-Left and bottom-right corners
            rect1.Set(0, 0, 10.f, 10.f);
            rect2.Set(10.f, 10.f, 20.f, 20.f);
            REQUIRE(Math::Intersects(rect1, rect2));

            // Top-right and bottom-left corners
            rect1.Set(10.f, 0, 10.f, 10.f);
            rect2.Set(0, 10.f, 10.f, 10.f);
            REQUIRE(Math::Intersects(rect1, rect2));
        }

        SECTION("Overlapping on borders")
        {
            // Top and bottom
            rect1.Set(0, 0, 10.f, 10.f);
            rect2.Set(0, 10.f, 20.f, 20.f);
            REQUIRE(Math::Intersects(rect1, rect2));

            // Left and right
            rect1.Set(0, 0, 10.f, 10.f);
            rect2.Set(10.f, 0, 10.f, 10.f);
            REQUIRE(Math::Intersects(rect1, rect2));
        }
    }

    SECTION("Rectangle - Circle")
    {
        Rectangle rect;
        Circle    circ;

        SECTION("Not colliding")
        {
            rect.Set(0, 0, 10, 10);
            circ.Set(100, 100, 1);
            REQUIRE(!Math::Intersects(rect, circ));
        }

        SECTION("Basic collision")
        {
            rect.Set(0, 0, 10, 10);
            circ.Set(0, 0, 1);
            REQUIRE(Math::Intersects(rect, circ));
        }
        SECTION("Touching side")
        {
            rect.Set(0, 0, 10, 10);
            circ.Set(11, 5, 1);
            REQUIRE(Math::Intersects(rect, circ));
        }
        SECTION("Touching corner")
        {
            rect.Set(0, 0, 10, 10);
            circ.Set(11, 0, 1);
            REQUIRE(Math::Intersects(rect, circ));
        }
    }

    SECTION("Rect - Point")
    {
        Rectangle rect;
        Point point;

        SECTION("Not inside")
        {
            rect.Set(0, 0, 10, 10);
            point.X(100).Y(100);
            REQUIRE(!Math::Intersects(rect, point));
        }
        SECTION("Inside")
        {
            rect.Set(0, 0, 10, 10);
            point.X(5).Y(5);
            REQUIRE(Math::Intersects(rect, point));
        }
        SECTION("Touching side")
        {
            rect.Set(0, 0, 10, 10);
            point.X(5).Y(10);
            REQUIRE(Math::Intersects(rect, point));
        }
        SECTION("Touching corner")
        {
            rect.Set(0, 0, 10, 10);
            point.X(10).Y(10);
            REQUIRE(Math::Intersects(rect, point));
        }
    }

    SECTION("PointDistance")
    {
        SECTION("Distance")
        {
            SECTION("From {0,0} -> {1,1}")
            {
                Vector2 base = Vector2::Zero();
                Vector2 extension = Vector2::One();

                float result = Math::PointDistance(base, extension);
                REQUIRE(result == std::sqrt(2.f));
                REQUIRE(extension.Length() == result);
            }

            SECTION("From negative number")
            {
                Vector2 base = {-2.5, -4.4};
                Vector2 extension = {4.2f, 5.9f};

                float a = extension.X() - base.X();
                float b = extension.Y() - base.Y();
                float expected = std::sqrt(a * a + b * b);

                float result = Math::PointDistance(base, extension);
                REQUIRE(result == expected);
            }

            SECTION("From mixed negative positive")
            {
                Vector2 base = {2.5412f, -4.4};
                Vector2 extension = {4.22f, -5.99f};

                float a = extension.X() - base.X();
                float b = extension.Y() - base.Y();
                float expected = std::sqrt(a * a + b * b);

                float result = Math::PointDistance(base, extension);
                REQUIRE(result == expected);
            }
        }
    }
}
