#include "SDG_Tests.h"
#include <SDG/Math/Intersection.h>

TEST_CASE("Intersects")
{
    SECTION("Intersects")
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
}
