#pragma once
#include <Engine/Lib/Ref.h>

namespace SDG
{
    class IUpdatable {
    public:
        virtual void Update() = 0;
    };

    class IRenderable {
    public:
        virtual void Render() = 0;
    };

    class Component
    {
    public:
        Component() : priority(), parent() { }
        virtual ~Component() { }
        virtual void Initialize() = 0;
        virtual void Close() = 0;

        const CRef<Component> Parent() const { return parent; }
        Component &Parent(Component *p) { parent = p; return *this; }
        const int Priority() const { return priority; }
    private:
        int priority;
        Component *parent;
    };
}
