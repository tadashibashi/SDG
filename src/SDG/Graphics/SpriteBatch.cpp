//
// Created by aishi on 4/24/2022.
//
#include "SpriteBatch.h"
#include "RenderTarget.h"
#include "Private/TranslateFlip.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Math/Matrix4x4.h>

#include <SDL_gpu.h>
#include <algorithm>
#include <utility>

namespace SDG
{
    // ===== BatchCall ============================================================================
    SpriteBatch::BatchCall::BatchCall(
        CRef<Texture> texture, Rectangle src, FRectangle dest,
        float rotation, Vector2 anchor, Flip flip,
        Color color, float depth)
            : texture(texture), src(std::move(src)), dest(std::move(dest)), rotation(rotation),
              anchor(anchor), flip(flip), color(std::move(color)), depth(depth) {}

    // ===== SpriteBatch ==========================================================================
    SpriteBatch::SpriteBatch() :
            matrix(), sortMode(SortMode::FrontToBack), batch(), pixel()
    {
    }

    bool
    SpriteBatch::Initialize(Ref<Window> context)
    {
        const uint8_t data[4]{ UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX };
        bool didLoad = pixel.LoadPixels(context, 1, 1, data);

        pixel.FilterMode(TexFilter::Nearest);

        return didLoad;
    }

    void
    SpriteBatch::RenderBatches()
    {
        // Get the last graphics state
        GPU_Target *lastTarget = GPU_GetActiveTarget();
        float *lastMatrix = GPU_GetCurrentMatrix();

        // Set the graphics state
        GPU_Target *gpuTarget = target->Target().Get();
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
            GPU_BlitRectX(b.texture->Image().Get(), &src, gpuTarget, &dest, b.rotation, b.anchor.X(), b.anchor.Y(),
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
            case SortMode::Texture:
                std::stable_sort(batch.begin(), batch.end(),
                                 [](const BatchCall &b1, const BatchCall &b2)
                                 {
                                     return b1.texture.Get() < b2.texture.Get();
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
    SpriteBatch::DrawTexture(CRef<Texture> texture, Rectangle src,
        FRectangle dest, float rotation, Vector2 anchor, Flip flip, Color color, float depth)
    {
        SDG_Assert(texture); // please make sure to pass a non-null Texture
        batch.emplace_back(texture, std::move(src), std::move(dest), rotation, anchor,
                           flip, std::move(color), depth);
    }

    void
    SpriteBatch::DrawTexture(CRef<Texture> texture, Vector2 position,
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
        batch.emplace_back(CRef(pixel), Rectangle{ 0, 0, 1, 1 }, rect, rotation, anchor, Flip::None, color, depth);
    }

    void
    SpriteBatch::Begin(Ref<RenderTarget> target, CRef<Matrix4x4> transformMatrix, SortMode sort)
    {
        sortMode = sort;
        batch.clear();
        this->target = target;

        static Matrix4x4 identityMat = Matrix4x4::Identity();

        if (transformMatrix)
            matrix = transformMatrix;
        else
            matrix = CRef(identityMat);
    }

    void
    SpriteBatch::End()
    {
        SortBatches();
        RenderBatches();
    }


}



