#include "SDG_Tests.h"
#include <Engine/Debug/Log.h>
#include <Engine/Lib/String.h>

#include <sstream>
#include <utility>

TEST_CASE("String tests", "[String]")
{
    SECTION("Default Cap should be > 0")
    {
        REQUIRE(String::DefaultCap > 0);
    }

    SECTION("String::NullPos should be > String::DefaultCap")
    {
        REQUIRE(String::NullPos > String::DefaultCap);
    }

    SECTION("Default constructor test")
    {
        String str;

        // Creates a valid c-string from the start
        REQUIRE(str.Cstr() != nullptr);
        // Valid capacity from the start
        REQUIRE(str.Capacity() == String::DefaultCap);
        REQUIRE(str.Length() == 0);
        REQUIRE((str == ""));
    }

    SECTION("Constructor from std::string")
    {
        std::string stdstr("Hello");
        String str(stdstr);

        REQUIRE(str.Length() == stdstr.length());
        REQUIRE(strcmp(str.Cstr(), stdstr.c_str()) == 0);
    }

    SECTION("Constructor from empty std::string")
    {
        std::string stdstr("");
        String str(stdstr);

        REQUIRE(str.Length() == stdstr.length());
        REQUIRE(str.Empty());
    }

    SECTION("Constructor from c string")
    {
        const char *cstr = "Hello";
        String str(cstr);

        REQUIRE(str.Length() == strlen(cstr));
        REQUIRE(strcmp(str.Cstr(), cstr) == 0);
    }

    SECTION("Constructor from nullptr c string")
    {
        const char *cstr = nullptr;
        String str(cstr);

        REQUIRE(str.Length() == 0);
        REQUIRE(str.Empty());
    }

    SECTION("Constructor from empty c string")
    {
        const char *cstr = "";
        String str(cstr);

        REQUIRE(str.Length() == 0);
        REQUIRE(str.Empty());
    }

    SECTION("Copy Constructor")
    {
        String str1("12345");
        String str2(str1);

        REQUIRE(strcmp(str1.Cstr(), str2.Cstr()) == 0);
    }

    SECTION("Assignment from another String")
    {
        String str1("Hello");
        String str2;
        str2 = str1;

        REQUIRE(str1.Length() == str2.Length());
        REQUIRE(strcmp(str1.Cstr(), str2.Cstr()) == 0);
    }

    SECTION("Assignment from std::string")
    {
        std::string stdstr("Hello");
        String str;
        str = stdstr;

        REQUIRE(str.Length() == stdstr.length());
        REQUIRE(strcmp(str.Cstr(), stdstr.c_str()) == 0);
    }

    SECTION("Assignment from empty std::string")
    {
        std::string stdstr("");
        String str;
        str = stdstr;

        REQUIRE(str.Length() == stdstr.length());
        REQUIRE(str.Empty());
    }

    SECTION("Assignment from c string")
    {
        const char *cstr = "Hello";
        String str;
        str = cstr;

        REQUIRE(str.Length() == strlen(cstr));
        REQUIRE(strcmp(str.Cstr(), cstr) == 0);
    }

    SECTION("Assignment from nullptr c string")
    {
        const char *cstr = nullptr;
        String str;
        str = cstr;

        REQUIRE(str.Length() == 0);
        REQUIRE(str.Empty());
    }

    SECTION("Assignment from empty c string")
    {
        const char *cstr = "";
        String str;
        str = cstr;

        REQUIRE(str.Length() == 0);
        REQUIRE(str.Empty());
    }

    SECTION("FindFirstOf")
    {
        SECTION("When not found, it returns String::NullPos")
        {
            String str("testing");
            REQUIRE(str.FindFirstOf('/') == str.NullPos);
        }

        SECTION("When not found in empty str, it returns String::NullPos")
        {
            String str("");
            REQUIRE(str.FindFirstOf('/') == str.NullPos);
        }

        SECTION("Looking for terminator should return String::NullPos, not length")
        {
            String str("");
            size_t pos = str.FindFirstOf('\0');
            REQUIRE(pos == str.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("path/");
            size_t pos = str.FindFirstOf('/');
            REQUIRE(pos == str.Length()-1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("/path");
            size_t pos = str.FindFirstOf('/');
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("path/file.txt");
            size_t pos = str.FindFirstOf('/');
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            size_t pos = str.FindFirstOf('/');
            REQUIRE(pos == 4);
        }
    }

    SECTION("FindLastOf: single char")
    {
        SECTION("When not found, it returns String::NullPos")
        {
            String str("testing");
            REQUIRE(str.FindLastOf('/') == str.NullPos);
        }

        SECTION("When not found in empty str, it returns String::NullPos")
        {
            String str("");
            REQUIRE(str.FindLastOf('/') == str.NullPos);
        }

        SECTION("Looking for terminator should return String::NullPos, not length")
        {
            String str("");
            size_t pos = str.FindLastOf('\0');
            REQUIRE(pos == str.NullPos);
        }

        SECTION("Finds at end of string")
        {
            String str("path/");
            size_t pos = str.FindLastOf('/');
            REQUIRE(pos == str.Length()-1);
        }

        SECTION("Finds at beginning of string")
        {
            String str("/path");
            size_t pos = str.FindLastOf('/');
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string")
        {
            String str("path/file.txt");
            size_t pos = str.FindLastOf('/');
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            size_t pos = str.FindLastOf('/');
            REQUIRE(pos == 7);
        }
    }

    SECTION("FindLastOf: multiple char")
    {
        SECTION("When not found, it returns String::NullPos: one char")
        {
            String str("testing");
            REQUIRE(str.FindLastOf("/") == str.NullPos);
        }
        SECTION("When not found, it returns String::NullPos: multiple chars")
        {
            String str("testing");
            REQUIRE(str.FindLastOf("/810w") == str.NullPos);
        }

        SECTION("When not found in empty str, it returns String::NullPos: one char")
        {
            String str("");
            REQUIRE(str.FindLastOf("/") == str.NullPos);
        }
        SECTION("When not found in empty str, it returns String::NullPos: multiple chars")
        {
            String str("");
            REQUIRE(str.FindLastOf("/sdf") == str.NullPos);
        }

        SECTION("Finds at end of string: one char")
        {
            String str("path/");
            size_t pos = str.FindLastOf("/");
            REQUIRE(pos == str.Length() - 1);
        }
        SECTION("Finds at end of string: multi char")
        {
            String str("path/");
            size_t pos = str.FindLastOf("q/^");
            REQUIRE(pos == str.Length() - 1);
        }
        SECTION("Finds at end of string: multi char, end of list")
        {
            String str("path/");
            size_t pos = str.FindLastOf("q^/");
            REQUIRE(pos == str.Length() - 1);
        }

        SECTION("Finds at beginning of string: one char")
        {
            String str("/path");
            size_t pos = str.FindLastOf("/");
            REQUIRE(pos == 0);
        }
        SECTION("Finds at beginning of string: multi char")
        {
            String str("/path");
            size_t pos = str.FindLastOf("q/f");
            REQUIRE(pos == 0);
        }

        SECTION("Finds in middle of string: one char")
        {
            String str("path/file.txt");
            size_t pos = str.FindLastOf("/");
            REQUIRE(pos == 4);
        }
        SECTION("Finds in middle of string: multi char")
        {
            String str("path/file.txt");
            size_t pos = str.FindLastOf("*/!@#");
            REQUIRE(pos == 4);
        }

        SECTION("Finds first when there are two occurrences")
        {
            String str("path/to/file.txt");
            size_t pos = str.FindLastOf('/');
            REQUIRE(pos == 7);
        }
    }

    SECTION("Comparison")
    {
        SECTION("with other String")
        {
            SECTION("Empty")
            {
                String str1;
                String str2;

                REQUIRE((str1 == str2));
            }

            SECTION("With substance")
            {
                String str1("123456");
                String str2("123456");

                REQUIRE((str1 == str2));
            }
        }

        SECTION("with std::string")
        {
            SECTION("Empty")
            {
                String str1;
                std::string str2;

                REQUIRE((str1 == str2));
            }

            SECTION("With substance")
            {
                String str1("123456");
                std::string str2("123456");

                REQUIRE((str1 == str2));
            }
        }

        SECTION("with c-string")
        {
            SECTION("Empty")
            {
                String str1;
                const char *str2 = "";

                REQUIRE((str1 == str2));
            }

            SECTION("With substance")
            {
                String str1("123456");
                const char *str2 = "123456";

                REQUIRE((str1 == str2));
            }
        }
    }

    SECTION("Reserve")
    {
        SECTION("Reserving smaller size does not affect Capacity")
        {
            String str;

            REQUIRE(str.Capacity() == str.DefaultCap);

            str.Reserve(str.DefaultCap - 1);

            REQUIRE(str.Capacity() == str.DefaultCap);
        }

        SECTION("Reserving larger size affects Capacity")
        {
            String str;

            REQUIRE(str.Capacity() == str.DefaultCap);

            str.Reserve(str.DefaultCap * 2);

            REQUIRE(str.Capacity() == str.DefaultCap * 2);
        }
    }

    SECTION("Appending")
    {
        SECTION("with other String")
        {
            SECTION("with empty")
            {
                String str1("12345");
                String str2;

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                String str2("678910");

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with std::string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                std::string str2;

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                std::string str2("678910");

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with c-string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                const char *str2 = "";

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                const char *str2("678910");

                str1.Append(str2);
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with char")
        {
            SECTION("On empty String")
            {
                String str;
                str.Append('c');

                REQUIRE(strcmp(str.Cstr(), "c") == 0);
            }

            SECTION("On String with substance")
            {
                String str("123");
                str.Append('4');

                REQUIRE(strcmp(str.Cstr(), "1234") == 0);
            }
        }
    }

    SECTION("operator +=")
    {
        SECTION("with other String")
        {
            SECTION("with empty")
            {
                String str1("12345");
                String str2;

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                String str2("678910");

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with std::string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                std::string str2;

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                std::string str2("678910");

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with c-string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                const char *str2 = "";

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                const char *str2("678910");

                str1 += str2;
                REQUIRE(strcmp(str1.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with char")
        {
            SECTION("On empty String")
            {
                String str;
                str += 'c';

                REQUIRE(strcmp(str.Cstr(), "c") == 0);
            }

            SECTION("On String with substance")
            {
                String str("123");
                str += '4';

                REQUIRE(strcmp(str.Cstr(), "1234") == 0);
            }
        }
    }


    SECTION("operator +")
    {
        SECTION("with other String")
        {
            SECTION("with empty")
            {
                String str1("12345");
                String str2;
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                String str2("678910");
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with std::string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                std::string str2;
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                std::string str2("678910");
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345678910") == 0);
            }
        }

        SECTION("with c-string")
        {
            SECTION("with empty")
            {
                String str1("12345");
                const char *str2 = "";
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345") == 0);
            }

            SECTION("when other has substance")
            {
                String str1("12345");
                const char *str2("678910");
                String str3;

                str3 = str1 + str2;
                REQUIRE(strcmp(str3.Cstr(), "12345678910") == 0);
            }
        }
    }

    SECTION("std::string == SDG::String")
    {
        SECTION("Empty")
        {
            String str1;
            std::string str2;

            REQUIRE((str2 == str1));
        }

        SECTION("With substance")
        {
            String str1("12345");
            std::string str2("12345");

            REQUIRE((str2 == str1));
        }
    }

    SECTION("(const char *) + (const SDG::String &)")
    {
        String str1 = "World";
        const char *str2 = "Hello ";

        String combined = str2 + str1;
        REQUIRE((combined == "Hello World"));
    }

    SECTION("std::ostream &operator << (std::ostream &, const SDG::String &)")
    {
        SECTION("Empty")
        {
            String str;
            std::stringstream ss;

            ss << str;

            REQUIRE(ss.str().empty());
        }

        SECTION("With substance")
        {
            String str("12345");
            std::stringstream ss;

            ss << str;

            REQUIRE(ss.str() == "12345");
        }
    }

    SECTION("Str")
    {
        SECTION("Empty")
        {
            String str;

            REQUIRE(str.Str().empty());
        }

        SECTION("With substance")
        {
            String str("12345");

            REQUIRE(str.Str() == "12345");
        }
    }

    SECTION("Indexer")
    {
        SECTION("Const indexer throws when out of range")
        {
            // Using a const function to force use of const indexer
            struct StringIndexerTest
            {
                StringIndexerTest() : str("0123") { }
                void TestConst() const
                {
                    bool didThrow = false;
                    try {
                        char c = str[4];
                    }
                    catch (const OutOfRangeException &e)
                    {
                        didThrow = true;
                    }

                    REQUIRE(didThrow);
                }

                String str;

            } test{ };

            test.TestConst();
        }

        SECTION("Non-const indexer throws when out of range")
        {
            String str("0123");

            bool didThrow;
            try {
                str[4] = 'x';
                didThrow = false;
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }

            REQUIRE(didThrow);
        }
        SECTION("Sets the index correctly with non-const indexer")
        {
            String str("0123");
            REQUIRE((str == "0123"));

            str[0] = 'a';
            REQUIRE((str == "a123"));

            str[1] = 'b';
            REQUIRE((str == "ab23"));

            str[2] = 'c';
            REQUIRE((str == "abc3"));

            str[3] = 'd';
            REQUIRE((str == "abcd"));
        }

        SECTION("Reads the indexes correctly")
        {
            String str("0123");
            REQUIRE(str[0] == '0');
            REQUIRE(str[1] == '1');
            REQUIRE(str[2] == '2');
            REQUIRE(str[3] == '3');
        }

        SECTION("Iterate using range-based for loop")
        {
            String str("0123");
            for (char &c : str)
                c += 1;

            REQUIRE((str == "1234"));
        }
    }

    SECTION("Erase")
    {
        SECTION("char")
        {
            SECTION("first char")
            {
                String str("012345");
                str.Erase(0);

                REQUIRE((str == "12345"));
            }
            SECTION("middle char")
            {
                String str("012345");
                str.Erase(3);
                REQUIRE((str == "01245"));
            }
            SECTION("last char")
            {
                String str("012345");
                str.Erase(5);
                REQUIRE((str == "01234"));
            }
        }

        SECTION("iterators")
        {
            SECTION("first char")
            {
                String str("012345");
                str.Erase(str.begin(), str.begin() + 1);

                REQUIRE((str == "12345"));
            }
            SECTION("middle char")
            {
                String str("012345");
                str.Erase(str.begin() + 3, str.begin() + 4);
                REQUIRE((str == "01245"));
            }
            SECTION("last char")
            {
                String str("012345");
                str.Erase(str.begin() + 5, str.end());
                REQUIRE((str == "01234"));
            }
            SECTION("range, including first char")
            {
                String str("012345");
                str.Erase(str.begin(), str.begin() + 2);

                REQUIRE((str == "2345"));
            }

            SECTION("range, including last char")
            {
                String str("012345");
                str.Erase(str.begin() + 3, str.end());

                REQUIRE((str == "012"));
            }

            SECTION("range, full")
            {
                String str("012345");
                str.Erase(str.begin(), str.end());

                REQUIRE((str.Empty()));
            }
        }

        SECTION("EraseIf")
        {
            SECTION("Does not remove any due to predicate")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return std::isalpha(c);
                });

                REQUIRE((str == "012345"));
            }

            SECTION("Removes first char")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '0';
                });

                REQUIRE((str == "12345"));
            }

            SECTION("Removes middle char")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '3';
                });

                REQUIRE((str == "01245"));
            }

            SECTION("Removes last char")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '5';
                });

                REQUIRE((str == "01234"));
            }

            SECTION("Removes multiple first, touching")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '0' || c == '1';
                });

                REQUIRE((str == "2345"));
            }

            SECTION("Removes multiple end, touching")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '4' || c == '5';
                });

                REQUIRE((str == "0123"));
            }

            SECTION("Removes multiple, both ends")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return c == '0' || c == '5';
                });

                REQUIRE((str == "1234"));
            }

            SECTION("Removes all")
            {
                String str("012345");
                str.EraseIf([](char c)->bool {
                    return std::isdigit(c);
                });

                REQUIRE((str.Empty()));
            }

            SECTION("Removes multiple, same char")
            {
                String str("/01//2/3/45/");
                str.EraseIf([](char c)->bool {
                    return c == '/';
                });

                REQUIRE((str == "012345"));
            }
        }
    }

    SECTION("Substr")
    {
        SECTION("Whole string, using default NullPos")
        {
            String str("012345");
            REQUIRE((str.Substr(0) == "012345"));
        }

        SECTION("Whole string, using literal")
        {
            String str("012345");
            REQUIRE((str.Substr(0, 6) == "012345"));
        }

        SECTION("Last part, using default NullPos")
        {
            String str("012345");
            REQUIRE((str.Substr(2) == "2345"));
        }

        SECTION("Last char, using default NullPos")
        {
            String str("012345");
            REQUIRE((str.Substr(5) == "5"));
        }

        SECTION("Out of range index returns blank string")
        {
            String str("012345");
            REQUIRE(str.Substr(6).Empty());
        }

        SECTION("First part")
        {
            String str("012345");
            REQUIRE((str.Substr(0, 2) == "01"));
        }

        SECTION("Last part")
        {
            String str("012345");
            REQUIRE((str.Substr(3, 3) == "345"));
        }

        SECTION("Middle part")
        {
            String str("012345");
            REQUIRE((str.Substr(3, 3) == "345"));
        }
    }

    SECTION("Find")
    {
        SECTION("Empty string, empty search")
        {
            String str;
            REQUIRE(str.Find("") == str.NullPos);
        }
        SECTION("Empty string, str search")
        {
            String str;
            REQUIRE(str.Find("123") == str.NullPos);
        }
        SECTION("One char string, multi-char search")
        {
            String str("a");
            REQUIRE(str.Find("abc") == str.NullPos);
        }
        SECTION("One char string, empty search")
        {
            String str("a");
            REQUIRE(str.Find("") == str.NullPos);
        }
        SECTION("One char string, matching search")
        {
            String str("a");
            REQUIRE(str.Find("a") == 0);
        }
        SECTION("Multi-char string, one char search matches midway")
        {
            String str("abcdefg");
            REQUIRE(str.Find("d") == 3);
        }
        SECTION("Multi-char string, one char search matches last char")
        {
            String str("abcdefg");
            REQUIRE(str.Find("g") == 6);
        }
        SECTION("Multi-char string, search too long")
        {
            String str("abc");
            REQUIRE(str.Find("abcdef") == str.NullPos);
        }
        SECTION("Multi-char string, matching search position 0")
        {
            String str("abcdef");
            REQUIRE(str.Find("abcdef") == 0);
        }
        SECTION("Multi-char string, matching search position 3")
        {
            String str("abcdef");
            REQUIRE(str.Find("de") == 3);
        }
        SECTION("Multi-char string, matching search position 3 until end")
        {
            String str("abcdef");
            REQUIRE(str.Find("def") == 3);
        }
        SECTION("StartingAt matches on-the-nose")
        {
            String str("abcabcd");
            REQUIRE(str.Find("abc", 3) == 3);
        }
        SECTION("StartingAt misses a match")
        {
            String str("abcabcd");
            REQUIRE(str.Find("abc", 1) == 3);
        }
        SECTION("StartingAt too high index")
        {
            String str("abcabcd");

            bool didThrow;
            try {
                size_t pos = str.Find("abc", 10);
                didThrow = false;
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }
    }

    SECTION("Format")
    {
        // Extensive tests here aren't too necessary since the function is a thin wrapper around the fmt library
        REQUIRE(String::Format("Hello") == "Hello");
        REQUIRE(String::Format("Hello {}", "World") == "Hello World");
        REQUIRE(String::Format("Hello {} {}", 10, "Worlds") == "Hello 10 Worlds");
        REQUIRE(String::Format("Hello {} {}{}", 10, "Worlds", '!') == "Hello 10 Worlds!");
        REQUIRE(String::Format("Hello {} {}{} {}", 10, "Worlds", '!', String("String")) == 
            "Hello 10 Worlds! String");
    }

    SECTION("Convert To")
    {
        SECTION("Throw on invalid number")
        {
            String str = "zypqwer";
            bool didThrow = false;
            try {
                int i = str.To<int>();
            }
            catch (const RuntimeException &e)
            {
                didThrow = true;
            }
            
            REQUIRE(didThrow);
        }

        SECTION("Convert from hex string")
        {
            SECTION("Normal")
            {
                REQUIRE(String("FF").To<unsigned>(16) == 255u);
                REQUIRE(String("ff").To<unsigned>(16) == 255u);
                REQUIRE(String("fea").To<unsigned>(16) == 0xfea);
                REQUIRE(String("-fea").To<unsigned>(16) == -0xfea);
                REQUIRE(String("0123").To<unsigned>(8) == 0123);
            }


            SECTION("Prepending symbols")
            {
                REQUIRE(String("0xFF").To<unsigned>(16) == 255u);
                REQUIRE(String("#ff").To<unsigned>(16) == 255u);
                REQUIRE(String("0127").To<unsigned>(8) == 0127);
                REQUIRE(String("x-fea").To<unsigned>(16) == -0xfea);
            }

            SECTION("Postpending symbols")
            {
                REQUIRE(String("0xFFzwer").To<unsigned>(16) == 255u);
                REQUIRE(String("#ff#").To<unsigned>(16) == 255u);
                REQUIRE(String("0127&*").To<unsigned>(8) == 0127);
                REQUIRE(String("x-fea)(").To<unsigned>(16) == -0xfea);
            }
        }

        SECTION("Convert decimal")
        {
            REQUIRE(String("123.123").To<float>() == 123.123f);
            REQUIRE(String("-123.123").To<float>() == -123.123f);
            REQUIRE(String("0.123f").To<float>() == .123f);
            REQUIRE(String(".123f").To<float>() == .123f);
            REQUIRE(String("-.123f").To<float>() == -.123f);
            REQUIRE(String("0.123f").To<float>() == .123f);
        }
    }

    SECTION("Split")
    {
        SECTION("Typical use case")
        {
            String str("hello world lots of space-separated words\n"
                "with a line-break and also a carriage return\r"
                "and now this is the end");

            auto vec = str.Split();
            REQUIRE(vec.Size() == 20);
            REQUIRE(vec[0] == "hello");
            REQUIRE(vec[5] == "words");
            REQUIRE(vec[10] == "also");
            REQUIRE(vec[19] == "end");
        }

        SECTION("Space in the beginning")
        {
            String str("   \n\n\r there is space in the beginning.");
            auto vec = str.Split();
            REQUIRE(vec.Size() == 6);
            REQUIRE(vec[0] == "there");
            REQUIRE(vec[5] == "beginning.");
        }

        SECTION("Space in the beginning and end")
        {
            String str("   \n\n\r there is space in the beginning.    \n\n \r");
            auto vec = str.Split();
            REQUIRE(vec.Size() == 6);
            REQUIRE(vec[0] == "there");
            REQUIRE(vec[5] == "beginning.");
        }
    }

    SECTION("Insert")
    {
        SECTION("Insert in the middle")
        {
            String str = "hello"; String str2 = "world";

            SECTION("String overload")
            {
                REQUIRE(str.Insert(str2, 1) == "hworldello");
            }
            SECTION("StringView overload")
            {
                REQUIRE(str.Insert(StringView(str2), 1) == "hworldello");
            }
            SECTION("C-string overload")
            {
                REQUIRE(str.Insert(str2.Cstr(), 5, 1) == "hworldello");
            }
        }

        SECTION("Append at end")
        {
            String str = "hello"; String str2 = "world";

            SECTION("String overload")
            {
                REQUIRE(str.Insert(str2, str.Length()) == "helloworld");
            }
            SECTION("StringView overload")
            {
                REQUIRE(str.Insert(StringView(str2), str.Length()) == "helloworld");
            }
            SECTION("C-string overload")
            {
                REQUIRE(str.Insert(str2.Cstr(), str2.Length(), str.Length()) == "helloworld");
            }
        }

        SECTION("Insert at beginning")
        {
            String str1 = "hijklmn"; String str2 = "abcdefg";

            SECTION("String overload")
            {
                REQUIRE(str1.Insert(str2, 0) == "abcdefghijklmn");
            }
            
            SECTION("StringView overload")
            {
                REQUIRE(str1.Insert(StringView(str2), 0) == "abcdefghijklmn");
            }
            
            SECTION("C-string overload")
            {
                REQUIRE(str1.Insert(str2.Cstr(), str2.Length(), 0) == "abcdefghijklmn");
            }
        }

        SECTION("Insertion past index throws exception")
        {
            String str1 = "a"; String str2 = "b";
            bool didThrow = false;

            SECTION("String overload")
            {
                try {
                    str1.Insert(str2, 2);
                }
                catch (const OutOfRangeException &e)
                {
                    didThrow = true;
                }

                REQUIRE(didThrow);
            }

            SECTION("StringView overload")
            {
                try {
                    str1.Insert(StringView(str2), 2);
                }
                catch (const OutOfRangeException &e)
                {
                    didThrow = true;
                }

                REQUIRE(didThrow);
            }

            SECTION("C-String overload")
            {
                try {
                    str1.Insert(str2.Cstr(), 1, 2);
                }
                catch (const OutOfRangeException &e)
                {
                    didThrow = true;
                }

                REQUIRE(didThrow);
            }

        }

        SECTION("Insertion of nullptr on empty String does not affect String")
        {
            String str;

            str.Insert(nullptr, 0, 0);
            REQUIRE(str.Empty());
        }

        SECTION("Insertion of nullptr on String with size does not affect String")
        {
            String str("abc");

            str.Insert(nullptr, 0, 0);
            REQUIRE(str == "abc");
        }

        SECTION("Insertion of empty String does not affect String")
        {
            String str1;
            String str2;

            SECTION("String overload")
            {
                str1.Insert(str2, 0);
                REQUIRE(str1.Empty());
            }

            SECTION("StringView overload")
            {
                str1.Insert(StringView(str2), 0);
                REQUIRE(str1.Empty());
            }

            SECTION("C-string overload")
            {
                str1.Insert(str2.Cstr(), 0, 0);
                REQUIRE(str1.Empty());
            }
        }
    }

    SECTION("Move constructor")
    {
        SECTION("Typical case")
        {
            String str2("world");
            const char *origPtr = str2.Cstr();
            String str1 = std::move(str2);

            REQUIRE(str1 == "world");
            REQUIRE(str1.Cstr() == origPtr);
            REQUIRE(str2.Cstr() == nullptr);
        }

        SECTION("Empty strings, memory still moves")
        {  
            String str2;

            const char *origPtr = str2.Cstr();
            String str1 = std::move(str2);

            REQUIRE(str1.Cstr() == origPtr);
            REQUIRE(str2.Cstr() == nullptr);
        }
    }

    SECTION("Move assignment operator")
    {
        SECTION("Typical case")
        {
            String str1("hello");
            String str2("world");

            const char *origPtr = str2.Cstr();

            str1 = std::move(str2);

            REQUIRE(str1 == "world");
            REQUIRE(str1.Cstr() == origPtr);
            REQUIRE(str2.Cstr() == nullptr);
        }

        SECTION("Empty strings, memory still moves")
        {
            String str1;
            String str2;

            const char *origPtr = str2.Cstr();

            str1 = std::move(str2);
            REQUIRE(str1.Cstr() == origPtr);
            REQUIRE(str2.Cstr() == nullptr);
        }
    }
    
} 
