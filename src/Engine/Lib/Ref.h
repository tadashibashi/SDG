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
#include <Engine/Exceptions/NullReferenceException.h>

namespace SDG
{
    /// Reference to an object. Access via ->
    template <typename T>
    class Ref
    {
    public:
        Ref() : ref(nullptr) { }
        Ref(T &ref) : ref(&ref) { }
        Ref(T *ref) : ref(ref) { }

        auto operator = (Ref ref) { this->ref = ref.ref; return *this; }
        auto operator = (T *ref) { this->ref = ref; return *this; }
        auto operator = (T &ref) { this->ref = &ref; return *this; }

        [[nodiscard]] auto Get() -> T *{ return ref; }
        [[nodiscard]] auto Get() const -> const T *{ return const_cast<const T *>(ref); }
        [[nodiscard]] auto operator->() -> T * { return ref ? ref : throw NullReferenceException(); }
        [[nodiscard]] auto operator->() const -> T * { return ref ? const_cast<const T *>(ref) : throw NullReferenceException(); }
        [[nodiscard]] auto operator *() -> T & { return ref ? *ref : throw NullReferenceException(); }
        [[nodiscard]] auto operator *() const -> T * { return ref ? const_cast<const T &>(*ref) : throw NullReferenceException(); }
        [[nodiscard]] explicit operator bool() { return ref; }
        [[nodiscard]] bool operator== (const Ref &other) { return other.ref == ref; }
        [[nodiscard]] bool operator!= (const Ref &other) { return other.ref != ref; }
    private:
        T *ref;
    };
}
