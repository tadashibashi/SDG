#include "Flip.h"
#include "Private/TranslateFlip.h"

uint32_t
SDG::Conv::ToGPUFlip(SDG::Flip flip)
{
    return TranslateFlip[(int)flip];
}
