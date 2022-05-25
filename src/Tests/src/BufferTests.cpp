#include "SDG_Tests.h"
#include <SDG/Buffer.h>
#include <SDG/Exceptions/OutOfRangeException.h>

TEST_CASE("Buffer tests", "[Buffer]")
{
    SECTION("Constructor")
    {
        SECTION("Default")
        {
            Buffer buf;
            REQUIRE(buf.Size() == 0);
            REQUIRE(buf.Empty());
            REQUIRE(buf.Capacity() == buf.DefaultInitCap);
            REQUIRE(buf.Tell() == 0);
            REQUIRE(buf.Endianness() == Endian::Little);
        }

        SECTION("Init cap")
        {
            Buffer buf(48, Endian::Big);
            REQUIRE(buf.Capacity() == 48);
            REQUIRE(buf.Endianness() == Endian::Big);
        }

    }

    SECTION("Seek/Tell")
    {
        Buffer buf;
        buf.Write(10);
        buf.Write(20);
        buf.Seek(0); // resets to 0

        SECTION("Throws OutOfRangeException when seek below")
        {
            bool didThrow;
            try {
                buf.Seek(-1);
                didThrow = false;
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Throws OutOfRangeException when seek above")
        {
            bool didThrow;
            try {
                buf.Seek(1, Position::End);
                didThrow = false;
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Tell reads zero when no reads have been made yet")
        {
            REQUIRE(buf.Tell() == 0);
        }

        SECTION("Tell reads the seek position")
        {
            buf.Seek(sizeof(int));
            REQUIRE(buf.Tell() == sizeof(int));
            buf.Seek(sizeof(int) * 2);
            REQUIRE(buf.Tell() == sizeof(int) * 2);
            buf.Seek(0);
            REQUIRE(buf.Tell() == 0);
        }

        SECTION("Seek from end")
        {
            buf.Seek(-(int)sizeof(int), Position::End);
            REQUIRE(buf.Tell() == sizeof(int));
            buf.Seek(-(int)sizeof(int) * 2, Position::End);
            REQUIRE(buf.Tell() == 0);
        }

        SECTION("Seek relatively")
        {
            buf.Seek(2, Position::Relative);
            REQUIRE(buf.Tell() == 2);
            buf.Seek(2, Position::Relative);
            REQUIRE(buf.Tell() == 4);
            buf.Seek(4, Position::Relative);
            REQUIRE(buf.Tell() == 8);
            buf.Seek(-8, Position::Relative);
            REQUIRE(buf.Tell() == 0);
        }
    }

    SECTION("Read/Write")
    {
        Buffer buf;

        SECTION("Read/Write template")
        {
            buf.Write(10);
            buf.Write(20.512f);
            buf.Seek(0);
            int i; float f;
            buf.Read(i);
            REQUIRE(i == 10);
            buf.Read(f);
            REQUIRE(f == 20.512f);

            bool didThrow;
            try {
                buf.Read(i);
                didThrow = false;
            }
            catch (const OutOfRangeException &e)
            {
                didThrow = true;
            }
            REQUIRE(didThrow);
        }

        SECTION("Read/Write c-string")
        {
            buf.Write("hello world");
            buf.Seek(0);

            char str[12];
            buf.Read(str, 11);
            str[11] = 0;
            REQUIRE(strcmp(str, "hello world") == 0);
        }

        SECTION("Read/Write c-string 0 chars: unmutated data")
        {
            buf.Write("hello");
            buf.Seek(0);
            char str[2]{ 'a', '\0'};
            buf.Read(str, 0);
            REQUIRE(str[0] == 'a');
            REQUIRE(str[1] == '\0');
        }

        SECTION("Read/Write SDG::String")
        {
            buf.Write(String("Hello World"));
            buf.Seek(0);
            String str;
            buf.Read(str, 5);
            REQUIRE(str == "Hello");

            buf.Read(str, 6);
            REQUIRE(str == " World");
        }

        SECTION("Read/write buffer")
        {
            int i = 10;
            buf.Write(&i, sizeof(int));
            buf.Seek(0);
            int k;
            buf.Read(&k, sizeof(int));
            REQUIRE(k == 10);
        }
    }
}
