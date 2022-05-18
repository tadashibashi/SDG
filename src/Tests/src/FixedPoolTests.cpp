#include "SDG_Tests.h"
#include "SDG/Debug/Logging.h"
#include <SDG/Templates/FixedPool.h>

TEST_CASE("FixedFixedPool tests", "[FixedPool]")
{
    SECTION("Constructor sets pool size correctly")
    {
        FixedPool<int> pool(128);

        REQUIRE(pool.Size() == 128);
    }

    SECTION("Constructor sets pool size")
    {
        FixedPool<int> pool(512);

        REQUIRE(pool.Size() == 512);
    }

    SECTION("FixedPool throws RuntimeException upon full checkout")
    {
        FixedPool<int> pool(16);
        std::vector<PoolID> ids;

        for (int i = 0; i < 16; ++i)
            ids.emplace_back(pool.Checkout());

        bool didThrow;
        try {
            ids.emplace_back(pool.Checkout());
            didThrow = false;
        }
        catch(const RuntimeException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }

    SECTION("CheckOut")
    {
        FixedPool<int> pool(1);
        PoolID id = pool.Checkout();
        REQUIRE(pool.LiveCount() == 1);
        REQUIRE(pool.IDValid(id));
    }

    SECTION("PutBack")
    {
        FixedPool<int> pool(1);
        PoolID id = pool.Checkout();
        REQUIRE(pool.IDValid(id));
        REQUIRE(pool.LiveCount() == 1);

        pool.PutBack(id);
        REQUIRE(!pool.IDValid(id));
        REQUIRE(pool.LiveCount() == 0);
    }

    SECTION("FixedPool put back all")
    {
        FixedPool<int> pool(17);
        std::vector<PoolID> ids;

        bool allAlive = true;
        for (int i = 0; i < 17; ++i)
        {
            PoolID &id = ids.emplace_back(pool.Checkout());
            if (!pool.IDValid(id))
            {
                allAlive = false;
                break;
            }
        }
        REQUIRE(pool.LiveCount() == 17);
        REQUIRE(allAlive);

        pool.PutBackAll();
        bool allDormant = true;
        for (int i = 0; i < 17; ++i)
        {
            if (pool.IDValid(ids[i]))
            {
                allDormant = false;
                break;
            }
        }
        REQUIRE(pool.LiveCount() == 0);
        REQUIRE(allDormant);
    }

    SECTION("operator[](const PoolID &) returns null reference when invalid")
    {
        FixedPool<int> pool(1);
        PoolID id = pool.Checkout();
        REQUIRE(pool.IDValid(id));
        REQUIRE(pool.LiveCount() == 1);

        pool.PutBack(id);
        REQUIRE(!pool.IDValid(id));
        REQUIRE(!pool[id]);
        REQUIRE(pool.LiveCount() == 0);
    }

    SECTION("FixedPool successfully empties and replenishes multiple times")
    {
        // Most use cases probably use less than one million
        size_t size = 1000000;
        FixedPool<int> pool(size);
        std::vector<PoolID> ids;

        ids.reserve(size);

        for (int i = 0; i < size; ++i)
            ids.emplace_back(pool.Checkout());
        REQUIRE(pool.LiveCount() == size);
        for (int i = 0; i < size; ++i)
            pool.PutBack(ids[i]);
        ids.clear();
        REQUIRE(pool.LiveCount() == 0);
        for (int i = 0; i < size; ++i)
            ids.emplace_back(pool.Checkout());
        REQUIRE(pool.LiveCount() == size);
        for (int i = 0; i < size; ++i)
            pool.PutBack(ids[i]);
        REQUIRE(pool.LiveCount() == 0);

        REQUIRE(pool.Size() == size);
    }

    SECTION("FixedPool set values are as expected")
    {
        FixedPool<int> pool(128);
        std::vector<PoolID> ids;

        for (int i = 0; i < 128; ++i)
        {
            PoolID id = pool.Checkout();
            *pool[id] = i;
            ids.emplace_back(id);
        }

        bool allEqual = true;
        for (int i = 0; i < 128; ++i)
        {
            if (*pool[ids[i]] != i)
            {
                allEqual = false;
                break;
            }
        }

        REQUIRE(allEqual);
    }

    SECTION("Max size is less than Null")
    {
        FixedPool<int> intPool(16);
        REQUIRE(intPool.MaxSize() < PoolNullIndex);

        FixedPool<char> charPool(16);
        REQUIRE(charPool.MaxSize() < PoolNullIndex);
    }

    SECTION("Throws invalid argument when attempting to initialize too big")
    {
        bool didThrow;
        try {
            FixedPool<char> charPool(SIZE_MAX);
            didThrow = false;
        }
        catch(const InvalidArgumentException &e)
        {
            didThrow = true;
        }

        REQUIRE(didThrow);
    }
}