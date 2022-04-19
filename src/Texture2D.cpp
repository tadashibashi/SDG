//
// Created by Aaron Ishibashi on 4/16/22.
//
#include "Texture2D.h"
#include "FileSys.h"
#include "Logging.h"

#include <SDL_gpu.h>

namespace SDG
{
    Texture2D::Texture2D() : image{}
    {

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
        GPU_Image *tempImage = GPU_LoadImage(FileSys::MakePath(path).c_str());
        if (!tempImage)
        {
            SDG_Err("problem loading image file ({}): {}", path, GPU_PopErrorCode().details);
            return false;
        }

        image = tempImage;
        return true;
    }

    void
    Texture2D::GetAnchor(float *x, float *y) const
    {
        assert(image);
        *x = image->anchor_x;
        *y = image->anchor_y;
    }

    bool
    Texture2D::WasLoaded() const
    {
        return image;
    }
}