/*!
 * @file Ref.h – SDG_Engine
 * @copyright Aaron Ishibashi © 2022
 *
 * @class Ref / CRef
 * @description A capsule wrapping a pointer, to safely reference another object
 * in a uniform fashion. An object holding a Ref object has a clear
 * indicator that it is not the owner of the internal pointer.
 * It also helps prevent accidental copy assignment when retrieving a
 * reference from a getter function, and provides a common interface (->)
 * for accessing its members. (It can be a slight hindrance to have to
 * remember whether to use (.) or (->) if it was a pointer or reference.)
 * If the internal pointer is absolutely needed for a function parameter,
 * Get() can be called to retrieve it. While deletion of this pointer is not
 * prevented, this class at least encourages intentionality about doing so.
 * CRef is the const version of the Ref object.
 *
 * @future Make Ref track pointer validity. This seems like it could result in
 * wide-scale unfavorable performance loss if we have to dereference an
 * extra time from a ptr to ptr. Optionally, we could cache an additional ptr
 * but this would double the size of each reference.
 * To ID memory, we could store the timestamp of when the memory was allocated
 * inside of a structure.
 *
 */
#pragma once
#include <SDG/Exceptions/NullReferenceException.h>

namespace SDG
{
    template <typename T>
    class Ref {
    public:
        Ref() : ref() { }
        explicit Ref(T &ref) : ref(&ref) { }
        explicit Ref(T *ref) : ref(ref) { }

        /// Get the internal ptr. Please do not call delete on it, since it is owned
        /// by the object this reference was retrieved from.
        T *Get() const { return ref; }

        /// Access ptr members. Throws a NullReference exception if ptr was null.
        T *operator->() const;
        T &operator *() const;

        bool operator==(const Ref &other);
        bool operator !=(const Ref &other);
        operator bool() { return static_cast<bool>(ref); }

        template <typename U>
        operator Ref<U>() {
            static_assert(std::is_base_of_v<T, U> || std::is_void_v<U>,
                    "Casted type must derive from type T or void");
            return Ref<U>(ref);
        }
    private:
        T *ref;
    };


    /// Non-smart ptr that serves as a wrapper around a
    /// ptr reference to prevent accidental deletion and copying
    /// when retrieving an object ref from another. Accessed via ->
    template <typename T>
    class CRef {
    public:
        CRef() : ref() { }
        explicit CRef(T *ref) : ref(ref) { }
        explicit CRef(T &ref) : ref(&ref) { }

        /// Get internal ptr
        const T *Get() const { return ref; }
        const T *operator->() const;
        const T &operator *() const;

        bool operator==(const CRef &other);
        bool operator !=(const CRef &other);
        operator bool() { return static_cast<bool>(ref); }
    private:
        const T *ref;
    };
}

template<typename T>
bool
SDG::Ref<T>::operator==(const Ref &other)
{
    return ref == other.ref;
}

template<typename T>
bool
SDG::Ref<T>::operator!=(const Ref &other)
{
    return ref != other.ref;
}

template<typename T>
T *
SDG::Ref<T>::operator->() const
{
    if (!ref) /// Prevent access to a nullptr
        throw NullReferenceException();
    return ref;
}

template<typename T>
T &
SDG::Ref<T>::operator *() const
{
    if (!ref) /// Prevent access to a nullptr
        throw NullReferenceException();
    return *ref;
}

template<typename T>
const T *
SDG::CRef<T>::operator->() const
{
    if (!ref) /// Prevent access to a nullptr
        throw NullReferenceException();
    return ref;
}

template<typename T>
const T &
SDG::CRef<T>::operator *() const
{
    if (!ref) /// Prevent access to a nullptr
        throw NullReferenceException();
    return *ref;
}

template<typename T>
bool
SDG::CRef<T>::operator==(const CRef &other)
{
    return ref == other.ref;
}

template<typename T>
bool
SDG::CRef<T>::operator!=(const CRef &other)
{
    return ref != other.ref;
}
