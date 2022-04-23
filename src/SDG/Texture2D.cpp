#include "Texture2D.h"
#include "FileSys.h"
#include "Logging.h"

#ifdef M_PI
#undef M_PI
#endif

#include <cassert>
#include <SDL_gpu.h>

// Prevent Windows API macro clash
#ifdef LoadImage
#undef LoadImage
#endif


namespace SDG
{
    Texture2D::Texture2D() : mImage{}, mAnchorX{}, mAnchorY{}, mOffsetX{},
                             mOffsetY{}, mWidth{}, mHeight{}, mRotated{}
    {

    }

    Texture2D::Texture2D(const std::string &path) : mImage{}, mAnchorX{}, mAnchorY{},
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
        if (mImage)
        {
            GPU_FreeImage(mImage);
            mImage = nullptr;
        }
    }


    // TODO: Move all of this into a file loading class. LoadImage should then call this func.
    bool
    Texture2D::LoadImage(const std::string &path)
    {
        // Make sure the texture is clean before loading
        Close();

        int64_t fileSize;
        SDG::RWopsMem io = SDG::FileSys::DecryptFile(path, FileSys::DirectoryBase::Root, &fileSize);

        GPU_Image *tempImage = GPU_LoadImage_RW(io.rwops, false);
        io.Free();
        if (!tempImage)
        {
            SDG_Err("problem loading image file ({}): {}", path, GPU_PopErrorCode().details);
            return false;
        }

        // Finished without errors, set internals
        mImage = tempImage;
        mPath = path;

        return true;
    }

    void
    Texture2D::GetAnchor(int *x, int *y) const
    {
        assert(WasLoaded());
        *x = mImage->anchor_x;
        *y = mImage->anchor_y;
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
        return mImage;
    }
}
