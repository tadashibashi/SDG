#include "SDG_Tests.h"
#include <SDG/FileSys/FileSys.h>

TEST_CASE("FileSys tests", "[FileSys]")
{
    SECTION("CreateWindow and Constructor produce same result")
    {
        FileSys fileSys1("SDG Tests", "SDG");
        FileSys fileSys2;
        fileSys2.Initialize("SDG Tests", "SDG");

        SECTION("App and Org names are set")
        {
            REQUIRE(fileSys1.AppName() == "SDG Tests");
            REQUIRE(fileSys1.OrgName() == "SDG");
        }

        SECTION("BasePath is created")
        {
            REQUIRE(!fileSys1.BasePath().Empty());
        }

        SECTION("PrefPath is created")
        {
            // If this fails, it either means that Read/Write permissions aren't granted to this program
            // in the directory location, or this pref directory is not supported on the platform.
            REQUIRE(!fileSys1.PrefPath().Empty());
        }

        SECTION("FileSys #1 is equal to FileSys #2")
        {
            REQUIRE(fileSys1.BasePath() == fileSys2.BasePath());
            REQUIRE(fileSys1.PrefPath() == fileSys2.PrefPath());
            REQUIRE(fileSys1.AppName() == fileSys2.AppName());
            REQUIRE(fileSys1.OrgName() == fileSys2.OrgName());
        }
    }
}