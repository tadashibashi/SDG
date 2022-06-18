#pragma once
#include "Shared.h"

#include <Engine/Lib/ClassMacros.h>
#include <Engine/Exceptions/Fwd.h>

#include <functional>

namespace SDG
{
    /// A unique ptr-like smart pointer. Does not need the full declaration of template parameters.
    /// This information only needs to be available when constructor is called.
    template <typename T>
    class Unique
    {
        struct Impl {
            explicit Impl(T *ptr) : ptr(ptr), deleter([ptr]()->void { delete ptr; }) { }
            explicit Impl(std::nullptr_t ptr) : ptr(ptr), deleter() { }
            Impl(T *ptr, const std::function<void()> &deleter) : ptr(ptr), deleter(deleter) { }
            T *ptr;
            std::function<void()> deleter;
        };

        SDG_NOCOPY(Unique);
    public:
        /// Creates a nullptr
        Unique() : impl(new Impl(nullptr)) { }

        /// @param t a dynamically allocated object.
        Unique(T *t) : impl(new Impl(t)) { }
        Unique(T *t, const std::function<void()> &deleter) : impl(new Impl(t, deleter)) { }
        Unique(std::nullptr_t ptr) : impl(new Impl(ptr)) { }

        Unique(Unique &&u) noexcept : impl(u.impl)
        {
            u.impl = nullptr;
        }

        auto operator= (Unique &&u) noexcept-> Unique &
        {
            if (u.impl->ptr != impl->ptr)
            {
                Delete();
                impl = u.impl;
            }

            u.impl = nullptr;
            return *this;
        }

        /// Deletes old pointer and sets to null
        auto Reset()->void
        {
            Assign(nullptr, std::function<void()>{});
        }

        /// Deletes old pointer and sets up a new one
        auto Assign(T *newT)->void
        {
            Delete();
            impl->ptr = newT;
            impl->deleter = [newT]() { delete newT; };
        }

        auto Assign(T *newT, const std::function<void()> &deleter)->void
        {
            Delete();
            impl->deleter = deleter;
            impl->ptr = newT;
        }

        ~Unique()
        {
            Delete();
            delete impl;
        }

        auto SetDeleter(const std::function<void()> &deleter)->void
        {
            impl->deleter = deleter;
        }

        [[nodiscard]] T *Get() { return impl->ptr; }
        [[nodiscard]] const T *Get() const { return impl->ptr; }
        [[nodiscard]] const T *operator->() const { return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] T *operator->() {return impl->ptr ? impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] const T &operator *() const { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }
        [[nodiscard]] T &operator *() { return impl->ptr ? *impl->ptr : throw NullReferenceException(); }

        [[nodiscard]] operator bool() { return static_cast<bool>(impl->ptr); }
    private:
        void Delete() 
        {
            if (impl && impl->deleter)
                impl->deleter();
        }

        Impl *impl;
    };
}
