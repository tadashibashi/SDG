#include "StringView.h"
#include <SDG/Debug/Assert.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Math/Math.h>

#include <utility>

namespace SDG
{
    const size_t StringView::NullPos = SIZE_MAX;

    StringView::StringView() : str_(""), size_() { }
    StringView::StringView(const char *str, size_t size) : str_(str), size_(size) { }
    StringView &StringView::operator = (const StringView &str)
    {
        str_ = str.str_;
        size_ = str.size_;
        return *this;
    }
    StringView &StringView::operator = (const String &str)
    {
        str_ = str.Cstr();
        size_ = str.Length();
        return *this;
    }
    StringView &StringView::operator = (const std::string &str)
    {
        str_ = str.data();
        size_ = str.size();
        return *this;
    }
    StringView &StringView::operator=(const char *cstr)
    {
        str_ = cstr;
        size_ = cstr ? std::strlen(cstr) : 0;
        return *this;
    }
    StringView::StringView(const String &str) : str_(str.Cstr()), size_(str.Length()) { }
    StringView::StringView(const std::string &str) : str_(str.c_str()), size_(str.length()) { }
    StringView::StringView(const char *cstr) : str_(cstr), size_(cstr ? std::strlen(cstr) : 0) { }

    size_t
    StringView::Length() const { return size_; }

    bool
    StringView::Empty() const { return size_ == 0; }

    String
    StringView::Str() const { return String(str_, size_); }

    StringView
    StringView::Substr(size_t index, size_t count) const 
    {
        if (index >= size_)
            throw OutOfRangeException(index, "Max range is: " + std::to_string(size_ - 1));

        return StringView(str_ + index, (count > size_ - index) ? size_ - index : count); 
    }

    size_t
    StringView::FindFirstOf(char c, size_t startingAt) const
    {
        if (Empty()) return NullPos;

        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, "String max index: " +
                std::to_string(Length() - 1));

        for (const char *p = str_ + startingAt, *ends = str_ + size_; p < ends; ++p)
            if (*p == c)
                return p - str_;

        return NullPos;
    }

    size_t
    StringView::FindFirstOf(const char *list, size_t startingAt) const
    {
        SDG_Assert(list && *list != '\0'); // list should have substance
        if (Empty()) return NullPos;

        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, "String max index: " +
                std::to_string(Length() - 1));

        for (const char *p = str_ + startingAt, *ends = str_ + size_; p < ends; ++p)
            for (const char *q = list; *q != '\0'; ++q)
                if (*p == *q)
                    return p - str_;

        return NullPos;
    }

    size_t
    StringView::Find(const char *pattern, size_t startingAt) const
    {
        if (Empty()) return NullPos;

        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, "String max index: " +
                std::to_string(Length() - 1));

        for (const char *p = str_ + startingAt, *find = pattern, *ret = str_, *ends = str_ + size_;
            p < ends; ++p)
        {
            if (*p == *find)
            {
                if (find++ == pattern)
                    ret = p;
                if (*find == '\0')
                    return ret - str_;
            }
            else
                find = pattern;
        }

        return NullPos;
    }

    size_t
    StringView::FindLastOf(char c, size_t startingAt) const
    {
        if (Empty()) return NullPos;

        // Make sure we start at a valid index
        startingAt = Math::Min(startingAt, Length() - 1);

        for (const char *p = str_ + startingAt; p >= str_; --p)
            if (*p == c)
                return p - str_;

        return NullPos;
    }

    size_t
    StringView::FindLastOf(const char *list, size_t startingAt) const
    {
        SDG_Assert(list && *list != '\0'); // list should have substance
        if (Empty()) return NullPos;

        // Make sure we start at a valid index
        startingAt = Math::Min(startingAt, Length() - 1);

        for (const char *p = str_ + startingAt; p >= str_; --p)
            for (const char *q = list; *q != '\0'; ++q)
                if (*p == *q)
                    return p - str_;

        return NullPos;
    }

    StringView &
    StringView::Swap(StringView &other)
    {
        std::swap(str_, other.str_);
        std::swap(size_, other.size_);
        return *this;
    }

    const char *
    StringView::Cstr() const { return str_; }

    bool StringView::operator == (const StringView &s) const
    {
        return StrCmp(s.str_, s.size_);
    }

    bool StringView::operator != (const StringView &s) const
    {
        return !operator==(s);
    }

    bool StringView::operator == (const String &s) const
    {
        return StrCmp(s.Cstr(), s.Length());
    }

    bool StringView::operator != (const String &s) const
    {
        return !operator==(s);
    }

    bool StringView::operator == (const std::string &s) const
    {
        return StrCmp(s.c_str(), s.length());
    }

    bool StringView::operator != (const std::string &s) const
    {
        return !operator==(s);
    }

    bool
    StringView::operator == (const char *cstr) const
    {
        if (!cstr) return Empty();

        if (strlen(cstr) != Length()) return false;

        for (char c : *this)
            if (c != *cstr++) return false;

        return true;
    }

    bool
    StringView::operator != (const char *s) const
    {
        return !operator==(s);
    }

    StringView::Iterator
    StringView::begin() const
    {
        return str_;
    }

    StringView::Iterator
    StringView::end() const
    {
        return str_ + size_;
    }

    char StringView::operator[](unsigned i) const
    {
        if (i >= size_)
            throw OutOfRangeException(i, "Maximum index: " + 
                std::to_string(size_ - 1));
        return str_[i];
    }

    bool StringView::StrCmp(const char *s, size_t length) const
    {
        if (!s)
            return Empty();

        if (Length() != length)
            return false;

        for (const char *p = str_, *o = s, *end = str_ + size_;
            p != end;
            ++p, ++o)
        {
            if (*p != *o)
                return false;
        }

        return true;
    }

    String operator + (const StringView &a, const StringView &b)
    {
        return String(a.Cstr()).Append(b.Cstr(), b.Length());
    }

    String operator + (const StringView &a, const String &b)
    {
        return String(a.Cstr()).Append(b.Cstr(), b.Length());
    }

    String operator + (const StringView &a, const std::string &b)
    {
        return String(a.Cstr()).Append(b.c_str(), b.length());
    }

    String operator + (const StringView &a, const char *b)
    {
        return String(a.Cstr()).Append(b);
    }

    String operator + (const char *a, const StringView &b)
    {
        return String(a).Append(b.Cstr(), b.Length());
    }

    String operator + (const String &a, const StringView &b)
    {
        return String(a).Append(b.Cstr(), b.Length());
    }

    std::string operator + (const std::string &a, const StringView &b)
    {
        return std::string(a).append(b.Cstr(), b.Length());
    }

    bool operator == (const String &a, const StringView &b)
    {
        return b == a;
    }

    bool operator == (const std::string &a, const StringView &b)
    {
        return b == a;
    }

    bool operator == (const char *a, const StringView &b)
    {
        return b == a;
    }

    bool operator != (const String &a, const StringView &b)
    {
        return b != a;
    }

    bool operator != (const std::string &a, const StringView &b)
    {
        return b != a;
    }

    bool operator != (const char *a, const StringView &b)
    {
        return b != a;
    }
}
