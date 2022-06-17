/// String implementation file
#include "String.h"
#include "StringView.h"

#include <Engine/Debug.h>
#include <Engine/Exceptions.h>
#include <Engine/Math/Math.h>

#include <algorithm>
#include <cstdlib>
#include <utility>

// ===== C-string function helpers ============================================
static char *StrMalloc(size_t size);
static void StrFree(char *str);
static char *StrRealloc(char *str, size_t size);
static bool StringsEqual(const SDG::String &str, const char *cstr, size_t size);

namespace SDG
{
    const size_t String::DefaultCap = 16; // actual container size set + 1 for terminator.
    const size_t String::NullPos    = SIZE_MAX;

    // ===== Main implementation ==============================================

    void
    String::Allocate(const char *str, size_t size)
    {
        size_t cap = std::max(size * 2 + 1, DefaultCap + 1);
        str_ = StrMalloc(cap);
        end_ = str_ + size;
        full_ = str_ + cap;

        memcpy(str_, str, size);
        *end_ = '\0';
    }

    void
    String::Allocate(size_t cap)
    {
        cap = std::max(cap + 1, DefaultCap + 1);
        str_ = StrMalloc(cap);
        end_ = str_;
        full_ = str_ + cap;
        *end_ = '\0';
    }

    void
    String::Reallocate(const char *str, size_t size)
    {
        if (size > Capacity())
            Expand(size * 2 + 1); // calls realloc

        memcpy(str_, str, size);
        end_ = str_ + size;
        *end_ = '\0';
    }

    String &
    String::Append(const char *str, size_t size)
    {
        // Expand first if necessary
        size_t fullLen = size + Length();
        if (fullLen > Capacity())
            Expand(fullLen * 2 + 1);

        // Copy the rest of the string to the end
        memcpy(end_, str, size);
        end_ = str_ + fullLen;
        *end_ = '\0';

        return *this;
    }

    size_t String::FindFirstOf(size_t startingAt, const std::function<bool(char)> &func) const
    {
        if (Empty()) return NullPos;
        if (!func) 
            throw InvalidArgumentException("String::FindFirstOf(const std::function<bool(char)> &func)", 
                "func", "Callback function does not have a function target.");
        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, 
                String::Format("String::FindFirstOf: startingAt max index {} was exceeded", Length() - 1));

