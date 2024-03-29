#include "Array.h"
#include <Engine/Lib/Memory.h>
#include <Engine/Lib/TypeTraits.h>
#include <Engine/Exceptions/Fwd.h>

#include <utility>


namespace std
{
    template<typename T>
    inline void swap(SDG::Array<T> &a, SDG::Array<T> &b) noexcept { a.Swap(b); }
}


namespace SDG
{
    template<typename T>
    Array<T>::~Array() { Free(arr); }

    template<typename T>
    Array<T>::Array(const Array<T> &other) :
        arr((other.size > 0) ? Calloc<T>(other.size) : nullptr),
        size(other.size)
    {
        if (size > 0)
        {
            memset(arr, 0, sizeof(T) * size); // sets everything value to 0/null

            T *p = arr;
            for (Array<T>::ConstIterator it = other.cbegin(), end = other.cend(); it != end; ++it)
            {
                T temp(*it);
                std::swap(temp, *p++);
            }
        }
    }

    template<typename T>
    Array<T>::Array(Array<T> &&other) noexcept :
        arr(other.arr),
        size(other.size)
    {
        other.arr = nullptr;
        other.size = 0;
    }

    template<typename T>
    Array<T>::Array(size_t size) : arr((size > 0) ? Calloc<T>(size) : nullptr), size(size)
    {
        if (arr)
        {
            memset(arr, 0, sizeof(T) * size);
            for (T &value : *this)
            {
                value = T{};
            }
        }
    }

    template<typename T>
    Array<T>::Array(const std::initializer_list<T> &list) :
        arr(list.size() > 0 ? Calloc<T>(list.size()) : nullptr), size(list.size())
    {
        if (arr)
        {
            memset(arr, 0, size * sizeof(T));

            T *p = arr;
            for (const T &t : list)
            {
                *p++ = t;
            }
        }
    }

    template<typename T>
    template <typename It>
    Array<T>::Array(It pBegin, It pEnd)  : arr(), size()
    {
        Assign(pBegin, pEnd);
    }

    template<typename T>
    template<typename It>
    Array<T> &Array<T>::Assign(It pBegin, It pEnd)
    {
        static_assert(std::is_same_v<T, std::decay_t<decltype(*pBegin)>>,
            "ForwardIterator must contain Array's type T");
        Free(arr);

        // Get instances
        size_t count = 0;
        for (It it = pBegin; it != pEnd; ++it)
            ++count;

        // Allocate memory
        arr = (count > 0) ? Calloc<T>(count) : nullptr;
        memset(arr, 0, count * sizeof(T));
        size = count;

        // Copy data
        T *ptr = arr;
        for (It it = pBegin; it != pEnd; ++it)
        {
            T temp(*it);
            std::swap(temp, *ptr++);
        }

        return *this;
    }

    template<typename T>
    void Array<T>::Clear()
    {
        Free(arr);
        arr = nullptr;
        size = 0;
    }

    template<typename T>
    Array<T> &Array<T>::Assign(ConstIterator pBegin, ConstIterator pEnd)
    {
        Free(arr); // Free any pre-existing data
        
        // Allocate memory
        size_t count = pEnd - pBegin;
        arr = (count > 0) ? Calloc<T>(count) : nullptr;
        memset(arr, 0, count * sizeof(T));
        size = count;

        // Copy data
        T *ptr = arr;
        for (ConstIterator it = pBegin; it != pEnd; ++it)
        {
            T temp(*it);
            std::swap(temp, *ptr++);
        }

        return *this;
    }



    template<typename T>
    Array<T> &Array<T>::operator = (const Array<T> &arr)
    {
        return Assign(arr.begin(), arr.end());
    }

    template<typename T>
    Array<T> &Array<T>::operator = (Array<T> &&other) noexcept
    {
        if (&other == this)
            return *this;

        Free(arr);
        arr = other.arr;
        size = other.size;
        other.arr = nullptr;
        other.size = 0;

        return *this;
    }

    template<typename T>
    const T &Array<T>::At(unsigned index) const
    {
        if (index >= size)
            ThrowOutOfRangeException(index, "Array max index exceeded");
        return arr[index];
    }

    template<typename T>
    T &Array<T>::At(unsigned index)
    {
        if (index >= size)
            ThrowOutOfRangeException(index, "Array max index exceeded");
        return arr[index];
    }

    template<typename T>
    Array<T> &Array<T>::Swap(Array &other)
    {
        std::swap(arr, other.arr);
        std::swap(size, other.size);

        return *this;
    }

}

#include <Engine/Lib/Private/Fmt.h>
#include <Engine/Lib/Concepts.h>
#include <sstream>

template <typename T>
inline std::ostream &operator << (std::ostream &ss, const SDG::Array<T> &arr)
{
    ss << "Array<" << typeid(T).name() << "> Length: " << arr.Size() << "\n[";
    if (!arr.Empty())
    {
        for (auto it = arr.cbegin(), end = arr.cend() - 1; it != end; ++it)
            ss << *it << ", ";
        ss << *(arr.cend() - 1);
    }
    ss << ']';

    return ss;
}

template <Streamable<std::stringstream> T>
struct fmt::formatter< SDG::Array<T> >
{
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const SDG::Array<T> &arr, FormatContext &ctx) -> decltype(ctx.out())
    {
        std::stringstream ss;
        ss << arr;
        return fmt::format_to(ctx.out(), "{}", ss.str());
    }
};
