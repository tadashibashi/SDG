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

    template <typename T>
    class Pool
    {
    public:
        struct ID
        {
            ID() : index(UINT32_MAX), next(UINT32_MAX),
                innerID(UINT32_MAX), pool(), isAlive()
            { }
            ID(uint32_t index, uint32_t next, uint32_t innerID, Ref<Pool<T>> pool)
                : index(index), next(next), innerID(innerID), pool(pool), isAlive()
            { }

            uint32_t index;
            uint32_t next;
            uint32_t innerID;
            Ref<Pool<T>> pool;
            bool isAlive;
        };

        Pool(uint32_t initCap = 256) : pool(initCap)
        {

        }

        [[nodiscard]] Ref<T> Checkout()
        {

        }

        void PutBack(const ID &id)
        {
            SDG_Assert(id.pool.Get() == this);

        }

        Ref<T> Get(const ID &id)
        {
            SDG_Assert(id.pool.Get() == this);

        }

    private:
        void Expand(uint32_t size)
        {

        }

        std::deque<T> pool;
    };
}
