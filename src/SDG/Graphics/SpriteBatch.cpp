//
// Created by aishi on 4/24/2022.
//
#include "SpriteBatch.h"

#include <SDL_gpu.h>
#include <algorithm>
#include <utility>

SDG::SpriteBatch::BatchCall::BatchCall(SDG::Texture2D *texture, SDG::Rectangle src, SDG::FRectangle dest,
                                       float rotation, SDG::Vector2 anchor, SDG::Flip flip,
                                       SDG::Color color, float depth)
        : texture(texture), src(std::move(src)), dest(std::move(dest)), rotation(rotation),
          anchor(anchor), flip(flip), color(std::move(color)), depth(depth) {}

SDG::SpriteBatch::SpriteBatch() :
    sortMode(SortMode::FrontToBack), batch()
{

}

static const Uint32 TranslateFlip[4] = {
        GPU_FLIP_NONE, GPU_FLIP_HORIZONTAL, GPU_FLIP_VERTICAL,
        GPU_FLIP_HORIZONTAL | GPU_FLIP_VERTICAL
};

void
SDG::SpriteBatch::RenderBatches()
{
    GPU_Target *gpuTarget = target->Target().Get();
    for (BatchCall &b : batch)
    {
        // Create rects
        GPU_Rect src {(float)b.src.X(), (float)b.src.Y(), (float) b.src.Width(), (float) b.src.Height()};
        GPU_Rect dest {b.dest.X(), b.dest.Y(), b.dest.Width(), b.dest.Height()};

        // Blit to the current target
        GPU_SetColor(b.texture->Image(), {b.color.r, b.color.g, b.color.b, b.color.a});
        GPU_BlitRectX(b.texture->Image(), &src, gpuTarget, &dest, b.rotation, b.anchor.X(), b.anchor.Y(),
                      TranslateFlip[(int)b.flip]);
    }
}

void SDG::SpriteBatch::SortBatches()
{
    switch (sortMode)
    {
        case SortMode::Texture:
            std::stable_sort(batch.begin(), batch.end(),
                      [](const BatchCall &b1, const BatchCall &b2)
                      {
                            return b1.texture < b2.texture;
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

void SDG::SpriteBatch::DrawTexture(SDG::Texture2D *texture, SDG::Rectangle src,
                                   SDG::FRectangle dest, float rotation, SDG::Vector2 anchor,
                                   SDG::Flip flip, SDG::Color color, float depth)
{
    batch.emplace_back(texture, std::move(src), std::move(dest), rotation, anchor,
                       flip, std::move(color), depth);
}

void SDG::SpriteBatch::Begin(Ref<RenderTarget> target, SortMode sort)
{
    sortMode = sort;
    batch.clear();
    this->target = target;
}

void SDG::SpriteBatch::End()
{
    SortBatches();
    RenderBatches();
}

void SDG::SpriteBatch::DrawTexture(SDG::Texture2D *texture, SDG::Vector2 position,
                                   SDG::Vector2 scale, SDG::Vector2 normAnchor,
                                   float rotation, float depth, Color color)
{
    batch.emplace_back(texture,
                       Rectangle{0, 0, (int)texture->Image()->base_w, (int)texture->Image()->base_h},
                       FRectangle{position.X(), position.Y(), texture->Image()->base_w * scale.W(), texture->Image()->base_h * scale.H()},
                       rotation,
                       Vector2{(float)texture->Image()->base_w * normAnchor.W(), (float)texture->Image()->base_h * normAnchor.H()},
                       Flip::None, color, depth);
}


