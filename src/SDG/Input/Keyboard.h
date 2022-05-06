//
// Created by aishi on 4/21/2022.
//
#pragma once
#include "Key.h"
#include "InputComponent.h"

namespace SDG
{
    class Keyboard : public InputComponent
    {
        struct Impl;
    public:
        Keyboard();
        ~Keyboard();

        static const char *GetKeyName(Key key);
        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;
        bool JustPressed(Key key) const;
        bool JustReleased(Key key) const;
    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateImpl() override;
        void CloseImpl() override;

        Impl *impl;
    };
}
