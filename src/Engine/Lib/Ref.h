/*!
 * @file Ref.h – SDG_Engine
 * @namespace SDG
 * @class Ref / CRef
 * A reference to another object that behaves like a pointer.
 * You can get the internal pointer by calling Ref::Get()
 * It was designed for safety against accidental copying during ref retrieval,
 * and helping remember who owns what. It also has a uniform interface,
 * as opposed to cpp references using dot accessors, and pointers using arrows.
 * Ref simply uses pointer arrows.
 * Finally, CRef is a Ref where the internal reference is const.
 * You could write Ref<const T>, but CRef<T> seems more compact.
 *
 * Limitations: since void is not referencable, you can't have a Ref<void> object.
 * This is the cost of having a template constructor that accepts references.
 * In this case, an alternative would be to store Ref<void *> 
 * (calling Get() will retrieve a pointer to void pointer in this case)
 * or cast the void * to a uintptr_t to store in the Ref.
 *
 * Warning: Ref<T> does not guarantee a valid pointer.
 * Therefore, it is a good idea to design the application in a way where
 * any object with a Ref is guaranteed to go out of scope before the
 * referenced object does. Otherwise, a Shared<T> may possibly be a
 * better solution.
 *
 */
#pragma once

namespace SDG
{
    /// Reference to an object. Access via ->
    template<typename T>
    class Ref 
    {
    public:
        /// Initializes with a nullptr
        Ref() : ref() { }
        /// Initialization from a reference
        Ref(T &ref) : ref(&ref) { }
        /// Initialization from a pointer
        Ref(T *ref) : ref(ref) { }

        Ref &operator = (Ref ref);
        Ref &operator = (T *ref);
        Ref &operator = (T &ref);

        /// Get the internal ptr. Please do not call delete on it, since it is owned
        /// by the object this reference was retrieved from.
        [[nodiscard]] T *Get() const { return ref; }

        /// Access ptr members. Throws a NullReference exception if null.
        [[nodiscard]] T *operator->();
         /// Access ptr members. Throws a NullReference exception if null.
        [[nodiscard]] const T *operator->() const;
        /// Access raw reference. Throws a NullReference exception if null.
        [[nodiscard]] T &operator *();
        [[nodiscard]] const T &operator *() const;

        [[nodiscard]] bool operator==(const Ref &other) const;
        [[nodiscard]] bool operator !=(const Ref &other) const;
        [[nodiscard]] operator bool() const { return static_cast<bool>(ref); }

        /// Dynamically casts Ref<T> to Ref<U>. If it was unsuccessful,
        /// such as the underlying type was not truly of type U, it will
        /// return a null reference.
        template <typename U>
        [[nodiscard]] operator Ref<U>() const;

    private:
        T *ref;
    };


    /// Const reference to an object. Access via ->
    template <typename T>
    class CRef {
    public:
        CRef() : ref() { }
        CRef(const T *ref) : ref(ref) { }
        CRef(const T &ref) : ref(&ref) { }
        CRef(const Ref<T> ref) : ref(ref.Get()) { }

        CRef &operator = (const Ref<T> ref);
        CRef &operator = (const CRef<T> ref);
        CRef &operator = (const T *ref);
        CRef &operator = (const T &ref);

        /// Get internal ptr
        [[nodiscard]] const T *Get() const { return ref; }
        [[nodiscard]] const T *operator->() const;
        [[nodiscard]] const T &operator *() const;

        [[nodiscard]] bool operator==(const CRef &other) const;
        [[nodiscard]] bool operator !=(const CRef &other) const;
        [[nodiscard]] operator bool() const { return static_cast<bool>(ref); }

        /// Dynamically casts Ref<T> to Ref<U>. If it was unsuccessful,
        /// such as the underlying type was not truly of type U, it will
        /// return a null reference.
        template<typename U>
        [[nodiscard]] operator CRef<U>() const;
    private:
        const T *ref;
    };
}

#include "Ref.inl"
