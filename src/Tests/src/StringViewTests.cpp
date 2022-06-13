#include "SDG_Tests.h"
#include <Engine/Debug/Performance.h>
#include <Engine/Exceptions/OutOfRangeException.h>
#include <Engine/Lib/StringView.h>

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
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Construct from std::string")
        {
            std::string str = "ABCDEFG";
            StringView view(str);
            REQUIRE(view.Length() == strlen(str.c_str()));
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Construct from c-string")
        {
            const char *str = "ABCDEFG";
            StringView view(str);
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Construct from c-string with size")
        {
            const char *str = "ABCDEFG";
            StringView view(str, 7);
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
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
            REQUIRE(strcmp(view1.Data(), view2.Data()) == 0);
        }

        SECTION("Assign from String")
        {
            String str = "ABCDEFG";
            StringView view; 
            view = str;
            REQUIRE(str.Length() == view.Length());
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Assign from std::string")
        {
            std::string str = "ABCDEFG";
            StringView view;
            view = str;
            REQUIRE(view.Length() == strlen(str.c_str()));
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Assign from c-string")
        {
            const char *str = "ABCDEFG";
            StringView view;
            view = str;
            REQUIRE(view.Length() == strlen(str));
            REQUIRE(strcmp(view.Data(), "ABCDEFG") == 0);
        }

        SECTION("Assign from null c-string")
        {
            const char *str = nullptr;
            StringView view;
            view = str;
            REQUIRE(view.Empty());
            REQUIRE(view.Data() == nullptr);
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
        SECTION("Normal string")
        {
            std::stringstream ss;
            String str = "ABCDEFG";
            StringView view(str);

            ss << view;

            REQUIRE(strcmp(ss.str().c_str(), "ABCDEFG") == 0);
        }
        SECTION("Empty string")
        {
            std::stringstream ss;
            String str;
            StringView view(str);

            ss << view;

            REQUIRE(strcmp(ss.str().c_str(), "") == 0);
        }
        SECTION("Null string")
        {
            std::stringstream ss;
            const char *str = nullptr;
            StringView view(str);

            ss << view;

            REQUIRE(strcmp(ss.str().c_str(), "") == 0);
        }

    }

    SECTION("Substr")
    {
        SECTION("Typical use")
        {
            String str = "Hello world";
            StringView view(str);

            REQUIRE(view.Substr(0, 5) == "Hello");
            REQUIRE(view.Substr(6, 5) == "world");
        }

        SECTION("Out of range exception")
        {
            String str = "Hello world";
            StringView view(str);

            bool didThrow;
            try {
                view = view.Substr(view.Length());
                didThrow = false;
            }
            catch (const OutOfRangeException& e)
            {
                didThrow = true;
            }

            REQUIRE(didThrow);
        }

    }

    SECTION("Swap")
    {
        String str1("Hello");
        String str2("World");

        StringView view1(str1);
        StringView view2(str2);

        // swap
        view1.Swap(view2);
        REQUIRE(strcmp(str1.Cstr(), view2.Data()) == 0);
        REQUIRE(strcmp(str2.Cstr(), view1.Data()) == 0);

        // swap back
        view1.Swap(view2);
        REQUIRE(strcmp(str1.Cstr(), view1.Data()) == 0);
        REQUIRE(strcmp(str2.Cstr(), view2.Data()) == 0);
    }

    SECTION("FindFirstOf")
    {
        SECTION("When not found, it returns NullPos")
        {
            String str("testing");
            StringView view(str);
            REQUIRE(view.FindFirstOf('/') == view.NullPos);
        }

        SECTION("When not found in empty str, it returns NullPos")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindFirstOf('/') == view.NullPos);
        }

        SECTION("Looking for terminator should return NullPos, not length")
        {
            String str("");
            StringView view(str);
            size_t pos = view.FindFirstOf('\0');
            REQUIRE(pos == view.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("path/");
            StringView view(str);
            size_t pos = view.FindFirstOf('/');
            REQUIRE(pos == view.Length() - 1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("/path");
            StringView view(str);
            size_t pos = view.FindFirstOf('/');
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("path/file.txt");
            StringView view(str);
            size_t pos = view.FindFirstOf('/');
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            StringView view(str);
            size_t pos = view.FindFirstOf('/');
            REQUIRE(pos == 4);
        }
    }

    SECTION("FindLastOf: single char")
    {
        SECTION("When not found, it returns NullPos")
        {
            String str("testing");
            StringView view(str);
            REQUIRE(view.FindLastOf('/') == str.NullPos);
        }

        SECTION("When not found in empty str, it returns NullPos")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindLastOf('/') == str.NullPos);
        }

        SECTION("Looking for terminator should return NullPos, not length")
        {
            String str("");
            StringView view(str);
            size_t pos = view.FindLastOf('\0');
            REQUIRE(pos == view.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("path/");
            StringView view(str);
            size_t pos = view.FindLastOf('/');
            REQUIRE(pos == view.Length() - 1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("/path");
            StringView view(str);
            size_t pos = view.FindLastOf('/');
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("path/file.txt");
            StringView view(str);
            size_t pos = view.FindLastOf('/');
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            StringView view(str);
            size_t pos = view.FindLastOf('/');
            REQUIRE(pos == 7);
        }
    }

    SECTION("FindLastOf: multiple char")
    {
        SECTION("When not found, it returns NullPos: one char")
        {
            String str("testing");
            StringView view(str);
            REQUIRE(view.FindLastOf("/") == view.NullPos);
        }
        SECTION("When not found, it returns NullPos: multiple chars")
        {
            String str("testing");
            StringView view(str);
            REQUIRE(view.FindLastOf("/810w") == view.NullPos);
        }

        SECTION("When not found in empty str, it returns NullPos: one char")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindLastOf("/") == view.NullPos);
        }
        SECTION("When not found in empty str, it returns NullPos: multiple chars")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindLastOf("/sdf") == view.NullPos);
        }

        SECTION("Finds at end of string: one char")
        {
            String str("path/");
            StringView view(str);
            size_t pos = view.FindLastOf("/");
            REQUIRE(pos == view.Length() - 1);
        }
        SECTION("Finds at end of string: multi char")
        {
            String str("path/");
            StringView view(str);
            size_t pos = view.FindLastOf("q/^");
            REQUIRE(pos == view.Length() - 1);
        }
        SECTION("Finds at end of string: multi char, end of list")
        {
            String str("path/");
            StringView view(str);
            size_t pos = view.FindLastOf("q^/");
            REQUIRE(pos == view.Length() - 1);
        }

        SECTION("Finds at beginning of string: one char")
        {
            String str("/path");
            StringView view(str);
            size_t pos = view.FindLastOf("/");
            REQUIRE(pos == 0);
        }
        SECTION("Finds at beginning of string: multi char")
        {
            String str("/path");
            StringView view(str);
            size_t pos = view.FindLastOf("q/f");
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string: one char")
        {
            String str("path/file.txt");
            StringView view(str);
            size_t pos = view.FindLastOf("/");
            REQUIRE(pos == 4);
        }
        SECTION("Finds in middle of string: multi char")
        {
            String str("path/file.txt");
            StringView view(str);
            size_t pos = view.FindLastOf("*/!@#");
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            StringView view(str);
            size_t pos = view.FindLastOf('/');
            REQUIRE(pos == 7);
        }
    }

    SECTION("FindLastNotOf")
    {
        SECTION("When all of the same char it returns String::NullPos")
        {
            String str("///");
            StringView view(str);
            REQUIRE(view.FindLastNotOf('/') == str.NullPos);
        }

        SECTION("When not found in empty str, it returns String::NullPos")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindLastNotOf('/') == str.NullPos);
        }

        SECTION("Looking for terminator should return String::NullPos, not length")
        {
            String str("");
            StringView view(str);
            size_t pos = str.FindLastNotOf('\0');
            REQUIRE(pos == str.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("///a");
            StringView view(str);
            size_t pos = str.FindLastNotOf('/');
            REQUIRE(pos == str.Length() - 1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("a///");
            StringView view(str);
            size_t pos = str.FindLastNotOf('/');
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("////a/////");
            StringView view(str);
            size_t pos = str.FindLastNotOf('/');
            REQUIRE(pos == 4);
        }

        SECTION("Finds last when there are two occurrences")
        {
            String str("////a/////b////");
            StringView view(str);
            size_t pos = str.FindLastNotOf('/');
            REQUIRE(pos == 10);
        }
    }

    SECTION("FindLastNotOf: list overload")
    {
        SECTION("When all matching it returns String::NullPos")
        {
            String str("/@/!/#");
            StringView view(str);
            REQUIRE(view.FindLastNotOf("/!@#") == str.NullPos);
        }

        SECTION("When not found in empty str, it returns String::NullPos")
        {
            String str("");
            StringView view(str);
            REQUIRE(view.FindLastNotOf("abcdef") == str.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("Z$/a");
            StringView view(str);
            size_t pos = str.FindLastNotOf("/Z$");
            REQUIRE(pos == str.Length() - 1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("a**");
            StringView view(str);
            size_t pos = str.FindLastNotOf("^&*");
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("/&*(//a//*()//");
            StringView view(str);
            size_t pos = str.FindLastNotOf("/&*()");
            REQUIRE(pos == 6);
        }

        SECTION("Finds last when there are two occurrences")
        {
            String str("**//a/*/{//b///{/");
            StringView view(str);
            size_t pos = str.FindLastNotOf("/*{");
            REQUIRE(pos == 11);
        }
    }

    SECTION("== operator")
    {
        SECTION("StringView to StringView")
        {
            SECTION("Typical equality")
            {
                const char *str1 = "abcd";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) == StringView(str2));
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE(StringView(str1) == StringView(str2));
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE(StringView(nullptr) == StringView(nullptr));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(StringView(str1) == StringView(str2));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(!(StringView(str1) == StringView(str2)));
            }
        }

        SECTION("StringView to String")
        {
            SECTION("Typical equality")
            {
                const char *str1 = "abcd";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) == String(str2));
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE(StringView(str1) == String(str2));
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE(StringView(nullptr) == String(nullptr));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(StringView(str1) == String(str2));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(!(StringView(str1) == String(str2)));
            }
        }

        SECTION("StringView to std::string")
        {
            SECTION("Typical equality")
            {
                const char *str1 = "abcd";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) == std::string(str2));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(StringView(str1) == std::string(str2));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(!(StringView(str1) == std::string(str2)));
            }
        }

        SECTION("StringView to c-string")
        {
            SECTION("Typical equality")
            {
                const char *str1 = "abcd";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) == str2);
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE(StringView(str1) == str2);
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE(StringView(nullptr) == (const char *)nullptr);
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(StringView(str1) == str2);
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(!(StringView(str1) == str2));
            }

            SECTION("Same strings but differing lengths unequal, switch order")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(!(StringView(str2) == str1));
            }
        }
    }

    SECTION("!= operator")
    {
        SECTION("StringView to StringView")
        {
            SECTION("Typical inequality")
            {
                const char *str1 = "dcba";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) != StringView(str2));
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE( !(StringView(str1) != StringView(str2)) );
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE( !(StringView(nullptr) != StringView(nullptr)) );
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE( !(StringView(str1) != StringView(str2)) );
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(StringView(str1) != StringView(str2));
            }
        }

        SECTION("StringView to String")
        {
            SECTION("Typical inequality")
            {
                const char *str1 = "dcba";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) != String(str2));
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE(!(StringView(str1) != String(str2)));
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE(!(StringView(nullptr) != String(nullptr)));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(!(StringView(str1) != String(str2)));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(StringView(str1) != String(str2));
            }
        }

        SECTION("StringView to std::string")
        {
            SECTION("Typical inequality")
            {
                const char *str1 = "dcba";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) != std::string(str2));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(!(StringView(str1) != std::string(str2)));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(StringView(str1) != std::string(str2));
            }
        }

        SECTION("StringView to c-string")
        {
            SECTION("Typical inequality")
            {
                const char *str1 = "dcba";
                const char *str2 = "abcd";

                REQUIRE(StringView(str1) != str2);
            }

            SECTION("Nullptr string equal to empty")
            {
                const char *str1 = "";
                const char *str2 = nullptr;

                REQUIRE(!(StringView(str1) != str2));
            }

            SECTION("Nullptr string equal to nullptr")
            {
                REQUIRE(!(StringView(nullptr) != (const char *)nullptr));
            }

            SECTION("Empty string equal to empty string")
            {
                const char *str1 = "";
                const char *str2 = "";
                REQUIRE(!(StringView(str1) != str2));
            }

            SECTION("Same strings but differing lengths unequal")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(StringView(str1) != str2);
            }

            SECTION("Same strings but differing lengths unequal, swap order")
            {
                const char *str1 = "abc";
                const char *str2 = "abcdefg";
                REQUIRE(StringView(str2) != str1);
            }
        }
    }

    SECTION("operator []")
    {
        SECTION("Works within range")
        {
            const char *str = "012345";
            StringView view(str);

            REQUIRE(view[0] == '0');
            REQUIRE(view[1] == '1');
            REQUIRE(view[2] == '2');
            REQUIRE(view[3] == '3');
            REQUIRE(view[4] == '4');
            REQUIRE(view[5] == '5');
        }

        SECTION("Throws outside of range")
        {
            const char *str = "012345";
            StringView view(str);

            bool didThrow = false;;
            try {
                char c = view[10];
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }

            REQUIRE(didThrow);
        }
    }

    SECTION("operator +")
    {
        SECTION("StringView + StringView -> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(StringView(str1) + StringView(str2) == String("abcdefgh"));
        }

        SECTION("StringView + String -> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(StringView(str1) + String(str2) == String("abcdefgh"));
        }

        SECTION("StringView + std::string -> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(StringView(str1) + std::string(str2) == String("abcdefgh"));
        }

        SECTION("StringView + const char *-> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(StringView(str1) + str2 == String("abcdefgh"));
        }

        SECTION("const char * + StringView -> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(str1 + StringView(str2) == String("abcdefgh"));
        }

        SECTION("String + StringView -> String")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(String(str1) + StringView(str2) == String("abcdefgh"));
        }

        SECTION("std::string + StringView -> std::string")
        {
            const char *str1 = "abcd";
            const char *str2 = "efgh";
            REQUIRE(std::string(str1) + StringView(str2) == std::string("abcdefgh"));
        }
    }

    SECTION("Trim")
    {
        SECTION("Whitespace")
        {
            SECTION("Empty")
            {
                String str = "";
                String view = str;
                REQUIRE(view.Trim() == "");
            }

            SECTION("One whitespace, blank string")
            {
                String str = " ";
                String view = str;
                REQUIRE(view.Trim() == "");
            }

            SECTION("Many whitespaces, blank string")
            {
                String str = "                  ";
                String view = str;
                REQUIRE(view.Trim() == "");
            }

            SECTION("One whitespace")
            {
                String str = " abcdefg";
                String view = str;
                REQUIRE(view.Trim() == "abcdefg");
            }

            SECTION("Many whitespaces")
            {
                String str = "                 abcdefg";
                String view = str;
                REQUIRE(view.Trim() == "abcdefg");
            }
        }
        SECTION("Chars")
        {
            SECTION("Empty")
            {
                String str = "";
                String view = str;
                REQUIRE(view.Trim("abc&*(") == "");
            }

            SECTION("One matching, blank string")
            {
                String str = "c";
                String view = str;
                REQUIRE(view.Trim("abc&*(") == "");
            }

            SECTION("Many matching, blank string")
            {
                String str = "a&&*(c&abc&*(abc";
                String view = str;
                REQUIRE(view.Trim("abc&*(") == "");
            }

            SECTION("One matching")
            {
                String str = "&def";
                String view = str;
                REQUIRE(view.Trim("abc&*(") == "def");
            }

            SECTION("Many matching")
            {
                String str = "cabc&*(((((((((((baxbcdefg";
                String view = str;
                REQUIRE(view.Trim("abc&*(") == "xbcdefg");
            }
        }
    }

    SECTION("TrimEnd")
    {
        SECTION("Whitespace")
        {
            SECTION("Empty")
            {
                String str = "";
                String view = str;
                REQUIRE(view.TrimEnd() == "");
            }

            SECTION("One whitespace, blank string")
            {
                String str = " ";
                String view = str;
                REQUIRE(view.TrimEnd() == "");
            }

            SECTION("Many whitespaces, blank string")
            {
                String str = "                  ";
                String view = str;
                REQUIRE(view.TrimEnd() == "");
            }

            SECTION("One whitespace")
            {
                String str = "abcdefg ";
                String view = str;
                REQUIRE(view.TrimEnd() == "abcdefg");
            }

            SECTION("Many whitespaces")
            {
                String str = "abcdefg                  ";
                String view = str;
                REQUIRE(view.TrimEnd() == "abcdefg");
            }
        }
        SECTION("Chars")
        {
            SECTION("Empty")
            {
                String str = "";
                String view = str;
                REQUIRE(view.TrimEnd("abc&*(") == "");
            }

            SECTION("One matching, blank string")
            {
                String str = "c";
                String view = str;
                REQUIRE(view.TrimEnd("abc&*(") == "");
            }

            SECTION("Many matching, blank string")
            {
                String str = "a&&*(c&abc&*(abc";
                String view = str;
                REQUIRE(view.TrimEnd("abc&*(") == "");
            }

            SECTION("One matching")
            {
                String str = "abcdef*";
                String view = str;
                REQUIRE(view.TrimEnd("abc&*(") == "abcdef");
            }

            SECTION("Many matching")
            {
                String str = "abcdefgcabc&*(((((((((((ba";
                String view = str;
                REQUIRE(view.TrimEnd("abc&*(") == "abcdefg");
            }
        }
    }
}
