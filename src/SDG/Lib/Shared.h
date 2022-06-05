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
        explicit Shared(T *newPtr) : ptr(newPtr), count(new size_t(1)) { }
        Shared(const Shared &other);
        ~Shared() { Destroy(); }
        Shared &operator=(const Shared &other);
    public:
        /// Gets the raw pointer
        [[nodiscard]] T *Get() const { return ptr; }

        /// Gets the number of live references of Shared ptr
        [[nodiscard]] size_t Count() const { return (count) ? *count : 0; }

        /// Resets this pointer, setting it to null. If it was the last live
        /// reference, delete will be called on it.
        [[nodiscard]] void Reset() { Destroy(); ptr = nullptr; count = nullptr; }

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
        void Destroy();
        T *ptr;
        size_t *count;
    };
}

#include "Shared.inl"
