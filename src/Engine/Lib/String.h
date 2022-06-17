/*!
 * @file String.h
 * @namespace SDG
 * @class String
 * Functionality is similar to std::string, with some convenience extensions.
 * 
 */
#pragma once
#include <Engine/Lib/Array.h>
#include <Engine/Lib/RAIterator.h>
#include <Engine/Lib/ConstRAIterator.h>

#include <iosfwd>
#include <functional>
#include <string>

namespace SDG
{
    class String
    {
    public:
        typedef RAIterator<char> Iterator;
        typedef ConstRAIterator<char> ConstIterator;

        String();
        explicit String(size_t initCap);
        String(const String &str);
        String(String &&str) noexcept;
        String(const std::string &str);
        String(const char *str);
        String(const char *str, size_t count);
        String(const class StringView &view);
        ~String();

    public:
        // ===== Public Constants =====================================================================================

        /// Default position value
        static const size_t NullPos;
        /// Default minimum capacity the String starts with.
        static const size_t DefaultCap;

        // ===== Modifiers ============================================================================================

        /// Assignment from other strings
        String &operator = (const String &str);
        String &operator = (String &&str) noexcept;
        String &operator = (const std::string &str);
        String &operator = (const char *cstr);
        String &operator = (const class StringView &view);
        String &Assign(const char *str, size_t length);
        String &Assign(const char *str);
        String &Assign(const String &str);
        String &Assign(const class StringView &str);
        String &Assign(const std::string &str);

        String &operator += (const String &other);
        String &operator += (const std::string &other);
        String &operator += (const char *other);
        String &operator += (char c);
        String &Append(const String &str);
        String &Append(const std::string &str);
        String &Append(const char *str);
        String &Append(char c);
        String &Append(const char *str, size_t size);

        String &Insert(const char *str, size_t strLength, size_t index);
        String &Insert(const String &str, size_t index);
        String &Insert(const class StringView &str, size_t index);

        /// Reserves the amount of characters inside the String to help prevent
        /// unnecessary reallocations. Expands the Capacity if greater, but
        /// will not affect the String if it is smaller than the Capacity.
        String &Reserve(size_t size);

        /// Erases a character from the String at the specified index.
        String &Erase(size_t index);

        /// Erases a range of characters from the String.
        String &Erase(Iterator begin, Iterator end);

        /// Erases characters determined by a predicate function.
        /// @param func the callback that receives each char from the String, 
        /// one at a time, in which the return value determines whether the
        /// char will remain in the String. Return true to indicate erasure,
        /// and false to keep it.
        String &EraseIf(const std::function<bool(char)> &func);
        /// Swaps internals of this String with another
        String &Swap(String &other) noexcept;

        String &Clear();

        // ===== Querying =============================================================================================

        [[nodiscard]] char &operator[] (size_t index);
        [[nodiscard]] const char operator[] (size_t index) const;

        /// Finds first occurance based on a callback function: returning true indicates
        /// that the target has been found, and FindFirstOf returns the index it occurs.
        [[nodiscard]] size_t FindFirstOf(size_t startingAt, const std::function<bool(char)> &func) const;

        /// Finds first occurance of a char.
        /// @param c - the char to search for
        /// @param startingAt - the index to start searching from, default: 0
        /// @returns the index where char c was found in the string, or 
        /// String::NullPos if it wasn't found.
        [[nodiscard]] size_t FindFirstOf(char c, size_t startingAt = 0) const;

