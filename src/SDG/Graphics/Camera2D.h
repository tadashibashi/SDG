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
#include <SDG/Lib/Ref.h>

namespace SDG
{
    class Camera2D
    {
        struct Impl;
    public:
        Camera2D();
        ~Camera2D();

    public: 
        // ===== Driver functions =============================================

        /// Begins camera transformation on the current RenderTarget. 
        /// Please make sure the correct target has been made current, and also
        /// to call End() when finished using this camera's transformations.
        void Begin();

        /// Ends effects of camera transformation and restores the last one.
        /// Called sometime after Begin() when the effects of the camera are no
        /// longer needed.
        void End();

        // ===== Setters / Getters ============================================

        /// Converts a world position to a screen position
        Vector2 WorldToScreen(Vector2 worldPos) const;
        /// Converts a screen position to a world position
        Vector2 ScreenToWorld(Vector2 screenPos) const;

        /// Sets the pivot point about which the camera rotates
        /// @param point - position
        /// @param normalizer - multiplied to the position, default is (1, 1). 
        /// This allows use where param "point" can represent e.g. screen size, and scalar
        /// normalizes it.
        Camera2D &PivotPoint(Vector2 point, Vector2 normalizer = Vector2::One()) noexcept;
        /// Sets the pivot point about which the camera rotates
        Camera2D &PivotPoint(float pointX, float pointY) noexcept;
        /// Gets the pivot point about which the camera rotates
        const Vector2 &PivotPoint() const noexcept;

        /// Sets the angle of the camera, relatively
        /// @param degrees - number to add to the current angle
        Camera2D &Rotate(float degrees) noexcept;
        /// Sets the absolute rotation of the view, in degrees
        /// @param degrees - auto-wraps between 0 - 360
        Camera2D &Angle(float degrees) noexcept;
        /// Gets the absolute rotation of the view, in degrees (0-360)
        float Angle() const noexcept;
        
        /// Multiplies the current scale
        Camera2D &Zoom(Vector2 zoom) noexcept;
        /// Multiplies both current x and y scales by one value
        Camera2D &Zoom(float zoom) noexcept;
        /// Multiplies the current scale
        Camera2D &Zoom(float zoomX, float zoomY) noexcept;
        /// Sets the absolute scale of the view
        Camera2D &Scale(Vector2 scale) noexcept;
        /// Sets the absolute scale's width and height to the same value
        Camera2D &Scale(float scale) noexcept;
        /// Sets the absolute scale of the view
        Camera2D &Scale(float scaleX, float scaleY) noexcept;
        /// Gets the absolute scale or zoom of the view
        const Vector2 &Scale() const noexcept;

        /// Moves the camera relative to its current position
        Camera2D &Translate(Vector2 pos) noexcept;
        /// Moves the camera relative to its current position
        Camera2D &Translate(float posX, float posY) noexcept;
        /// Sets the absolute world position of the camera
        Camera2D &Position(Vector2 pos) noexcept;
        /// Sets the absolute world position of the camera
        Camera2D &Position(float posX, float posY) noexcept;
        /// Gets the absolute world position of the camera
        const Vector2 &Position() const noexcept;

        /// Sets the viewport resolution size
        Camera2D &ViewportSize(Point size) noexcept;
        /// Sets the viewport resolution size
        Camera2D &ViewportSize(int width, int height) noexcept;
        /// Gets the viewport resolution size
        const Point &ViewportSize() const noexcept;

        /// Gets the internal matrix for referencing
        CRef<class Matrix4x4> Matrix() const;
    private:
        /// Call this when updating the latest matrix state is required
        void Update() const;
        
        Impl *impl;
    };
}
