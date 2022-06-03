/*!
 * @file String.h
 * @namespace SDG
 * @class String
 * Functionality is similar to std::string, with some convenience extensions.
 * 
 */
#pragma once
#include <SDG/Debug/LogImpl.h>

#include <SDG/Lib/Private/Fmt.h>

#include <functional>
#include <iterator>
#include <string>
#include <utility>

using std::swap;

namespace SDG
{
    class String
    {
    public:
        String();
        String(size_t initCap);
        String(const String &str);
        String(const std::string &str);
        String(const char *str);
        String(const char *str, size_t count);
        ~String();

        typedef char *Iterator;
        typedef const char *ConstIterator;

        /// Assignment from other strings
        String &operator = (const String &str);
        String &operator = (const std::string &str);
        String &operator = (const char *cstr);

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

        [[nodiscard]] size_t Find(const char *str, size_t startingAt = 0) const;

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

        [[nodiscard]] const char *Cstr() const;

        /// Helper to create an std::string copy
        [[nodiscard]] std::string Str() const;

        /// Gets the character length of the String
        [[nodiscard]] size_t Length() const;

        /// Size of the internal memory.
        [[nodiscard]] size_t Capacity() const;

        /// Whether the String has any characters in it.
        /// More efficient than checking Length() == 0
        [[nodiscard]] bool Empty() const;

        /// Swaps internals of this String with another
        String &Swap(String &other);

        /// Reserves the amount of characters inside the String to help prevent
        /// unnecessary reallocations. Expands the Capacity if greater, but
        /// will not affect the String if it is smaller than the Capacity.
        String &Reserve(size_t size);
        String &Append(const String &str);
        String &Append(const std::string &str);
        String &Append(const char *str);
        String &Append(char c);
        /// Appends a String to a c-string.
        String &Append(const char *str, size_t size);

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
        
        /// Creates a substring from the String
        /// @param index the index that will begin the substring
        /// @param count the number of characters to copy to the substring,
        /// starting its count from the index position. A value of
        /// String::NullPos means that the rest of the String starting
        /// from the index will be copied.
        String Substr(size_t index, size_t count = NullPos) const;

        String &Clear();

        template <typename...Args>
        static String Format(const char *format, Args &&...args)
        {
            auto out = fmt::memory_buffer();
            fmt::format_to(std::back_inserter(out), format, 
                std::forward<Args>(args)...);
            return { out.data(), out.size()};
        }

        /// Default position value
        static const size_t NullPos;
        /// Default minimum capacity the String starts with.
        static const size_t DefaultCap;

        /// Creates a hash value for quick comparison.
        /// Please be sure to cache this value, since hash generation
        /// takes more computing than direct String comparison would.
        [[nodiscard]] uint64_t Hash() const;

        // operators
        [[nodiscard]] char &operator[] (size_t index);
        [[nodiscard]] const char operator[] (size_t index) const;

        [[nodiscard]] bool operator == (const String &other) const;
        [[nodiscard]] bool operator != (const String &other) const;
        [[nodiscard]] bool operator == (const std::string &other) const;
        [[nodiscard]] bool operator != (const std::string &other) const;
        [[nodiscard]] bool operator == (const char *other) const;
        [[nodiscard]] bool operator != (const char *other) const;
        String &operator += (const String &other);
        String &operator += (const std::string &other);
        String &operator += (const char *other);
        String &operator += (char c);

        // iterators
        Iterator begin() { return str_; }
        Iterator end()   { return end_; }
        ConstIterator cbegin() { return str_; }
        ConstIterator cend()   { return end_; }

        template <typename Ostream>
        friend Ostream &operator << (Ostream &os, const String &str)
        {
            os << str.Cstr();
            return os;
        }

    private:
        /// Safely expands the String's internal capacity.
        void Expand(size_t size);
        /// Called privately to initialize String. Useful for data
        /// structures with quick length calculation.
        void Allocate(const char *str, size_t size);
        /// Initializes an empty string with an initial reserved capacity
        void Allocate(size_t cap);
        /// Sets a String that has already initialized.
        void Reallocate(const char *str, size_t size);

        /// Internal string ptrs
        char *str_, *end_, *full_;
    };

    String operator + (const String &str1, const String &str2);
    String operator + (const String &str1, const std::string &str2);
    String operator + (const String &str1, const char *str2);
    String operator + (const char *str1, const String &str2);

    /// Accepts two c-strings and concatenates them into an String
    String Strcat(const char *str1, const char *str2);

    std::string operator + (const std::string &str1, const String &str2);
    bool operator == (const std::string &str1, const String &str2);
    bool operator != (const std::string &str1, const String &str2);
}

inline void swap(SDG::String &a, SDG::String &b)
{
    a.Swap(b);
}
