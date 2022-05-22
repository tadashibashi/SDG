#pragma once
#include <SDG/Debug/LoggingImpl.h>
#include <SDG/String.h>

#include <cstddef>

namespace SDG
{
    class StringView
    {
    public:
        /// Empty string
        StringView();
        explicit StringView(const String &str);
        explicit StringView(const std::string &str);
        explicit StringView(const char *str);
        StringView(const char *str, size_t size);

        StringView &operator = (const StringView &str);
        StringView &operator = (const String &str);
        StringView &operator = (const std::string &str);
        StringView &operator = (const char *str);

        size_t Length() const;

        /// Copies string to an SDG::String
        [[nodiscard]]
        String Str() const;
        /// Gets the internal c-string
        [[nodiscard]]
        const char *Cstr() const;

        [[nodiscard]]
        bool operator == (const StringView &s) const;
        [[nodiscard]]
        bool operator != (const StringView &s) const;
        [[nodiscard]]
        bool operator == (const String &s) const;
        [[nodiscard]]
        bool operator != (const String &s) const;
        [[nodiscard]]
        bool operator == (const std::string &s) const;
        [[nodiscard]]
        bool operator != (const std::string &s) const;
        [[nodiscard]]
        bool operator == (const char *s) const;
        [[nodiscard]]
        bool operator != (const char *s) const;

        typedef const char *Iterator;
        [[nodiscard]] Iterator begin();
        [[nodiscard]] Iterator end();

        [[nodiscard]]
        char operator [] (unsigned i) const;
    private:
        const char *str_;
        size_t size_;

        bool StrCmp(const char *s, size_t length) const;
    };

    [[nodiscard]]
    String operator + (const StringView &a, const StringView &b);
    [[nodiscard]]
    String operator + (const StringView &a, const String &b);
    [[nodiscard]]
    String operator + (const StringView &a, const std::string &b);
    [[nodiscard]]
    String operator + (const StringView &a, const char *b);
    [[nodiscard]]
    String operator + (const String &a, const StringView &b);
    [[nodiscard]]
    std::string operator + (const std::string &a, const StringView &b);

    [[nodiscard]]
    bool operator == (const String &a, const StringView &b);
    [[nodiscard]]
    bool operator == (const std::string &a, const StringView &b);
    [[nodiscard]]
    bool operator == (const char *a, const StringView &b);
    [[nodiscard]]
    bool operator != (const String &a, const StringView &b);
    [[nodiscard]]
    bool operator != (const std::string &a, const StringView &b);
    [[nodiscard]]
    bool operator != (const char *a, const StringView &b);


}
