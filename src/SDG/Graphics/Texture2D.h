//
// Created by Aaron Ishibashi on 4/16/22.
//
#pragma once
#include <string>
#include <SDG/Math/Vector2.h>

// Prevent MSVC macro clash
#ifdef LoadImage
#undef LoadImage
#endif

class GPU_Image;
class GPU_Target;

namespace SDG
{
    /// Wrapper around a GPU_Image. Meant to be copied.
    class Texture2D
    {
        struct Impl;
    public:
        Texture2D();
        explicit Texture2D(const std::string &path);
        Texture2D(GPU_Image *image, const std::string &path);
        ~Texture2D();

        /// Gets the inner GPU_Image object ptr.
        GPU_Image *Image() const;

        /// Load an image into the Texture2D.
        /// @param path
        bool LoadImage(const std::string &path);
        void Free();

        Point Size() const;

        bool WasLoaded() const;

        /// Gets the filepath this texture was loaded from.
        /// If this is text rendered from a font, it will contain the font's filepath.
        std::string Path() const;
        
    private:
        Impl *impl;
    };
}