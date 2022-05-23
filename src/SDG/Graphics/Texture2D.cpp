#include "Texture2D.h"
#include "RenderTarget.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Debug/Logging.h>
#include <SDG/Debug/Trace.h>

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
    struct Texture2D::Impl {
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
    Texture2D::Texture2D() : impl(new Impl)
    {

    }

    Texture2D::Texture2D(Ref<Window> context, const Path &path) : impl(new Impl)
    {
        Load(context, path);
    }

    Texture2D::Texture2D(Ref<Window> context, SDL_Surface *surf, const Path &path) : impl(new Impl)
    {
        LoadFromSurface(context, surf, path);
    }

    Texture2D::~Texture2D()
    {
        impl->Free();
        delete impl;
    }

    void
    Texture2D::Free()
    {
        impl->Free();
    }

    bool
    Texture2D::LoadFromSurface(Ref<Window> context, SDL_Surface *surf, const Path &path)
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
    Texture2D::Load(Ref<Window> context, const Path &path)
    {
        SDG_Assert(context); // context must not be null

        Free(); // make sure the texture is clean before loading

        File file;
        if (!file.Open(path))
        {
            SDG_Core_Err("problem while loading Texture2D file: {}", file.GetError());
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

    // ========= Getters ======================================================

    bool
    Texture2D::IsLoaded() const
    {
        return static_cast<bool>(impl->image);
    }

    Ref<GPU_Image>
    Texture2D::Image() const
    {
        SDG_Assert(IsLoaded());
        return Ref{impl->image};
    }

    const Path &
    Texture2D::Filepath() const
    {
        SDG_Assert(IsLoaded());
        return impl->path;
    }

    Point
    Texture2D::Size() const
    {
        SDG_Assert(IsLoaded());
        return {impl->image->base_w, impl->image->base_h};
    }
}
