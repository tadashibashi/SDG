// Inline implementation
#include "FixedPool.h"
#include <Engine/Debug/Assert.h>
#include <Engine/Exceptions/Fwd.h>

#include <utility>

namespace std
{
    template<typename T>
    inline void swap(SDG::FixedPool<T> &a, SDG::FixedPool<T> &b) noexcept { a.Swap(b); }
}

namespace SDG
{
    template<typename T>
    FixedPool<T>::FixedPool(size_t size) :
        pool(size), ticket(0), nextFree(PoolNullIndex), aliveCount(0)
    {
        for (size_t i = 0; i < size; ++i)
        {
            Capsule &capsule = pool[i];

            capsule.next = (i < size - 1) ? i + 1 : PoolNullIndex;
        }

        nextFree = 0;
    }

    template<typename T>
    FixedPool<T>::FixedPool(FixedPool &&moved) : pool(std::move(moved.pool)), ticket(moved.ticket),
        nextFree(moved.nextFree), aliveCount(moved.aliveCount)
    {
        moved.Clear();
    }

    template<typename T>
    FixedPool<T> &FixedPool<T>::operator = (FixedPool<T> &&moved)
    {
        if (&moved == this)
            return *this;

        Clear();
        pool = std::move(moved.pool);
        ticket = moved.ticket;
        nextFree = moved.nextFree;
        aliveCount = moved.aliveCount;
        moved.Clear();

        return *this;
    }

    template<typename T>
    void FixedPool<T>::Clear()
    {
        pool.Clear();
        ticket = 0;
        nextFree = PoolNullIndex;
        aliveCount = 0;
    }

    template<typename T>
    PoolID FixedPool<T>::Checkout()
    {
        // Check if Pool must be expanded
        if (nextFree == PoolNullIndex)
        {
            ThrowRuntimeException("Cannot call Checkout on an empty FixedPool.");
        }

        size_t index = nextFree;

        // Set capsule values
        Capsule &capsule = pool[index];
        do {
            capsule.id = ticket++ * 13 + (uintptr_t)(void *)this * 17 + index * 23; // hash
        } while (capsule.id == PoolNullIndex); // just ensure we never hit a null value

        capsule.isAlive = true;

        // Progress free list
        nextFree = capsule.next;
        ++aliveCount;
        return { index, capsule.id };
    }


    template<typename T>
    bool FixedPool<T>::IDValid(const PoolID &id)
    {
        return IsValid(id, GetCapsule(id));
    }


    template<typename T>
    void FixedPool<T>::PutBackAll()
    {
        size_t index = 0;
        for (Capsule &capsule : pool)
        {
            if (capsule.isAlive)
            {
                capsule.id = PoolNullIndex;
                capsule.next = nextFree;
                nextFree = index;
                capsule.isAlive = false;
            }

            ++index;
        }

        aliveCount = 0;
    }


    template<typename T>
    void FixedPool<T>::PutBack(const PoolID &id)
    {
        SDG_Assert(id.index < pool.Size());

        Capsule &capsule = pool[id.index];
        if (capsule.id == id.id)
        {
            capsule.id = PoolNullIndex;
            capsule.next = nextFree;
            nextFree = id.index;
            capsule.isAlive = false;

            --aliveCount;
        }
    }


    template<typename T>
    Ref<T> FixedPool<T>::operator[](const PoolID &id)
    {
        Capsule &capsule = GetCapsule(id);
        return IsValid(id, capsule) ?
            Ref{ capsule.object } :
            Ref<T>{};
    }


    // ========== Helper functions ==========

    template<typename T>
    typename FixedPool<T>::Capsule &FixedPool<T>::GetCapsule(const PoolID &id)
    {
        SDG_Assert(id.index < pool.Size());
        return pool[id.index];
    }


    template<typename T>
    bool FixedPool<T>::IsValid(const PoolID &id, const Capsule &capsule)
    {
        return (capsule.id == id.id && capsule.isAlive);
    }

    template <typename T>
    FixedPool<T> &FixedPool<T>::Swap(FixedPool<T> &other)
    {
        std::swap(pool, other.pool);
        std::swap(ticket, other.ticket);
        std::swap(aliveCount, other.aliveCount);
        std::swap(nextFree, other.nextFree);
        return *this;
    }
}


