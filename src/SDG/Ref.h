//
// Ref
//
#pragma once
#include <SDG/Exceptions/NullReferenceException.h>

namespace SDG
{
    /// Non-smart ptr that serves as a wrapper around a
    /// pointer to prevent accidental deletion and copying
    /// when retrieving an object ref from another. Access reference members via -> and
    /// get the internal ptr with Get(). It's best to not delete the internal ptr via
    /// "delete Ref::Get()", and while this object does not prevent this possibility,
    /// it at least requires significant intentionality by the user.
    /// May resolve to a bool: (true) if the internal ptr is non-null or
    /// (false) pointing to null.
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

        bool operator==(const Ref &other);
        bool operator !=(const Ref &other);
        operator bool() { return static_cast<bool>(ref); }
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
        throw NullReferenceException(typeid(T));
    return ref;
}

template<typename T>
const T *
SDG::CRef<T>::operator->() const
{
    if (!ref) /// Prevent access to a nullptr
        throw NullReferenceException(typeid(T));
    return ref;
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
