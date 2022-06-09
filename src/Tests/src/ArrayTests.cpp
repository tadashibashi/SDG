#include "SDG_Tests.h"
#include <Engine/Lib/Array.h>
#include <string>

struct ArrayTestStruct
{
    int i;
    float f;
    std::vector<std::string> strs;
};

TEST_CASE("Array tests", "[Array]")
{
    SECTION("Size constructor")
    {
        Array<ArrayTestStruct> arr(10);
        REQUIRE(arr.Size() == 10);
    }

    SECTION("Initializer list constructor")
    {
        Array<int> arr({ 10, 20, 30, 40, 50, 60 });
        REQUIRE(arr.Size() == 6);
        REQUIRE(arr[0] == 10);
        REQUIRE(arr[1] == 20);
        REQUIRE(arr[2] == 30);
        REQUIRE(arr[3] == 40);
        REQUIRE(arr[4] == 50);
        REQUIRE(arr[5] == 60);
    }

    SECTION("Copy constructor")
    {
        Array<int> arr{ 10, 20, 30, 40, 50, 60 };
        Array<int> copied = arr;

        REQUIRE(&arr[0] != &copied[0]);
        REQUIRE(copied[0] == 10);
        REQUIRE(copied[1] == 20);
        REQUIRE(copied[2] == 30);
        REQUIRE(copied[3] == 40);
        REQUIRE(copied[4] == 50);
        REQUIRE(copied[5] == 60);
    }

    SECTION("begin and end")
    {
        Array<int> arr{ 10, 20, 30, 40, 50, 60 };
        REQUIRE(&arr.begin() == &arr[0]);
        REQUIRE(&arr.end() == &arr[0] + arr.Size());
    }

    SECTION("cbegin and cend")
    {
        Array<int> arr{ 10, 20, 30, 40, 50, 60 };
        REQUIRE(&arr.cbegin() == &arr[0]);
        REQUIRE(&arr.cend() == &arr[0] + arr.Size());
    }

    SECTION("iterator constructor")
    {
        std::string str = "abcdefg";
        Array<char> arr(str.begin(), str.end());
        REQUIRE(arr.Size() == str.length());
        REQUIRE(&arr[0] != &str[0]); // data was copied
        REQUIRE(arr[0] == str[0]);
        REQUIRE(arr[1] == str[1]);
        REQUIRE(arr[2] == str[2]);
        REQUIRE(arr[3] == str[3]);
        REQUIRE(arr[4] == str[4]);
        REQUIRE(arr[5] == str[5]);
        REQUIRE(arr[6] == str[6]);
    }

    SECTION("At throws when out of range")
    {
        Array<char> arr{ 'a', 'b', 'c' };
        bool didThrow = false;
        try {
            char c = arr.At(3);
        }
        catch (const OutOfRangeException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }

    SECTION("At reads the same as indexer")
    {
        Array<char> arr{ 'a', 'b', 'c' };
        REQUIRE(&arr[0] == &arr.At(0));
        REQUIRE(arr[0] == arr.At(0));
        REQUIRE(&arr[1] == &arr.At(1));
        REQUIRE(arr[1] == arr.At(1));
        REQUIRE(&arr[2] == &arr.At(2));
        REQUIRE(arr[2] == arr.At(2));
    }

    SECTION("Set values through indexers")
    {
        Array<char> arr(3);
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 2;
        REQUIRE(arr[0] == 0);
        REQUIRE(arr[1] == 1);
        REQUIRE(arr[2] == 2);
    }

    SECTION("Set values via At")
    {
        Array<char> arr(3);
        arr.At(0) = 0;
        arr.At(1) = 1;
        arr.At(2) = 2;
        REQUIRE(arr[0] == 0);
        REQUIRE(arr[1] == 1);
        REQUIRE(arr[2] == 2);
    }

    SECTION("Empty")
    {
        Array<char> arr(0);
        REQUIRE(arr.Empty());
        Array<char> arr2{'a', 'b', 'c'};
        REQUIRE(!arr2.Empty());
    }

    SECTION("Data")
    {
        Array<char> arr{ '1', '2', '3' };
        REQUIRE(*arr.Data() == arr[0]);
        REQUIRE(arr.Data() == &arr.begin());
        REQUIRE(arr.Data() == &arr.cbegin());
    }

    SECTION("Swap")
    {
        SECTION("Swap with data")
        {
            Array<int> a1 {0, 1, 2, 3, 4};
            Array<int> a2{ 4, 3, 2, 1, 0, -1, -2, -3, -4 };
            size_t a1Size = a1.Size();
            size_t a2Size = a2.Size();
            const int *a1Data = a1.Data();
            const int *a2Data = a2.Data();

            a1.Swap(a2);

            REQUIRE(a1.Size() == a2Size);
            REQUIRE(a2.Size() == a1Size);
            REQUIRE(a1.Data() == a2Data);
            REQUIRE(a2.Data() == a1Data);
        }

        SECTION("Swap without data still swaps memory addresses")
        {
            Array<int> a1;
            Array<int> a2;
            const int *a1Data = a1.Data();
            const int *a2Data = a2.Data();

            a1.Swap(a2);

            REQUIRE(a1.Data() == a2Data);
            REQUIRE(a2.Data() == a1Data);
        }
    }

    SECTION("Move assignment")
    {
        Array<int> a2{ 0, 1, 2, 3, 4 };
        size_t a2Size = a2.Size();
        const int *a2Data = a2.Data();

        Array<int> a1;

        a1 = std::move(a2);

        REQUIRE(a1.Size() == a2Size);
        REQUIRE(a1.Data() == a2Data);
        REQUIRE(a1[0] == 0);
        REQUIRE(a1[2] == 2);
        REQUIRE(a1[4] == 4);
    }

    SECTION("Move constructor")
    {
        Array<int> a2{ 0, 1, 2, 3, 4 };
        size_t a2Size = a2.Size();
        const int *a2Data = a2.Data();

        Array<int> a1 = std::move(a2);

        REQUIRE(a1.Size() == a2Size);
        REQUIRE(a1.Data() == a2Data);
        REQUIRE(a1[0] == 0);
        REQUIRE(a1[2] == 2);
        REQUIRE(a1[4] == 4);
    }

    SECTION("Move assignment: empty")
    {
        Array<int> a2;
        const int *a2Data = a2.Data();

        Array<int> a1;

        a1 = std::move(a2);

        REQUIRE(a1.Data() == a2Data);
    }

    SECTION("Move constructor: empty")
    {
        Array<int> a2;
        const int *a2Data = a2.Data();

        Array<int> a1 = std::move(a2);

        REQUIRE(a1.Data() == a2Data);
    }
}
