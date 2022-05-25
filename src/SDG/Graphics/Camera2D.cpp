/// Camera implementation file
#include "Camera2D.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Log.h>
#include <SDG/Graphics/RenderTarget.h>
#include <SDG/Math/Shape.h>

#include <SDL_gpu.h>

#include <utility>


namespace SDG
{
    struct Camera2D::Impl {
        Impl() : wasChanged(true), mat(1), ortho(1), inverse(), position(), size(),
            scale(1, 1), angle()
        {}

        mutable bool wasChanged;
        Matrix4x4 mat, ortho, inverse;
        Vector2 position;
        Vector2 scale;
        Vector2 size;
        Vector2 anchor;
        float angle;
    };

    void
    Camera2D::ViewportSize(int width, int height)
    {
        impl->size = Vector2(width, height);
        impl->wasChanged = true;
    }

    Camera2D::Camera2D() : impl(new Impl)
    {

    }

    Camera2D::~Camera2D()
    {
        delete impl;
    }

    void Camera2D::Update() const
    {
        if (impl->wasChanged)
        {
            Matrix4x4 mat (impl->ortho);

            // Round projected position to the nearest pixel.
            Vector2 pos = impl->position;
            pos *= impl->scale;
            pos = Vector2(round(pos.X()), round(pos.Y()));
            pos /= impl->scale;

            //auto target = GPU_GetActiveTarget();
//            Vector3 translation(
//                    -pos.X() + (target ? target->w / 2.f : 0),
//                    -pos.Y() + (target ? target->h / 2.f : 0),
//                    0);
            Vector3 translation(
                    -pos.X(),
                    -pos.Y(),
                    0);
            
            mat  // Todo: optimize later by combining like transformations
                .Translate(translation)
                .Translate({ pos + impl->anchor, 0 })
                .Scale({ impl->scale, 1.f })
                .Rotate(impl->angle, { 0, 0, 1.f })
                .Translate({-pos - impl->anchor, 0 });

            // Commit results
            impl->mat = mat;
            impl->inverse = mat.Invert();
            impl->wasChanged = false;
        }
    }

    Camera2D &
    Camera2D::Zoom(Vector2 zoom)
    {
        impl->scale *= zoom;
        impl->wasChanged = true;
        return *this;
    }

    Camera2D &
    Camera2D::Scale(Vector2 scale)
    {
        impl->scale = scale;
        impl->wasChanged = true;
        return *this;
    }

    Vector2
    Camera2D::Scale() const
    {
        return impl->scale;
    }

    Vector2
    Camera2D::ViewportSize() const
    {
        return impl->size;
    }

    Vector2
    Camera2D::WorldToScreen(Vector2 worldPos) const
    {
        Update();
        return Math::Transform(worldPos, impl->mat);
    }

    Vector2
    Camera2D::ScreenToWorld(Vector2 screenPos) const
    {
        Update();
        return Math::Transform(screenPos, impl->inverse);
    }

    Camera2D &
    Camera2D::PivotPoint(Vector2 anchor) noexcept
    {
        impl->anchor = std::move(anchor);
        impl->wasChanged = true;
        return *this;
    }

    Vector2
    Camera2D::PivotPoint() const noexcept
    {
        return impl->anchor;
    }

    Camera2D &
    Camera2D::Rotate(float degrees) noexcept
    {
        impl->angle = Math::WrapF<float>(impl->angle + degrees, 0, 360.f);
        impl->wasChanged = true;
        return *this;
    }

    Camera2D &
    Camera2D::Angle(float degrees) noexcept
    {
        impl->angle = Math::WrapF<float>(degrees, 0, 360);
        impl->wasChanged = true;
        return *this;
    }

    float
    Camera2D::Angle() const noexcept
    {
        return impl->angle;
    }

    Camera2D &
    Camera2D::Translate(Vector2 pos)
    {
        impl->position += pos;
        impl->wasChanged = true;
        return *this;
    }

    Vector2
    Camera2D::Position() const
    {
        return impl->position;
    }

    /// EmplaceTarget the specific position
    Camera2D &
    Camera2D::Position(Vector2 pos)
    {
        impl->position = pos;
        impl->wasChanged = true;
        return *this;
    }

    void
    Camera2D::Begin()
    {
        Update();
        GPU_PushMatrix();
        GPU_LoadMatrix(impl->mat.Data());
    }

    void
    Camera2D::End()
    {
        GPU_PopMatrix();
    }

    CRef<Matrix4x4>
    Camera2D::Matrix() const
    {
        Update();
        return CRef(impl->mat);
    }
}
