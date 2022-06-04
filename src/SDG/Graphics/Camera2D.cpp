/// Camera implementation file
#include "Camera2D.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Log.h>
#include <SDG/Graphics/RenderTarget.h>
#include <SDG/Math/MathShape.h>

#include <SDL_gpu.h>

#include <utility>


namespace SDG
{
    struct Camera2D::Impl {
        Impl() : wasChanged(true), mat(1), ortho(1), inverse(), position(), size(),
            scale(1, 1), anchor(), angle()
        {}

        mutable bool wasChanged;
        Matrix4x4 mat, ortho, inverse;
        Vector2 position;
        Vector2 scale;
        Point size;
        Vector2 anchor;
        float angle;
    };

    Camera2D::Camera2D() : impl(new Impl)
    {

    }

    Camera2D::~Camera2D()
    {
        delete impl;
    }

    void
    Camera2D::Update() const
    {
        if (impl->wasChanged)
        {
            Matrix4x4 mat (impl->ortho);

            // Round projected position to the nearest pixel.
            Vector2 pos = impl->position;
            pos *= impl->scale;
            pos = Vector2(round(pos.X()), round(pos.Y()));
            pos /= impl->scale;
            
            mat  // Todo: optimize later by combining like transformations
                .Translate({-pos, 0})
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
    Camera2D::Zoom(Vector2 zoom) noexcept
    {
        return Scale(Scale() * zoom);
    }


    Camera2D &
    Camera2D::Zoom(float zoom) noexcept
    {
        return Zoom({ zoom, zoom });
    }

    Camera2D &
    Camera2D::Zoom(float zoomX, float zoomY) noexcept
    {
        return Zoom({ zoomX, zoomY });
    }

    Camera2D &
    Camera2D::Scale(Vector2 scale) noexcept
    {
        impl->scale = scale;
        impl->wasChanged = true;
        return *this;
    }

    Camera2D &
    Camera2D::Scale(float scaleX, float scaleY) noexcept
    {
        return Scale({ scaleX, scaleY });
    }

    Camera2D &
    Camera2D::Scale(float scale) noexcept
    {
        return Scale({ scale, scale });
    }

    const Vector2 &
    Camera2D::Scale() const noexcept
    {
        return impl->scale;
    }

    const Point &
    Camera2D::ViewportSize() const noexcept
    {
        return impl->size;
    }

    Camera2D &
    Camera2D::ViewportSize(Point size) noexcept
    {
        SDG_Assert(size.X() > 0 && size.Y() > 0);

        impl->size = std::move(size);
        impl->wasChanged = true;
        return *this;
    }


    Camera2D &
    Camera2D::ViewportSize(int width, int height) noexcept
    {
        return ViewportSize({ width, height });
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

    Camera2D &
    Camera2D::PivotPoint(float pointX, float pointY) noexcept
    {
        return PivotPoint({ pointX, pointY });
    }

    const Vector2 &
    Camera2D::PivotPoint() const noexcept
    {
        return impl->anchor;
    }

    Camera2D &
    Camera2D::Rotate(float degrees) noexcept
    {
        return Angle(Angle() + degrees);
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
    Camera2D::Translate(Vector2 pos) noexcept
    {
        return Position(Position() + pos);
    }

    Camera2D &
    Camera2D::Translate(float posX, float posY) noexcept
    {
        return Translate({ posX, posY });
    }

    const Vector2 &
    Camera2D::Position() const noexcept
    {
        return impl->position;
    }

    Camera2D &
    Camera2D::Position(float posX, float posY) noexcept
    {
        return Position({ posX, posY });
    }

    /// EmplaceTarget the specific position
    Camera2D &
    Camera2D::Position(Vector2 pos) noexcept
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
