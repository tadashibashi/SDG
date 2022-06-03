#include "Texture.h"
#include "RenderTarget.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Log.h>
#include <SDG/Debug/Trace.h>

#include <SDG/Exceptions/RuntimeException.h>
#include <SDG/Exceptions/NullReferenceException.h>

#include <SDG/FileSys/File.h>
#include <SDG/Graphics/Window.h>

#include <SDL_gpu.h>

#include <utility>


// Prevent Windows API macro clashes
#ifdef M_PI
#undef M_PI
#endif

#ifdef LoadImage
#undef LoadImage
#endif


namespace SDG
{
    static TexFilter defFilterMode = TexFilter::Linear;
    static TexSnap defSnapMode = TexSnap::Position;
    static Vector2 defAnchor = Vector2(0, 0);

    void Texture::DefaultFilterMode(TexFilter mode)
    {
        defFilterMode = mode;
    }

    void Texture::DefaultSnapMode(TexSnap mode)
    {
        defSnapMode = mode;
    }

    TexFilter Texture::DefaultFilterMode()
    {
        return defFilterMode;
    }

    TexSnap Texture::DefaultSnapMode()
    {
        return defSnapMode;
    }

    void Texture::DefaultAnchor(Vector2 anchor)
    {
        defAnchor = anchor;
    }

    Vector2 Texture::DefaultAnchor() { return defAnchor; }

    /// ========= Implementation class for Texture 2D =========================
    struct Texture::Impl {
        Impl() : image(), path() {}
        GPU_Image *image;

        // Sub-image data, to translate relative to the image
        Path path;

        void Free()
        {
            if (image)
            {
                GPU_FreeImage(image);
                image = nullptr;
                path = Path();
            }
        }
    };

    // ======== Constructors, Destructors, Initialization, Closure ============
    Texture::Texture() : impl(new Impl)
    {

    }

    Texture::Texture(Ref<Window> context, const Path &path) : impl(new Impl)
    {
        Load(context, path);
    }

    Texture::Texture(Ref<Window> context, SDL_Surface *surf, const Path &path) : impl(new Impl)
    {
        LoadFromSurface(context, surf, path);
    }

    Texture::Texture(GPU_Image *image) : impl(new Impl)
    {
        impl->image = image;
    }


    Texture::Texture(const Texture &tex) : impl(new Impl)
    {
        if (tex.IsLoaded())
        {
            GPU_Image *image = GPU_CopyImage(tex.Image().Get());
            if (!image)
            {
                throw RuntimeException("Texture: failed to copy GPU_Image"
                    "during copy construction");
            }

            impl->image = image;
            impl->path = tex.impl->path;
        }
    }


    Texture &Texture::operator = (const Texture &tex)
    {
        Close();

        if (tex.IsLoaded())
        {
            GPU_Image *image = GPU_CopyImage(tex.Image().Get());
            if (!image)
            {
                throw RuntimeException("Texture: failed to copy GPU_Image "
                    "during copy assignment");
            }

            impl->image = image;
            impl->path = tex.impl->path;
        }

        return *this;
    }

    Texture::~Texture()
    {
        Close();
        delete impl;
    }

    void
    Texture::Close()
    {
        impl->Free();
    }

    void Texture::Swap(Texture &tex)
    {
        std::swap(impl, tex.impl);
    }

    TexSnap Texture::SnapMode() const
    {
        GPU_SnapEnum snap = GPU_GetSnapMode(impl->image);
        switch (snap)
        {
        case GPU_SNAP_NONE: return TexSnap::None;
        case GPU_SNAP_POSITION: return TexSnap::Position;
        case GPU_SNAP_DIMENSIONS: return TexSnap::Dimensions;
        case GPU_SNAP_POSITION_AND_DIMENSIONS: return TexSnap::PositionAndDimensions;
        default: // in case GPU updates new values
            throw RuntimeException("Internal error: unknown GPU_SnapEnum argument");
        }
    }

    Texture &Texture::SnapMode(TexSnap snapMode)
    {
        GPU_SnapEnum snapEnum;
        switch (snapMode)
        {
        case TexSnap::None: snapEnum = GPU_SNAP_NONE; break;
        case TexSnap::Position: snapEnum = GPU_SNAP_POSITION; break;
        case TexSnap::Dimensions: snapEnum = GPU_SNAP_DIMENSIONS; break;
        case TexSnap::PositionAndDimensions: snapEnum = GPU_SNAP_POSITION_AND_DIMENSIONS; break;
        default:
            throw InvalidArgumentException("Texture::SnapMode(TexSnap mode)", "mode");
        }

        GPU_SetSnapMode(impl->image, snapEnum);

        return *this;
    }

    Texture &Texture::Blending(bool blending)
    {
        GPU_SetBlending(impl->image, blending);
        
        return *this;
    }

    bool Texture::Blending() const
    {
        return GPU_GetBlending(impl->image);
    }

    Texture &Texture::FilterMode(TexFilter mode)
    {
        GPU_FilterEnum gpuMode;
        switch (mode)
        {
        case TexFilter::Linear: gpuMode = GPU_FILTER_LINEAR; break;
        case TexFilter::LinearMipMap: gpuMode = GPU_FILTER_LINEAR_MIPMAP; break;
        case TexFilter::Nearest: gpuMode = GPU_FILTER_NEAREST; break;
        default:
            throw InvalidArgumentException("Texture::FilterMode(Filter mode)", "mode");
        }

        GPU_SetImageFilter(impl->image, gpuMode);

        return *this;
    }

