#include "SDG_Tests.h"
#include <Engine/Lib/Shared.h>

TEST_CASE("Shared ptr tests", "[Shared]")
{
    SECTION("Default constructor constructs default object")
    {
        Shared<int> i;

        REQUIRE(i.Get() == nullptr);
    }

    SECTION("Regular constructor sets members")
    {
        Shared<int> i = new int(145);
        REQUIRE(i.Get() != nullptr);
        REQUIRE(i.Count() == 1);
        REQUIRE(*i == 145); // same amount
    }

    SECTION("New ptr constructor sets members")
    {
        Shared i = new int(10);
        REQUIRE(i.Get() != nullptr);
        REQUIRE(i.Count() == 1);
        REQUIRE(*i == 10);
    }

    SECTION("Copying a Shared ptr increases count")
    {
        Shared<int> int1 = new int(135);
        Shared<int> int2 = int1;
        REQUIRE(int1.Get() == int2.Get());
        REQUIRE(int1.Count() == 2);
        REQUIRE(int2.Count() == 2);
        REQUIRE(*int1 == 135);
        REQUIRE(*int2 == 135);
    }

    SECTION("Creating and destroying many times maintains count: loop")
    {
        Shared<int> int1 = new int(12345);
        int i = 0;
        while (i < 1000)
        {
            Shared<int> int2 = int1;
            if (int2.Count() != 2)
                break;
            ++i;
        }
        REQUIRE(i == 1000);
        REQUIRE(int1.Count() == 1);
        REQUIRE(*int1 == 12345);
    }

    SECTION("Creating and destroying many times maintains count: array")
    {
        Shared<int> int1 = new int(12345);
        
        Shared<int> ints[1000];
        int i;
        for (i = 0; i < 1000; ++i)
        {
            ints[i] = int1;
            if (int1.Count() != i + 2)
                break;
        }
        REQUIRE(i == 1000); // counts were accurate every iteration

        for (i = 0; i < 1000; ++i)
        {
            ints[i].Reset();
            if (int1.Count() != 1000 - i)
                break;
        }
        REQUIRE(i == 1000); // counts were accurate every iteration
        
        REQUIRE(int1.Count() == 1);
        REQUIRE(*int1 == 12345);
    }

    SECTION("Destroyed Shared ptr decreases count")
    {
        Shared<int> int1 = new int(135);
        {
            Shared<int> int2 = int1;
            REQUIRE(int1.Count() == 2);
            REQUIRE(int2.Count() == 2);
        }
        REQUIRE(int1.Count() == 1);
    }

    SECTION("Copying to a second Shared ptr decreases first's count")
    {
        Shared<int> int1 = new int(128);
        Shared<int> int2 = new int(256);
        Shared<int> copied = int1;
        REQUIRE(int1.Count() == 2);
        copied = int2;
        REQUIRE(int1.Count() == 1);
        REQUIRE(int2.Count() == 2);
    }
}
