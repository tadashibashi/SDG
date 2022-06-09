//
// Created by Aaron Ishibashi on 5/5/22.
//
#include "ComponentList.h"
#include "Component.h"
namespace SDG
{
    ComponentList::ComponentList() : wasInit(false)
    {

    }

    ComponentList::~ComponentList()
    {

    }

    void ComponentList::Initialize()
    {
        for (Component *c : components)
            c->Initialize();
    }
}