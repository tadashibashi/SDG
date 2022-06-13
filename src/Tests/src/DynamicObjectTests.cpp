#include "SDG_Tests.h"
#include <Engine/Dynamic/Object.h>
#include <Engine/Dynamic/Struct.h>
#include <Engine/Dynamic/Array.h>

using namespace SDG::Dynamic;

TEST_CASE("DynamicObject tests")
{
    SECTION("Setting and getting a c-string")
    {
        var obj;
        obj = "hello world";

        REQUIRE(obj.AsString() == "hello world");
        REQUIRE(obj.GetType() == Dynamic::Type::String);
    }

    SECTION("Multiple c-string assignments")
    {
        var obj;

        obj = "hello world";
        REQUIRE(obj.AsString() == "hello world");
        REQUIRE(obj.GetType() == Type::String);

        obj = "abcdefg";
        REQUIRE(obj.AsString() == "abcdefg");
        REQUIRE(obj.GetType() == Type::String);
    }

    SECTION("C-string += operator")
    {
        var obj1;
        obj1 = "hello ";
        obj1 += "world";

        REQUIRE(obj1.AsString() == "hello world");
    }

    SECTION("Setting and getting a real number")
    {
        var obj;
        obj = 11;

        REQUIRE(obj.AsReal() == 11);
        REQUIRE(obj.GetType() == Type::Real);
    }

    SECTION("Multiple real number assignments")
    {
        var obj;
        obj = 11;

        REQUIRE(obj.AsReal() == 11);
        REQUIRE(obj.GetType() == Type::Real);

        obj = 11.5;
        REQUIRE(obj.AsReal() == 11.5);
        REQUIRE(obj.GetType() == Type::Real);
    }

    SECTION("Setting and getting a struct")
    {
        Struct s;
        s["animal"] = "rabbit";
        s["pizzas"] = 10;

        Struct yo;
        yo["acorns"] = 20;
        yo["struct"] = s;
        yo["null"] = null;
        s["recurse"] = yo;

        SDG_Log("{}", yo);

        var o;
        o = s;

        REQUIRE(o.Is(Type::Struct));
        REQUIRE(o == s);
    }

    SECTION("Getting and setting array")
    {
        var o(Dynamic::Array({ 0, 1, 2, String("hey") })); // improve the syntax for arrays
        REQUIRE(o.Is(Type::Array));
        REQUIRE(o.AsArray().Size() == 4);
        REQUIRE(o[0] == 0);
        REQUIRE(o[1] == 1);
        REQUIRE(o[3] == "hey");

        auto arr = MakeArray(10, 20, 30, "yo", Struct(), MakeArray("ACORNS", "yo2", 123.023));
        REQUIRE(arr.Size() == 6);
        REQUIRE(arr[3] == "yo");
        REQUIRE(arr[0] == 10);
        REQUIRE(arr[4].GetType() == Dynamic::Type::Struct);
        REQUIRE(arr[5].GetType() == Dynamic::Type::Array);
        REQUIRE(arr[5][0] == "ACORNS");
        REQUIRE(arr[5][1] == "yo2");
        REQUIRE(arr[5][2] == 123.023);

        auto s = Struct({ { "key1", Object("hey") }, { "key2", String("hey2") }, { "key3", 123.123 } });
        REQUIRE(s["key1"] == "hey");
        REQUIRE(s["key2"] == "hey2");
        REQUIRE(s["key3"] == 123.123);

    }

    SECTION("Switch types")
    {
        Dynamic::Object obj;
        obj = 11;

        REQUIRE(obj.AsReal() == 11);
        REQUIRE(obj.GetType() == Type::Real);

        obj = "pizza";
        REQUIRE(obj.AsString() == "pizza");
        REQUIRE(obj.GetType() == Dynamic::Type::String);

        obj = 123.123;
        REQUIRE(obj.AsReal() == 123.123);
        REQUIRE(obj.GetType() == Dynamic::Type::Real);
    }
}