//
// Created by Aaron Ishibashi on 5/13/22.
//
#pragma once
#include <cstdint>
#include <deque>

#include <SDG/Ref.h>
#include <SDG/Debug/Assert.h>

namespace SDG
{
    struct PoolID
    {
        PoolID() : index(UINT32_MAX), next(UINT32_MAX),
                   innerID(UINT32_MAX), pool(), isAlive()
        { }
        PoolID(uint32_t index, uint32_t next, uint32_t innerID, void *pool)
        : index(index), next(next), innerID(innerID), pool(pool), isAlive()
        { }

        uint32_t index;
        uint32_t next;
        uint32_t innerID;  //
        void *   pool;     // pool identifier
        bool     isAlive;
    };

    class Poolable
    {
    public:
        PoolID id;
    };

    template <typename T>
    class Pool
    {
        static_assert(std::is_base_of_v<Poolable, T>, "Pooled type must derive from Poolable");
    public:
        Pool(uint32_t initCap = 256) : pool(initCap)
        {
            for (int i = 0; i < initCap; ++i)
            {
                pool.emplace_back()
            }
        }

        [[nodiscard]] Ref<T> Checkout()
        {

        }

        void PutBack(const PoolID &id)
        {
            SDG_Assert(id.pool == this);

        }

        void PutBackAll()
        {
            for (T &t : pool)
            {

            }
        }

        Ref<T> Get(const PoolID &id)
        {
            SDG_Assert(id.pool.Get() == this);

        }

        size_t Size() const { return pool.size(); }
        size_t MaxSize() const { return pool.max_size(); }

    private:
        void Expand(uint32_t size)
        {

        }

        std::deque<T> pool;
    };
}
