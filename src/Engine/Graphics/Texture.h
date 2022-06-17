/*!
 * @file Texture.h
 * @namespace SDG
 * @class Texture
 * Texture loads and frees a texture file that can be used with SDG_Engine
 * image drawing functions. It supports .png, .bmp, and .tga file formats.
 *
 */
#pragma once
#include <Engine/Filesys/Path.h>
#include <Engine/Lib/Unique.h>
#include <Engine/Lib/Shared.h>
#include <Engine/Math/Vector2.h>

struct GPU_Image;
struct SDL_Surface;

namespace SDG
{
    /// Texture class automatically frees texture when every copy of this object goes out
    /// of scope. It's a shared resource, so maintaining a copy should ensure it is alive.
    /// Does not support multi-threaded safety.
    class Texture
    {
        struct Impl;
    public:
        /// Initializes an unloaded Texture
        Texture();
        /// Loads a texture loaded from the given path.
        Texture(class Window *context, const Path &path);
        
        /// Copies image data into this new Texture
        Texture(const Texture &tex);
        Texture(Texture &&tex) noexcept;


        /// Copies data into this new Texture
        Texture &operator = (const Texture &tex);
        Texture &operator = (Texture &&tex) noexcept;

        Texture(class Window *context, SDL_Surface *surf, const Path &path = Path());
        explicit Texture(GPU_Image *image);

        /// Automatically frees the internal texture if one was loaded.
        ~Texture();

    public:   
        enum class FileFormat { Auto, Png, Tga, Bmp };
        enum class Snap { None, Position, Dimensions, PositionAndDimensions };    
        enum class Filter { Nearest, Linear, LinearMipMap };
        enum class Wrap { None, Repeat, Mirror };

        // ========== Resource Management ==========

        /// Load an image into the Texture.
        /// @param path path to the image file. Must be in png, tga, or bmp format.
        /// @param context context to create texture with - it will only render in this context.
        bool Load(class Window *context, const Path &path);

        /// Load an image from a surface. Ownership of surface is passed to the Texture.
        /// @param context - context to create texture with - it will only render in this context.
        /// @param surf - the surface to load
        /// @param path - path that the surface was loaded from. Made optional since there is not always one.
        bool LoadFromSurface(class Window *context, SDL_Surface *surf, const Path &path = Path());

        bool LoadPixels(class Window *context, uint32_t width, uint32_t height, const uint8_t *rgbaPixels);

        /// Unload the current texture. Affects all other instances of this Texture.
        void Unload();

        /// Saves the file in a certain format
        bool SaveAs(const Path &filepath, FileFormat format = FileFormat::Png);

        /// Swap the internals of this Texture with another
        void Swap(Texture &tex);

        /// Creates an alias of this Texture to another. All setters/getters
        /// and even Close will not affect the original's data.
        /// In practice, this can be used to quickly load various preset modes.
        bool CreateAlias(Texture *alias);

        // ========== Getters/ Setters ==========
        // Static -------------------------------

        static void DefaultFilterMode(Filter mode);
        static Filter DefaultFilterMode();
        static void DefaultSnapMode(Snap mode);
        static Snap DefaultSnapMode();
        static void DefaultAnchor(Vector2 anchor);
        static Vector2 DefaultAnchor();

        // Member functions ----------------------
        Vector2 Anchor() const;
        Texture &Anchor(Vector2 anchor);

        bool Blending() const;
        Texture &Blending(bool blending);

        Filter FilterMode() const;
        Texture &FilterMode(Filter mode);

        Snap SnapMode() const;
        Texture &SnapMode(Snap mode);

        /// Gets the Wrap behavior for this Texture on the X axis.
        /// Wrap mode takes effect during rendering functions, when source
        /// rectangle is larger than the the source dimensions.
        Wrap WrapModeX() const;

        /// Gets the Wrap behavior for this Texture on the Y axis.
        /// Wrap mode takes effect during rendering functions, when source 
        /// rectangle is larger than the the source dimensions.
        Wrap WrapModeY() const;

        /// Sets the Wrap behavior for this Texture.
        /// This takes effect during rendering functions, when source rectangle
        /// is larger than the the source dimensions.
        Texture &WrapMode(Wrap x, Wrap y);

        /// Gets the dimensions of the texture in pixels.
        Point Size() const;

        /// Checks whether there is an internal texture loaded.
        bool IsLoaded() const;

        /// Gets the filepath this texture was loaded from.
        /// If this is text rendered from a font, it will contain the font's filepath.
        const Path &Filepath() const;

        /// Gets the inner GPU_Image object ptr.
        const GPU_Image *Image() const;
        
    private:
        /// Private implementation
        Impl *impl;
    };
}
