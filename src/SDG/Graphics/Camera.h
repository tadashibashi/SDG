//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include <SDG/Math/Vector2.h>
class GPU_Camera;

namespace SDG
{
    class Camera
    {
        struct Impl;
    public:
        Camera();
        ~Camera();
        void Update();
        Vector2 WorldToScreen(Vector2 point);
        Vector2 ScreenToWorld(Vector2 point);
        GPU_Camera *InnerCamera() const;

    private:
        Impl *mImpl;
    };
}