        /// Finds first occurance of any char inside a list.
        /// @param list - a list of chars in which each char will be checked against
        /// @param startingAt - the position in the string to start checking at
        /// @returns the index where a matching char was found or
        ///          String::NullPos if none was found.
        [[nodiscard]] size_t FindFirstOf(const char *list, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstNotOf(char c, size_t startingAt = 0) const;
        [[nodiscard]] size_t FindFirstNotOf(const char *list, size_t startingAt = 0) const;

        /// Finds the nth occurance of a char in the String. n should be >= 1 (n=0 -> NullPos)
        /// If the nth occurance could not be found, String::NullPos is returned.
        [[nodiscard]] size_t FindNthOf(char c, size_t n, size_t startingAt = 0) const;

        /// Finds the nth occurance of any char in the list parameter. n should be >= 1 (n=0 -> NullPos)
        /// If the nth occurance could not be found, String::NullPos is returned.
        [[nodiscard]] size_t FindNthOf(const char *list, size_t n, size_t startingAt = 0) const;

        [[nodiscard]] size_t Find(const char *str, size_t startingAt = 0) const;

        /// Finds first occurance based on a callback function: returning true indicates
        /// that the target has been found, and FindFirstOf returns the index it occurs.
        [[nodiscard]] size_t FindLastOf(size_t startingAt, const std::function<bool(char)> &func) const;

        /// Finds last occurance of a char
        /// @param c the char to search for
        /// @param startingAt the index to start searching from. Setting it to
        /// NullPos searches from the end, which is this param's default value.
        /// @returns index or String::NullPos if it wasn't found.
        [[nodiscard]] size_t FindLastOf(char c, size_t startingAt = NullPos) const;

        /// Finds last occurance of any char inside a list.
        /// @param list - a list of chars in which each char will be checked against
        /// @param startingAt - the position in the string to start checking at
        /// @returns the index where a matching char was found or
        ///          String::NullPos if none was found.
        [[nodiscard]] size_t FindLastOf(const char *list, size_t startingAt = NullPos) const;
        [[nodiscard]] size_t FindLastNotOf(char c, size_t startingAt = NullPos) const;
        [[nodiscard]] size_t FindLastNotOf(const char *list, size_t startingAt = NullPos) const;

        [[nodiscard]] Iterator FindIf(const std::function<bool(char)> &func) const;

        /// Separates String into an array of Strings. Split by whitespace.
        [[nodiscard]] Array<String> Split() const;

        /// Separates a String into an array of Strings depending on a callback:
        /// When the callback returns true, a split occurs. 
        /// Callback signature:
        /// [](char currentChar, size_t charIndex)->bool {...}
        [[nodiscard]] Array<String> SplitIf(const std::function<bool(char, size_t)> &func) const;

        /// Separates String into an array of Strings. 
        /// Split by occurance of char c.
        [[nodiscard]] Array<String> Split(char c) const;

        /// Separates String into an array of Strings. 
        /// Split by any occurance of a char from chars.
        [[nodiscard]] Array<String> Split(const char *chars) const;

        /// Creates a substring from the String
        /// @param index the index that will begin the substring
        /// @param instances the number of characters to copy to the substring,
        /// starting its instances from the index position. A value of
        /// String::NullPos means that the rest of the String starting
        /// from the index will be copied.
        [[nodiscard]] String Substr(size_t index, size_t count = NullPos) const;

        [[nodiscard]] String Substr(Iterator it, size_t count = NullPos) const;

        [[nodiscard]] const char *Cstr() const;

        /// Gets the character length of the String
        [[nodiscard]] size_t Length() const;

        /// Size of the internal memory.
        [[nodiscard]] size_t Capacity() const;

        /// Whether the String has any characters in it.
        /// More efficient than checking Length() == 0
        [[nodiscard]] bool Empty() const;

        /// Removes characters from the beginning of the string
        /// @param list - a list of chars to trim off the beginning; if null, whitespace will be trimmed.
        [[nodiscard]] String &Trim(const char *list = nullptr);
        [[nodiscard]] String &TrimEnd(const char *list = nullptr);


        // ===== Comparison ===========================================================================================

        [[nodiscard]] bool operator == (const String &other) const;
        [[nodiscard]] bool operator != (const String &other) const;
        [[nodiscard]] bool operator == (const std::string &other) const;
        [[nodiscard]] bool operator != (const std::string &other) const;
        [[nodiscard]] bool operator == (const char *other) const;
        [[nodiscard]] bool operator != (const char *other) const;

        [[nodiscard]] bool operator < (const String &other) const;
        [[nodiscard]] bool operator > (const String &other) const;
        [[nodiscard]] bool operator >= (const String &other) const { return !operator < (other); }
        [[nodiscard]] bool operator <= (const String &other) const { return !operator > (other); }

        
        // ===== Iterators ============================================================================================

        [[nodiscard]] Iterator begin() { return Iterator(str_, str_, end_); }
        [[nodiscard]] const Iterator begin() const { return Iterator(str_, str_, end_); }
        [[nodiscard]] Iterator end() { return Iterator(end_, str_, end_); }
        [[nodiscard]] const Iterator end() const { return Iterator(end_, str_, end_); }
        [[nodiscard]] ConstIterator cbegin() const { return ConstIterator(str_, str_, end_); }
        [[nodiscard]] ConstIterator cend() const  { return ConstIterator(end_, str_, end_); }

        // ===== Conversion ===========================================================================================

        /// Creates a hash value for quick comparison.
        /// Please be sure to cache this value, since hash generation
        /// takes more computing than direct String comparison would.
        [[nodiscard]] uint64_t Hash() const;

        /// Creates string using the fmt library
        template <typename...Args>
        [[nodiscard]] static String Format(const char *format, Args ...args);

        /// Converts a String to a numeric value. 
        /// Prepending and post-pending symbols besides releveant ones are ignored
        template <typename T>
        [[nodiscard]] T ToNumber(uint8_t base = 10u) const;

        /// Helper to create an std::string copy
        [[nodiscard]] std::string Str() const;
        [[nodiscard]] operator std::string() const { return Str(); }

    private:
        /// Safely expands the String's internal capacity.
        void Expand(size_t size);
        /// Initializes String memory and copies a c-string with specified length
        void Allocate(const char *str, size_t size);
        /// Initializes an empty string with a set memory capacity
        void Allocate(size_t cap);
        /// Sets a String that has already initialized.
        void Reallocate(const char *str, size_t size);

        /// Internal string ptrs
        char *str_, *end_, *full_;
    };

    std::ostream &operator << (std::ostream &os, const String &str);
    String operator + (const String &str1, const String &str2);
    String operator + (const String &str1, const std::string &str2);
    String operator + (const String &str1, const char *str2);
    String operator + (const char *str1, const String &str2);

    /// Accepts two c-strings and concatenates them into an String
    String Strcat(const char *str1, const char *str2);

    std::string operator + (const std::string &str1, const String &str2);
    bool operator == (const std::string &str1, const String &str2);
    bool operator != (const std::string &str1, const String &str2);

    /// Converts T to a String equivalent. Must T must have ostream operator overridden with LogImpl.h included.
    template <typename T>
    String ToString(const T &t);

    struct StringHashComparer
    {
        bool operator() (const String &lhs, const String &rhs) const
        {
            return lhs.Hash() < rhs.Hash();
        }
    };

    [[nodiscard]] String operator "" _s(const char *);
}

#include <utility>
using std::swap;

inline void swap(SDG::String &a, SDG::String &b) { a.Swap(b); }

#include "String.inl"
