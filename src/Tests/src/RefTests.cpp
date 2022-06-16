#include "SDG_Tests.h"
#include <Engine/Lib/Ref.h>
#include <string>

TEST_CASE("Ref tests", "[Ref]")
{
    SECTION("Constructor Tests")
    {
        SECTION("From Reference")
        {
            std::string original;
            Ref<std::string> ref(original);

            REQUIRE(ref.Get() == &original);
        }

        SECTION("From Pointer")
        {
            std::string original;
            Ref<std::string> ref(&original);

            REQUIRE(ref.Get() == &original);
        }

        SECTION("Fom null pointer")
        {
            Ref<std::string> ref(nullptr);

            REQUIRE(!ref.Get());
        }

        SECTION("Default ctor stores nullptr")
        {
            Ref<std::string> ref;
            REQUIRE(!ref.Get());
        }
    }

    SECTION("Dereference test")
    {
        std::string str = "hello world";
        Ref<std::string> ref(str);

        REQUIRE(*ref == str);
    }

    SECTION("Dereferencing a nullptr throws NullReferenceException")
    {
        Ref<std::string> ref;
        bool didThrow = false;
        try {
            std::string &str = *ref;
        }
        catch (const NullReferenceException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }

    SECTION("-> test")
    {
        std::string str = "hello world";
        Ref<std::string> ref(str);

        REQUIRE(ref->length() == str.length());
    }

    SECTION("-> on a nullptr throws NullReferenceException")
    {
        Ref<std::string> ref;
        bool didThrow = false;
        try {
            ref->assign("");
        }
        catch (const NullReferenceException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }

    SECTION("Automatic bool eval works on set reference")
    {
        std::string str = "hello world";
        Ref<std::string> ref(str);

        REQUIRE(ref);
    }

    SECTION("Automatic bool eval works on nullptr")
    {
        Ref<std::string> ref;

        REQUIRE(!ref);
    }

    SECTION("Ref == Ref")
    {
        std::string str;
        std::string str2;

        Ref<std::string> refSame1(str);
        Ref<std::string> refSame2(str);
        Ref<std::string> refDiff(str2);

        REQUIRE((refSame1 == refSame2));
        REQUIRE(!(refSame1 == refDiff));
    }

    SECTION("Ref != Ref")
    {
        std::string str;
        std::string str2;

        Ref<std::string> refSame1(str);
        Ref<std::string> refSame2(str);
        Ref<std::string> refDiff(str2);

        REQUIRE(!(refSame1 != refSame2));
        REQUIRE((refSame1 != refDiff));
    }
}
