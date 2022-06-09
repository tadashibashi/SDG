#pragma once
#include "InputComponent.h"
#include "MButton.h"

#include <Engine/Math/Vector2.h>

namespace SDG
{
    /// Mouse input processor. There is current support for one mouse.
    class Mouse : public InputComponent
    {
    public:
        Mouse();
        ~Mouse();

        /// Checks if a mouse button is currently down
        bool Press(MButton button) const;

        /// Checks if a mouse button was just pressed this frame
        bool Pressed(MButton button) const;

        /// Checks if a mouse button is currently up
        bool Release(MButton button) const;

        /// Checks if a mouse button was just released this frame
        bool Released(MButton button) const;

        /// Gets the screen coordinates of the cursor
        Point Position() const { return position; }

        /// Gets the screen coordinates of the cursor last frame
        Point LastPosition() const { return lastPosition; }

        /// Checks if the cursor moved this frame
        bool DidMove() const { return lastPosition != position; }

        /// Gets the wheel motion this frame
        Vector2 Wheel() const { return wheel; }

        /// Gets the wheel motion last frame
        Vector2 LastWheel() const { return lastWheel; }

        /// Checks if the wheel moved this frame
        bool WheelDidMove() const { return wheel != Vector2::Zero(); }

    private:
        bool InitializeImpl() override;
        void ProcessInputImpl(const SDL_Event &ev) override;
        void UpdateLastStatesImpl() override;
        void CloseImpl() override;

        Point position, lastPosition;
        uint32_t buttonMask, lastButtonMask;
        Vector2 wheel, lastWheel;
    };
}
