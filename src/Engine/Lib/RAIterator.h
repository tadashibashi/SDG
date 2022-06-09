#pragma once
#include "ConstRAIterator.h"

#include <Engine/Exceptions/Fwd.h>

#include <cstdint>

namespace SDG
{
    /// Random access iterator for contiguous SDG engine containers. Essentially just a wrapper around a pointer. 
    /// Invalidated if the originating container is mutated.
    template <typename T>
    class RAIterator
    {
    public:
        RAIterator(T *ptr, const T *root, const T *end) : ptr(ptr), root(root), end(end) { }

        // ===== Access ===============================================================================================

        [[nodiscard]] T &operator *() { return *CheckBounds(ptr); }
        [[nodiscard]] const T &operator *() const { return *ConstCheckBounds(ptr); }
        [[nodiscard]] T *operator &() { return CheckBounds(ptr); }
        [[nodiscard]] const T *operator &() const { return ConstCheckBounds(ptr); }
        [[nodiscard]] T *operator->() { return CheckBounds(ptr); }
        [[nodiscard]] const T *operator->() const { return ConstCheckBounds(ptr); }
        [[nodiscard]] const T &operator [] (size_t index) const { return *ConstCheckBounds(ptr + index); }
        [[nodiscard]] T &operator [] (size_t index) { return *CheckBounds(ptr + index); }

        // ===== Getters ==============================================================================================

        /// Index in the originating container.
        [[nodiscard]] size_t Index() const { return ptr - root; }
        /// Size of the originating container
        [[nodiscard]] size_t Size() const { return end - root; }

        /// May differ between compilers. Checking the name is intended for debugging purposes only, 
        /// and not for strict runtime checks.
        [[nodiscard]] const char *TypeName() const noexcept { return typeid(T).name(); }

        // ===== Modulation ===========================================================================================

        RAIterator &operator += (int i) { ptr += i; return *this; }
        RAIterator &operator -= (int i) { ptr -= i; return *this; }
        RAIterator &operator ++() { ptr += 1; return *this; }
        RAIterator operator ++(int) { T *temp = ptr; ptr += 1; return RAIterator(temp, root, end); }
        RAIterator &operator --() { ptr -= 1; return *this; }
        RAIterator operator --(int) { T *temp = ptr; ptr -= 1; return RAIterator(temp, root, end); }

        // ===== Comparison ===========================================================================================

        [[nodiscard]] bool operator == (const RAIterator &it) const { return ptr == it.ptr; }
        [[nodiscard]] bool operator != (const RAIterator &it) const { return ptr != it.ptr; }
        [[nodiscard]] bool operator < (const RAIterator &it) const { return ptr < it.ptr; }
        [[nodiscard]] bool operator > (const RAIterator &it) const { return ptr < it.ptr; }
        [[nodiscard]] bool operator <= (const RAIterator &it) const { return !(ptr > it.ptr); }
        [[nodiscard]] bool operator >= (const RAIterator &it) const { return !(ptr < it.ptr); }

        // ===== Casting ==============================================================================================

        operator ConstRAIterator<T>() { return { ptr, root, end }; }
    private:
        /// Ensures a pointer is within bounds. For use in accessor functions.
        T *CheckBounds(T *p)
        {
            if (p > end || p < root)
                ThrowOutOfRangeException(p - root, std::string("RAIterator<") +
                    typeid(T).name() + std::string(">: dereferenced out of range iterator: max index: ") +
                    std::to_string(end - root));
            return p;
        }

        const T *ConstCheckBounds(const T *p) const 
        {
            if (p > end || p < root)
                ThrowOutOfRangeException(p - root, std::string("RAIterator<") +
                    typeid(T).name() + std::string(">: dereferenced out of range iterator: max index: ") +
                    std::to_string(end - root));
            return p;
        }

        T *ptr;
        const T *root;
        const T *end;
    };

    template<typename T>
    [[nodiscard]] inline uintptr_t operator + (const RAIterator<T> &a, const RAIterator<T> &b)
    {
        return static_cast<uintptr_t>(&a) + static_cast<uintptr_t>(&b);
    }

    template<typename T>
    [[nodiscard]] inline RAIterator<T> operator + (const RAIterator<T> &a, int i)
    {
        return RAIterator<T>(a) += i;
    }

    template<typename T>
    [[nodiscard]] inline uintptr_t operator - (const RAIterator<T> &a, const RAIterator<T> &b)
    {
        return (uintptr_t)&a - (uintptr_t)&b;
    }

    template<typename T>
    [[nodiscard]] inline RAIterator<T> operator - (const RAIterator<T> &a, int i)
    {
        return RAIterator<T>(a) -= i;
    }
}