        for (char *p = str_ + startingAt; p < end_; ++p)
            if (func(*p))
                return p - str_;
        return NullPos;
    }

    size_t String::FindFirstOf(char c, size_t startingAt) const
    {
        return FindFirstOf(startingAt, [c](char currentChar) {
            return currentChar == c;
            });
    }

    size_t String::FindFirstOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindFirstOf(startingAt, [list](char currentChar) -> bool {
            for (const char *c = list; *c != '\0'; ++c)
                if (*c == currentChar) return true;
            return false;
            });
    }

    size_t String::FindFirstNotOf(char c, size_t startingAt) const
    {
        return FindFirstOf(startingAt, [c](char currentChar) {
            return currentChar != c;
            });
    }

    size_t String::FindFirstNotOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindFirstOf(startingAt, [list](char currentChar) -> bool {
            for (const char *c = list; *c != '\0'; ++c)
                if (*c == currentChar) return false;
            return true;
            });
    }

    size_t
    String::FindNthOf(const char *list, size_t n, size_t startingAt) const
    {
        if (n == 0) return NullPos;
        size_t pos = 0;
        for (size_t i = 1; i <= n; ++i)
        {
            pos = FindFirstOf(list, pos) + 1;

            if (pos == NullPos) break;
        }

        return pos;
    }

    size_t
    String::FindNthOf(char c, size_t n, size_t startingAt) const
    {
        if (n == 0) return NullPos;
        size_t pos = 0;
        for (size_t i = 1; i <= n; ++i)
        {
            pos = FindFirstOf(c, pos) + 1;

            if (pos == NullPos) break;
        }

        return pos;
    }


    size_t
    String::Find(const char *str, size_t startingAt) const
    {
        if (Empty()) return NullPos;

        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, 
                String::Format("String::Find: max index {} was exceeded", Length()-1));

        for (const char *p = str_ + startingAt, *find = str, *ret = str_; p < end_; ++p)
        {
            if (*p == *find)
            {
                if (find++ == str)
                    ret = p;
                if (*find == '\0')
                    return ret - str_;
            } 
            else
                find = str;
        }

        return NullPos;
    }

    size_t String::FindLastOf(size_t startingAt, const std::function<bool(char)> &func) const
    {
        if (Empty()) return NullPos;
        if (!func)
            throw InvalidArgumentException("String::FindFirstOf(const std::function<bool(char)> &func)",
                "func", "Callback function does not have a function target.");

        // Make sure we start at a valid index
        startingAt = Math::Min(startingAt, Length() - 1);

        for (char *p = str_ + startingAt; p >= str_; --p)
            if (func(*p))
                return p - str_;

        return NullPos;
    }

    size_t
    String::FindLastOf(char c, size_t startingAt) const
    {
        return FindLastOf(startingAt, [c](char currentChar) { return c == currentChar; });
    }

    size_t String::FindLastOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindLastOf(startingAt, [list](char c) {
            for (const char *q = list; *q != '\0'; ++q)
                if (c == *q) return true;
            return false;
            });
    }

    size_t String::FindLastNotOf(char c, size_t startingAt) const
    {
        return FindLastOf(startingAt, [c](char cc) { return cc != c; });
    }

    size_t String::FindLastNotOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindLastOf(startingAt, [list](char c) {
            for (const char *q = list; *q != '\0'; ++q)
                if (c == *q) return false;
            return true;
            });
    }

    String &String::Insert(const String &str, size_t index)
    {
        return Insert(str.Cstr(), str.Length(), index);
    }

    String &String::Insert(const StringView &str, size_t index)
    {
        return Insert(str.Data(), str.Length(), index);
    }

    String &String::Insert(const char *str, size_t strLength, size_t index)
    {
        if (!str || *str == 0) // empty or null string, quick check
            return *this;
        if (index > Length())
            throw OutOfRangeException(index, String::Format("String::Insert: max index {} was exceeded.", Length()-1));

        size_t newSize = Length() + strLength;
        if (newSize > Capacity())
            Expand(newSize * 2u + 1u);

        char *buf = (char *)Malloc(Length() - index);
        try {
            // Copy old data to right to make room for inserted data
            Memcpy(buf, str_ + index, Length() - index);

            // Fill string with inserted characters
            Memcpy(str_ + index, str, strLength);

            // Fill old data after newly filled data
            Memcpy(str_ + index + strLength, buf, Length() - index);
        }
        catch (...)
        {
            Free(buf);
            throw;
        }

        end_ = str_ + newSize;
        *end_ = '\0';

        Free(buf);
        return *this;
    }

    // Split based on a callback: anytime it returns true, a split occurs
    Array<String> String::SplitIf(const std::function<bool(char, size_t)> &func) const
    {
        if (!func)
            throw InvalidArgumentException(SDG_FUNC, "func", "Callback does not have a function target");
        std::vector<String> result;

        bool onDelimiter = true;
        size_t index = 0;
        for (Iterator it = begin(), startWord = begin(); it <= end(); ++it)
        {
            if (onDelimiter)
            {
                if (!func(*it, index))
                {
                    startWord = it;
                    onDelimiter = false;
                }
            }
            else
            {
                if (func(*it, index) || *it == 0)
                {
                    if (it - startWord > 0)
                        result.emplace_back(&startWord, it - startWord);
                    onDelimiter = true;
                }
            }
            ++index;
        }

        return Array<String>(result.begin(), result.end());
    }

    // Split anytime whitespace occurs in the String.
    Array<String> String::Split() const
    {
        return SplitIf([](char c, size_t i)->bool { return static_cast<bool>(std::isspace(c)); });
    }

    // Split anytime char c occurs in the String.
    Array<String> String::Split(char c) const
    {
        return SplitIf([c](char character, size_t i)->bool { return character == c; });
    }

    // Split anytime a character from chars occurs in the String.
    Array<String> String::Split(const char *chars) const
    {
        return SplitIf([chars](char character, size_t i)->bool {
            for (const char *c = chars; *c != '\0'; ++c)
                if (*c == character) return true;
            return false;
        });
    }

    void
    String::Expand(size_t size)
    {
        if (size > Capacity())
        {
            size_t length = Length();
            str_ = StrRealloc(str_, size);
            full_ = str_ + size;
            end_ = str_ + length;
        }
    }

    String &
    String::Erase(size_t index)
    {
        if (index >= Length())
            throw OutOfRangeException(index, "String max index: " +
                                             std::to_string(Length() - 1));

        for (char *p = str_ + index; p < end_ - 1; ++p)
            *p = *(p + 1);

        --end_;
        *end_ = '\0';

        return *this;
    }

    String &
    String::Erase(Iterator begin, Iterator end)
    {
        // Make sure iterators are in bounds.
        SDG_Assert(&begin >= str_ && &begin <= &end && &end <= end_);

        // Shift everything from end onward onto begin
        Iterator p = begin, o = end;
        while (&o < end_)
            *p++ = *o++;

        end_ -= &end - &begin;
        *end_ = '\0';

        return *this;
    }

    String &
    String::EraseIf(const std::function<bool(char)> &func)
    {
        if (!func)
            throw InvalidArgumentException(SDG_FUNC, "func", "Callback function is missing a target");
        // Remove-if erase idiom
        return Erase(std::remove_if(begin(), end(), func), end());
    }

    String::Iterator
    String::FindIf(const std::function<bool(char)> &func) const
    {
        return std::find_if(begin(), end(), func);
    }

    String
    String::Substr(size_t index, size_t count) const
    {
        size_t length = Length();
        if (index >= length)
            return {};
        return {str_ + index, (count > length - index) ? length - index : count};
    }

    String String::Substr(Iterator it, size_t count) const
    {
        if (it > end() || it < begin())
            throw OutOfRangeException(it.Index(), String::Format("in String: \"{}\" (called from String::Substr)", *this));
        if (it == end())
            return String();

        return { &it, count > &cend() - &it ?  &cend() - &it : count };
    }

    char &
    String::operator[] (size_t index)
    {
        if (index >= Length())
            throw OutOfRangeException(index, "String's current max index is " +
                std::to_string(Length() - 1));

        return str_[index];
    }

    const char
    String::operator[] (size_t index) const
    {
        if (index >= Length())
            throw OutOfRangeException(index, "String's current max index is " +
                                             std::to_string(Length() - 1));

        return str_[index];
    }

    String &
    String::Swap(String &other) noexcept
    {
        std::swap(str_, other.str_);
        std::swap(end_, other.end_);
        std::swap(full_, other.full_);
        return *this;
    }

    // Implementation from:
    // https://cp-algorithms.com/string/string-hashing.html#calculation-of-the-hash-of-a-string
    uint64_t
    String::Hash() const
    {
        const uint64_t p = 31;
        const uint64_t m = 1e9 + 9;
        uint64_t hash = 0;
        uint64_t pPow = 1;
        for (const char *c = str_; c < end_; ++c)
        {
            hash = (hash + ((int64_t)*c - 'a' + 1) * pPow) % m;
            pPow = (pPow * p) % m;
        }

        return hash;
    }

    const char *
    String::Cstr() const
    {
        return str_;
    }

    std::string
    String::Str() const
    {
        return str_;
    }

    size_t
    String::Length() const
    {
        return end_ - str_;
    }

    size_t
    String::Capacity() const
    {
        return full_ - str_ - 1;
    }

    bool
    String::Empty() const
    {
        return str_ == end_;
    }

    // ===== Other functions that make use of implementation ==================

    String::String() : str_(), end_(), full_()
    {
        Allocate(nullptr, 0);
    }

    String::String(size_t initCap) : str_(), end_(), full_()
    {
        Allocate(initCap);
    }

    String::String(const std::string &str) :
            str_(), end_(), full_()
    {
        Allocate(str.c_str(), str.length());
    }

    String::String(const char *str) :
            str_(), end_(), full_()
    {
        Allocate(str, str ? strlen(str): 0);
    }

    String::String(const char *str, size_t count) :
        str_(), end_(), full_()
    {
        Allocate(str, count);
    }

    String::String(const StringView &view) :
        str_(), end_(), full_()
    {
        Allocate(view.Data(), view.Length());
    }

    String::~String()
    {
        StrFree(str_);
    }

    String &
    String::Clear()
    {
        end_ = str_;
        *end_ = '\0';
        return *this;
    }

    String::String(const String &str) :
            str_(), end_(), full_()
    {
        Allocate(str.Cstr(), str.Length());
    }

    String::String(String &&str) noexcept :
        str_(str.str_), end_(str.end_), full_(str.full_)
    {
        // Mover string is now dead
        str.str_ = nullptr;
        str.end_ = nullptr;
        str.full_ = nullptr;
    }

    String &
    String::operator = (const String &str)
    {
        return Assign(str);
    }

    String &
    String::operator = (String &&str) noexcept
    {
        if (&str == this)
            return *this;

        // Release previously owned data and take new data from moved string
        StrFree(str_);
        str_ = str.str_;
        end_ = str.end_;
        full_ = str.full_;
        
        // Mover string is now dead
        str.str_ = nullptr;
        str.end_ = nullptr;
        str.full_ = nullptr;
        return *this;
    }

    String &
    String::operator = (const std::string &str)
    {
        return Assign(str);
    }

    String &
    String::operator = (const char *str)
    {
        return Assign(str);
    }

    String &String::operator = (const class StringView &view)
    {
        return Assign(view);
    }

    String &String::Assign(const char *str, size_t length)
    {
        StrFree(str_);
        Allocate(str, length);
        return *this;
    }

    String &String::Assign(const char *str)
    {
        return Assign(str, str ? std::strlen(str) : 0);
    }

    String &String::Assign(const String &str)
    {
        return Assign(str.Cstr(), str.Length());
    }

    String &String::Assign(const StringView &str)
    {
        return Assign(str.Data(), str.Length());
    }

    String &String::Assign(const std::string &str)
    {
        return Assign(str.c_str(), str.length());
    }

    String &
    String::Reserve(size_t size)
    {
        Expand(size + 1);
        return *this;
    }

    String &
    String::Append(const String &str)
    {
        return Append(str.Cstr(), str.Length());
    }

    String &
    String::Append(const std::string &str)
    {
        return Append(str.c_str(), str.length());
    }

    String &
    String::Append(const char *str)
    {
        return Append(str, str ? strlen(str) : 0);
    }

    String &
    String::Append(char c)
    {
        return Append(&c, 1);
    }

    String &String::Trim(const char *list)
    {
        size_t index;
        if (list)
            index = FindFirstNotOf(list);
        else
        {
            index = FindIf([](char c)->bool {
                return !isspace(c);
                }).Index();
        }

        if (index < Length())
        {
            for (char *it = str_ + index, *dest = str_; it < end_; ++it, ++dest)
                *dest = *it;

            end_ = str_ +  Length() - index;
            *end_ = '\0';
        }
        else
        {
            Clear();
        }

        return *this;
    }

    String &String::TrimEnd(const char *list)
    {
        size_t index = NullPos;
        if (list)
            index = FindLastNotOf(list);
        else
        {
            for (auto it = end() - 1, fin = begin(); it >= fin; --it)
            {
                if (!isspace(*it))
                {
                    index = it.Index();
                    break;
                }
            }
        }

        if (index < Length() - 1)
        {
            end_ = str_ + (index + 1);
            *end_ = '\0';
        }
        else
        {
            Clear();
        }
            

        return *this;
    }

    std::ostream &operator << (std::ostream &os, const String &str)
    {
        return os << str.Cstr();
    }

    bool
    String::operator==(const String &other) const
    {
        return StringsEqual(*this, other.Cstr(), other.Length());
    }

    bool
    String::operator!=(const String &other) const
    {
        return !StringsEqual(*this, other.Cstr(), other.Length());
    }

    bool
    String::operator==(const std::string &other) const
    {
        return StringsEqual(*this, other.c_str(), other.length());
    }

    bool
    String::operator!=(const std::string &other) const
    {
        return !StringsEqual(*this, other.c_str(), other.length());
    }

    bool
    String::operator==(const char *other) const
    {
        return StringsEqual(*this, other, other ? strlen(other) : 0);
    }

    bool
    String::operator!=(const char *other) const
    {
        return !StringsEqual(*this, other, other ? strlen(other) : 0);
    }

    bool String::operator<(const String &other) const
    {
        return std::strcmp(str_, other.str_) < 0;
    }

    bool String::operator>(const String &other) const
    {
        return std::strcmp(str_, other.str_) > 0;
    }

    String &
    String::operator+=(const String &other)
    {
        return Append(other.Cstr(), other.Length());
    }

    String &
    String::operator+=(const std::string &other)
    {
        return Append(other.c_str(), other.length());
    }

    String &
    String::operator+=(const char *other)
    {
        return Append(other);
    }


    String &
    String::operator+=(char c)
    {
        return Append(c);
    }
}

