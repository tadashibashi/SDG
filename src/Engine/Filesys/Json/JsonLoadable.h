#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Filesys/Path.h>
#include <nlohmann/json_fwd.hpp>

namespace SDG
{
    using json = nlohmann::json;
    class JsonLoadable
    {
        struct Impl;
    public:
        JsonLoadable(const String &typeName);
        JsonLoadable(const JsonLoadable &loadable);
        JsonLoadable &operator=(const JsonLoadable &loadable);

        virtual ~JsonLoadable();

        void LoadJson(const Path &path);
        void LoadJson(const json &j);

        [[nodiscard]] json &Json();
        [[nodiscard]] const json &Json() const;
        [[nodiscard]] const String &TypeName() const;
    private:
        virtual void LoadJsonImpl(const json &j) = 0;
        Impl *impl;
    };
}
