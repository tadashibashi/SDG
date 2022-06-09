#pragma once
#include <Engine/Graphics/Color.h>
#include <Engine/Lib/String.h>

#include <any>
#include <variant>
#include <cstddef>

namespace SDG::Tiled
{
    struct Property
    {
    private:
        struct Impl;
    public:
        /// Type of the property.
        enum class Type {
            Null,
            String, // (default)
            Int,
            Float,
            Bool,   // since 1.6, "true", "false"
            Color,  // #aarrggbb, must translate to our native color format
            File,   // added in 0.17, string with relative filepath from the .tmx file
            Object, // added in 1.4, object index e.g. "1"
            Class   // added in 1.8
        };

        Property();
        Property(const String &name, enum Type type, const std::any &value);
        ~Property();

        const String &Name() const;
        enum Type Type() const;
        
        const String &StringValue() const;
        int IntValue() const;
        float FloatValue() const;
        bool BoolValue() const;
        const Color &ColorValue() const;
        const String &FileValue() const;
        size_t ObjectValue() const;
        const struct Class &ClassValue() const;

        explicit operator bool() const;

    private:
        Impl *impl;
    };
}