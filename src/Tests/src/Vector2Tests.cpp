/* =============================================================================
 * Vector2Tests
 * 
 * 
 * ===========================================================================*/
#include "SDG_Tests.h"
#include <SDG/Math/Vector2.h>

static float RoundF(float f)
{
    f *= 1000000.f;
    f = std::round(f);
    f /= 1000000.f;
    return f;
}

TEST_CASE("Vector2 tests", "[Vector2]")
{
    SECTION("Constructors")
    {
        SECTION("Default")
        {
            Vector2 vec;
            REQUIRE(vec.X() == 0);
            REQUIRE(vec.Y() == 0);

            REQUIRE(vec.W() == 0);
            REQUIRE(vec.H() == 0);

            // Test indexer
            REQUIRE(vec[0] == 0);
            REQUIRE(vec[1] == 0);
        }

        SECTION("Params")
        {
            Vector2 vec(-1, 25);
            REQUIRE(vec.X() == -1);
            REQUIRE(vec.Y() == 25);

            REQUIRE(vec.W() == -1);
            REQUIRE(vec.H() == 25);

            // Test indexer
            REQUIRE(vec[0] == -1);
            REQUIRE(vec[1] == 25);
        }

        SECTION("Static factory funcs")
        {
            Vector2 one = Vector2::One();
            REQUIRE(one.X() == 1);
            REQUIRE(one.Y() == 1);

            Vector2 zero = Vector2::Zero();
            REQUIRE(zero.X() == 0);
            REQUIRE(zero.Y() == 0);
        }
    }

    SECTION("Distance")
    {
        SECTION("From {0,0} -> {1,1}")
        {
            Vector2 base = Vector2::Zero();
            Vector2 extension = Vector2::One();

            float result = Vector2::Distance(base, extension);
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

            float result = Vector2::Distance(base, extension);
            REQUIRE(result == expected);
        }

        SECTION("From mixed negative positive")
        {
            Vector2 base = {2.5412f, -4.4};
            Vector2 extension = {4.22f, -5.99f};

            float a = extension.X() - base.X();
            float b = extension.Y() - base.Y();
            float expected = std::sqrt(a * a + b * b);

            float result = Vector2::Distance(base, extension);
            REQUIRE(result == expected);
        }
    }

    SECTION("Rotate")
    {
        Vector2 vec(1, 0);
        REQUIRE(vec.X() == 1.f);
        REQUIRE(vec.Y() == 0.f);
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
        REQUIRE(RoundF(vec.Y()) == RoundF(std::sqrt(.5f)));
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(vec.X() == 0.f);
        REQUIRE(RoundF(vec.Y()) == RoundF(1.f));
        vec = Vector2::Rotate(vec, 180);
        REQUIRE(RoundF(vec.X()) == 0.f);
        REQUIRE(RoundF(vec.Y()) == -1.f);
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == RoundF(std::sqrt(.5f)));
        REQUIRE(RoundF(vec.Y()) == RoundF(-std::sqrt(.5f)));
        vec = Vector2::Rotate(vec, 45);
        REQUIRE(RoundF(vec.X()) == 1.f);
        REQUIRE(RoundF(vec.Y()) == 0.f);
    }




}