//
// Created by Aaron Ishibashi on 5/5/22.
//
#pragma once
#include "InputComponent.h"
#include "SDG/Math/Vector2.h"
#include "MButton.h"

namespace SDG
{
    class Mouse : public InputComponent
    {
    public:
        Mouse();
        ~Mouse();
        bool ButtonPress(MButton button) const;
        bool ButtonPressed(MButton button) const;
        bool ButtonRelease(MButton button) const;
        bool ButtonReleased(MButton button) const;
        Point Position() const { return position; }
        Point LastPosition() const { return lastPosition; }
        bool DidMove() const { return lastPosition != position; }
        Vector2 Wheel() const { return wheel; }
        Vector2 LastWheel() const { return lastWheel; }
        bool WheelDidMove() const { return wheel != lastWheel; }
    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateImpl() override;
        void CloseImpl() override;

        Point position, lastPosition;
        uint32_t buttonMask, lastButtonMask;
        Vector2 wheel, lastWheel;
    };
}
