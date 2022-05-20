/*!
 * @file Texture2D.h
 * @namespace SDG
 * @class Texture2D
 * Texture2D loads and frees a texture file that can be used with SDG_Engine
 * image drawing functions. It supports .png, .bmp, and .tga file formats.
 *
 */
#pragma once
#include <string>
#include <SDG/FileSys/Path.h>
#include <SDG/Math/Vector2.h>

#include <SDG/Ref.h>

// Prevent MSVC macro clash
#ifdef LoadImage
#undef LoadImage
#endif

struct GPU_Image;

namespace SDG
{
    class RenderTarget;
    class Window;

    /// Texture2D class automatically frees texture when this object goes out
    /// of scope. Please be aware of this, as the object will become
    /// invalidated if the destructor is called.
    class Texture2D
    {
        struct Impl;
    public:
        // ========== Initialization and Destruction ==========
        /// Initializes an unloaded Texture
        Texture2D();
        /// Initializes a texture loaded from the given path.
        Texture2D(const Path &path, Ref<Window> target);
        /// Wraps a GPU_Image object that was already loaded.
        Texture2D(GPU_Image *image, const Path &path);
        /// Automatically frees the internal texture if one was loaded.
        ~Texture2D();

        // ========== Loading and unloading ==========
        /// Load an image into the Texture2D.
        /// @param path
        /// @param target RenderTarget to create texture with. The texture only works on the RenderTarget it was
        /// created with.
        bool LoadImage(const Path &path, Ref<Window> target);
        /// Free the internal texture, and resets container for reuse.
        void Free();

        // ========== Getters ==========
        /// Gets the dimensions of the texture in pixels.
        Point Size() const;

        /// Checks whether there is an internal texture loaded.
        bool IsLoaded() const;

        /// Gets the filepath this texture was loaded from.
        /// If this is text rendered from a font, it will contain the font's filepath.
        const Path &Filepath() const;

        /// Gets the inner GPU_Image object ptr.
        Ref<GPU_Image> Image() const;
        
    private:
        /// Private implementation
        Impl *impl;
    };
}
