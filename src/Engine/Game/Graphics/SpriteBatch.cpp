#include "SpriteBatch.h"
#include <Engine/Graphics/RenderTarget.h>
#include <Engine/Graphics/Private/Conversions.h>
#include <Engine/Graphics/Private/TranslateFlip.h>

#include <Engine/Debug/Assert.h>

#include <Engine/Math/Matrix4x4.h>
#include <Engine/Math/MathShape.h>
#include <Engine/Math/Private/Conversions.h>

#include <SDL_gpu.h>
#include <algorithm>
#include <utility>

namespace SDG
{
    struct BatchCall
    {
        BatchCall(
            const GPU_Image *texture, GPU_Rect src, GPU_Rect dest,
            float rotation, Vector2 anchor, Flip flip,
            SDL_Color color, float depth)
            : texture{ texture }, src{ std::move(src) }, dest{ std::move(dest) }, rotation{ rotation },
            anchor{ anchor }, flip{ flip }, color{ std::move(color) }, depth{ depth } { }

        const GPU_Image *texture;
        GPU_Rect   src;
        GPU_Rect   dest;
        float      rotation;
        Vector2    anchor;
        SDL_Color  color;
        Flip       flip;
        float      depth;
    };

    struct SpriteBatch::Impl
    {
        Impl() : matrix{}, sortMode{ SortMode::FrontToBack }, target{}, batch{}, pixel{}, batching{ false } { }
        std::vector<BatchCall>   batch;
        SortMode                 sortMode;
        GPU_Target               *target;
        const float              *matrix;
        Texture                  pixel;
        bool                     batching;
    };

    // ===== BatchCall ============================================================================


    // ===== SpriteBatch ==========================================================================
    SpriteBatch::SpriteBatch() : impl(new Impl)
    {

    }

    SpriteBatch::~SpriteBatch()
    {
        delete impl;
    }

    bool
    SpriteBatch::Initialize(Ref<Window> context)
    {
        const uint8_t data[4]{ UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX };
        bool didLoad = impl->pixel.LoadPixels(context.Get(), 1, 1, data);

        impl->pixel.FilterMode(Texture::Filter::Nearest);

        return didLoad;
    }

    // Uses direct calls to SDL GPU for speed instead of going through RenderTarget abstraction
    void
    SpriteBatch::RenderBatches()
    {
        // Get the last graphics state
        GPU_Target *lastTarget = GPU_GetActiveTarget();
        float *lastMatrix = GPU_GetCurrentMatrix();

        GPU_Target *target = impl->target;
        const float *matrix = impl->matrix;

        // Set the graphics state
        if (target != lastTarget)
            GPU_SetActiveTarget(target);
        if (matrix != lastMatrix)
            GPU_LoadMatrix(matrix);

        // Blit images
        for (BatchCall &b : impl->batch)
        {
            
            // Blit to the current target
            GPU_SetTargetColor(target, std::move(b.color));
            GPU_BlitRectX((GPU_Image *)b.texture, &b.src, target, &b.dest, b.rotation, b.anchor.X(), b.anchor.Y(),
                          TranslateFlip[(int)b.flip]);
        }

        // Restore the last graphics state, if mutated
        if (lastTarget != target)
            GPU_SetActiveTarget(lastTarget);
        if (lastMatrix != matrix)
            GPU_LoadMatrix(lastMatrix);
    }

