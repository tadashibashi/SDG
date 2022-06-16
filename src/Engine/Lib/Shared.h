#pragma once
#include <Engine/Exceptions/NullReferenceException.h>
#include <Engine/Lib/Concepts.h>
#include <functional>
#include <cstddef>

namespace SDG
{
    template <typename T>
    class Shared
    {
        struct Impl {
            explicit Impl(T *ptr);
            Impl(T *ptr, const std::function<void()> &deleter);
            ~Impl();

            T *ptr;
            size_t count;
            std::function<void()> deleter;
        };
    public:

        /// Must be called with a dynamically allocated object
        Shared();
        Shared(T *newT);

        /// Adds a special deleter for cleaning up the pointer
        Shared(T *newT, const std::function<void()> &deleter);

        Shared(const Shared &other);
        Shared &operator=(const Shared &other);

        ~Shared();
    public:
        [[nodiscard]] T *Get() { return impl->ptr; }
        [[nodiscard]] const T *Get() const { return impl->ptr; }
        [[nodiscard]] T *operator->() { return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] const T *operator->() const { return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] T &operator *() { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] const T *operator *() const { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] explicit operator bool() { return impl->ptr; }

        /// Gets the number of live references of Shared ptr
        [[nodiscard]] size_t Count() const { return impl->count; }

        void Reset() { DestroyRef(); impl = new Impl(nullptr); }
    private:
        /// Removes reference instances, calling destructor on ptr when it reaches zero
        void DestroyRef();
        Shared::Impl *impl;
    };
}

#include "Shared.inl"
