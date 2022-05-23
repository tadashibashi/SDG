#include "SDG_Tests.h"
#include <SDG/Math/MathEx.h>

TEST_CASE("Math::Lerp")
{
    SECTION("Floating point tests")
    {
        SECTION("Zero amount does not affect result")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, 0) == 10.f);
        }

        SECTION("Amount of .25f brings result a quarter way")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, 0.25) == 12.5f);
        }

        SECTION("Amount of .5f brings result half way")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, 0.5) == 15.f);
        }

        SECTION("Amount of .75f brings three-thirds way")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, 0.75) == 17.5f);
        }

        SECTION("Amount of 1.f brings all the way")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, 1.0) == 20.f);
        }

        SECTION("Negative amount flips result")
        {
            REQUIRE(Math::Lerp(10.f, 20.f, -.5) == 5.f);
        }
    }

    SECTION("Integer tests")
    {
        SECTION("Amount of zero does not affect result")
        {
            REQUIRE(Math::Lerp(10, 20, 0) == 10);
        }

        SECTION("Amount of .25f brings result quarter way")
        {
            REQUIRE(Math::Lerp(10, 20, 0.25) == 12.5);
        }

        SECTION("Amount of .5f brings result half way")
        {
            REQUIRE(Math::Lerp(10, 20, 0.5) == 15);
        }

        SECTION("Amount of .75f brings three-thirds way")
        {
            REQUIRE(Math::Lerp(10, 20, 0.75) == 17.5);
        }

        SECTION("Amount of 1.f brings all the way")
        {
            REQUIRE(Math::Lerp(10, 20, 1.0) == 20);
        }

        SECTION("Negative amount flips result")
        {
            REQUIRE(Math::Lerp(10, 20, -.5) == 5);
        }
    }

    SECTION("Vector2 tests")
    {
        SECTION("Amount of zero does not affect result")
        {
            REQUIRE(Math::Lerp(Vector2(10, 10), Vector2(20, 20), 0) == Vector2(10, 10));
        }

        SECTION("Amount of .25f brings result quarter way")
        {
            REQUIRE(Math::Lerp(Vector2(10, 10), Vector2{20, 20}, 0.25) == Vector2{12.5f, 12.5f});
        }

        SECTION("Amount of .5f brings result half way")
        {
            REQUIRE(Math::Lerp(Vector2(10.f, 10.f), Vector2(20.f, 20.f), 0.5) == Vector2(15.f, 15.f));
        }

        SECTION("Amount of .75f brings three-thirds way")
        {
            REQUIRE(Math::Lerp(Vector2(10.f, 10.f), Vector2(20.f, 20.f), 0.75) == Vector2(17.5f, 17.5f));
        }

        SECTION("Amount of 1.f brings all the way")
        {
            REQUIRE(Math::Lerp(Vector2(10.f, 10.f), Vector2(20.f, 20.f), 1.0) == Vector2(20.f, 20.f));
        }

        SECTION("Negative amount flips result")
        {
            REQUIRE(Math::Lerp(Vector2(10.f, 10.f), Vector2(20.f, 20.f), -.5) == Vector2(5.f, 5.f));
        }
    }
} /* end TEST_CASE("Math::Lerp") */

TEST_CASE("Math::ToDegrees")
{
    REQUIRE(Math::ToDegrees(2 * Math::Pi) == 360);
    REQUIRE(Math::ToDegrees(1.5 * Math::Pi) == 270);
    REQUIRE(Math::ToDegrees(Math::Pi) == 180);
    REQUIRE(Math::ToDegrees(.5 * Math::Pi) == 90);
    REQUIRE(Math::ToDegrees(0) == 0);
}

TEST_CASE("Math::ToRadians")
{
    REQUIRE(Round(Math::ToRadians(360)) == Round(2 * Math::Pi));
    REQUIRE(Round(Math::ToRadians(270)) == Round(1.5 * Math::Pi));
    REQUIRE(Round(Math::ToRadians(180)) == Round(Math::Pi));
    REQUIRE(Round(Math::ToRadians(90)) == Round(.5 * Math::Pi));
    REQUIRE(Round(Math::ToRadians(0)) == Round(0));
}

