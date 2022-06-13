#pragma once
#include <cstdint>

#include "Array.h"
#include "Struct.h"

namespace SDG
{
    class String;
}

namespace SDG::Dynamic
{
    class Struct;
    class Array;

    enum class Type
    {
        Null,
        Real, // a double
        String,
        Struct,
        Array
    };

    String GetTypeName(Type type);

    class Object
    {
        struct Impl;
    public:

        Object();
        Object(const Object &obj);
        Object(const Struct &s);
        explicit Object(const Array &arr);
        Object(const String &str);
        Object(double d);
        ~Object();

        //template <typename... Args>
        //Object(Args&&... args) : impl()
        //{
        //    NewImpl();
        //    Assign(Array({ args... }));
        //}
        
        /// ===== Interface with other types =====

        [[nodiscard]] const double &AsReal() const;
        [[nodiscard]] double &AsReal();
        [[nodiscard]] const String &AsString() const;
        [[nodiscard]] String &AsString();
        [[nodiscard]] const Struct &AsStruct() const;
        [[nodiscard]] Struct &AsStruct();
        [[nodiscard]] const Array &AsArray() const;
        [[nodiscard]] Array &AsArray();

        [[nodiscard]] Type GetType() const;
        [[nodiscard]] bool Is(Type type) const;

        Object &operator += (double n);
        Object &operator -= (double n);
        Object &operator *= (double n);
        Object &operator /= (double n);
        Object &operator %= (double n);

        Object &operator += (const String &str);

        Object &operator = (double n)                { Assign(n); return *this; }
        Object &operator = (const Struct &s)         { Assign(s); return *this; }
        Object &operator = (const String &str)       { Assign(str); return *this; }
        Object &operator = (const Object &other)     { Assign(other); return *this; }

        [[nodiscard]] Object &operator [] (const String &key);
        [[nodiscard]] const Object &operator [] (const String &key) const;
        [[nodiscard]] Object &operator [] (size_t index);
        [[nodiscard]] const Object &operator [] (size_t index) const;

        [[nodiscard]] bool operator==(const Object &other) const;
        [[nodiscard]] bool operator==(double d) const;
        [[nodiscard]] bool operator==(const String &str) const;
        [[nodiscard]] bool operator==(const Struct &s) const;
        [[nodiscard]] bool operator==(const Array &arr) const;

    private:
        Impl *impl;
        void Assign(const Object &other);
        void Assign(const Struct &s);
        void Assign(const Array &arr);
        void Assign(const String &str);
        void Assign(double d);
        void AssignNull();
        void NewImpl();
    };

    extern const Object null;

    typedef Object var;
}

#include <Engine/Debug/LogImpl.h>
#include <sstream>
std::ostream &operator<<(std::ostream &os, const SDG::Dynamic::Object &obj);

template<>
struct fmt::formatter<SDG::Dynamic::Object>
{
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const SDG::Dynamic::Object &input, FormatContext &ctx) -> decltype(ctx.out()) {
        std::stringstream ss;
        ss << input;
        return fmt::format_to(ctx.out(), "{}", ss.str());
    }
};
