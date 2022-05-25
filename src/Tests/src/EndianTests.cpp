#include "SDG_Tests.h"
#include <SDG/Math/Endian.h>

TEST_CASE("SwapEndian buffer")
{
    SECTION("buffer")
    {
        char chars[4] = {'a', 'b', 'c', 'd'};
        ReverseEndian((uint8_t *)chars, 4);
        REQUIRE(chars[0] == 'd');
        REQUIRE(chars[1] == 'c');
        REQUIRE(chars[2] == 'b');
        REQUIRE(chars[3] == 'a');
    }

    SECTION("template")
    {
        int i = 1;
        ReverseEndian(i);
        REQUIRE(i > 0);
    }

}