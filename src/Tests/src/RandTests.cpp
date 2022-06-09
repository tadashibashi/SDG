#include "SDG_Tests.h"
#include <Engine/Exceptions/AssertionException.h>
#include <Engine/Math/Rand.h>

TEST_CASE("Rand::Next")
{
    REQUIRE(Rand::Next() < 1.f);
    REQUIRE(Rand::Next(5.f) < 5.f);
    REQUIRE(Rand::Next(.1f) < .1f);
    REQUIRE(Rand::Next(.000001f) < .000001f);
}

TEST_CASE("Rand::INext")
{
    // One
    REQUIRE(Rand::INext(1) == 0);

    // Small
    REQUIRE(Rand::INext(5) < 5);

    // Large
    REQUIRE(Rand::INext(200000) < 200000);

    // Zero
    REQUIRE(Rand::INext(0) == 0);

    // Negative
    REQUIRE(Rand::INext(-1) == 0);
    REQUIRE(Rand::INext(-20) > -20);
}

TEST_CASE("Rand::Range")
{
    REQUIRE(Rand::Range(0, 0) == 0);
    REQUIRE(Rand::Range(1.f, 1.f) == 1.f);
    REQUIRE(Rand::Range(-100.f, -100.f) == -100.f);

    float n = Rand::Range(0, 2.2f);
    REQUIRE(n >= 0);
    REQUIRE(n < 2.2f);

    n = Rand::Range(-20.f, 20.f);
    REQUIRE(n > -20.f);
    REQUIRE(n < 20.f);
}

TEST_CASE("Rand::IRange")
{
    REQUIRE(Rand::IRange(0, 0) == 0);
    REQUIRE(Rand::IRange(1, 1) == 1);
    REQUIRE(Rand::IRange(-100, -100) == -100);

    float n = Rand::IRange(0, 2);
    REQUIRE(n >= 0);
    REQUIRE(n < 2);

    n = Rand::IRange(-20, 20);
    REQUIRE(n > -20);
    REQUIRE(n < 20);
}

TEST_CASE("Math::Chance: int overload tests")
{
    // Only testing guaranteed outcome cases
    REQUIRE(Rand::Chance(0, 0) == false);
    REQUIRE(Rand::Chance(0, 100) == false);
    REQUIRE(Rand::Chance(100, -2) == false); // always false if denom less than 0
    REQUIRE(Rand::Chance(1, 1) == true);
}

TEST_CASE("Math::Chance: float overload tests")
{
    // Only testing guaranteed outcome cases
    REQUIRE(Rand::Chance(1.f, 0.f) == false);
    REQUIRE(Rand::Chance(0.f, 100.f) == false);
    REQUIRE(Rand::Chance(100.f, -2.f) == false); // always false if denom less than 0
    REQUIRE(Rand::Chance(1.f, 1.f) == true);
}

TEST_CASE("Math::Choose")
{
    const int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6;
    for (int iters = 0; iters < 21; ++iters)
    {
        const int *i = Rand::Choose({&a, &b, &c, &d, &e, &f, &g});

        bool result = (i == &a || i == &b || i == &c || i == &d
                       || i == &e || i == &f || i == &g);
        REQUIRE(result);
    }
}
