#include "Array.h"
#include "Object.h"

#include <vector>

namespace SDG::Dynamic
{
    struct Array::Impl
    {
        Impl() : objects(), count(1) { }
        mutable std::vector<Object> objects; // allow to grow while querying
        size_t count;
    };

    Array::Array() : impl(new Impl) { }

    Array::Array(size_t size) : impl(new Impl) { impl->objects.resize(size); }
    Array::Array(const std::initializer_list<Object> &objs) : impl(new Impl) 
    { 
        impl->objects.insert(impl->objects.begin(), objs);
    }

    Array::Array(const std::vector<Object> &objs) : impl(new Impl)
    {
        impl->objects = objs;
    }

    Array::~Array()
    {
        if (--impl->count == 0)
            delete impl;
    }

    Array::Array(const Array &arr) : impl(arr.impl)
    {
        ++impl->count;
    }

    Array &Array::operator=(const Array &arr)
    {
        if (impl != arr.impl)
        {
            if (--impl->count)
                delete impl;

            impl = arr.impl;
            ++impl->count;
        }

        return *this;
    }

    Array &Array::operator=(const std::initializer_list<Object> &objs)
    {
        if (--impl->count == 0)
            delete impl;
        impl = new Impl;

        impl->objects.insert(impl->objects.begin(), objs);
        return *this;
    }

    void Array::Resize(size_t size)
    {
        if (size >= impl->objects.size())
            impl->objects.resize(size);
    }

    void Array::Erase(size_t index)
    {
        impl->objects.erase(impl->objects.begin() + index);
    }

    void Array::Erase(Iterator _begin, Iterator _end)
    {
        impl->objects.erase(_begin, _end);
    }

    Object &Array::operator[](size_t index)
    {
        if (index >= impl->objects.size())
            impl->objects.resize(index * 2 + 1);
        return impl->objects[index];
    }

    const Object &Array::operator[](size_t index) const
    {
        if (index >= impl->objects.size())
            impl->objects.resize(index * 2 + 1);
        return impl->objects[index];
    }

    size_t Array::Size() const { return impl->objects.size(); }

    Array::Iterator Array::begin() { return impl->objects.begin(); }
    Array::ConstIterator Array::begin() const { return impl->objects.begin(); }
    Array::Iterator Array::end() { return impl->objects.end(); }
    Array::ConstIterator Array::end() const { return impl->objects.end(); }
    Array::ConstIterator Array::cbegin() const { return impl->objects.cbegin(); }
    Array::ConstIterator Array::cend() const { return impl->objects.cend(); }

    bool Array::operator==(const Array &other) const { return impl == other.impl; }
}
