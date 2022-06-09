/*!
 * @file Flip.h
 * @enum Flip
 * Describes image flip direction, used in rendering functions.
 *
 */
#pragma once
#include <cstdint>

namespace SDG
{
    /// Image flip direction. Used with rendering functions.
    enum class Flip
    {
        None = 0,
        Horizontal,
        Vertical,
        Both
    };

    /// Namespace for conversion functions
    namespace Conv
    {
        /// Converts an SDG::Flip to a GPU_Flip flag
        uint32_t ToGPUFlip(Flip flip);
    }
}
