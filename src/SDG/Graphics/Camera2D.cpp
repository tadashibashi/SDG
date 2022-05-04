//
// Created by Aaron Ishibashi on 4/29/22.
//

#include "Camera2D.h"
#include <SDL_gpu.h>

namespace SDG
{
    struct Camera2D::Impl {
        Impl() : camera(), wasChanged(false), mat{0}
        {
            GPU_MatrixIdentity(mat);
        }
        mutable bool wasChanged;
        GPU_Camera camera;
        float mat[16];
    };

    Camera2D::Camera2D() : mImpl(new Impl)
    {

    }

    Camera2D::~Camera2D()
    {
        delete mImpl;
    }

    void Camera2D::Update()
    {

    }

    Vector2 Camera2D::WorldToScreen(Vector2 point)
    {

        return SDG::Vector2();
    }

    Vector2 Camera2D::ScreenToWorld(Vector2 point)
    {

        return SDG::Vector2();
    }

    Camera2D &Camera2D::Rotate(float degrees)
    {

        return *this;
    }

    Camera2D &Camera2D::Translate(Vector2 position)
    {
        GPU_MatrixTranslate(mImpl->mat, position.x, position.y, 0);
        return *this;
    }
}