#include "SDG_Tests.h"
#include <Engine/Lib/Unique.h>

TEST_CASE("Unique tests")
{
    SECTION("Default constructor sets a nullptr")
    {
        Unique<int> u;
        REQUIRE(u.Get() == nullptr);
    }

    SECTION("Setting a new object sets its internal value correctly")
    {
        Unique<int> u = new int(20);
        REQUIRE(*u == 20);
    }
}