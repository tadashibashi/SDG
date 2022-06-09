#include "Pool.h"
#include <Engine/Debug/Assert.h>
#include <Engine/Exceptions/Fwd.h>

#include <utility>

namespace std
{
    template<typename T>
    inline void swap(SDG::Pool<T> &a, SDG::Pool<T> &b) noexcept { a.Swap(b); }
}

namespace SDG
{
    template<typename T>
    Pool<T>::Pool(Pool<T> &&moved) : pool(std::move(moved.pool)), ticket(moved.ticket), 
        aliveCount(moved.aliveCount), nextFree(moved.nextFree)
    {
        moved.Clear();
    }

    template<typename T>
    void Pool<T>::Clear()
    {
        pool.clear();
        nextFree = PoolNullIndex;
        ticket = 0;
        aliveCount = 0;
    }

    template<typename T>
    Pool<T> &Pool<T>::operator = (Pool &&moved)
    {
        if (&moved == this)
            return *this;

        Clear();
        pool = std::move(moved.pool);
        nextFree = moved.nextFree;
        ticket = moved.ticket;
        aliveCount = moved.aliveCount;
        moved.Clear();

        return *this;
    }

    template<typename T>
    Pool<T>::Pool(size_t initSize) : pool(), ticket(0), nextFree(PoolNullIndex),
        aliveCount(0)
    {
        Expand(initSize);
    }

    template<typename T>
    PoolID Pool<T>::Checkout()
    {
        // Check if Pool must be expanded
        if (nextFree == PoolNullIndex)
        {
            // Upon Pool expansion, nextFree will be udpated.
            // Will throw if pool's MaxSize has been exceeded.
            Expand(std::min(pool.size() * 2 + 1, MaxSize()));
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
    bool Pool<T>::IDValid(const PoolID &id)
    {
        return IsValid(id, GetCapsule(id));
    }


    template<typename T>
    void Pool<T>::PutBackAll()
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
    void Pool<T>::PutBack(const PoolID &id)
    {
        SDG_Assert(id.index < pool.size());

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
    size_t Pool<T>::MaxSize() const
    {
        // -1 in case max_size == PoolNullIndex for some reason
        return pool.max_size() - 1;
    }


    template<typename T>
    Ref<T> Pool<T>::operator[] (const PoolID &id)
    {
        Capsule &capsule = GetCapsule(id);

        return IsValid(id, capsule) ?
            &capsule.object :
            nullptr;
    }

    template<typename T>
    CRef<T> Pool<T>::operator[](const PoolID &id) const
    {
        Capsule &capsule = GetCapsule(id);

        return IsValid(id, capsule) ?
            &capsule.object:
            nullptr;
    }


    // ========== Helper functions ==========


    template<typename T>
    void Pool<T>::Expand(size_t size)
    {
        size_t current = pool.size();

        // Check for errors
        if (size > MaxSize())
        {
            ThrowInvalidArgumentException("Pool::Pool(size_t initSize)",
                "initSize", "initCap must be <= Pool<T>::MaxSize(): " +
                std::to_string(MaxSize()) + ", but got " + std::to_string(size));
        }
        if (size <= current)
            ThrowOutOfRangeException(size, "Pool most likely has reached maximum size.");

        // Perform resize, and set pool capsule values
        pool.resize(size);

        for (size_t i = current; i < size; ++i)
        {
            Capsule &capsule = pool[i];

            capsule.next = (i == current) ? nextFree : i - 1;
        }
        nextFree = size - 1;
    }


    template<typename T>
    typename Pool<T>::Capsule &Pool<T>::GetCapsule(const PoolID &id)
    {
        SDG_Assert(id.index < pool.size());
        return pool[id.index];
    }


    template<typename T>
    bool Pool<T>::IsValid(const PoolID &id, const Pool::Capsule &capsule)
    {
        return (capsule.id == id.id && capsule.isAlive);
    }

    template<typename T>
    Pool<T> &Pool<T>::Swap(Pool &other)
    {
        std::swap(pool, other.pool);
        std::swap(aliveCount, other.aliveCount);
        std::swap(ticket, other.ticket);
        std::swap(nextFree, other.nextFree);
        return *this;
    }
}