TEST_CASE("Trajectory Functions")
{
    const double SqrtOfHalf = Round(std::sqrt(.5));

    SECTION("TrajectoryX")
    {
        REQUIRE(Round(Math::TrajectoryX(0, 1)) == 1);
        REQUIRE(Round(Math::TrajectoryX(45, 1)) == SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryX(90, 1)) == 0);
        REQUIRE(Round(Math::TrajectoryX(135, 1)) == -SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryX(180, 1)) == -1);
        REQUIRE(Round(Math::TrajectoryX(225, 1)) == -SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryX(270, 1)) == 0);
        REQUIRE(Round(Math::TrajectoryX(315, 1)) == SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryX(360, 1)) == 1);
    }

    SECTION("TrajectoryY")
    {
        REQUIRE(Round(Math::TrajectoryY(0, 1)) == 0);
        REQUIRE(Round(Math::TrajectoryY(45, 1)) == -SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryY(90, 1)) == -1);
        REQUIRE(Round(Math::TrajectoryY(135, 1)) == -SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryY(180, 1)) == 0);
        REQUIRE(Round(Math::TrajectoryY(225, 1)) == SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryY(270, 1)) == 1);
        REQUIRE(Round(Math::TrajectoryY(315, 1)) == SqrtOfHalf);
        REQUIRE(Round(Math::TrajectoryY(360, 1)) == 0);
    }

    // Trust that Trajectory Vector2 works because it simply uses the
    // TrajectoryX and TrajectoryY functions

} /* end TEST_CASE("Trajectory Functions") */

TEST_CASE("Math::Min and Math::Max")
{
    REQUIRE(Math::Min(10, 20) == 10);
    REQUIRE(Math::Min(20, 10) == 10);
    REQUIRE(Math::Max(10, 20) == 20);
    REQUIRE(Math::Max(20, 10) == 20);
}

