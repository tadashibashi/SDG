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

static Uint32 TranslateFlip[4] = {
        GPU_FLIP_NONE, GPU_FLIP_HORIZONTAL, GPU_FLIP_VERTICAL,
        GPU_FLIP_HORIZONTAL | GPU_FLIP_VERTICAL
};

void
SDG::SpriteBatch::RenderBatches()
{
    for (auto &b : batch)
    {
        GPU_Rect src {(float)b.src.x, (float)b.src.y, (float)b.src.w, (float)b.src.h};
        GPU_Rect dest { b.dest.x, b.dest.y, b.dest.w, b.dest.h};
        GPU_SetColor(b.texture->Image(), {b.color.r, b.color.g, b.color.b, b.color.a});
        GPU_BlitRectX(b.texture->Image(), &src, target, &dest, b.rotation, b.anchor.x, b.anchor.y,
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

void SDG::SpriteBatch::Begin(GPU_Target *target, SortMode sort)
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
                       FRectangle{position.x, position.y, texture->Image()->base_w * scale.w, texture->Image()->base_h * scale.h},
                       rotation,
                       Vector2{(float)texture->Image()->base_w * normAnchor.w, (float)texture->Image()->base_h * normAnchor.h},
                       Flip::None, color, depth);
}


