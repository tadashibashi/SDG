#include "SDG_Tests.h"
#include <SDG/Math/Intersection.h>
#include <SDG/Math/Shape.h>

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