    TexFilter Texture::FilterMode() const
    {
        switch (impl->image->filter_mode)
        {
        case GPU_FILTER_LINEAR: return TexFilter::Linear;
        case GPU_FILTER_LINEAR_MIPMAP: return TexFilter::LinearMipMap;
        case GPU_FILTER_NEAREST: return TexFilter::Nearest;
        default:
            throw RuntimeException("GPU_FilterEnum value not anticipated by SDG_Engine, internal error");
        }
    }

    Vector2 Texture::Anchor() const
    {
        float x, y;
        GPU_GetAnchor(impl->image, &x, &y);

        return { x, y };
    }

    Texture &Texture::Anchor(Vector2 anchor)
    {
        GPU_SetAnchor(impl->image, anchor.X(), anchor.Y());
        return *this;
    }

    bool
    Texture::LoadFromSurface(Ref<Window> context, SDL_Surface *surf, const Path &path)
    {
        SDG_Assert(context);         // context must not be null
        SDG_Assert(surf != nullptr); // if surface is null, the function that
                                     // created the surface  probably failed.
        // Make sure the texture is clean before loading
        Close();

        // Textures will load from this context
        context->MakeCurrent();

        // Surface -> GPU_Image
        GPU_Image *image = GPU_CopyImageFromSurface(surf);
        SDL_FreeSurface(surf); // surface data gets copied, so we no longer need it.

        if (!image)
        {
            SDG_Core_Err("{}: SDL_gpu failed to copy image from SDL_Surface: {}", SDG_TRACE(),
                GPU_GetErrorString(GPU_PopErrorCode().error));
            return false;
        }
        
        // Conversion was successful, commit changes
        impl->image = image;
        impl->path = path;

        FilterMode(defFilterMode); // pixel art style
        SnapMode(defSnapMode);
        Anchor(defAnchor);
        return true;
    }

    bool 
    Texture::LoadPixels(Ref<class Window> context, uint32_t width, uint32_t height, const uint8_t *rgbaPixels)
    {
        if (!context)
            throw NullReferenceException();

        Close();
        
        context->MakeCurrent();
        GPU_Image *img = GPU_CreateImage(width, height, GPU_FORMAT_RGBA);
        if (!img)
        {
            throw RuntimeException(String::Format("SpriteBatch: failed to "
                "create GPU_Image pixel: {}", GPU_PopErrorCode().details));
        }

        img->bytes_per_pixel = 4; // one byte per channel
        
        GPU_Rect rect{ 0, 0, static_cast<float>(width), static_cast<float>(height) };
        GPU_UpdateImageBytes(img, &rect, rgbaPixels, 4 * width);
        
        impl->image = img;
        FilterMode(defFilterMode);
        SnapMode(defSnapMode);
        Anchor(defAnchor);
        return true;
    }


    bool
    Texture::Load(Ref<Window> context, const Path &path)
    {
        SDG_Assert(context); // context must not be null

        Close(); // make sure the texture is clean before loading

        File file;
        if (!file.Open(path))
        {
            SDG_Core_Err("problem while loading Texture file: {}", file.GetError());
            return false;
        }

        SDL_RWops *io = SDL_RWFromConstMem(file.Data(), file.Size());
        if (!io)
        {
            SDG_Core_Err("problem while sending data to SDL_RWops: {}", SDL_GetError());
            return false;
        }

        context->MakeCurrent();
        GPU_Image *tempImage = GPU_LoadImage_RW(io, true);
        if (!tempImage)
        {
            SDG_Core_Err("problem loading image file ({}): {}", path.Str(),
                    GPU_PopErrorCode().details);
            return false;
        }

        // Finished without errors, set internals
        impl->image = tempImage;
        impl->path = path;
        FilterMode(defFilterMode);
        SnapMode(defSnapMode);
        Anchor(defAnchor);
        return true;
    }

    bool Texture::SaveAs(const Path &filepath, TexFormat format)
    {
        GPU_FileFormatEnum gpuFormat;
        String path = filepath.Str();

        switch (format)
        {
        case TexFormat::Auto: gpuFormat = GPU_FILE_AUTO; break;
        case TexFormat::Png: gpuFormat = GPU_FILE_PNG; break;
        case TexFormat::Tga: gpuFormat = GPU_FILE_TGA; break;
        case TexFormat::Bmp: gpuFormat = GPU_FILE_BMP; break;
        default:
            throw InvalidArgumentException(
                "Texture::SaveAs(const Path &filepath, Format format)", 
                "format");
        }

        SDL_RWops * io = SDL_RWFromFile(path.Cstr(), "r+");
        if (!io)
        {
            throw RuntimeException(String::Format("Texture::SaveAs: failed to "
                "create file at {}: {}. Does the program have adequate write "
                "permissions here?", filepath.Str(), SDL_GetError()));
        }

        if (!GPU_SaveImage_RW(impl->image, io, true, gpuFormat))
        {
            throw RuntimeException("Texture::SaveAs: failure during GPU_SaveImage_RW");
        }

        return true;
    }

    // ========= Getters ======================================================

    bool
    Texture::IsLoaded() const
    {
        return static_cast<bool>(impl->image);
    }

    Ref<GPU_Image>
    Texture::Image() const
    {
        SDG_Assert(IsLoaded());
        return Ref{impl->image};
    }

    const Path &
    Texture::Filepath() const
    {
        SDG_Assert(IsLoaded());
        return impl->path;
    }

    Point
    Texture::Size() const
    {
        SDG_Assert(IsLoaded());
        return {impl->image->base_w, impl->image->base_h};
    }
}
