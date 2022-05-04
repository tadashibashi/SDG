//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include <SDG/Math/Vector2.h>
class GPU_Camera;

namespace SDG
{
    class Camera2D
    {
        struct Impl;
    public:
        Camera2D();
        ~Camera2D();
        void Update();
        Vector2 WorldToScreen(Vector2 point);
        Vector2 ScreenToWorld(Vector2 point);

        Camera2D &Translate(Vector2 position);
        Camera2D &Rotate(float degrees);

    private:
        Impl *mImpl;
    };
}
