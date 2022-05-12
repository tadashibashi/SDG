//
// Created by Aaron Ishibashi on 5/9/22.
//
#pragma once
#include <utility>

namespace SDG
{
    template <typename T>
    class Ptr
    {
    public:
        Ptr() : ptr() { }
        ~Ptr()
        {
            delete ptr;
        }

        template <typename ...Args>
        void New(Args...args)
        {
            if (ptr)
            {
                delete ptr;
            }

            T *t = new T(std::forward<Args>(args)...);
            ptr = t;
        }

        T *Get() { return ptr; }

    private:
        T *ptr;
    };
}
