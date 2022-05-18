#pragma once
#include "PoolID.h"
#include "Private/PoolNullIndex.h"

#include <cstdlib>
#include <type_traits>
#include <vector>

#include "SDG/Debug/Assert.h"
#include "SDG/Exceptions/OutOfRangeException.h"
#include "SDG/Exceptions/InvalidArgumentException.h"
#include "SDG/Ref.h"

namespace SDG
{
    /// Slightly more efficient version of Pool since it does not expand. All data is
    /// contiguous, speeding up indexing and iteration times.
    template <typename T>
    class FixedPool
    {
        static_assert(std::is_default_constructible_v<T>,
                      "Pooled type must be default constructable");
    public:
        /// Creates a pool with a specified size, default: 256.
        /// Throws InvalidArgumentException if the size exceeds its max size.
        FixedPool(size_t size);

        /// Checks out a fresh Pool object ID.
        /// Pool::operator[] can be used to get a ref to the actual object.
        /// The PoolID retrieved from this function is used to index the Pool.
        [[nodiscard]]
        PoolID Checkout();

        /// Put back a Pool object that has previously been checked out.
        void PutBack(const PoolID &id);
        /// Put back every Pool object that has previously been checkout out.
        void PutBackAll();

        /// Checks whether an ID is currently valid.
        /// A valid ID represents a pool object that is currently checked out.
        /// E.g. calling PutBack on the id will invalidate it.
        [[nodiscard]]
        bool IDValid(const PoolID &id);

        /// Indexes the pool for a reference to the actual object.
        /// Will return the Ref if it's a valid ID, or a null reference if not.
        [[nodiscard]]
        Ref<T> operator[](const PoolID &id);

        /// The number of pool objects that are currently checked out.
        [[nodiscard]]
        size_t LiveCount()  const
        {
            return aliveCount;
        }

        /// Gets the current size of the pool
        [[nodiscard]]
        size_t Size() const { return pool.size(); }
        /// Gets the maximum potential pool size. This is calculated according to the
        /// C++ standard by certain system and library calculations. This size is not guaranteed,
        /// however, as the system may fail to allocate any time before it is reached.
        [[nodiscard]]
        size_t MaxSize() const;

    private:
        /// Holds freeList and pool object state information
        struct Capsule
        {
            Capsule() : id(PoolNullIndex), next(PoolNullIndex), isAlive(), object() {}
            size_t id;    // unique identifier
            size_t next;  // next free pool index
            bool isAlive; // state whether it is live outside or dormant in pool
            T object;     // the object
        };

        [[nodiscard]]
        bool IsValid(const PoolID &id, const Capsule &capsule);

        [[nodiscard]]
        Capsule &GetCapsule(const PoolID &id);

        /// pool storage
        std::vector<Capsule> pool;

        /// assigner of unique id #'s to pool objects
        size_t ticket;
        size_t aliveCount;
        size_t nextFree;
    };


    template<typename T>
    FixedPool<T>::FixedPool(size_t size) : pool(), ticket(0), nextFree(PoolNullIndex),
                                           aliveCount(0)
    {
        // Check for errors
        if (size > MaxSize())
        {
            throw InvalidArgumentException("Pool::Pool(size_t initSize)",
                                           "initSize", "initCap must be <= Pool<T>::MaxSize(): " +
                                                       std::to_string(MaxSize()) + ", but got " + std::to_string(size));
        }

        // Perform resize, and set pool capsule values
        pool.resize(size);

        for (size_t i = 0; i < size; ++i)
        {
            Capsule &capsule = pool[i];

            capsule.next = (i < size - 1) ? i + 1 : PoolNullIndex;
        }

        nextFree = 0;
    }

    template<typename T>
    PoolID FixedPool<T>::Checkout()
    {
        // Check if Pool must be expanded
        if (nextFree == PoolNullIndex)
        {
            throw RuntimeException("Cannot call Checkout on an empty FixedPool.");
        }

        size_t index = nextFree;

        // Set capsule values
        Capsule &capsule = pool[index];
        do {
            capsule.id = ticket++ * 13 + (uintptr_t)(void *)this * 17 + index * 23; // hash
        }
        while (capsule.id == PoolNullIndex); // just ensure we never hit a null value

        capsule.isAlive = true;

        // Progress free list
        nextFree = capsule.next;
        ++aliveCount;
        return {index, capsule.id};
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
    size_t FixedPool<T>::MaxSize() const
    {
        // -1 in case max_size == PoolNullIndex for some reason
        return pool.max_size()-1;
    }


    template<typename T>
    Ref<T> FixedPool<T>::operator[](const PoolID &id)
    {
        Capsule &capsule = GetCapsule(id);
        return IsValid(id, capsule) ?
               Ref{capsule.object} :
               Ref<T>{};
    }


    // ========== Helper functions ==========

    template<typename T>
    typename FixedPool<T>::Capsule &FixedPool<T>::GetCapsule(const PoolID &id)
    {
        SDG_Assert(id.index < pool.size());
        return pool[id.index];
    }


    template<typename T>
    bool FixedPool<T>::IsValid(const PoolID &id, const Capsule &capsule)
    {
        return (capsule.id == id.id && capsule.isAlive);
    }


}