    void
    SpriteBatch::SortBatches()
    {
        switch (impl->sortMode)
        {
        case SortMode::None:
            break;
        case SortMode::Texture:
            std::stable_sort(impl->batch.begin(), impl->batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.texture < b2.texture;
                                });
            break;
        case SortMode::FrontToBack:
            std::stable_sort(impl->batch.begin(), impl->batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.depth < b2.depth;
                                });
            break;
        case SortMode::BackToFront:
            std::stable_sort(impl->batch.begin(), impl->batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.depth > b2.depth;
                                });
            break;
        }
    }

    void
    SpriteBatch::DrawTexture(const Texture *texture, const Rectangle &src,
        const FRectangle &dest, float rotation, const Vector2 &anchor, Flip flip, const Color &color, float depth)
    {
        SDG_Assert(texture); // please make sure to pass a non-null Texture
        impl->batch.emplace_back((GPU_Image *)texture->Image(), 
            GPU_Rect{ (float)src.X(), (float)src.Y(), (float)src.Width(), (float)src.Height() }, 
            GPU_Rect{ dest.X(), dest.Y(), dest.Width(), dest.Height() }, rotation, anchor,
            flip, SDL_Color{ color.R(), color.G(), color.B(), color.A() }, depth);
    }

    void
    SpriteBatch::DrawTexture(const Texture *texture, const Vector2 &position,
        const Vector2 &scale, const Vector2 &normAnchor, float rotation, float depth, const Color &color)
    {
        SDG_Assert(texture != nullptr); // makes sure to pass a non-null Texture

        float baseW = texture->Image()->base_w;
        float baseH = texture->Image()->base_h;

        impl->batch.emplace_back((GPU_Image *)texture->Image(),
            GPU_Rect{0, 0, baseW, baseH},
            GPU_Rect{position.X(), position.Y(), baseW * scale.X(), baseH * scale.Y()},
            rotation,
            Vector2{baseW * normAnchor.X(), baseH * normAnchor.Y()},
            Flip::None, SDL_Color{color.R(), color.G(), color.B(), color.A()}, depth);
    }

    void 
    SpriteBatch::DrawRectangle(const FRectangle &rect, const Vector2 &anchor, const Color &color, float rotation, float depth)
    {
        impl->batch.emplace_back((GPU_Image *)impl->pixel.Image(),
            GPU_Rect{ 0, 0, 1.f, 1.f }, 
            GPU_Rect{ rect.X(), rect.Y(), rect.Width(), rect.Height() }, 
            rotation, anchor, Flip::None,
            SDL_Color{ color.R(), color.G(), color.B(), color.A() }, depth);
    }

    void SpriteBatch::DrawLine(const Vector2 &a, const Vector2 &b, float thickness, const Color &color, float depth)
    {
        float distance = Math::PointDistance(a, b);
        float angle = Math::PointDirection(a, b);

        impl->batch.emplace_back(
            (GPU_Image *)impl->pixel.Image(), 
            GPU_Rect{ 0, 0, 1.f, 1.f }, 
            GPU_Rect{ a.X(), a.Y() - thickness * 0.5f, distance, thickness },
            angle, Vector2{ 0, 0.5f }, Flip::None, 
            SDL_Color{ color.R(), color.G(), color.B(), color.A() }, depth);
    }

    void SpriteBatch::DrawLine(const Vector2 &position, float length, float angle, float thickness, const Color &color, float depth)
    {
        impl->batch.emplace_back((GPU_Image *)impl->pixel.Image(), 
            GPU_Rect{ 0, 0, 1.f, 1.f },
            GPU_Rect{ position.X(), position.Y() - thickness * 0.5f, length, thickness },
            angle, Vector2{ 0, 0.5f }, Flip::None, SDL_Color{ color.R(), color.G(), color.B(), color.A() }, depth);
    }

    void SpriteBatch::DrawLines(const std::vector<Vector2> &points, float thickness, const Color &color, float depth)
    {
        for (size_t i = 0; i < points.size() - 1; ++i)
            DrawLine(points[i], points[i + 1], thickness, color, depth);
    }

    void
    SpriteBatch::Begin(Ref<RenderTarget> target, Ref<const Matrix4x4> transformMatrix, SortMode sortMode)
    {
        if (impl->batching)
            throw RuntimeException("SpriteBatch::Begin called while batching. Did you forget a matching call to SpriteBatch::End()?");

        impl->batching = true;
        impl->sortMode = sortMode;
        impl->target = target ? target->Target().Get() : GPU_GetActiveTarget();
        impl->batch.clear();

        static Matrix4x4 identityMat = Matrix4x4::Identity();
        impl->matrix = (transformMatrix.Get()) ? transformMatrix->Data() : identityMat.Data();
    }

    void
    SpriteBatch::End()
    {
        SortBatches();
        RenderBatches();
        impl->batching = false;
    }


}



