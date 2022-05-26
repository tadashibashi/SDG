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

    SECTION("Transform")
    {
        Matrix4x4 transform(1);
        Vector2 position;
        SECTION("Translated position")
        {
            transform.Translate({ 10, 10, 0 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 6) == Math::RoundN(Vector2(10, 10), 6));
            transform.Translate({ 100, -100, 0 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 6) == Math::RoundN(Vector2(110, -90), 6));
        }
        SECTION("Rotated position")
        {
            position.Set(10, 0);
            transform.Rotate(90, { 0, 0, 1 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 5) == Math::RoundN(Vector2(0, 10), 5));
            transform.Rotate(90, { 0, 0, 1 });
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 5) == Math::RoundN(Vector2(-10, 0), 5));
        }
        SECTION("Scaled position")
        {
            position.Set(10, 10);
            transform.Scale(2);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 6) == Math::RoundN(Vector2(20, 20), 6));
            transform.Scale(2);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 6) == Math::RoundN(Vector2(40, 40), 6));
            transform.Scale(.25);
            REQUIRE(Math::RoundN(Math::Transform(position, transform), 6) == Math::RoundN(Vector2(10, 10), 6));
        }
    }
     

    SECTION("Trajectory Vector2")
    {
        const double SqrtOfHalf = Round(std::sqrt(.5));

        SECTION("Trajectory")
        {
            REQUIRE(Math::RoundN(Math::Trajectory(0, 1), 5) == 
                Math::RoundN(Vector2(1, 0), 5));
            REQUIRE(Math::RoundN(Math::Trajectory(45, 1), 6) == 
                Math::RoundN(Vector2(SqrtOfHalf,-SqrtOfHalf), 6));
            REQUIRE(Math::RoundN(Math::Trajectory(90, 1), 5) == 
                Math::RoundN(Vector2(0, -1), 5));
            REQUIRE(Math::RoundN(Math::Trajectory(135, 1), 6) == 
                Math::RoundN(Vector2(-SqrtOfHalf, -SqrtOfHalf), 6));
            REQUIRE(Math::RoundN(Math::Trajectory(180, 1), 5) == 
                Math::RoundN(Vector2(-1, 0), 5));
            REQUIRE(Math::RoundN(Math::Trajectory(225, 1), 6) == 
                Math::RoundN(Vector2(-SqrtOfHalf, SqrtOfHalf), 6));
            REQUIRE(Math::RoundN(Math::Trajectory(270, 1), 5) == 
                Math::RoundN(Vector2(0, 1), 5));
            REQUIRE(Math::RoundN(Math::Trajectory(315, 1), 6) == 
                Math::RoundN(Vector2(SqrtOfHalf, SqrtOfHalf), 6));
            REQUIRE(Math::RoundN(Math::Trajectory(360, 1), 5) == 
                Math::RoundN(Vector2(1, 0), 5));
        }
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
