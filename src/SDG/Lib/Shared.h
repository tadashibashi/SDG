#pragma once

namespace SDG
{
    template<typename T>
    class Shared
    {
    public:
        // Creates a null shared pointer
        Shared() : ptr(), count() { }

        // Must be called with a dynamically allocated object
        template <typename... Args>
        explicit Shared(Args &&...args);
        Shared(const Shared &other);
        ~Shared();
        Shared &operator=(const Shared &other);
    public:
        /// Gets the raw pointer
        [[nodiscard]] T *Get() const { return ptr; }

        /// Gets the number of live references of Shared ptr
        [[nodiscard]] size_t Count() const { return (count) ? *count : 0; }

        /// Resets this pointer, setting it to null. If it was the last live
        /// reference, delete will be called on it.
        void Reset() { Destroy(); ptr = nullptr; count = nullptr; }

        /// Member access. Throws a NullReferenceException if null.
        [[nodiscard]] T *operator->() const;
        /// Gets raw reference. Throws a NullReferenceException if null.
        [[nodiscard]] T &operator *() const;

        /// Compare two shared ptr
        [[nodiscard]] bool operator ==(const Shared &other) const;
        [[nodiscard]] bool operator !=(const Shared &other) const;

        /// Resolves to bool, checking if reference is null
        [[nodiscard]] explicit operator bool() const;
    private:
        /// Removes reference count, calling destructor on ptr when it reaches zero
        void Destroy();
        T *ptr;
        size_t *count;
    };
}

#include "Shared.inl"
