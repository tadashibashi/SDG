#include "Texture.h"
#include "RenderTarget.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Log.h>
#include <SDG/Debug/Trace.h>

#include <SDG/Exceptions/RuntimeException.h>

#include <SDG/FileSys/File.h>
#include <SDG/Graphics/Window.h>

#include <SDL_gpu.h>


// Prevent Windows API macro clashes
#ifdef M_PI
#undef M_PI
#endif

#ifdef LoadImage
#undef LoadImage
#endif


namespace SDG
{
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

    Texture::~Texture()
    {
        impl->Free();
        delete impl;
    }

    void
    Texture::Free()
    {
        impl->Free();
    }

    Texture::Snap Texture::SnapMode() const
    {
        GPU_SnapEnum snap = GPU_GetSnapMode(impl->image);
        switch (snap)
        {
        case GPU_SNAP_NONE: return Snap::None;
        case GPU_SNAP_POSITION: return Snap::Position;
        case GPU_SNAP_DIMENSIONS: return Snap::Dimensions;
        case GPU_SNAP_POSITION_AND_DIMENSIONS: return Snap::Both;
        default: // in case GPU updates add new ones
            throw RuntimeException("Unknown GPU_SnapEnum argument");
        }
    }

    Texture &Texture::SnapMode(Snap snapMode)
    {
        GPU_SnapEnum snapEnum;
        switch (snapMode)
        {
        case Snap::None: snapEnum = GPU_SNAP_NONE; break;
        case Snap::Position: snapEnum = GPU_SNAP_POSITION; break;
        case Snap::Dimensions: snapEnum = GPU_SNAP_DIMENSIONS; break;
        case Snap::Both: snapEnum = GPU_SNAP_POSITION_AND_DIMENSIONS; break;
        default:
            throw InvalidArgumentException("Texture::SnapMode(SDG::SnapMode mode)", "mode");
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

    Texture &Texture::FilterMode(Filter mode)
    {
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
        switch (impl->image->filter_mode)
        {
        case GPU_FILTER_LINEAR: return Filter::Linear;
        case GPU_FILTER_LINEAR_MIPMAP: return Filter::LinearMipMap;
        case GPU_FILTER_NEAREST: return Filter::Nearest;
        default:
            throw RuntimeException("GPU_FilterEnum value not anticipated by SDG_Engine, internal error");
        }
    }

    bool
    Texture::LoadFromSurface(Ref<Window> context, SDL_Surface *surf, const Path &path)
    {
        SDG_Assert(context);         // context must not be null
        SDG_Assert(surf != nullptr); // if surface is null, the function that
                                     // created the surface  probably failed.
        // Make sure the texture is clean before loading
        Free();

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
        return true;
    }


    bool
    Texture::Load(Ref<Window> context, const Path &path)
    {
        SDG_Assert(context); // context must not be null

        Free(); // make sure the texture is clean before loading

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

        return true;
    }

    bool Texture::SaveAs(const Path &filepath, Format format)
    {
        GPU_FileFormatEnum gpuFormat;
        switch (format)
        {
        case Format::Auto: gpuFormat = GPU_FILE_AUTO; break;
        case Format::Png: gpuFormat = GPU_FILE_PNG; break;
        case Format::Tga: gpuFormat = GPU_FILE_TGA; break;
        case Format::Bmp: gpuFormat = GPU_FILE_BMP; break;
        default:
            throw InvalidArgumentException("Texture::SaveAs(const Path &filepath, Format format)", "format");
        }

        return GPU_SaveImage(impl->image, filepath.Str().Cstr(), gpuFormat);
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
