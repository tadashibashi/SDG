#pragma once

namespace SDG
{
    class Entity
    {
    public:
        Entity();
        ~Entity();

        virtual void Initialize();
        virtual void Update();
        virtual void Close();
    private:

    };
}
