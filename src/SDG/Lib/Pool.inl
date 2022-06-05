#include "Pool.h"
#include <SDG/Debug/Assert.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Exceptions/InvalidArgumentException.h>

namespace SDG
{
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
    Ref<T> Pool<T>::operator[](const PoolID &id)
    {
        Capsule &capsule = GetCapsule(id);

        return IsValid(id, capsule) ?
            Ref{ capsule.object } :
            Ref<T>{};
    }


    // ========== Helper functions ==========


    template<typename T>
    void Pool<T>::Expand(size_t size)
    {
        size_t current = pool.size();

        // Check for errors
        if (size > MaxSize())
        {
            throw InvalidArgumentException("Pool::Pool(size_t initSize)",
                "initSize", "initCap must be <= Pool<T>::MaxSize(): " +
                std::to_string(MaxSize()) + ", but got " + std::to_string(size));
        }
        if (size <= current)
            throw OutOfRangeException(size, "Pool most likely has reached maximum size.");

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
}