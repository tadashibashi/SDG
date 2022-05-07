#include "Camera2D.h"
#include <SDG/Math/Math.h>
#include <SDG/Math/Matrix4x4.h>

#include <SDG/Graphics/Window.h>
#include <SDL_gpu.h>

namespace SDG
{
    struct Camera2D::Impl {
        Impl() : wasChanged(true), mat(1), ortho(1), inverse(), position(), size(),
            scale(1, 1), rotation(), window()
        {}

        mutable bool wasChanged;
        Matrix4x4 mat, ortho, inverse;
        Vector2 position;
        Vector2 scale;
        Vector2 size;
        Vector2 anchor;
        float rotation;
        Ref<Window> window;
        FRectangle worldBounds;
    };

    void
    Camera2D::SetDimensions(int width, int height)
    {
        //impl->ortho = Matrix4x4::Ortho(0, (float)width, 0, (float)height);
        impl->size = Vector2(width, height);
        impl->wasChanged = true;
        SDG_Log("Window dimensions set to {}", impl->size.String());
    }

    void
    Camera2D::Initialize(Ref<Window> window)
    {
        impl->window = window;
        //window->onSizeChange.AddListener(this, &Camera2D::SetDimensions);
        Point resolution = window->Resolution();
        SetDimensions(resolution.X(), resolution.Y());
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

            Vector3 translation(
                    -pos.X() + impl->window->Size().X()/2.f + impl->anchor.X(),
                    -pos.Y() + impl->window->Size().Y()/2.f + impl->anchor.Y(),
                    0);
            mat.Translate(translation)
               .Rotate(impl->rotation, {0, 0, 1.f})
               .Translate({-impl->anchor.X(), -impl->anchor.Y(), 0})
               .Scale({impl->scale.X(), impl->scale.Y(), 1.f});


            // Commit results
            impl->mat = mat;
            impl->inverse = mat.Invert();

            pos = Math::Transform(pos, impl->mat); // screen-to-world
            Vector2 dimensions = Math::Transform(pos + impl->window->Size(), impl->mat);
            impl->worldBounds = FRectangle(pos.X(), pos.Y(),
                                           dimensions.W(),
                                           dimensions.H());
            impl->wasChanged = false;
        }
    }

    Camera2D &
    Camera2D::Zoom(Vector2 zoom)
    {
        impl->scale = zoom;
        impl->wasChanged = true;
        return *this;
    }

    Vector2
    Camera2D::Zoom() const
    {
        return impl->scale;
    }

    Vector2
    Camera2D::ScreenSize() const
    {
        return impl->size;
    }

    Vector2
    Camera2D::WorldToScreen(Vector2 point) const
    {
        Update();
        return Math::Transform(point, impl->mat);
    }

    Vector2
    Camera2D::ScreenToWorld(Vector2 point) const
    {
        Update();
        return Math::Transform(point, impl->inverse);
    }

    Camera2D &
    Camera2D::Rotation(float degrees)
    {
        impl->rotation = Math::Wrap<float>(degrees, 0, 360.f);
        impl->wasChanged = true;
        return *this;
    }

    float
    Camera2D::Rotation() const
    {
        return impl->rotation;
    }

    FRectangle
    Camera2D::WorldBounds() const
    {
        Update();
        return impl->worldBounds;
    }

    Camera2D &
    Camera2D::Rotate(float degrees, Vector2 anchor)
    {
        impl->anchor = anchor;
        impl->rotation = Math::Wrap<float>(degrees + impl->rotation, 0, 360.f);
        impl->wasChanged = true;
        return *this;
    }

    Camera2D &
    Camera2D::Translate(Vector2 position)
    {
        impl->position += position;
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

    Camera2D &
    Camera2D::MakeCurrent()
    {
        Update();
        GPU_LoadMatrix(impl->mat.Data());
        return *this;
    }

    Matrix4x4 Camera2D::Matrix() const
    {
        Update();
        return impl->mat;
    }
}
