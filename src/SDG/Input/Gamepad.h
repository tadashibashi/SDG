#pragma once
#include "Button.h"
#include "GamepadType.h"
#include "InputComponent.h"


#include <SDG/Lib/Delegate.h>

#include <cstdint>

namespace SDG
{
    class Gamepad : public InputComponent
    {
        struct Impl;
    public:
        Gamepad(int index);
        ~Gamepad();
    public:
        bool Press(Button button) const;
        bool Release(Button button) const;
        bool Pressed(Button button) const;
        bool Released(Button button) const;
        float Axis(Button button) const;

        /// Gets the controller number
        int Index() const;
        bool IsOpen() const;

        GamepadType Type() const;

        /// Invoked when the device is connected.
        /// Callbacks receive the controller index (not id).
        Delegate<void(int)> OnConnect;

        /// Invoked when the device is removed.
        /// Callbacks receive the controller index (not id).
        Delegate<void(int)> OnRemove;
    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateLastStatesImpl() override;
        void CloseImpl() override;
        Impl *impl;
    };
}