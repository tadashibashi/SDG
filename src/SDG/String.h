/*!
 * @file String.h
 * @namespace SDG
 * @class String
 * Functionality is similar to std::string, with some convenience extensions.
 * 
 */
#pragma once
#include <string>
#include <functional>
#include <iosfwd>

namespace SDG
{
    class String
    {
    public:
        String();
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

        /// Finds first occurance of a char
        /// @param c the char to search for
        /// @param startingAt the index to start searching from, default: 0
        /// @returns index or String::NullPos if it wasn't found.
        [[nodiscard]] size_t FindFirstOf(char c, size_t startingAt = 0) const;

        /// Finds last occurance of a char
        /// @param c the char to search for
        /// @param startingAt the index to start searching from. Setting it to
        /// NullPos searches from the end, which is this param's default value.
        /// @returns index or String::NullPos if it wasn't found.
        [[nodiscard]] size_t FindLastOf(char c, size_t startingAt = NullPos) const;

        [[nodiscard]] const char *Cstr() const;
        [[nodiscard]] std::string Str() const;

        [[nodiscard]] size_t Length() const;
        [[nodiscard]] size_t Capacity() const;
        [[nodiscard]] bool Empty() const;

        /// Reserves the amount of characters inside the String to help prevent
        /// unnecessary reallocations. Expands the Capacity if greater, but
        /// will not affect the String if it is smaller than the Capacity.
        String &Reserve(size_t size);
        String &Append(const String &str);
        String &Append(const std::string &str);
        String &Append(const char *str);
        String &Append(char c);

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
        String Substr(size_t index, size_t count = NullPos);

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
        [[nodiscard]] bool operator == (const String &other);
        [[nodiscard]] bool operator == (const std::string &other);
        [[nodiscard]] bool operator == (const char *other);
        String &operator += (const String &other);
        String &operator += (const std::string &other);
        String &operator += (const char *other);
        String &operator += (char c);

        // iterators
        Iterator begin() { return str_; }
        Iterator end()   { return end_; }
        ConstIterator cbegin() { return str_; }
        ConstIterator cend()   { return end_; }



    private:
        /// Appends a String to a c-string.
        void Append(const char *str, size_t size);
        /// Safely expands the String's internal capacity.
        void Expand(size_t size);
        /// Called privately to initialize String.
        void Allocate(const char *str, size_t size);
        /// Sets a String that has already initialized.
        void Reallocate(const char *str, size_t size);

        /// Internal string ptrs
        char *str_, *end_, *full_;
    };
}

SDG::String operator + (const SDG::String &str1, const SDG::String &str2);
SDG::String operator + (const SDG::String &str1, const std::string &str2);
SDG::String operator + (const SDG::String &str1, const char *str2);
SDG::String operator + (const char *str1, const SDG::String &str2);

std::string operator + (const std::string &str1, const SDG::String &str2);
bool operator == (const std::string &str1, const SDG::String &str2);

std::ostream &operator << (std::ostream &os, const SDG::String &str);
