/*!
 * @file Camera2D.h
 * @namespace SDG
 * @class Camera2D
 * Controls a camera matrix to control a viewport
 * Provides functions for converting coordinates between virtual and screen spaces.
 */
#pragma once
#include <SDG/Math/Vector2.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Ref.h>

namespace SDG
{
    /// Class that
    class Camera2D
    {
        struct Impl;
    public:
        Camera2D();
        ~Camera2D();

        /// Converts a world position to a screen position
        Vector2 WorldToScreen(Vector2 worldPos) const;
        /// Converts a screen position to a world position
        Vector2 ScreenToWorld(Vector2 screenPos) const;

        /// Sets the pivot point about which the camera rotates
        Camera2D &PivotPoint(Vector2 point) noexcept;
        /// Gets the pivot point about which the camera rotates
        Vector2 PivotPoint() const noexcept;

        /// Sets the angle of the camera, relatively
        /// @param degrees - number to add to the current angle
        Camera2D &Rotate(float degrees) noexcept;
        /// Sets the absolute rotation of the view, in degrees
        /// @param degrees - auto-wraps between 0 - 360
        Camera2D &Angle(float degrees) noexcept;
        /// Gets the absolute rotation of the view, in degrees (0-360)
        float Angle() const noexcept;
        
        /// Multiplies the current scale
        Camera2D &Zoom(Vector2 zoom);
        /// Sets the absolute scale or zoom of the view
        Camera2D &Scale(Vector2 scale);
        /// Gets the absolute scale or zoom of the view
        Vector2 Scale() const;

        /// Moves the camera relative to its current position
        Camera2D &Translate(Vector2 pos);
        /// Sets the absolute world position of the camera
        Camera2D &Position(Vector2 pos);
        /// Gets the absolute world position of the camera
        Vector2 Position() const;

        /// Begins camera transformation on the current target
        void Begin();
        /// Ends effects of camera transformation and restores the last one
        void End();

        /// Gets the internal matrix for referencing
        CRef<class Matrix4x4> Matrix() const;

        /// Sets the viewport resolution size
        void ViewportSize(int width, int height);

        /// Gets the viewport resolution size
        Vector2 ViewportSize() const;
    private:
        // Only call this when changed
        void Update() const;
        
        Impl *impl;
    };
}
