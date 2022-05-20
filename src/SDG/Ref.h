/*!
 * @file Ref.h – SDG_Engine
 *
 * @class Ref / CRef
 * A reference to another object that acts like a pointer.
 * You can get the internal pointer by calling Ref::Get()
 * It was designed for safety against accidental copying during ref retrieval,
 * and helping remember who owns what. It also has a uniform interface,
 * as opposed to cpp references using dot accessors, and pointers using arrows.
 * Ref simply uses pointer arrows.
 * Finally, CRef is the const version of Ref.
 *
 * Limitations: since void is not referencable, you can't have a Ref<void> object.
 * This is the cost of having a template constructor that accepts references.
 * In this case, an alternative would be to store Ref<void *> 
 * (calling Get() will retrieve a pointer to void pointer in this case)
 * or cast the void * to a uintptr_t to store in the Ref.
 *
 * Warning: please make sure to keep these references valid, or let the objects
 * holding these references know when they are no longer valid. The Ref class
 * does not track pointer validity in any way, or keep them alive like a
 * shared_ptr would.
 *
 */
#pragma once
#include <SDG/Exceptions/NullReferenceException.h>

namespace SDG
{
    template <typename T>
    class Ref 
    {
    public:
        Ref() : ref() { }
        Ref(T &ref) : ref(&ref) { }
        Ref(T *ref) : ref(ref) { }

        /// Get the internal ptr. Please do not call delete on it, since it is owned
        /// by the object this reference was retrieved from.
        [[nodiscard]] T *Get() const { return ref; }

        /// Access ptr members. Throws a NullReference exception if ptr was null.
        [[nodiscard]] T *operator->() const;
        [[nodiscard]] T &operator *() const;

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
        CRef(T *ref) : ref(ref) { }
        CRef(T &ref) : ref(&ref) { }

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


    template<typename T>
    bool
    Ref<T>::operator==(const Ref &other)
    {
        return ref == other.ref;
    }

    template<typename T>
    bool
    Ref<T>::operator!=(const Ref &other)
    {
        return ref != other.ref;
    }

    template<typename T>
    T *
    Ref<T>::operator->() const
    {
        if (!ref) /// Prevent access to a nullptr
            throw NullReferenceException();
        return ref;
    }

    template<typename T>
    T &
    Ref<T>::operator *() const
    {
        if (!ref) /// Prevent access to a nullptr
            throw NullReferenceException();
        return *ref;
    }

    template<typename T>
    const T *
    CRef<T>::operator->() const
    {
        if (!ref) /// Prevent access to a nullptr
            throw NullReferenceException();
        return ref;
    }

    template<typename T>
    const T &
    CRef<T>::operator *() const
    {
        if (!ref) /// Prevent access to a nullptr
            throw NullReferenceException();
        return *ref;
    }

    template<typename T>
    bool
    CRef<T>::operator==(const CRef &other)
    {
        return ref == other.ref;
    }

    template<typename T>
    bool
    CRef<T>::operator!=(const CRef &other)
    {
        return ref != other.ref;
    }

}