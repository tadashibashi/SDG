#include "SDG_Tests.h"
#include <SDG/Lib/Algorithm.h>

TEST_CASE("Algorithms tests")
{
    SECTION("foreach: container")
    {
        std::vector<int> ints{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<int> result;
        foreach(ints, [&result](auto i) {
            result.emplace_back(i);
            });

        REQUIRE(result.size() == 10);
        REQUIRE(result[0] == 0);
        REQUIRE(result[5] == 5);
        REQUIRE(result[9] == 9);
    }

    SECTION("foreach: begin/end")
    {
        std::vector<int> ints{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<int> result;
        foreach(ints.begin(), ints.end(), [&result](auto i) {
            result.emplace_back(i);
            });

        REQUIRE(result.size() == 10);
        REQUIRE(result[0] == 0);
        REQUIRE(result[5] == 5);
        REQUIRE(result[9] == 9);
    }

    SECTION("foreach RAIterator<T>")
    {
        Array<int> ints{ 0, 1, 2, 3, 4, 5 };
        Array<int> result(6);

        foreach(ints.begin(), ints.end(), [&result](int value, int index) {
            result[index] = value;
            });

        REQUIRE(result[0] == 0);
        REQUIRE(result[3] == 3);
        REQUIRE(result[5] == 5);
    }
}
