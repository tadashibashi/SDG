#pragma once

namespace SDG
{
    template<typename T>
    class Shared
    {
    public:
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
        [[nodiscard]] const T *operator->() const;
        [[nodiscard]] T *operator->();
        /// Gets raw reference. Throws a NullReferenceException if null.
        [[nodiscard]] const T &operator *() const;
        [[nodiscard]] T &operator *();

        /// Compare two shared ptr
        [[nodiscard]] bool operator ==(const Shared &other) const;
        [[nodiscard]] bool operator !=(const Shared &other) const;

        /// Resolves to bool, checking if reference is null
        [[nodiscard]] explicit operator bool() const;
    private:
        /// Removes reference instances, calling destructor on ptr when it reaches zero
        void Destroy();
        T *ptr;
        size_t *count;
    };
}

#include "Shared.inl"
