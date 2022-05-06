//
// Created by Aaron Ishibashi on 5/6/22.
//
#pragma once
#include <stdexcept>
#include <string>
#include <typeindex>
namespace SDG
{
    class NullReference : std::exception {
    public:
        NullReference(std::type_index type)
            : std::exception(), message()
        {
            message = "Null reference of type " + std::string(type.name());
        }

        const char *what() const noexcept override
        {
            return message.c_str();
        }
    private:
        std::string message;
    };

    /// Wrapper around a reference to prevent deletion and copying
    /// when retrieving an object from another.
    template <typename T>
    class Ref {
    public:
        Ref() : ref() { }
        explicit Ref(T &ref) : ref(&ref) { }
        explicit Ref(T *ref) : ref(ref) { }

        T *operator->()
        {
            if (!ref)
                throw NullReference(typeid(T));
            return ref;
        }
    private:
        T *ref;
    };

    /// Wrapper around a const reference to prevent copying
    /// when retrieving an object from another.
    template <typename T>
    class CRef {
    public:
        CRef() : ref() { }
        explicit CRef(T *ref) : ref(ref) { }
        explicit CRef(T &ref) : ref(&ref) { }

        const T *operator->() const
        {
            if (!ref)
                throw NullReference(typeid(T));
            return ref;
        }
    private:
        const T *ref;
    };
}