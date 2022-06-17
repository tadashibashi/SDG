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
        [[nodiscard]] auto Get() -> T *                    { return impl->ptr; }
        [[nodiscard]] auto Get() const -> const T *        { return impl->ptr; }
        [[nodiscard]] auto operator->() -> T *             { return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] auto operator->() const -> const T * { return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] auto operator *() -> T &             { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] auto operator *() const -> const T & { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] operator bool()                      { return static_cast<bool>(impl->ptr); }
        
        /// Gets the number of live references of Shared ptr
        [[nodiscard]] auto RefCount()->size_t const { return impl->count; }

        auto Reset()->void { DestroyRef(); impl = new Impl(nullptr); }
    private:
        /// Removes reference instances, calling destructor on ptr when it reaches zero
        void DestroyRef();
        Shared::Impl *impl;
    };
}

#include "Shared.inl"
