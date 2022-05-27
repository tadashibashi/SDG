#include "StringView.h"
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/Math/Math.h>

namespace SDG
{
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
    StringView &StringView::operator=(const char *str)
    {
        str_ = str;
        size_ = str ? std::strlen(str) : 0;
        return *this;
    }
    StringView::StringView(const String &str) : str_(str.Cstr()), size_(str.Length()) { }
    StringView::StringView(const std::string &str) : str_(str.c_str()), size_(str.length()) { }
    StringView::StringView(const char *str) : str_(str), size_(str ? std::strlen(str) : 0) { }

    size_t
    StringView::Length() const { return size_; }

    bool
    StringView::Empty() const { return size_ == 0; }

    String
    StringView::Str() const { return String(str_, size_); }

    StringView
    StringView::Substr(size_t index, size_t count) const 
    {
        index = Math::Min(size_ - 1, index);
        return StringView(str_ + index, (count > size_ - index) ? size_ - index : count); 
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

    bool StringView::operator==(const std::string &s) const
    {
        return StrCmp(s.c_str(), s.length());
    }

    bool StringView::operator!=(const std::string &s) const
    {
        return !operator==(s);
    }

    bool
    StringView::operator == (const char *s) const
    {
        for (const char *p = str_, *end = str_ + size_;
            p != end;
            ++p, ++s)
        {
            if (*s == '\0' || *p != *s)
                return false;
        }

        return true;
    }

    bool StringView::operator != (const char *s) const
    {
        return !operator==(s);
    }

    StringView::Iterator
    StringView::begin()
    {
        return str_;
    }

    StringView::Iterator
    StringView::end()
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
        return String(a.Cstr()) + b.Cstr();
    }

    String operator + (const StringView &a, const String &b)
    {
        return String(a.Cstr()) + b.Cstr();
    }

    String operator + (const StringView &a, const std::string &b)
    {
        return String(a.Cstr()) + b.c_str();
    }

    String operator + (const StringView &a, const char *b)
    {
        return String(a.Cstr()) + b;
    }

    String operator + (const String &a, const StringView &b)
    {
        return String(a) + b.Cstr();
    }

    std::string operator + (const std::string &a, const StringView &b)
    {
        return std::string(a) + b.Cstr();
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
