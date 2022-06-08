#pragma once
#include <SDG/Exceptions/Fwd.h>

#include <cstdint>
#include <string>
#include <typeinfo>

namespace SDG
{
    /// Random access iterator for contiguous SDG engine containers. Essentially just a wrapper around a const pointer. 
    /// Invalidated if the originating container is mutated.
    template <typename T>
    class ConstRAIterator
    {
    public:
        ConstRAIterator(const T *ptr, const T *root, const T* end) : ptr(ptr), root(root), end(end) { }

        // ===== Access ===============================================================================================

        [[nodiscard]] const T &operator *() const { return *CheckBounds(ptr); }
        [[nodiscard]] const T *operator &() const { return CheckBounds(ptr); }
        [[nodiscard]] const T *operator->() const { return CheckBounds(ptr); }
        [[nodiscard]] const T &operator [] (size_t index) const { return *CheckBounds(ptr + index); }

        // ===== Getters ==============================================================================================

        /// Index in the originating container.
        [[nodiscard]] size_t Index() const { return ptr - root; }
        /// Size of the originating container.
        [[nodiscard]] size_t Size() const { end - root; }

        /// May differ between compilers. Checking the name is intended for debugging purposes only, 
        /// and not for strict runtime checks.
        [[nodiscard]] const char *TypeName() const noexcept { return typeid(T).name(); }

        // ===== Comparison ===========================================================================================

        [[nodiscard]] bool operator == (const ConstRAIterator &it) const { return ptr == it.ptr; }
        [[nodiscard]] bool operator != (const ConstRAIterator &it) const { return ptr != it.ptr; }
        [[nodiscard]] bool operator < (const ConstRAIterator &it) const { return ptr < it.ptr; }
        [[nodiscard]] bool operator > (const ConstRAIterator &it) const { return ptr < it.ptr; }
        [[nodiscard]] bool operator <= (const ConstRAIterator &it) const { return !(ptr > it.ptr); }
        [[nodiscard]] bool operator >= (const ConstRAIterator &it) const { return !(ptr < it.ptr); }

        // ===== Modulation ===========================================================================================

        ConstRAIterator &operator += (int i) { ptr += i; return *this; }
        ConstRAIterator &operator -= (int i) { ptr -= i; return *this; }
        ConstRAIterator &operator ++() { ptr += 1; return *this; }
        ConstRAIterator operator ++(int) { const T *temp = ptr; ptr += 1; return ConstRAIterator(temp, root, end); }
        ConstRAIterator &operator --() { ptr -= 1; return *this; }
        ConstRAIterator operator --(int) { const T *temp = ptr; ptr -= 1; return ConstRAIterator(temp, root, end); }

    private:
        /// Ensures a pointer is within bounds. For use in accessor functions.
        const T *CheckBounds(const T *p) const
        {
            if (p > end || p < root)
                ThrowOutOfRangeException(p - root, std::string("ConstRAIterator<") +
                    typeid(T).name() + std::string(">: dereferenced out of range iterator: max index: ") +
                    std::to_string(end - root));
            return p;
        }

        const T *ptr;
        const T *root;
        const T *end;
    };

    template<typename T>
    [[nodiscard]] inline uintptr_t operator + (const ConstRAIterator<T> &a, const ConstRAIterator<T> &b)
    {
        return (uintptr_t)&a + (uintptr_t)&b;
    }

    template<typename T>
    [[nodiscard]] inline ConstRAIterator<T> operator + (const ConstRAIterator<T> &a, int i)
    {
        return ConstRAIterator<T>(a) += i;
    }

    template<typename T>
    [[nodiscard]] inline uintptr_t operator - (const ConstRAIterator<T> &a, const ConstRAIterator<T> &b)
    {
        return (uintptr_t)&a - (uintptr_t)&b;
    }

    template<typename T>
    [[nodiscard]] inline ConstRAIterator<T> operator - (const ConstRAIterator<T> &a, int i)
    {
        return ConstRAIterator<T>(a) -= i;
    }
}
