#include "ServiceProvider.h"
#include <Engine/Exceptions/InvalidArgumentException.h>

namespace SDG
{
    template <typename T>
    ServiceProvider &ServiceProvider::Emplace(Ref<T> service)
    {
        static_assert(!std::is_null_pointer_v<T>,
            "must not pass explicit nullptr to container");
        if (!service.Get())
            throw InvalidArgumentException("ServiceProvider::Emplace",
                "service", "service cannot be a null reference");

        services[typeid(T)] = (void *)service.Get();
        return *this;
    }

    template <typename T>
    ServiceProvider &ServiceProvider::Remove()
    {
        auto it = services.find(typeid(T));
        if (it != services.end())
            services.erase(it);
        return *this;
    }

    template <typename T>
    Ref<T> ServiceProvider::Get()
    {
        auto it = services.find(typeid(T));
        return (it == services.end()) ? Ref<T>() : Ref<T>((T *)it->second);
    }

    template <typename T>
    bool ServiceProvider::TryGet(Ref<T> &service)
    {
        auto ref = Ref<T>(Get<T>());
        service = ref;
        return static_cast<bool>(ref);
    }
}
