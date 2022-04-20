//
// Created by Aaron Ishibashi on 4/16/22.
//
#include "Texture2D.h"
#include "FileSys.h"
#include "Logging.h"

#include <SDL_gpu.h>
#include <cassert>

// Prevent Windows API macro clash
#ifdef LoadImage
#undef LoadImage
#endif

namespace SDG
{
    Texture2D::Texture2D() : image{}, mAnchorX{}, mAnchorY{}, mOffsetX{}, 
        mOffsetY{}, mWidth{}, mHeight{}, mRotated{}
    {

    }

    Texture2D::Texture2D(const std::string &path) : image{}, mAnchorX{}, mAnchorY{},
        mOffsetX{}, mOffsetY{}, mWidth{}, mHeight{}, mRotated{}
    {
        LoadImage(path);
    }

    Texture2D::~Texture2D()
    {
        Close();
    }

    void
    Texture2D::Close()
    {
        if (image)
        {
            GPU_FreeImage(image);
            image = nullptr;
        }
    }

    bool
    Texture2D::LoadImage(const std::string &path)
    {
        // Make sure the texture is clean before loading
        Close();

        GPU_Image *tempImage = GPU_LoadImage(FileSys::MakePath(path).c_str());
        if (!tempImage)
        {
            SDG_Err("problem loading image file ({}): {}", path, GPU_PopErrorCode().details);
            return false;
        }

        image = tempImage;
        this->mPath = path;

        return true;
    }

    void
    Texture2D::GetAnchor(int *x, int *y) const
    {
        assert(WasLoaded());
        *x = image->anchor_x;
        *y = image->anchor_y;
    }

    void 
    Texture2D::GetOffset(int *x, int *y) const
    {
        assert(WasLoaded());
        *x = mOffsetX;
        *y = mOffsetY;
    }

    bool
    Texture2D::WasLoaded() const
    {
        return image;
    }
}
