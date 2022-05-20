/// String implementation file
#include "String.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Logging.h>
#include <SDG/Exceptions/OutOfRangeException.h>

#include <algorithm>
#include <cstdlib>
#include <ostream>

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
    String::Reallocate(const char *str, size_t size)
    {
        if (size > Capacity())
            Expand(size * 2 + 1); // calls realloc

        memcpy(str_, str, size);
        end_ = str_ + size;
        *end_ = '\0';
    }

    void
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
    }

    size_t
    String::FindFirstOf(char c, size_t startingAt) const
    {
        for (char *p = str_ + startingAt; p < end_; ++p)
            if (*p == c)
                return p - str_;

        return NullPos;
    }

    size_t
    String::FindLastOf(char c, size_t startingAt) const
    {
        if (startingAt >= Length())
            startingAt = Length() - 1;

        for (char *p = str_ + startingAt; p >= str_; --p)
            if (*p == c)
                return p - str_;

        return NullPos;
    }


    void
    String::Expand(size_t size)
    {
        if (size > Capacity())
        {
            str_ = StrRealloc(str_, size);
            full_ = str_ + size;
        }
    }

    String &
    String::Erase(size_t index)
    {
        if (index >= Length())
            throw OutOfRangeException(index, "String's current max index is " +
                                             std::to_string(Length() - 1));

        for (char *p = str_ + index; p < end_ - 1; ++p)
        {
            *p = *(p + 1);
        }
        --end_;
        *end_ = '\0';

        return *this;
    }

    String &
    String::Erase(Iterator begin, Iterator end)
    {
        // Make sure iterators are in bounds.
        SDG_Assert(begin >= str_ && begin <= end && end <= end_);

        Iterator p = begin, o = end;
        while (o < end_)
            *p++ = *o++;

        end_ -= end - begin;
        *end_ = '\0';

        return *this;
    }

    String &
    String::EraseIf(const std::function<bool(char)> &func)
    {
        return Erase(std::remove_if(begin(), end(), func), end());
    }

    String
    String::Substr(size_t index, size_t count)
    {
        size_t length = Length();
        if (index >= length)
            throw OutOfRangeException(index, "String's current max index is " +
                                             std::to_string(length - 1));
        return {str_ + index, (count > length - index) ? length - index : count};
    }

    char &
    String::operator[] (size_t index)
    {
        if (index >= Length())
            throw OutOfRangeException(index, "String's current max index is " +
                std::to_string(Length() - 1));

        return str_[index];
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
            hash = (hash + (*c - 'a' + 1) * pPow) % m;
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

    String::~String()
    {
        StrFree(str_);
    }

    String::String(const String &str) :
            str_(), end_(), full_()
    {
        Allocate(str.Cstr(), str.Length());
    }

    String &
    String::operator = (const String &str)
    {
        Reallocate(str.Cstr(), str.Length());
        return *this;
    }

    String &
    String::operator = (const std::string &str)
    {
        Reallocate(str.c_str(), str.length());
        return *this;
    }

    String &
    String::operator = (const char *str)
    {
        Reallocate(str, str ? strlen(str) : 0);
        return *this;
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
        Append(str.Cstr(), str.Length());
        return *this;
    }

    String &
    String::Append(const std::string &str)
    {
        Append(str.c_str(), str.length());
        return *this;
    }

    String &
    String::Append(const char *str)
    {
        Append(str, str ? strlen(str) : 0);
        return *this;
    }

    String &
    String::Append(char c)
    {
        Append(&c, 1);
        return *this;
    }

    bool
    String::operator==(const String &other)
    {
        return StringsEqual(*this, other.Cstr(), other.Length());
    }

    bool
    String::operator==(const std::string &other)
    {
        return StringsEqual(*this, other.c_str(), other.length());
    }

    bool
    String::operator==(const char *other)
    {
        return StringsEqual(*this, other, other ? strlen(other) : 0);
    }

    String &
    String::operator+=(const String &other)
    {
        return Append(other);
    }

    String &
    String::operator+=(const std::string &other)
    {
        return Append(other);
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
operator + (const SDG::String &str1, const SDG::String &str2)
{
    return SDG::String(str1) += str2;
}

SDG::String
operator + (const SDG::String &str1, const std::string &str2)
{
    return SDG::String(str1) += str2;
}

SDG::String
operator + (const SDG::String &str1, const char *str2)
{
    return SDG::String(str1) += str2;
}

std::string
operator + (const std::string &str1, const SDG::String &str2)
{
    return std::string(str1) += str2.Cstr();
}

SDG::String
operator + (const char *str1, const SDG::String &str2)
{
    return SDG::String(str1) + str2;
}

bool
operator == (const std::string &str1, const SDG::String &str2)
{
    return str1 == str2.Cstr();
}

std::ostream &
operator << (std::ostream &os, const SDG::String &str)
{
    return os << str.Cstr();
}

// ===== Cstring Helper Impl ==================================================
char *
StrMalloc(size_t size)
{
    char *m = (char *)malloc(size);
    if (!m)
    {
        SDG_Err("String allocation failed: out of memory.");
        exit(-1);
    }

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
    {
        SDG_Err("String reallocation failed: out of memory.");
        exit(-1);
    }

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
