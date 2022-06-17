#include "Texture.h"
#include "RenderTarget.h"

#include <Engine/Debug/Assert.h>
#include <Engine/Debug/Log.h>
#include <Engine/Debug/Trace.h>

#include <Engine/Exceptions.h>

#include <Engine/Filesys/File.h>
#include <Engine/Graphics/Window.h>

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
    static Texture::Filter defFilterMode = Texture::Filter::Linear;
    static Texture::Snap defSnapMode = Texture::Snap::Position;
    static Vector2 defAnchor = Vector2(0, 0);

    void Texture::DefaultFilterMode(Filter mode)
    {
        defFilterMode = mode;
    }

    void Texture::DefaultSnapMode(Snap mode)
    {
        defSnapMode = mode;
    }

    Texture::Filter Texture::DefaultFilterMode()
    {
        return defFilterMode;
    }

    Texture::Snap Texture::DefaultSnapMode()
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

    Texture::Texture(Window *context, const Path &path) : impl(new Impl)
    {
        Load(context, path);
    }

    Texture::Texture(Window *context, SDL_Surface *surf, const Path &path) : impl(new Impl)
    {
        LoadFromSurface(context, surf, path);
    }

    // Takes on ownership of image
    Texture::Texture(GPU_Image *image) : impl(new Impl)
    {
        impl->image = std::move(image);
    }

    // Copy constructor
    Texture::Texture(const Texture &tex) : impl(new Impl)
    {
        if (tex.impl->image)
        {
            auto image = GPU_CopyImage(tex.impl->image);
            if (!image)
                SDG_Core_Err("Failed to copy Texture: {}", GPU_PopErrorCode().details);
            impl->image = image;
            impl->path = tex.impl->path;
        }
    }

    // Copy assignment
    auto Texture::operator = (const Texture &tex) -> Texture &
    {
        if (impl != tex.impl)
        {
            Unload();
            if (tex.impl->image)
            {
                auto image = GPU_CopyImage(tex.impl->image);
                if (!image)
                    SDG_Core_Err("Texture copy failed: {}", GPU_PopErrorCode().details);
                impl->image = image;
                impl->path = tex.impl->path;
            }
        }

        return *this;
    }

    // Move constructor
    auto Texture::operator = (Texture &&tex) noexcept -> Texture &
    {
        if (impl != tex.impl)
        {
            Unload();
            impl = tex.impl;
            tex.impl = nullptr;
        }

        return *this;
    }

    auto Texture::Unload() -> void
    {
        impl->Free();
    }

    Texture::~Texture()
    {
        Unload();
        delete impl;
    }

    void Texture::Swap(Texture &tex)
    {
        std::swap(impl, tex.impl);
    }

    Texture::Snap Texture::SnapMode() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_SnapEnum snap = GPU_GetSnapMode(impl->image);
        switch (snap)
        {
        case GPU_SNAP_NONE: return Texture::Snap::None;
        case GPU_SNAP_POSITION: return Texture::Snap::Position;
        case GPU_SNAP_DIMENSIONS: return Texture::Snap::Dimensions;
        case GPU_SNAP_POSITION_AND_DIMENSIONS: return Texture::Snap::PositionAndDimensions;
        default: // in case GPU updates new values
            throw RuntimeException("Internal error: unknown GPU_SnapEnum argument");
        }
    }

    Texture &Texture::SnapMode(Texture::Snap snapMode)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_SnapEnum snapEnum;
        switch (snapMode)
        {
        case Texture::Snap::None: snapEnum = GPU_SNAP_NONE; break;
        case Texture::Snap::Position: snapEnum = GPU_SNAP_POSITION; break;
        case Texture::Snap::Dimensions: snapEnum = GPU_SNAP_DIMENSIONS; break;
        case Texture::Snap::PositionAndDimensions: snapEnum = GPU_SNAP_POSITION_AND_DIMENSIONS; break;
        default:
            throw InvalidArgumentException("Texture::SnapMode(TexSnap mode)", "mode");
        }

        GPU_SetSnapMode(impl->image, snapEnum);

        return *this;
    }

    Texture &Texture::Blending(bool blending)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_SetBlending(impl->image, blending);
        
        return *this;
    }

    bool Texture::Blending() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        return GPU_GetBlending(impl->image);
    }

    Texture &Texture::FilterMode(Filter mode)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_FilterEnum gpuMode;
        switch (mode)
        {
        case Filter::Linear: gpuMode = GPU_FILTER_LINEAR; break;
        case Filter::LinearMipMap: gpuMode = GPU_FILTER_LINEAR_MIPMAP; break;
        case Filter::Nearest: gpuMode = GPU_FILTER_NEAREST; break;
        default:
            throw InvalidArgumentException("Texture::FilterMode(Filter mode)", "mode");
        }

        GPU_SetImageFilter(impl->image, gpuMode);

        return *this;
    }

    Texture::Filter Texture::FilterMode() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        switch (impl->image->filter_mode)
        {
        case GPU_FILTER_LINEAR: return Filter::Linear;
        case GPU_FILTER_LINEAR_MIPMAP: return Filter::LinearMipMap;
        case GPU_FILTER_NEAREST: return Filter::Nearest;
        default:
            throw RuntimeException("GPU_FilterEnum value not anticipated by SDG_Engine, internal error");
        }
    }

    Vector2 Texture::Anchor() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        float x, y;
        GPU_GetAnchor(impl->image, &x, &y);

        return { x, y };
    }

    Texture &Texture::Anchor(Vector2 anchor)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_SetAnchor(impl->image, anchor.X(), anchor.Y());
        return *this;
    }

    static Texture::Wrap ToTextureWrap(GPU_WrapEnum gpuWrap)
    {
        switch (gpuWrap)
        {
        case GPU_WRAP_NONE: return Texture::Wrap::None;
        case GPU_WRAP_REPEAT: return Texture::Wrap::Repeat;
        case GPU_WRAP_MIRRORED: return Texture::Wrap::Mirror;
        default:
            throw UncaughtCaseException("missing GPU_WRAP_* enum conversion case");
        }
    }

    namespace Conv
    {
        static GPU_WrapEnum ToGPUWrap(Texture::Wrap mode)
        {
            switch (mode)
            {
            case Texture::Wrap::None: return GPU_WRAP_NONE;
            case Texture::Wrap::Repeat: return GPU_WRAP_REPEAT;
            case Texture::Wrap::Mirror: return GPU_WRAP_MIRRORED;
            default:
                throw InvalidArgumentException("Private ToGPUWrapEnum(Texture::Wrap mode)", "mode");
            }
        }
    }

    Texture::Wrap Texture::WrapModeX() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        return ToTextureWrap(impl->image->wrap_mode_x);
    }

    Texture::Wrap Texture::WrapModeY() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        return ToTextureWrap(impl->image->wrap_mode_y);
    }

    Texture &Texture::WrapMode(Texture::Wrap x, Texture::Wrap y)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_SetWrapMode(impl->image, Conv::ToGPUWrap(x), Conv::ToGPUWrap(y));
        return *this;
    }

    auto Texture::LoadFromSurface(Window *context, SDL_Surface *surf, const Path &path) -> bool
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        SDG_Assert(context);         // context must not be null
        SDG_Assert(surf != nullptr); // if surface is null, the function that
                                     // created the surface  probably failed.
        // Make sure the texture is clean before loading
        Unload();

        // Textures will load from this context
        context->MakeCurrent();

        // Surface -> GPU_Image
        auto image = GPU_CopyImageFromSurface(surf);
        SDL_FreeSurface(surf); // surface data gets copied, so we no longer need it.

        if (!image)
        {
            SDG_Core_Err("{}: SDL_gpu failed to copy image from SDL_Surface: {}", SDG_TRACE,
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
    Texture::LoadPixels(Window *context, uint32_t width, uint32_t height, const uint8_t *rgbaPixels)
    {
        if (!context)
            throw NullReferenceException();

        Unload();
        
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
        
        impl->image = std::move(img);
        FilterMode(defFilterMode);
        SnapMode(defSnapMode);
        Anchor(defAnchor);
        return true;
    }


    bool
    Texture::Load(Window *context, const Path &path)
    {
        SDG_Assert(context); // context must not be null

        Unload(); // make sure the texture is clean before loading

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
        impl->image = std::move(tempImage);
        impl->path = path;
        FilterMode(defFilterMode);
        SnapMode(defSnapMode);
        Anchor(defAnchor);
        return true;
    }

    bool Texture::SaveAs(const Path &filepath, FileFormat format)
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");

        GPU_FileFormatEnum gpuFormat;
        String path = filepath.Str();

        switch (format)
        {
        case FileFormat::Auto: gpuFormat = GPU_FILE_AUTO; break;
        case FileFormat::Png: gpuFormat = GPU_FILE_PNG; break;
        case FileFormat::Tga: gpuFormat = GPU_FILE_TGA; break;
        case FileFormat::Bmp: gpuFormat = GPU_FILE_BMP; break;
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

    const GPU_Image *
    Texture::Image() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");
        return impl->image;
    }

    const Path &
    Texture::Filepath() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");
        return impl->path;
    }

    Point
    Texture::Size() const
    {
        if (!impl->image)
            throw NullReferenceException("Access violation on unloaded Texture");
        return {impl->image->base_w, impl->image->base_h};
    }
}
