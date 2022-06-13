#include "JsonLoadable.h"

#include <Engine/Filesys/Json.h>
#include <Engine/Debug.h>

#include <exception>

namespace SDG
{
    struct JsonLoadable::Impl
    {
        Impl(const String &typeName) : typeName(typeName), j() { }
        String typeName;
        json j;
    };

    JsonLoadable::JsonLoadable(const String &name) : impl(new Impl(name)) { }
    JsonLoadable::JsonLoadable(const JsonLoadable &loadable) : impl(new Impl(loadable.impl->typeName)) 
    {
        impl->j = loadable.impl->j;
    }

    JsonLoadable &JsonLoadable::operator=(const JsonLoadable &loadable)
    {
        impl->typeName = loadable.impl->typeName;
        impl->j = loadable.impl->j;
        return *this;
    }

    JsonLoadable::~JsonLoadable() { delete impl; }

    void JsonLoadable::LoadJson(const Path &path)
    {
        LoadJson(OpenJson(path));
    }

    const String &JsonLoadable::TypeName() const
    {
        return impl->typeName;
    }

    const json &JsonLoadable::Json() const
    {
        return impl->j;
    }

    json &JsonLoadable::Json()
    {
        return impl->j;
    }

    void JsonLoadable::LoadJson(const json &j)
    {
        try {
            LoadJsonImpl(j);
        }
        catch (const std::exception &e)
        {
            SDG_Core_Err("{}::Load: failed to load json: {}", impl->typeName, e.what());
        }
        catch (...)
        {
            SDG_Core_Err("{}::Load: failed to load json: unknown error", impl->typeName);
            throw;
        }

        impl->j = j;
    }
}
