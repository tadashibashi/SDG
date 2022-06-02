/*!
 * @file Texture.h
 * @namespace SDG
 * @class Texture
 * Texture loads and frees a texture file that can be used with SDG_Engine
 * image drawing functions. It supports .png, .bmp, and .tga file formats.
 *
 */
#pragma once
#include <SDG/FileSys/Path.h>
#include <SDG/Math/Vector2.h>

#include <SDG/Lib/Ref.h>

struct GPU_Image;
struct SDL_Surface;

namespace SDG
{

    /// Texture class automatically frees texture when this object goes out
    /// of scope. Please be aware of this, as the object will become
    /// invalidated if the destructor is called.
    class Texture
    {
        struct Impl;
    public:
        enum class Format {
            Auto,
            Png,
            Tga,
            Bmp
        };

        enum class Snap
        {
            None,
            Position,
            Dimensions,
            Both
        };

        enum class Filter
        {
            Linear,
            LinearMipMap,
            Nearest
        };

        // ========== Initialization and Destruction ==========
        /// Initializes an unloaded Texture
        Texture();
        /// Initializes a texture loaded from the given path.
        Texture(Ref<class Window> context, const Path &path);

        Texture(Ref<class Window> context, SDL_Surface *surf, const Path &path = Path());

        /// Automatically frees the internal texture if one was loaded.
        ~Texture();

        // ========== Loading and unloading ==========
        /// Load an image into the Texture.
        /// @param path path to the image file. Must be in png, tga, or bmp format.
        /// @param context context to create texture with - it will only render in this context.
        bool Load(Ref<class Window> context, const Path &path);

        /// Load an image from a surface. Ownership of surface is passed to the Texture.
        /// @param surf the surface to load
        /// @param context context to create texture with - it will only render in this context.
        /// @param path path that the surface was loaded from. Made optional since there is not always one.
        bool LoadFromSurface(Ref<class Window> context, SDL_Surface *surf, const Path &path = Path());

        /// Free the internal texture, and resets container for reuse.
        void Free();

        bool SaveAs(const Path &filepath, Format format = Format::Auto);


        // ========== Getters/ Setters ==========

        Snap SnapMode() const;
        Texture &SnapMode(Snap snapMode);

        bool Blending() const;
        Texture &Blending(bool blending);

        Filter FilterMode() const;
        Texture &FilterMode(Filter mode);

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
