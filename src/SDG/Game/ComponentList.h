//
// Created by Aaron Ishibashi on 5/5/22.
//
#pragma once
#include <utility>
#include <map>
#include <typeindex>
#include <vector>
#include <algorithm>
#include "Component.h"

namespace SDG
{
    class Component;

    class ComponentList
    {
    public:
        ComponentList();
        ~ComponentList();
        template <typename T, typename ...Args>
        T &AddComponent(Args&&...args)
        {
            T *newComp = new T(std::forward<Args>(args)...);
            if (wasInit)
                newComp->CreateWindow();

            typeMap[typeid(T)].emplace_back(newComp);
            components.emplace_back((Component *)newComp);
            return *newComp;
        }

        template <typename T>
        T &GetComponent()
        {

        }

        /// Removes every component of type T stored in the container
        template <typename T>
        ComponentList &RemoveComponents()
        {
            auto it = typeMap.find(typeid(T));
            if (it != typeMap.end() && !it->second.empty())
            {
                components.erase(std::remove_if(
                        components.begin(), components.end(),[&it](Component *c)
                        {
                            for (void *toRemove : it->second)
                            {
                                if (c == toRemove)
                                {
                                    delete c;
                                    return true;
                                }
                            }
                            return false;
                        }));
            }

            return *this;
        }

        virtual void Initialize();
        bool WasInit() const { return wasInit; }
    private:
        std::map<std::type_index, std::vector<void *> > typeMap;
        std::vector<Component *> components;
        std::vector<std::type_index> removing;
        bool wasInit;

    };
}
