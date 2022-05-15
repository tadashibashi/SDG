//
// Created by Aaron Ishibashi on 4/16/22.
//
#pragma once
#include <string>

#include <SDG/FileSys/Path.h>
#include <SDG/Math/Vector2.h>
#include <SDG/Ref.h>

// Prevent MSVC macro clash
#ifdef LoadImage
#undef LoadImage
#endif

class GPU_Image;
class GPU_Target;

namespace SDG
{
    /// Texture2D class automatically frees texture when this object goes out
    /// of scope. Please be aware of this, as the object will become
    /// invalidated if the destructor is called.
    class Texture2D
    {
        struct Impl;
    public:
        Texture2D();
        explicit Texture2D(const Path &path);
        Texture2D(GPU_Image *image, const Path &path);
        ~Texture2D();

        /// Gets the inner GPU_Image object ptr.
        Ref<GPU_Image> Image() const;

        /// Load an image into the Texture2D.
        /// @param path
        bool LoadImage(const Path &path);
        void Free();

        /// Gets the dimensions of the texture in pixels
        Point Size() const;

        /// Checks whether there is an internal texture loaded.
        bool IsLoaded() const;

        /// Gets the filepath this texture was loaded from.
        /// If this is text rendered from a font, it will contain the font's filepath.
        const Path &Filepath() const;
        
    private:
        Impl *impl;
    };
}