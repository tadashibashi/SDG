#include "SDG_Tests.h"
#include <SDG/StringView.h>

#include <sstream>

TEST_CASE("StringView tests", "[StringView]")
{
    SECTION("Constructors")
    {
        SECTION("Default Constructor")
        {
            StringView view;
            REQUIRE(view.Length() == 0);
            REQUIRE(view.Empty());
            REQUIRE(view.begin() == view.end());
        }

        SECTION("Construct from String")
        {
            String str = "ABCDEFG";
            StringView view(str);
            REQUIRE(str.Length() == view.Length());
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Construct from std::string")
        {
            std::string str = "ABCDEFG";
            StringView view(str);
            REQUIRE(view.Length() == strlen(str.c_str()));
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Construct from c-string")
        {
            const char *str = "ABCDEFG";
            StringView view(str);
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Construct from c-string with size")
        {
            const char *str = "ABCDEFG";
            StringView view(str, 7);
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Construct from null c-string")
        {
            StringView view(nullptr);
            REQUIRE(view.Empty());
        }
    }

    SECTION("Assignment")
    {
        SECTION("Assign from another StringView")
        {
            String str = "ABCDEFG";
            StringView view1(str);
            StringView view2;
            view2 = view1;
            REQUIRE(view1.Length() == view2.Length());
            REQUIRE(strcmp(view1.Cstr(), view2.Cstr()) == 0);
        }

        SECTION("Assign from String")
        {
            String str = "ABCDEFG";
            StringView view; 
            view = str;
            REQUIRE(str.Length() == view.Length());
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Assign from std::string")
        {
            std::string str = "ABCDEFG";
            StringView view;
            view = str;
            REQUIRE(view.Length() == strlen(str.c_str()));
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Assign from c-string")
        {
            const char *str = "ABCDEFG";
            StringView view;
            view = str;
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Cstr(), "ABCDEFG") == 0);
        }

        SECTION("Assign from null c-string")
        {
            const char *str = nullptr;
            StringView view;
            view = str;
            REQUIRE(view.Empty());
            REQUIRE(view.Cstr() == nullptr);
        }
    }

    SECTION("Empty")
    {
        SECTION("Null c-string results in Empty")
        {
            const char *str = nullptr;
            StringView view(str);
            REQUIRE(view.Empty());
        }

        SECTION("Empty c-string results in Empty")
        {
            const char *str = "";
            StringView view(str);
            REQUIRE(view.Empty());
        }

        SECTION("Empty String set results in Empty")
        {
            String str;
            StringView view(str);
            REQUIRE(view.Empty());
        }

        SECTION("Empty std::string set results in Empty")
        {
            std::string str;
            StringView view(str);
            REQUIRE(view.Empty());
        }
    }

    SECTION("Length")
    {
        SECTION("Length retrieved from c-string set")
        {
            const char *str = "ABCDEFG";
            StringView view(str);

            REQUIRE(strlen(str) == view.Length());
        }

        SECTION("Length retrieved from null c-string")
        {
            const char *str = nullptr;
            StringView view(str);

            REQUIRE(0 == view.Length());
        }

        SECTION("Length retrieved from std::string set")
        {
            std::string str = "ABCDEFG";
            StringView view(str);

            REQUIRE(str.length() == view.Length());
        }

        SECTION("Length retrieved from SDG::String set")
        {
            String str = "ABCDEFG";
            StringView view(str);

            REQUIRE(str.Length() == view.Length());
        }
    }

    SECTION("Output operator")
    {
        std::stringstream ss;
        String str = "ABCDEFG";
        StringView view(str);

        ss << view;

        REQUIRE(strcmp(ss.str().c_str(), "ABCDEFG") == 0);
    }

    SECTION("")
    {

    }
}
