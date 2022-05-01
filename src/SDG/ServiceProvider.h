#pragma once
#include <typeindex>
#include <map>

namespace SDG
{
    /// Generic container that can store one object pointer per type.
    /// ServiceContainer does not own these pointers, and the responsibility
    /// to manage their memory remains with the user who emplaces each service.
    /// This generically allows users to store specific data
    /// structures that other components are dependent on, without tying them
    /// to the the class that owns it.
    class ServiceProvider {
    public:
        /// Gets a pointer to a stored object of type T, or nullptr if
        /// one does not exist in the container.
        /// @tparam T the type of object ptr to retrieve.
        template <typename T>
        T *Get() const
        {
            auto it = services.find(typeid(T));
            return (it == services.end()) ? nullptr : (T *)it->second;
        }

        /// Gets a pointer to a stored object of type T, or nullptr if
        /// one does not exist in the container.
        /// Intended to be used if a service is not guaranteed to be in this obj.
        /// @param service [out] service to get
        /// @returns true, if pointer was found; false, if not.
        template <typename T>
        bool TryGet(T **service) const
        {
            T *s = Get<T>();
            *service = s;
            return static_cast<bool>(s);
        }

        /// Stores an object ptr of type T that is passed into the function.
        /// You as the user maintain responsibility for its memory management.
        /// @param service The object ptr to store
        /// @returns reference to this ServiceContainer for chaining function calls.
        template <typename T>
        ServiceProvider &Emplace(T *service)
        {
            services[typeid(T)] = service;
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

    private:
        // internal map of object ptr services
        std::map<std::type_index, void *> services;
    };
}
