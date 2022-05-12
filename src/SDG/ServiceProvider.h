#pragma once
#include <typeindex>
#include <map>
#include <SDG/Ref.h>

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
        Ref<T> Get() const
        {
            auto it = services.find(typeid(T));
            return (it == services.end()) ? Ref<T>() : Ref<T>((T *)it->second);
        }

        /// Gets a pointer to a stored object of type T, or nullptr if
        /// one does not exist in the container.
        /// Intended to be used if a service is not guaranteed to be in this obj.
        /// @param service [out] service to get
        /// @returns true, if pointer was found; false, if not.
        template <typename T>
        bool TryGet(Ref<T> &service) const
        {
            auto ref = Ref<T>(Get<T>());
            service = ref;
            return static_cast<bool>(ref);
        }

        /// Stores an object ptr of type T that is passed into the function.
        /// You as the user maintain responsibility for its memory management.
        /// @param service The object ptr to store
        /// @returns reference to this ServiceContainer for chaining function calls.
        template <typename T>
        ServiceProvider &Emplace(Ref<T> service)
        {
            static_assert(!std::is_null_pointer_v<T>, "must not pass explicit nullptr to container");
            if (!service.Get())
                throw NullReferenceException(typeid(T));

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

        /// Gets the number of services stored
        size_t Size() const
        {
            return services.size();
        }

        /// Checks whether the container is empty
        bool Empty() const
        {
            return services.empty();
        }

    private:
        // internal map of object ptr services
        std::map<std::type_index, void *> services;
    };
}
