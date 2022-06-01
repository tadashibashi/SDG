#pragma once

#include <SDG/Exceptions/NullReferenceException.h>
#include <SDG/Lib/Memory.h>

namespace SDG
{
    template<typename T>
    class Shared
    {
    public:
        // Creates a null shared pointer
        Shared() : ptr(), count() { }

        // Must be called with a dynamically allocated object
        explicit Shared(T *newPtr) : ptr(newPtr), count(new size_t(1))
        {}

        Shared(const Shared &other) : 
            ptr(other.ptr), count(other.count)
        {
            if (count) ++(*count);
        }

        ~Shared()
        {
            Destroy();
        }

        Shared &operator=(const Shared &other)
        {
            if (ptr != other.ptr) // only perform operation if differing ptrs
            {
                Destroy();                      // destroy current
                ptr = other.ptr;
                count = other.count;

                if (count) ++(*count);
            }

            return *this;
        }

        [[nodiscard]] const T *Get() const { return ptr; }
        [[nodiscard]] size_t Count() const { return (count) ? *count : 0; }
        [[nodiscard]] void Reset() { Destroy(); ptr = nullptr; count = nullptr; }
        [[nodiscard]] T *operator->();
        [[nodiscard]] T &operator *();

        [[nodiscard]] bool operator ==(const Shared &other) const;
        [[nodiscard]] bool operator !=(const Shared &other) const;

        [[nodiscard]] operator bool() const;
    private:
        void Destroy();
        T *ptr;
        size_t *count;
    };


    template<typename T>
    inline T *Shared<T>::operator->()
    {
        if (!ptr) // prevent undefined behavior by throwing
            throw NullReferenceException();
        return ptr;
    }

    template<typename T>
    inline T &Shared<T>::operator*()
    {
        if (!ptr) // prevent undefined behavior by throwing
            throw NullReferenceException();
        return *ptr;
    }

    template<typename T>
    inline bool Shared<T>::operator==(const Shared &other) const
    {
        return ptr == other.ptr;
    }

    template<typename T>
    inline bool Shared<T>::operator!=(const Shared &other) const
    {
        return ptr != other.ptr;
    }

    template<typename T>
    inline void Shared<T>::Destroy()
    {
        if (count && --(*count) <= 0)
        {
            delete ptr;
            delete count;

            // Don't need since usage is during destruction-like scenarios
            // ptr = nullptr; 
            // count = nullptr;
        }
    }

    template<typename T>
    inline Shared<T>::operator bool() const
    {
        return static_cast<bool>(ptr);
    }
}