#pragma once
#include <SDG/Debug/LogImpl.h>
#include <SDG/String.h>

#include <cstddef>
#include <SDG/Debug/LogImpl.h>

namespace SDG
{
    class StringView
    {
    public:
        /// Empty string
        StringView();
        StringView(const String &str);
        StringView(const std::string &str);
        StringView(const char *str);
        StringView(const char *str, size_t size);

        StringView &operator = (const StringView &str);
        StringView &operator = (const String &str);
        StringView &operator = (const std::string &str);
        StringView &operator = (const char *str);

        static const size_t NullPos;

        [[nodiscard]] size_t Length() const;
        [[nodiscard]] bool Empty() const;

        /// Copies string to an SDG::String
        [[nodiscard]]
        String Str() const;

        [[nodiscard]] size_t Find(const char *pattern, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstOf(char c, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstOf(const char *list, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindLastOf(char c, size_t startingAt = NullPos) const;
        [[nodiscard]] size_t FindLastOf(const char *list, size_t startingAt = NullPos) const;

        [[nodiscard]]
        StringView Substr(size_t index, size_t count = NullPos) const;

        /// Gets the internal c-string
        [[nodiscard]]
        const char *Cstr() const;

        /// Swaps the internals of one StringView with another
        StringView &Swap(StringView &other);

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

        template<typename Ostream>
        friend Ostream &operator << (Ostream &os, const StringView &view)
        {
            for (const char *p = view.str_, *end = view.str_ + view.size_;
                p != end; ++p)
                os << *p;

            return os;
        }

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
    String operator + (const char *b, const StringView &a);
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
