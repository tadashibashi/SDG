#include "Texture2D.h"
#include <SDG/FileSys/FileSys.h>
#include <SDG/FileSys/File.h>
#include <SDG/Debug.h>
#include <SDL_gpu.h>

#ifdef M_PI
#undef M_PI
#endif

// Prevent Windows API macro clash
#ifdef LoadImage
#undef LoadImage
#endif


namespace SDG
{
    /// ========= Implementation class for Texture 2D =========================
    struct Texture2D::Impl {
        Impl() : image(), size(), anchor(), offset(), rotated(), path() {}
        GPU_Image *image;

        // Sub-image data, to translate relative to the image
        Point size, anchor, offset;
        bool rotated;

        std::string path;

        void Free()
        {
            if (image)
            {
                GPU_FreeImage(image);
                image = nullptr;
                path = "";
                size = Point();
                anchor = Point();
                offset = Point();
                rotated = false;
            }
        }
    };

    // ======== Constructors, Destructors, Initialization, Closure ============
    Texture2D::Texture2D() : impl(new Impl)
    {

    }

    Texture2D::Texture2D(const std::string &path) : impl(new Impl)
    {
        LoadImage(path);
    }

    Texture2D::~Texture2D()
    {
        delete impl;
    }

    void
    Texture2D::Free()
    {
        impl->Free();
    }


    bool
    Texture2D::LoadImage(const std::string &path)
    {
        // Make sure the texture is clean before loading
        Free();

        FileSys::File file;
        if ((FileSys::GetExtension(path) == "sdgc") ? !file.OpenEncrypted(path) : !file.Open(path))
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

        GPU_Image *tempImage = GPU_LoadImage_RW(io, true);
        if (!tempImage)
        {
            SDG_Err("problem loading image file ({}): {}", path,
                    GPU_PopErrorCode().details);
            return false;
        }

        // Finished without errors, set internals
        impl->image = tempImage;
        impl->path = path;

        return true;
    }

    // ========= Getters ======================================================
    Point
    Texture2D::Anchor() const
    {
        SDG_Assert(WasLoaded());
        return impl->anchor;
    }

    Point
    Texture2D::Offset() const
    {
        SDG_Assert(WasLoaded());
        return impl->offset;
    }

    bool
    Texture2D::WasLoaded() const
    {
        return static_cast<bool>(impl->image);
    }

    GPU_Image *
    Texture2D::Image()
    {
        return impl->image;
    }

    std::string
    Texture2D::Path() const
    {
        return impl->path;
    }
}
