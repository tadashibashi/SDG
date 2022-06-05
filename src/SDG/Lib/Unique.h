#pragma once
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/ClassMacros.h>
#include <SDG/Exceptions/NullReferenceException.h>
namespace SDG
{
    /// unique_ptr implementation.
    template <typename T>
    class Unique
    {
        SDG_NOCOPY(Unique);
    public:
        /// Creates a nullptr
        Unique() : ptr() { }

        /// @param t a dynamically allocated object.
        explicit Unique(T *t) : ptr(t) { }

        ~Unique() { delete ptr; }

        [[nodiscard]] T *Get() const {return ptr; }

        /// Access the internal pointer. Throws a NullReferenceException if null.
        [[nodiscard]] T *operator->() const
        {
            if (!ptr) /// Prevent access to a nullptr
                throw NullReferenceException();
            return ptr;
        }

        [[nodiscard]] T &operator *() const { return *ptr; }

        [[nodiscard]] Ref<T> MakeRef() const { return Ref{ptr}; }
        [[nodiscard]] CRef<T> MakeCRef() const { return CRef{ptr}; }
        [[nodiscard]] explicit operator bool() const { return static_cast<bool>(ptr); }

        [[nodiscard]] bool operator==(const Ref<T> &other) { return ptr == other.Get(); }
        [[nodiscard]] bool operator !=(const Ref<T> &other) { return ptr != other.Get(); }
        [[nodiscard]] bool operator==(const T *other) { return ptr == other; }
        [[nodiscard]] bool operator !=(const T *other) { return ptr != other; }
    private:
        T *ptr;
    };
}
