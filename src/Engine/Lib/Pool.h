#pragma once
#include "PoolID.h"
#include "Private/PoolNullIndex.h"

#include <Engine/Lib/ClassMacros.h>
#include <Engine/Lib/Ref.h>

#include <cstddef>
#include <type_traits>
#include <deque>

namespace SDG
{
    template <typename T>
    class Pool
    {
        static_assert(std::is_default_constructible_v<T>,
                "Pooled type must be default constructable");
        SDG_NOCOPY(Pool);
    public:
        /// Creates a pool with a specified size, default: 256.
        /// Throws InvalidArgumentException if the size exceeds its max size.
        Pool(size_t initSize = 256);
        Pool(Pool &&moved);

        ///Clearing overwrites any entities currently stored. 
        /// Please make sure to do any clean up the internal entities
        /// if there is anything that their destructors wouldn't automatically do.
        void Clear();

        /// Moving overwrites any entities currently stored. 
        /// Please make sure to do any clean up the internal entities
        /// if there is anything that their destructors wouldn't automatically do.
        Pool &operator = (Pool &&moved);

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
        auto operator[] (const PoolID &id) -> Ref<T>;
        [[nodiscard]]
        auto operator[] (const PoolID &id) const -> Ref<const T>;

        /// The number of pool objects that are currently checked out.
        [[nodiscard]]
        size_t LiveCount()  const { return aliveCount; }

        [[nodiscard]]
        size_t RemainingCount() const { return pool.size() - aliveCount; }

        /// Gets the current size of the pool
        [[nodiscard]]
        size_t Size() const { return pool.size(); }
        /// Gets the maximum potential pool size. This is calculated according to the
        /// C++ standard by certain system and library calculations. This size is not guaranteed,
        /// however, as the system may fail to allocate any time before it is reached.
        [[nodiscard]]
        size_t MaxSize() const;

        Pool &Swap(Pool &pool);

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

        void Expand(size_t size);

        /// pool storage
        std::deque<Capsule> pool;
        /// assigner of unique id #'s to pool objects
        size_t ticket;
        size_t aliveCount;
        size_t nextFree;
    };
}

#include "Pool.inl"
