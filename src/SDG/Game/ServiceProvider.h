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
#include <SDG/Exceptions/InvalidArgumentException.h>
#include <SDG/Lib/Ref.h>

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
        ServiceProvider &Emplace(Ref<T> service)
        {
            static_assert(!std::is_null_pointer_v<T>,
                    "must not pass explicit nullptr to container");
            if (!service.Get())
                throw InvalidArgumentException("ServiceProvider::Emplace",
                    "service", "service cannot be a null reference");

            services[typeid(T)] = (void *)service.Get();
            return *this;
        }

        /// Removes an object ptr of type T that was previously passed into
        /// the function. Please remember to manage cleanup for that object,
        /// as this function does not manage deletion, etc.
        /// @tparam T the type of object pointer to remove
        /// @returns reference to this ServiceContainer for chaining function calls.
        template <typename T>
        ServiceProvider &Remove()
        {
            auto it = services.find(typeid(T));
            if (it != services.end())
                services.erase(it);
            return *this;
        }

        /// Removes all objects from the services container.
        ServiceProvider &RemoveAll()
        {
            services.clear();
            return *this;
        }

        // ========== Getters =================================================

        /// Gets a reference to an object of type T in the container.
        /// Reference will be null if none exists within.
        /// @tparam T the type of object ptr to retrieve.
        template <typename T>
        [[nodiscard]] Ref<T> Get()
        {
            auto it = services.find(typeid(T));
            return (it == services.end()) ? Ref<T>() : Ref<T>((T *)it->second);
        }

        template <typename T>
        [[nodiscard]] CRef<T> Get() const
        {
            auto it = services.find(typeid(T));
            return (it == services.end()) ? Ref<T>() : Ref<T>((T *)it->second);
        }

        /// Gets a reference to a stored object of type T. Reference will be null if
        /// one does not exist in the container.
        /// Intended to be used if a service is not guaranteed to be in this obj.
        /// @param service [out] service to get
        /// @returns true, if pointer was found; false, if not.
        template <typename T>
        bool TryGet(Ref<T> &service)
        {
            auto ref = Ref<T>(Get<T>());
            service = ref;
            return static_cast<bool>(ref);
        }

        template <typename T>
        bool TryGet(CRef<T> &service) const
        {
            auto ref = Ref<T>(Get<T>());
            service = ref;
            return static_cast<bool>(ref);
        }

        /// Gets the number of services stored
        [[nodiscard]] size_t Size() const
        {
            return services.size();
        }

        /// Checks whether the container is empty
        [[nodiscard]] bool Empty() const
        {
            return services.empty();
        }

    private:
        /// Internal map of object services
        std::map<std::type_index, void *> services;
    };
}
