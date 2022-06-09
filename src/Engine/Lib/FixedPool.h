#pragma once
#include "PoolID.h"
#include "Private/PoolNullIndex.h"

#include <Engine/Lib/Array.h>
#include <Engine/Lib/ClassMacros.h>
#include <Engine/Lib/Ref.h>

#include <cstddef>
#include <type_traits>


namespace SDG
{
    /// Slightly more efficient version of Pool since it does not expand. All data is
    /// contiguous, helping make indexing and iteration more efficient.
    template <typename T>
    class FixedPool
    {
        static_assert(std::is_default_constructible_v<T>,
                      "Pooled type must be default constructable");
        SDG_NOCOPY(FixedPool);
    public:
        /// Creates a pool with a specified size, default: 256.
        /// Throws InvalidArgumentException if the size exceeds its max size.
        FixedPool(size_t size);
        FixedPool(FixedPool &&moved);

        FixedPool &operator = (FixedPool &&moved);

        void Clear();

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

        [[nodiscard]]
        const Ref<T> operator[](const PoolID &id) const;

        /// The number of pool objects that are currently checked out.
        [[nodiscard]]
        size_t LiveCount()  const { return aliveCount; }

        /// Gets the current size of the pool
        [[nodiscard]]
        size_t Size() const { return pool.Size(); }

        [[nodiscard]]
        size_t RemainingCount() const { return pool.Size() - aliveCount; }

        FixedPool &Swap(FixedPool &other);

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
        Array<Capsule> pool;

        /// assigner of unique id #'s to pool objects
        size_t ticket;
        size_t aliveCount;
        size_t nextFree;
    };
}

#include "FixedPool.inl"
