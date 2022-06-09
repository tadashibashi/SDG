/*!
 * @file ServiceProvider.h
 * @namespace SDG
 * @class ServiceProvider
 * A container that allows generic storage by type. It can store one
 * object reference per type. This allows users to store specific data structures
 * without tying them to the class that owns it, helping prevent circular dependencies.
 * Users maintain ownership of the objects that are passed in, since ServiceProvider
 * does not call destructors or manage memory in any way.
 */
#pragma once
#include <Engine/Lib/Ref.h>

#include <map>
#include <typeindex>

namespace SDG
{
    /// A container that allows generic storage by type. It can store one
    /// object reference per type.
    /// Users maintain ownership of the objects that are passed in, since ServiceProvider
    /// does not call destructors or manage memory in any way.
    class ServiceProvider 
    {
    public:
        // ========== Emplacement and Removal =================================

        /// Stores an object reference of type T that is passed into the function.
        /// You as the user maintain ownership responsibility of this object.
        /// (ServiceProvider does not call destructors or manage memory)
        /// @param service The object ptr to store
        /// @returns reference to this ServiceContainer for chaining function calls.
        template <typename T>
        ServiceProvider &Emplace(Ref<T> service);

        /// Removes an object ptr of type T that was previously passed into
        /// the function. Please remember to manage cleanup for that object,
        /// as this function does not manage deletion, etc.
        /// @tparam T the type of object pointer to remove
        /// @returns reference to this ServiceContainer for chaining function calls.
        template <typename T>
        ServiceProvider &Remove();

        /// Removes all objects from the services container.
        ServiceProvider &RemoveAll() { services.clear(); return *this; }

        // ========== Getters =================================================

        /// Gets a reference to an object of type T in the container.
        /// Reference will be null if none exists within.
        /// @tparam T the type of object ptr to retrieve.
        template <typename T>
        [[nodiscard]] Ref<T> Get();

        template <typename T>
        [[nodiscard]] CRef<T> Get() const;

        /// Gets a reference to a stored object of type T. Reference will be null if
        /// one does not exist in the container.
        /// Intended to be used if a service is not guaranteed to be in this obj.
        /// @param service [out] service to get
        /// @returns true, if pointer was found; false, if not.
        template <typename T>
        bool TryGet(Ref<T> &service);

        template <typename T>
        bool TryGet(CRef<T> &service) const;

        /// Gets the number of services stored
        [[nodiscard]] size_t Size() const { return services.size(); }

        /// Checks whether the container is empty
        [[nodiscard]] bool Empty() const { return services.empty(); }
    private:
        /// Internal map of object services
        std::map<std::type_index, void *> services;
    };
}

#include "ServiceProvider.inl"
