#include "TextRenderer.h"
#include <SDL_gpu.h>

namespace SDG
{
    auto TextRenderer::Render(Ref<RenderTarget> target) -> void
    {
        if (font)
            font->Draw(target.Get(), position, scale, alignment, color, "{}", text);
        
    }
}