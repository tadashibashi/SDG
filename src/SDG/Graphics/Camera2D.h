//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include <SDG/Math/Vector2.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Ref.h>

namespace SDG
{
    class RenderTarget;
    class Matrix4x4;

    class Camera2D
    {
        struct Impl;
    public:
        Camera2D();
        ~Camera2D();
        void Initialize(Ref<RenderTarget> target);

        Vector2 WorldToScreen(Vector2 point) const;
        Vector2 ScreenToWorld(Vector2 point) const;


        Camera2D &Rotate(float degrees, Vector2 anchor = Vector2());
        Camera2D &Rotation(float degrees);
        float Rotation() const;

        Camera2D &Zoom(Vector2 zoom);
        Vector2 Zoom() const;

        Camera2D &Translate(Vector2 position);
        Vector2 Position() const;
        Camera2D &Position(Vector2 pos);
        Camera2D &MakeCurrent();
        CRef<Matrix4x4> Matrix() const;

        Vector2 ScreenSize() const;

        FRectangle WorldBounds() const;
    private:
        // Only call this when changed
        void Update() const;
        void SetDimensions(int width, int height);
        Impl *impl;
    };
}
