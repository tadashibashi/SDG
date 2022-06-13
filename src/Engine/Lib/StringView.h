#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Exceptions/Fwd.h>

#include <cstddef>
#include <functional>
#include <iosfwd>

namespace SDG
{
    /// Quickly peruse a string of chars
    class StringView
    {
    public:
        typedef String::ConstIterator ConstIterator;

        /// Empty string
        StringView();
        StringView(const String &str);
        StringView(const std::string &str);
        StringView(const char *cstr);
        StringView(const char *str, size_t size);

        StringView &operator = (const StringView &str);
        StringView &operator = (const String &str);
        StringView &operator = (const std::string &str);
        StringView &operator = (const char *cstr);

        /// Definition of a null position, used as a default or false
        /// return  value in the Find* functions.
        static const size_t NullPos;

        /// Length of the string
        [[nodiscard]] size_t Length() const;
        /// Whether the string is empty
        [[nodiscard]] bool Empty() const;

        /// Copies string to an SDG::String
        [[nodiscard]]
        String Str() const;

        /// Find a pattern within the string. Returns the position it was first found
        /// or NullPos if it was not found
        /// @param pattern - the pattern to search for
        /// @param startingAt - the position to start searching from
        [[nodiscard]] size_t Find(const char *pattern, size_t startingAt = 0) const;

        [[nodiscard]] ConstIterator FindIf(const std::function<bool(char)> &func) const;
        
        /// Finds the first occurance of a character.
        /// @param c - the character to find
        /// @param startingAt - the position to start search from
        [[nodiscard]] size_t FindFirstOf(char c, size_t startingAt = 0) const;
        
        /// Finds the first occurance of any character in a list.
        /// @param list - the list of characters to search for.
        /// @param startingAt - the position to start search from
        [[nodiscard]] size_t FindFirstOf(const char *list, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstOf(size_t startingAt, const std::function<bool(char)> &func) const;
        [[nodiscard]] size_t FindFirstNotOf(char c, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstNotOf(const char *list, size_t startingAt = 0) const;
        
        /// Finds the last occurance of a character.
        /// @param c - the character to find
        /// @param startingAt - the position to start search from
        [[nodiscard]] size_t FindLastOf(char c, size_t startingAt = NullPos) const;
        
        /// Finds the last occurance of any character in a list.
        /// @param list - the list of characters to search for.
        /// @param startingAt - the position to start search from
        [[nodiscard]] size_t FindLastOf(const char *list, size_t startingAt = NullPos) const;
        [[nodiscard]] size_t FindLastOf(size_t startingAt, const std::function<bool(char)> &func) const;

        [[nodiscard]] size_t FindLastNotOf(char c, size_t startingAt = NullPos) const;
        [[nodiscard]] size_t FindLastNotOf(const char *list, size_t startingAt = NullPos) const;

        [[nodiscard]] ConstIterator begin() const;
        [[nodiscard]] ConstIterator end() const;
        [[nodiscard]] ConstIterator cbegin() const;
        [[nodiscard]] ConstIterator cend() const;

        /// Makes a string from within the string. This operation is much
        /// faster than a regular String, which must allocate memory
        /// each time a substring is created. StringView does not allocate.
        [[nodiscard]]
        StringView Substr(size_t index, size_t count = NullPos) const;
        [[nodiscard]]
        StringView Substr(ConstIterator it, size_t count = NullPos) const;

        StringView &Trim(const char *list = nullptr);
        StringView &TrimEnd(const char *list = nullptr);

        /// Gets the internal c-string
        [[nodiscard]]
        const char *Data() const;

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

        [[nodiscard]]
        char operator [] (unsigned i) const;

        template<typename T>
        [[nodiscard]] T ToNumber(int base = 10) const;

    private:
        const char *str_;
        size_t size_;

        bool StrCmp(const char *s, size_t length) const;
    };

    std::ostream &operator << (std::ostream &os, const StringView &view);

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

#include "StringView.inl"
