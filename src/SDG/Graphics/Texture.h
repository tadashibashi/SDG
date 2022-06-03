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
    enum class TexFormat 
    {
        Auto,
        Png,
        Tga,
        Bmp
    };

    enum class TexSnap
    {
        None,
        Position,
        Dimensions,
        PositionAndDimensions
    };

    enum class TexFilter
    {
        Linear,
        LinearMipMap,
        Nearest
    };
    /// Texture class automatically frees texture when this object goes out
    /// of scope. Please be aware of this, as the object will become
    /// invalidated if the destructor is called.
    class Texture
    {
        struct Impl;
    public:
        /// Initializes an unloaded Texture
        Texture();
        /// Loads a texture loaded from the given path.
        Texture(Ref<class Window> context, const Path &path);
        
        /// Copies image data into this new Texture
        Texture(const Texture &tex);

        /// Copies data into this new Texture
        Texture &operator = (const Texture &tex);

        Texture(Ref<class Window> context, SDL_Surface *surf, const Path &path = Path());
        explicit Texture(GPU_Image *image);

        /// Automatically frees the internal texture if one was loaded.
        ~Texture();

    public:
        // ========== Resource Management ==========

        /// Load an image into the Texture.
        /// @param path path to the image file. Must be in png, tga, or bmp format.
        /// @param context context to create texture with - it will only render in this context.
        bool Load(Ref<class Window> context, const Path &path);

        /// Load an image from a surface. Ownership of surface is passed to the Texture.
        /// @param surf the surface to load
        /// @param context context to create texture with - it will only render in this context.
        /// @param path path that the surface was loaded from. Made optional since there is not always one.
        bool LoadFromSurface(Ref<class Window> context, SDL_Surface *surf, const Path &path = Path());

        bool LoadPixels(Ref<class Window> context, uint32_t width, uint32_t height, const uint8_t *rgbaPixels);

        /// Saves the file in a certain format
        bool SaveAs(const Path &filepath, TexFormat format = TexFormat::Png);

        /// Free the internal texture, and resets container for reuse.
        void Close();

        /// Swap the internals of this Texture with another
        void Swap(Texture &tex);

        /// Creates an alias of this Texture to another. All setters/getters
        /// and even Close will not affect the original's data.
        /// In practice, this can be used to quickly load various preset modes.
        bool MakeAlias(Texture *alias);

        // ========== Getters/ Setters ==========
        // Static -------------------------------

        static void DefaultFilterMode(TexFilter mode);
        static TexFilter DefaultFilterMode();
        static void DefaultSnapMode(TexSnap mode);
        static TexSnap DefaultSnapMode();
        static void DefaultAnchor(Vector2 anchor);
        static Vector2 DefaultAnchor();
        TexSnap SnapMode() const;
        Texture &SnapMode(TexSnap snapMode);

        // Member functions ----------------------

        bool Blending() const;
        Texture &Blending(bool blending);

        TexFilter FilterMode() const;
        Texture &FilterMode(TexFilter mode);

        Vector2 Anchor() const;
        Texture &Anchor(Vector2 anchor);

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
