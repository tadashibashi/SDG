#pragma once
#include <Engine/Lib/RAIterator.h>
#include <vector>

namespace SDG::Dynamic
{
    class Object;
    class Array
    {
        struct Impl;
    public:
        using Iterator = std::vector<Object>::iterator;
        using ConstIterator = std::vector<Object>::const_iterator;

        Array();
        explicit Array(size_t initSize);
        explicit Array(const std::vector<Object> &objs);
        explicit Array(const std::initializer_list<Object> &objs);

        Array(const Array &arr);
        ~Array();


        Array &operator=(const Array &arr);
        Array &operator=(const std::initializer_list<Object> &objs);

        size_t Size() const;
        void Resize(size_t size);

        Object &operator [] (size_t index);
        const Object &operator [] (size_t index) const;

        void Erase(size_t index);
        void Erase(Iterator startIndex, Iterator endIndex);

        void Insert(size_t index, const Object &obj);
        void Insert(size_t index, const std::initializer_list<Object> &objs);

        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        [[nodiscard]] bool operator==(const Array &other) const;


    private:
        Impl *impl;
    };  

    template <typename...Args>
    inline Array MakeArray(Args&&...args)
    {
        std::vector<Object> objs;
        ((objs.emplace_back(args)), ...);
        return Array(std::move(objs));
    }
}

