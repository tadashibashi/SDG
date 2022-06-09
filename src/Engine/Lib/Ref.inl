// Inline implementation
#include "Ref.h"
#include <Engine/Exceptions/Fwd.h>

#include <type_traits>


namespace SDG
{
    // ===== Ref Implementation ==============================================

    template<typename T>
    Ref<T> &Ref<T>::operator = (Ref<T> ref)
    {
        this->ref = ref.ref;
        return *this;
    }

    template<typename T>
    Ref<T> &Ref<T>::operator = (T *ref)
    {
        this->ref = ref;
        return *this;
    }

    template<typename T>
    Ref<T> &Ref<T>::operator = (T &ref)
    {
        this->ref = &ref;
        return *this;
    }

    template<typename T>
    bool Ref<T>::operator==(const Ref &other) const
    {
        return ref == other.ref;
    }

    template<typename T>
    bool Ref<T>::operator!=(const Ref &other) const
    {
        return ref != other.ref;
    }

    template<typename T>
    T *Ref<T>::operator->()
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return ref;
    }

    template<typename T>
    const T *Ref<T>::operator->() const
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return ref;
    }

    template<typename T>
    T &Ref<T>::operator *()
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return *ref;
    }

    template<typename T>
    const T &Ref<T>::operator *() const
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return *ref;
    }

    template<typename T>
    template <typename U>
    Ref<T>::operator Ref<U>() const
    {
        static_assert(std::is_base_of_v<T, U>,
            "Casted type must derive from type T");
        return { dynamic_cast<U *>(ref) };
    }


    // ===== CRef Implementation ==============================================

    template<typename T>
    CRef<T> &CRef<T>::operator = (const Ref<T> ref)
    {
        this->ref = ref.ref;
        return *this;
    }

    template<typename T>
    CRef<T> &CRef<T>::operator = (const CRef<T> ref)
    {
        this->ref = ref.ref;
        return *this;
    }

    template<typename T>
    CRef<T> &CRef<T>::operator = (const T *ref)
    {
        this->ref = ref;
        return *this;
    }

    template<typename T>
    CRef<T> &CRef<T>::operator = (const T &ref)
    {
        this->ref = &ref;
        return *this;
    }

    template<typename T>
    const T *CRef<T>::operator->() const
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return ref;
    }

    template<typename T>
    const T &CRef<T>::operator *() const
    {
        if (!ref) /// Prevent access to a nullptr
            ThrowNullReferenceException();
        return *ref;
    }

    template<typename T>
    bool CRef<T>::operator==(const CRef &other) const
    {
        return ref == other.ref;
    }

    template<typename T>
    bool CRef<T>::operator!=(const CRef &other) const
    {
        return ref != other.ref;
    }

    template<typename T>
    template <typename U>
    CRef<T>::operator CRef<U>() const
    {
        static_assert(std::is_base_of_v<T, U>,
            "Casted type must derive from type T");
        return { dynamic_cast<U *>(ref) };
    }
}
