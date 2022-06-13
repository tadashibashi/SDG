#include "StringView.h"
#include <Engine/Debug/Assert.h>
#include <Engine/Debug/LogImpl.h>
#include <Engine/Exceptions.h>
#include <Engine/Math/Math.h>

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

    StringView
    StringView::Substr(ConstIterator it, size_t count) const
    {
        if (it > end() || it < begin())
            throw OutOfRangeException(it.Index(), "String::Substr passed iterator is out of range!");

        return { &it, count > &end() - &it ? &end() - &it : count };
    }

    StringView &StringView::Trim(const char *list)
    {
        size_t index;
        if (list)
        {
            index = FindIf([](char c)->bool {
                return !isspace(c);
                }).Index();
        }
        else
        {
            index = FindFirstNotOf(list);
        }

        if (index < Length())
        {
            size_ = Length() - index;
            str_ += index;
        }
        else
        {
            size_ = 0;
        }

        return *this;
    }

    StringView &StringView::TrimEnd(const char *list)
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
            size_ =  (index + 1);

        return *this;
    }

    size_t StringView::FindFirstOf(char c, size_t startingAt) const
    {
        return FindFirstOf(startingAt, [c](char currentChar) {
            return currentChar == c;
            });
    }

    StringView::ConstIterator 
    StringView::FindIf(const std::function<bool(char)> &func) const
    {
        return std::find_if(begin(), end(), func);
    }

    size_t StringView::FindFirstOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindFirstOf(startingAt, [list](char currentChar) -> bool {
            for (const char *c = list; *c != '\0'; ++c)
                if (*c == currentChar) return true;
            return false;
            });
    }

    size_t StringView::FindFirstOf(size_t startingAt, const std::function<bool(char)> &func) const
    {
        if (Empty()) return NullPos;
        if (!func)
            throw InvalidArgumentException("String::FindFirstOf(const std::function<bool(char)> &func)",
                "func", "Callback function does not have a function target.");
        if (startingAt >= Length())
            throw OutOfRangeException(startingAt, String::Format(
                "String::FindFirstOf: startingAt max index {} was exceeded",
                Length() - 1));

        for (const char *p = str_ + startingAt, *fin = str_ + size_; p < fin; ++p)
            if (func(*p))
                return p - str_;
        return NullPos;
    }

    size_t StringView::FindFirstNotOf(char c, size_t startingAt) const
    {
        return FindFirstOf(startingAt, [c](char currentChar) {
            return currentChar != c;
            });
    }

    size_t StringView::FindFirstNotOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindFirstOf(startingAt, [list](char currentChar) -> bool {
            for (const char *c = list; *c != '\0'; ++c)
                if (*c == currentChar) return false;
            return true;
            });
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

    size_t StringView::FindLastOf(size_t startingAt, const std::function<bool(char)> &func) const
    {
        if (Empty()) return NullPos;
        if (!func)
            throw InvalidArgumentException("String::FindFirstOf(const std::function<bool(char)> &func)",
                "func", "Callback function does not have a function target.");

        // Make sure we start at a valid index
        startingAt = Math::Min(startingAt, Length() - 1);

        for (const char *p = str_ + startingAt; p >= str_; --p)
            if (func(*p))
                return p - str_;

        return NullPos;
    }


    size_t StringView::FindLastOf(char c, size_t startingAt) const
    {
        return FindLastOf(startingAt, [c](char currentChar) { return c == currentChar; });
    }

    size_t StringView::FindLastOf(const char *list, size_t startingAt) const
    {
        SDG_Assert(list && *list != '\0'); // list should have substance

        return FindLastOf(startingAt, [&list](char c) {
            for (const char *q = list; *q != '\0'; ++q)
                if (c == *q) return true;
            return false;
            });
    }

    size_t StringView::FindLastNotOf(char c, size_t startingAt) const
    {
        return FindLastOf(startingAt, [c](char cc) {
            return cc != c;
            });
    }

    size_t StringView::FindLastNotOf(const char *list, size_t startingAt) const
    {
        if (!list || *list == '\0') return NullPos;

        return FindLastOf(startingAt, [&list](char c) {
            for (const char *q = list; *q != '\0'; ++q)
                if (c == *q) return false;
            return true;
            });
    }


    StringView &
    StringView::Swap(StringView &other)
    {
        std::swap(str_, other.str_);
        std::swap(size_, other.size_);
        return *this;
    }

    const char *
    StringView::Data() const { return str_; }

    bool StringView::operator == (const StringView &s) const
    {
        return StrCmp(s.str_, s.size_);
    }

    std::ostream &operator << (std::ostream &os, const StringView &view)
    {
        for (char c : view)
            os << c;

        return os;
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

    StringView::ConstIterator
    StringView::begin() const
    {
        return ConstIterator(str_, str_, str_ + size_);
    }

    StringView::ConstIterator
        StringView::cbegin() const
    {
        return begin();
    }

    StringView::ConstIterator
    StringView::end() const
    {
        return ConstIterator(str_ + size_, str_, str_ + size_);
    }

    StringView::ConstIterator
        StringView::cend() const
    {
        return end();
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
        return String(a.Data()).Append(b.Data(), b.Length());
    }

    String operator + (const StringView &a, const String &b)
    {
        return String(a.Data()).Append(b.Cstr(), b.Length());
    }

    String operator + (const StringView &a, const std::string &b)
    {
        return String(a.Data()).Append(b.c_str(), b.length());
    }

    String operator + (const StringView &a, const char *b)
    {
        return String(a.Data()).Append(b);
    }

    String operator + (const char *a, const StringView &b)
    {
        return String(a).Append(b.Data(), b.Length());
    }

    String operator + (const String &a, const StringView &b)
    {
        return String(a).Append(b.Data(), b.Length());
    }

    std::string operator + (const std::string &a, const StringView &b)
    {
        return std::string(a).append(b.Data(), b.Length());
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
