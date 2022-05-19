#include "Texture2D.h"
#include "RenderTarget.h"
#include <SDG/FileSys/File.h>
#include <SDG/Debug.hpp>
#include <SDL_gpu.h>
#include <memory>
#include <SDG/Graphics/Window.h>

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

    Texture2D::Texture2D(const Path &path, Ref<Window> target) : impl(new Impl)
    {
        LoadImage(path, target);
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
    Texture2D::LoadImage(const Path &path, Ref<Window> target)
    {
        // Make sure the texture is clean before loading
        Free();

        File file;
        if (!file.Open(path))
        {
            SDG_Err("problem while loading Texture2D file: {}", file.GetError());
            return false;
        }

        SDL_RWops *io = SDL_RWFromConstMem(file.Data(), file.Size());
        if (!io)
        {
            SDG_Err("problem while sending data to SDL_RWops: {}", SDL_GetError());
            return false;
        }

        GPU_MakeCurrent(target->Target()->Target().Get(), target->Id());
        GPU_Image *tempImage = GPU_LoadImage_RW(io, true);
        if (!tempImage)
        {
            SDG_Err("problem loading image file ({}): {}", path.String(),
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

    Texture2D::Texture2D(GPU_Image *image, const Path &path)
    {
        impl->image = image;
        impl->path = path;
    }

    Point Texture2D::Size() const
    {
        SDG_Assert(IsLoaded());
        return {impl->image->base_w, impl->image->base_h};
    }
}
