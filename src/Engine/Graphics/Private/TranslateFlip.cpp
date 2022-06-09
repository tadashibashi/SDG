/* =============================================================================
 * TranslateFlip
 * 
 * 
 * ===========================================================================*/
#include "TranslateFlip.h"
#include <SDL_gpu.h>

namespace SDG
{
    const uint32_t TranslateFlip[4] = {
    GPU_FLIP_NONE, GPU_FLIP_HORIZONTAL, GPU_FLIP_VERTICAL,
    GPU_FLIP_HORIZONTAL | GPU_FLIP_VERTICAL
    };
}
