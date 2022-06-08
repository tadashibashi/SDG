#include "SDG_Tests.h"
#include "SDG/Debug/Log.h"
#include <SDG/Lib/FixedPool.h>

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

    SECTION("FixedPools swap successfully")
    {
        FixedPool<int> p1(16), p2(32);
        std::vector<PoolID> p1ids, p2ids;

        for (int i = 0; i < 16; ++i)
        {
            *p1[p1ids.emplace_back(p1.Checkout())] = i;
        }

        for (int i = 31; i >= 0; --i)
        {
            *p2[p2ids.emplace_back(p2.Checkout())] = i;
        }

        p1.Swap(p2);
        REQUIRE(p1.Size() == 32);
        REQUIRE(p2.Size() == 16);

        bool allCorrect = true;
        for (int i = 0; i < 16; ++i)
        {
            if (*p2[p1ids[i]] != i)
            {
                allCorrect = false;
                break;
            }
        }
        REQUIRE(allCorrect);

        allCorrect = true;
        for (int i = 31; i >= 0; --i)
        {
            if (*p1[p2ids[i]] != 31 - i)
            {
                allCorrect = false;
                break;
            }
        }
        REQUIRE(allCorrect);
        
    }

    SECTION("Pools move assigns successfully")
    {
        FixedPool<int> p1(16), p2(32);
        p1 = std::move(p2);

        REQUIRE(p1.Size() == 32);
    }

    SECTION("Pools move assigns successfully")
    {
        FixedPool<int> p2(32);
        FixedPool<int> p1 = std::move(p2);

        REQUIRE(p1.Size() == 32);
    }
}
