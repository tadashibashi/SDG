//
// Created by Aaron Ishibashi on 4/29/22.
//

#include "Camera.h"
#include <SDL_gpu.h>

namespace SDG
{
    struct Camera::Impl {
        mutable bool wasChanged;
        GPU_Camera camera;
    };

    Camera::Camera() : mImpl(new Impl)
    {

    }

    Camera::~Camera()
    {
        delete mImpl;
    }

    void Camera::Update()
    {

    }

    Vector2 Camera::WorldToScreen(Vector2 point)
    {

        return SDG::Vector2();
    }

    Vector2 Camera::ScreenToWorld(Vector2 point)
    {

        return SDG::Vector2();
    }

    GPU_Camera *Camera::InnerCamera() const
    {
        return &mImpl->camera;
    }
}