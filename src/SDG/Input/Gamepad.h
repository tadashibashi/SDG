#pragma once
#include "InputComponent.h"
#include <cstdint>

namespace SDG
{
    class Gamepad : public InputComponent
    {
        struct Impl;
    public:
        Gamepad();
        ~Gamepad();
    public:
        bool Press(uint32_t input) const;
        bool Release(uint32_t input) const;
        bool Pressed(uint32_t input) const;
        bool Released(uint32_t input) const;
        float Axis(uint32_t input) const;

    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateLastStatesImpl() override;
        void CloseImpl() override;
        Impl *impl;
    };
}