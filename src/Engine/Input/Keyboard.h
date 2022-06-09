#pragma once
#include "Key.h"
#include "InputComponent.h"

namespace SDG
{
    /// Keyboard input processor. There is current support for one keyboard.
    class Keyboard : public InputComponent
    {
        struct Impl;
    public:
        Keyboard();
        ~Keyboard();

        static const char *KeyName(Key key);
        bool Release(Key key) const;
        bool Press(Key key) const;
        bool Pressed(Key key) const;
        bool Released(Key key) const;
    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateLastStatesImpl() override;
        void CloseImpl() override;
        Impl *impl;
    };
}
