//
// Created by Aaron Ishibashi on 5/1/22.
//

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
