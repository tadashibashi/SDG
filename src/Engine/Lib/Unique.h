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
            Impl(T *ptr, const std::function<void()> &deleter) : ptr(ptr), deleter(deleter) { }
            T *ptr;
            std::function<void()> deleter;
        };

        SDG_NOCOPY(Unique);
    public:
        class Ref {
        public:
            Ref(const Unique<T> &u) : impl(u.impl) { }

            Ref() : impl(nullptr) { }

            [[nodiscard]] T *Get() { return impl->ptr; }
            [[nodiscard]] const T *Get() const { return impl->ptr; }
            [[nodiscard]] const T *operator->() const { return impl->ptr; }
            [[nodiscard]] T *operator->() { return impl->ptr; }
            [[nodiscard]] const T &operator *() const { return impl->ptr; }
            [[nodiscard]] T &operator *() { return impl->ptr; }

            [[nodiscard]] operator bool() { return static_cast<bool>(impl->ptr); }
        private:
            Shared<Unique::Impl> impl;
        };

        /// Creates a nullptr
        Unique() : impl(new Impl(nullptr)) { }

        /// @param t a dynamically allocated object.
        Unique(T *t) : impl(new Impl(t)) { }
        Unique(T *t, const std::function<void()> &deleter) : impl(new Impl(t, deleter)) { }
        
        Unique(Unique &&u) : impl(u.impl)
        {
            u.impl = new Impl(nullptr);
        }

        auto operator= (Unique &&u) -> Unique &
        {
            if (u.impl.Get() != impl.Get())
            {
                Delete();
                impl = u.impl;
            }

            u.impl.Reset();

            return *this;
        }

        /// Deletes old pointer and sets to null
        Unique &Reset()
        {
            return Assign(nullptr);
        }

        /// Deletes old pointer and sets up a new one
        Unique &Assign(T *newT)
        {
            Delete();
            impl = new Impl(newT, [newT]() { delete newT; });
            return *this;
        }

        Unique &Assign(T *newT, const std::function<void()> &deleter)
        {
            Delete();
            impl = new Impl(newT, deleter);
            return *this;
        }

        ~Unique()
        {
            Delete();
        }

        [[nodiscard]] T *Get() {return impl->ptr; }
        [[nodiscard]] const T *Get() const {return impl->ptr; }
        [[nodiscard]] const T *operator->() const {return impl->ptr; }
        [[nodiscard]] T *operator->() {return impl->ptr; }
        [[nodiscard]] const T &operator *() const {return *impl->ptr; }
        [[nodiscard]] T &operator *() {return *impl->ptr; }

        [[nodiscard]] size_t RefCount() const { return impl->Count(); }

        [[nodiscard]] operator bool() { return static_cast<bool>(impl->ptr); }
    private:
        void Delete() 
        {
            if (impl)
            {
                impl->deleter();
                impl->ptr = nullptr;
            }
        }
        Shared<Impl> impl;

        friend class Unique::Ref;
    };

    template <typename T>
    using URef = Unique<T>::Ref;
}
