#include "SDG_Tests.h"
#include <SDG/Exceptions.hpp>

TEST_CASE("NullReferenceException tests", "[NullReferenceException]")
{
    SECTION("Default constructor message")
    {
        NullReferenceException e;
        REQUIRE(strcmp(e.what(), "NullReferenceException") == 0);
    }

    SECTION("string constructor message: empty string")
    {
        NullReferenceException e("");
        REQUIRE(strcmp(e.what(), "NullReferenceException") == 0);
    }

    SECTION("Can be thrown and received by class name")
    {
        bool wasCaught = false;
        try {
            throw NullReferenceException("App");
        }
        catch (const NullReferenceException &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by Exception base class")
    {
        bool wasCaught = false;
        try {
            throw NullReferenceException("App");
        }
        catch (const Exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by std::exception base class")
    {
        bool wasCaught = false;
        try {
            throw NullReferenceException("App");
        }
        catch (const std::exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }
}

TEST_CASE("InvalidArgumentException tests", "[InvalidArgumentException]")
{
    SECTION("Constructor without info param")
    {
        InvalidArgumentException e("main", "argc");
        REQUIRE(strcmp(e.what(), "Invalid argument passed to main. Arg name: argc") == 0);
    }

    SECTION("Constructor with empty info param")
    {
        InvalidArgumentException e("main", "argc", std::string());
        REQUIRE(strcmp(e.what(), "Invalid argument passed to main. Arg name: argc") == 0);
    }

    SECTION("Constructor with info param")
    {
        InvalidArgumentException e("main", "argc", "there must be 3 arguments passed to main");
        REQUIRE(strcmp(e.what(), "Invalid argument passed to main. Arg name: argc:"
                                 " there must be 3 arguments passed to main") == 0);
    }

    SECTION("Can be thrown and received by class name")
    {
        bool wasCaught = false;
        try {
            throw InvalidArgumentException("main", "arg");
        }
        catch (const InvalidArgumentException &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by Exception base class")
    {
        bool wasCaught = false;
        try {
            throw InvalidArgumentException("main", "arg");
        }
        catch (const Exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by std::exception base class")
    {
        bool wasCaught = false;
        try {
            throw InvalidArgumentException("main", "arg");
        }
        catch (const std::exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }
}

TEST_CASE("AssertionException tests", "[AssertionException]")
{
    SECTION("Constructor without info param")
    {
        AssertionException e("argc == 10", "main.cpp", 3, "main");
        REQUIRE(strcmp(e.what(), "main.cpp:3: main: \"argc == 10\" assertion failed!") == 0);
    }

    SECTION("Can be thrown and received by class name")
    {
        bool wasCaught = false;
        try {
            throw AssertionException("argc == 10", "main.cpp", 3, "main");
        }
        catch (const AssertionException &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by Exception base class")
    {
        bool wasCaught = false;
        try {
            throw AssertionException("argc == 10", "main.cpp", 3, "main");
        }
        catch (const Exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by std::exception base class")
    {
        bool wasCaught = false;
        try {
            throw AssertionException("argc == 10", "main.cpp", 3, "main");
        }
        catch (const std::exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }
}

TEST_CASE("XMLReaderException tests", "[XMLReaderException]")
{
    SECTION("Constructor")
    {
        XMLReaderException e("parsing file string", 15);
        REQUIRE(strcmp(e.what(), "XMLReaderException occured while parsing file string: XML_ERROR_PARSING") == 0);
    }

    SECTION("Can be thrown and received by class name")
    {
        bool wasCaught = false;
        try {
            throw XMLReaderException ("parsing file string", 15);
        }
        catch (const XMLReaderException &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by Exception base class")
    {
        bool wasCaught = false;
        try {
            throw XMLReaderException ("parsing file string", 15);
        }
        catch (const Exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by std::exception base class")
    {
        bool wasCaught = false;
        try {
            throw XMLReaderException ("parsing file string", 15);
        }
        catch (const std::exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }
}

TEST_CASE("OutOfRangeException tests", "[OutOfRangeException]")
{
    SECTION("Constructor")
    {
        OutOfRangeException e(10, "array out of bounds, max value is 4");
        REQUIRE(strcmp(e.what(), "Out-of-range error with value 10: "
                                 "array out of bounds, max value is 4") == 0);
    }

    SECTION("Can be thrown and received by class name")
    {
        bool wasCaught = false;
        try
        {
            throw OutOfRangeException(10, "array out of bounds, max value is 4");
        }
        catch (const OutOfRangeException &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by Exception base class")
    {
        bool wasCaught = false;
        try
        {
            throw OutOfRangeException(10, "array out of bounds, max value is 4");
        }
        catch (const Exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }

    SECTION("Can be thrown and received by std::exception base class")
    {
        bool wasCaught = false;
        try
        {
            throw OutOfRangeException(10, "array out of bounds, max value is 4");
        }
        catch (const std::exception &e)
        {
            wasCaught = true;
        }

        REQUIRE(wasCaught);
    }
}
