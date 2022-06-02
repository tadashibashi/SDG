#include "SDG_Tests.h"
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/FileSys/File.h>
#include <SDG/FileSys/FileSys.h>
#include <SDL.h>

TEST_CASE("File tests", "[SDG::File]")
{
    FileSys fileSys("SDG Tests", "SDG"); // this object must always remain in scope
    SECTION("Setup")
    {
        Path::PushFileSys(fileSys);
    }

    SECTION("File reads and writes to internal buffer")
    {
        File file;
        size_t bytes = 0;

        // Write to file buffer
        bytes += file.Write(-10);
        bytes += file.Write('c');
        bytes += file.Write(123u);
        bytes += file.Write("abcdefg");

        REQUIRE(file.Size() == bytes);
        REQUIRE(file.Capacity() >= bytes);
        REQUIRE(file.Tell() == bytes);

        // Reset file buffer head
        file.Seek(0);
        REQUIRE(file.Tell() == 0);

        // Read from File buffer
        int i;
        char c;
        unsigned int u;
        String s;

        file.Read(i);
        REQUIRE(i == -10);
        file.Read(c);
        REQUIRE(c == 'c');
        file.Read(u);
        REQUIRE(u == 123u);
        file.Read(s, 7);
        REQUIRE(s == "abcdefg");
    }

    SECTION("Read/Write other overloads")
    {
        File file;
        file.Write("hello"); // c-string
        int i = 10;
        file.Write(&i, sizeof(int)); // raw ptr/bytes
        String str = "hello again";
        file.Write(str); // SDG::String
        REQUIRE(file.Tell() == file.Size());

        file.Seek(0);
        
        char buf[6];
        file.Read(buf, 5); // c-string
        buf[5] = '\0';

        REQUIRE(strcmp("hello", buf) == 0);

        int i2;
        file.Read(&i2, sizeof(int)); // raw ptr/bytes
        REQUIRE(i2 == i);

        String str2;
        file.Read(str2, str.Length()); // String
        REQUIRE(str2 == "hello again");

        REQUIRE(file.Tell() == file.Size());
    }

    SECTION("Read return value overload")
    {
        File file;
        file.Write(10);

        file.Seek(0);

        int i = file.Read<int>();
        REQUIRE(i == 10);
    }

    SECTION("File buffer expands when capacity is reached")
    {
        File file;
        size_t cap = file.Capacity();

        size_t bytes = 0;
        while (bytes <= cap) bytes += file.Write(10);

        REQUIRE(file.Capacity() > cap);
    }

    SECTION("Throws when seeking out of bounds")
    {
        File file;
        bool didThrow = false;
        try {
            file.Seek(1);
        }
        catch (const OutOfRangeException &e)
        {
            didThrow = true;
        }
        REQUIRE(didThrow);
    }

    SECTION("Throws when reading out of bounds")
    {
        File file;
        bool didThrow = false;
        int i = 10;
        try {
            i = file.Read<int>();
        }
        catch (const OutOfRangeException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
        REQUIRE(i == 10);
    }

    SECTION("File read and write to and from system file")
    {
        File file;
        file.Write(10);
        file.Write('c');
        file.Write("hello");

        file.SaveAs(BasePath("file.bin"));
        
        file.Open(BasePath("file.bin"));
        REQUIRE(file.IsOpen());
        REQUIRE(file.Filepath() == BasePath("file.bin"));
        REQUIRE(file.Tell() == 0); // head resets on load

        REQUIRE(file.Read<int>() == 10);
        REQUIRE(file.Read<char>() == 'c');
        char buf[6];
        file.Read(buf, 5);
        buf[5] = '\0';
        REQUIRE(strcmp(buf, "hello") == 0);
    }

    SECTION("File constructor with Path param opens file")
    {
        File file;
        file.Write(5);
        file.Write('z');

        file.SaveAs(BasePath("file.bin"));
    }

    SECTION("Breakdown")
    {
        Path::PopFileSys();
    }
}