TEST_CASE("Math::Clamp")
{
    SECTION("Floating point")
    {
        SECTION("Transparent result when within range")
        {
            float num = 17.5f;
            float lowerLimit = 15.f;
            float upperLimit = 20.f;
            float result = Math::Clamp<float>(num, lowerLimit, upperLimit);
            REQUIRE(result == num);
        }

        SECTION("Lower end clamp")
        {
            float num = 10.f;
            float lowerLimit = 15.f;
            float upperLimit = 20.f;
            float result = Math::Clamp<float>(num, lowerLimit, upperLimit);
            REQUIRE(result == lowerLimit);
        }

        SECTION("Upper-end clamp")
        {
            float num = 25.f;
            float lowerLimit = 15.f;
            float upperLimit = 20.f;
            float result = Math::Clamp<float>(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("Same number limit clamp")
        {
            float num = 25.f;
            float lowerLimit = 15.f;
            float upperLimit = 15.f;
            float result = Math::Clamp<float>(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("lower > upper")
        {
            float num = 100.0123f;
            float lowerLimit = 50.14f;
            float upperLimit = 20.941f;
            float result = Math::Clamp<float>(num, lowerLimit, upperLimit);
            REQUIRE(result == lowerLimit);
        }
    }

    SECTION("Integer")
    {
        SECTION("Transparent result when within range")
        {
            int num = 17;
            int lowerLimit = 15;
            int upperLimit = 20;
            int result = Math::Clamp<int>(num, lowerLimit, upperLimit);
            REQUIRE(result == num);
        }

        SECTION("Lower end clamp")
        {
            int num = 10;
            int lowerLimit = 15;
            int upperLimit = 20;
            int result = Math::Clamp<int>(num, lowerLimit, upperLimit);
            REQUIRE(result == lowerLimit);
        }

        SECTION("Upper-end clamp")
        {
            int num = 25;
            int lowerLimit = 15;
            int upperLimit = 20;
            int result = Math::Clamp<int>(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("Same number limit clamp")
        {
            int num = 25;
            int lowerLimit = 15;
            int upperLimit = 15;
            int result = Math::Clamp<int>(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("lower > upper")
        {
            int num = 100;
            int lowerLimit = 50;
            int upperLimit = 20;
            int result = Math::Clamp<int>(num, lowerLimit, upperLimit);
            REQUIRE(result == lowerLimit);
        }
    }

    SECTION("Vector2")
    {
        SECTION("Transparent result when within range")
        {
            Vector2 num = {17, 17};
            Vector2 lowerLimit = {15, 15};
            Vector2 upperLimit = {20, 20};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == num);
        }

        SECTION("Lower end clamp")
        {
            Vector2 num = {10, 10};
            Vector2 lowerLimit = {15, 15};
            Vector2 upperLimit = {20, 20};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == lowerLimit);
        }

        SECTION("Upper-end clamp")
        {
            Vector2 num = {25, 25};
            Vector2 lowerLimit = {15, 15};
            Vector2 upperLimit = {20, 20};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("Same number limit clamp")
        {
            Vector2 num = {25, 25};
            Vector2 lowerLimit = {15, 15};
            Vector2 upperLimit = {15, 15};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == upperLimit);
        }

        SECTION("X low > X high")
        {
            Vector2 num = {1000, 50};
            Vector2 lowerLimit = {100, 15};
            Vector2 upperLimit = {15, 24};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == Vector2{100, 24});
        }

        SECTION("Y low > Y high")
        {
            Vector2 num = {-24, 1000};
            Vector2 lowerLimit = {0, 100};
            Vector2 upperLimit = {15, 24};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == Vector2{0, 100});
        }

        SECTION("X low > X high && Y low > Y high")
        {
            Vector2 num = {-24, 1000};
            Vector2 lowerLimit = {1000, 100};
            Vector2 upperLimit = {15, 24};
            Vector2 result = Math::Clamp(num, lowerLimit, upperLimit);
            REQUIRE(result == Vector2{15, 100});
        }
    }

} /* end TEST_CASE("Math::Clamp") */

TEST_CASE("Math::Abs")
{
    SECTION("Integer tests")
    {
        SECTION("Negative number made positive")
        {
            REQUIRE(Math::Abs(-10) == 10);
        }

        SECTION("Positive number remains positive")
        {
            REQUIRE(Math::Abs(10) == 10);
        }
    }

    SECTION("Floating point tests")
    {
        SECTION("Negative number made positive")
        {
            REQUIRE(Math::Abs(-10.f) == 10.f);
        }

        SECTION("Positive number remains positive")
        {
            REQUIRE(Math::Abs(10.f) == 10.f);
        }
    }

} /* end TEST_CASE("Math::Abs") */

TEST_CASE("Math::Sign")
{
    // ints
    REQUIRE(Math::Sign(-5) == -1);
    REQUIRE(Math::Sign(5) == 1);

    // floats
    REQUIRE(Math::Sign(-5.f) == -1.f);
    REQUIRE(Math::Sign(5.f) == 1.f);

    // 0 results in 1
    REQUIRE(Math::Sign(0) == 1);

}

TEST_CASE("Math::Mod")
{
    SECTION("Performs as modulo does when both nums are positive")
    {
        REQUIRE(Math::Mod(555, 10) == 555 % 10);
        REQUIRE(Math::Mod(12345, 3) == 12345 % 3);
        REQUIRE(Math::Mod(12345, 4) == 12345 % 4);
    }
    SECTION("Performs as modulo does when both nums are negative")
    {
        REQUIRE(Math::Mod(-555, -10) == -555 % -10);
        REQUIRE(Math::Mod(-12345, -3) == -12345 % -3);
        REQUIRE(Math::Mod(-12345, -4) == -12345 % -4);
    }
    SECTION("Does not reflect across zero")
    {
        REQUIRE(Math::Mod(-10, 15) == 5);
        REQUIRE(Math::Mod(-1, 10) == 9);
        REQUIRE(Math::Mod(-11, 10) == 9);
        REQUIRE(Math::Mod(11, -10) == -9);
    }
} /* end TEST_CASE("Math::Mod") */

TEST_CASE("Math::ModF")
{
    SECTION("Performs as modulo does when both nums are positive")
    {
        REQUIRE(RoundF(Math::ModF(555.5f, 10.111f)) == RoundF(fmodf(555.5f, 10.111f)));
        REQUIRE(RoundF(Math::ModF(12345.6f, 3.123f)) == RoundF(fmodf(12345.6f, 3.123f)));
        REQUIRE(RoundF(Math::ModF(12345.f, 4.152f)) == RoundF(fmodf(12345.f, 4.152f)));
    }

    SECTION("Performs as modulo does when both nums are negative")
    {
        REQUIRE(RoundF(Math::ModF(-555.1f, -10.77f)) == RoundF(fmodf(-555.1f, -10.77f)));
        REQUIRE(RoundF(Math::ModF(-12345.4f, -3.5f)) == RoundF(fmodf(-12345.4f, -3.5f)));
        REQUIRE(RoundF(Math::ModF(-12345.7f, -4.1f)) == RoundF(fmodf(-12345.7f, -4.1f)));
    }

    SECTION("Does not reflect across zero")
    {
        REQUIRE(RoundF(Math::ModF(-10.1f, 15.f)) == RoundF(4.9f));
        REQUIRE(RoundF(Math::ModF(-1.2f, 10.f)) == RoundF(8.8f));
        REQUIRE(RoundF(Math::ModF(-11.4f, 10.f)) == RoundF(8.6f));
        REQUIRE(RoundF(Math::ModF(11.12f, -10.f)) == RoundF(-8.88f));
    }
} /* end TEST_CASE("Math::ModF") */

TEST_CASE("Math::Wrap")
{
    SECTION("Same number range")
    {
        REQUIRE(Math::Wrap(0, 5, 5) == 5);
        REQUIRE(Math::Wrap(0, -5, -5) == -5);
        REQUIRE(Math::Wrap(0, 0, 0) == 0);
    }

    SECTION("Wrap around low end")
    {
        REQUIRE(Math::Wrap(-5, 1, 7) == 1);
        REQUIRE(Math::Wrap(-50, 1, 7) == 4);
        REQUIRE(Math::Wrap(-12, -7, -1) == -6);
        REQUIRE(Math::Wrap(-50, -5, 2) == -1); // multiple wraps
    }

    SECTION("Wrap around high end")
    {
        REQUIRE(Math::Wrap(12, 1, 7) == 6);
        REQUIRE(Math::Wrap(50, 1, 7) == 2);
        REQUIRE(Math::Wrap(10, -40, 5) == -35); // one wrap
        REQUIRE(Math::Wrap(50, -4, 7) == 6); // multiple wraps
    }

    SECTION("Wrap when low > high")
    {
        REQUIRE(Math::Wrap(12, 7, 1) == 6);
        REQUIRE(Math::Wrap(50, 7, 1) == 2);
        REQUIRE(Math::Wrap(10, 5, -40) == -35); // one wrap
        REQUIRE(Math::Wrap(50, 7, -4) == 6); // multiple wraps
        REQUIRE(Math::Wrap(-5, 7, 1) == 1);
        REQUIRE(Math::Wrap(-50, 7, 1) == 4);
        REQUIRE(Math::Wrap(-12, -1, -7) == -6);
        REQUIRE(Math::Wrap(-50, 2, -5) == -1); // multiple wraps
    }
} /* end TEST_CASE("Math::Wrap") */

TEST_CASE("Math::WrapF")
{
    SECTION("Same number range")
    {
        REQUIRE(Math::WrapF(0.f, 5.f, 5.f) == 5.f);
        REQUIRE(Math::WrapF(0.f, -5.f, -5.f) == -5.f);
        REQUIRE(Math::WrapF<float>(0, 0, 0) == 0);
    }

    SECTION("Wrap around low end")
    {
        REQUIRE(Math::WrapF(-5.f, 1.f, 7.f) == 1.f);
        REQUIRE(Math::WrapF(-50.f, 1.f, 7.f) == 4.f);
        REQUIRE(Math::WrapF(-12.f, -7.f, -1.f) == -6.f);
        REQUIRE(Math::WrapF(-50.f, -5.f, 2.f) == -1.f); // multiple wraps
    }

    SECTION("Wrap around high end")
    {
        REQUIRE(Math::WrapF(12.f, 1.f, 7.f) == 6.f);
        REQUIRE(Math::WrapF(50.f, 1.f, 7.f) == 2.f);
        REQUIRE(Math::WrapF(10.f, -40.f, 5.f) == -35.f); // one wrap
        REQUIRE(Math::WrapF(50.f, -4.f, 7.f) == 6.f); // multiple wraps
    }

    SECTION("Wrap when low > high")
    {
        REQUIRE(Math::WrapF(-5.f, 7.f, 1.f) == 1.f);
        REQUIRE(Math::WrapF(-50.f, 7.f, 1.f) == 4.f);
        REQUIRE(Math::WrapF(-12.f, -1.f, -7.f) == -6.f);
        REQUIRE(Math::WrapF(-50.f, 2.f, -5.f) == -1.f); // multiple wraps
        REQUIRE(Math::WrapF(12.f, 7.f, 1.f) == 6.f);
        REQUIRE(Math::WrapF(50.f, 7.f, 1.f) == 2.f);
        REQUIRE(Math::WrapF(10.f, 5.f, -40.f) == -35.f); // one wrap
        REQUIRE(Math::WrapF(50.f, 7.f, -4.f) == 6.f); // multiple wraps
    }
} /* end TEST_CASE("Math::WrapF") */

// Not sure how to extensively test transform, but it has the same impl as MonoGame, so it should be ok