// ===== Global operators =====================================================
SDG::String
SDG::operator + (const SDG::String &str1, const SDG::String &str2)
{
    return SDG::String(str1).Append(str2.Cstr(), str2.Length());
}

SDG::String
SDG::operator + (const SDG::String &str1, const std::string &str2)
{
    return SDG::String(str1).Append(str2.c_str(), str2.length());
}

SDG::String
SDG::operator + (const SDG::String &str1, const char *str2)
{
    return SDG::String(str1).Append(str2);
}

std::string
SDG::operator + (const std::string &str1, const SDG::String &str2)
{
    return std::string(str1).append(str2.Cstr(), str2.Length());
}

SDG::String
SDG::operator + (const char *str1, const SDG::String &str2)
{
    return SDG::String(str1).Append(str2.Cstr(), str2.Length());
}

SDG::String
SDG::Strcat(const char *str1, const char *str2)
{
    return SDG::String(str1).Append(str2);
}

bool
SDG::operator == (const std::string &str1, const SDG::String &str2)
{
    return str1 == str2.Cstr();
}

bool
SDG::operator != (const std::string &str1, const SDG::String &str2)
{
    return str1 != str2.Cstr();
}

SDG::String SDG::operator "" _s(const char *str)
{
    return SDG::String(str);
}


// ===== Cstring Helper Impl ==================================================
char *
StrMalloc(size_t size)
{
    char *m = (char *)malloc(size);
    if (!m)
        throw SDG::RuntimeException("String allocation failed: out of memory.");

    return m;
}

void
StrFree(char *str)
{
    free(str);
}

char *
StrRealloc(char *str, size_t size)
{
    char *m = (char *)realloc(str, size);
    if (!m)
        throw SDG::RuntimeException("String reallocation failed");

    return m;
}

bool
StringsEqual(const SDG::String &str, const char *other, size_t size)
{
    if (str.Length() != size)
        return false;

    for (const char *p = str.Cstr(), *o = other;
        p < str.Cstr() + str.Length();
        ++p, ++o)
    {
        if (*p != *o)
            return false;
    }

    return true;
}
