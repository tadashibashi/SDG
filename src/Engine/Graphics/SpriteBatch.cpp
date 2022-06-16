//
// Created by aishi on 4/24/2022.
//
#include "SpriteBatch.h"
#include "RenderTarget.h"
#include "Private/TranslateFlip.h"

#include <Engine/Debug/Assert.h>

#include <Engine/Math/Matrix4x4.h>
#include <Engine/Math/MathShape.h>
#include <Engine/Math/Private/Conversions.h>

#include <SDL_gpu.h>
#include <algorithm>
#include <utility>

namespace SDG
{
    // ===== BatchCall ============================================================================
    SpriteBatch::BatchCall::BatchCall(
        const Texture *texture, Rectangle src, FRectangle dest,
        float rotation, Vector2 anchor, Flip flip,
        Color color, float depth)
            : texture(texture), src(std::move(src)), dest(std::move(dest)), rotation(rotation),
              anchor(anchor), flip(flip), color(std::move(color)), depth(depth) { }

    // ===== SpriteBatch ==========================================================================
    SpriteBatch::SpriteBatch() :
            matrix(), sortMode(SortMode::FrontToBack), batch(), pixel()
    {
    }

    bool
    SpriteBatch::Initialize(URef<Window> context)
    {
        const uint8_t data[4]{ UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX };
        bool didLoad = pixel.LoadPixels(context.Get(), 1, 1, data);

        pixel.FilterMode(Texture::Filter::Nearest);

        return didLoad;
    }

    void
    SpriteBatch::RenderBatches()
    {
        // Get the last graphics state
        GPU_Target *lastTarget = GPU_GetActiveTarget();
        float *lastMatrix = GPU_GetCurrentMatrix();

        // Set the graphics state
        GPU_Target *gpuTarget = target->Target();
        if (gpuTarget != lastTarget)
            GPU_SetActiveTarget(gpuTarget);
        if (matrix->Data() != lastMatrix)
            GPU_LoadMatrix(matrix->Data());

        // Blit images
        for (BatchCall &b : batch)
        {
            // Create rects
            GPU_Rect src {(float)b.src.X(), (float)b.src.Y(), (float) b.src.Width(), (float) b.src.Height()};
            GPU_Rect dest {b.dest.X(), b.dest.Y(), b.dest.Width(), b.dest.Height()};
            
            // Blit to the current target
            GPU_SetTargetColor(gpuTarget, {b.color.R(), b.color.G(), b.color.B(), b.color.A()});
            GPU_BlitRectX((GPU_Image *)b.texture->Image(), &src, gpuTarget, &dest, b.rotation, b.anchor.X(), b.anchor.Y(),
                          TranslateFlip[(int)b.flip]);
        }

        // Restore the last graphics state, if mutated
        if (lastTarget != gpuTarget)
            GPU_SetActiveTarget(lastTarget);
        if (lastMatrix != matrix->Data())
            GPU_LoadMatrix(lastMatrix);
    }

    void
    SpriteBatch::SortBatches()
    {
        switch (sortMode)
        {
        case SortMode::None:
            break;
        case SortMode::Texture:
            std::stable_sort(batch.begin(), batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.texture->Image() < b2.texture->Image();
                                });
            break;
        case SortMode::FrontToBack:
            std::stable_sort(batch.begin(), batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.depth < b2.depth;
                                });
            break;
        case SortMode::BackToFront:
            std::stable_sort(batch.begin(), batch.end(),
                                [](const BatchCall &b1, const BatchCall &b2)
                                {
                                    return b1.depth > b2.depth;
                                });
            break;
        }
    }

    void
    SpriteBatch::DrawTexture(const Texture *texture, Rectangle src,
        FRectangle dest, float rotation, Vector2 anchor, Flip flip, Color color, float depth)
    {
        SDG_Assert(texture); // please make sure to pass a non-null Texture
        batch.emplace_back(texture, std::move(src), std::move(dest), rotation, anchor,
                           flip, std::move(color), depth);
    }

    void
    SpriteBatch::DrawTexture(const Texture *texture, Vector2 position,
        Vector2 scale, Vector2 normAnchor, float rotation, float depth, Color color)
    {
        SDG_Assert(texture != nullptr); // please make sure to pass a non-null Texture
        batch.emplace_back(texture,
                           Rectangle{0, 0, (int)texture->Image()->base_w, (int)texture->Image()->base_h},
                           FRectangle{position.X(), position.Y(), texture->Image()->base_w * scale.W(), texture->Image()->base_h * scale.H()},
                           rotation,
                           Vector2{(float)texture->Image()->base_w * normAnchor.W(), (float)texture->Image()->base_h * normAnchor.H()},
                           Flip::None, color, depth);
    }

    void 
    SpriteBatch::DrawRectangle(FRectangle rect, Vector2 anchor, Color color, float rotation, float depth)
    {
        batch.emplace_back(&pixel, Rectangle{ 0, 0, 1, 1 }, rect, rotation, anchor, Flip::None, color, depth);
    }

    void SpriteBatch::DrawLine(Vector2 a, Vector2 b, float thickness, Color color, float depth)
    {
        float distance = Math::PointDistance(a, b);
        float angle = Math::PointDirection(a, b);

        batch.emplace_back(&pixel, Rectangle{ 0, 0, 1, 1 }, FRectangle{ a.X(), a.Y() - thickness * 0.5f, distance, thickness },
            angle, Vector2{ 0, 0.5f }, Flip::None, color, depth);
    }

    void SpriteBatch::DrawLine(Vector2 position, float length, float angle, float thickness, Color color, float depth)
    {
        batch.emplace_back( &pixel, Rectangle{ 0, 0, 1, 1 }, 
            FRectangle{ position.X(), position.Y() - thickness * 0.5f, length, thickness },
            angle, Vector2{ 0, 0.5f }, Flip::None, color, depth);
    }

    void SpriteBatch::DrawLines(std::vector<Vector2> points, float thickness, Color color, float depth)
    {
        for (size_t i = 0; i < points.size() - 1; ++i)
            DrawLine(points[i], points[i + 1], thickness, color, depth);
    }

    void
    SpriteBatch::Begin(Ref<RenderTarget> target, Ref<const Matrix4x4> transformMatrix, SortMode sortMode)
    {
        this->sortMode = sortMode;
        this->target = target;
        batch.clear();

        static Matrix4x4 identityMat = Matrix4x4::Identity();
        matrix = (transformMatrix) ? transformMatrix : identityMat;
    }

    void
    SpriteBatch::End()
    {
        SortBatches();
        RenderBatches();
    }


}



