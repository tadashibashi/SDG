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


    // TODO: Move all of this into a file loading class. LoadImage should then call this func.
    static std::string encryptionKey = "john316";
    bool
    Texture2D::LoadImage(const std::string &path)
    {
        // Make sure the texture is clean before loading
        Close();

        SDL_RWops *io = SDL_RWFromFile(FileSys::MakePath(path + ".sdgc").c_str(), "rb");
        if (!io)
        {
            SDG_Err("could not read from file {}: {}", path, SDL_GetError());
            return false;
        }

        std::vector<unsigned char> imageData;
        SDL_RWseek(io, 0, RW_SEEK_END);
        Sint64 fileSize = SDL_RWtell(io);
        SDL_RWseek(io, 0, RW_SEEK_SET);
        imageData.reserve(fileSize);

        for (Sint64 i = 0; i < fileSize; ++i)
        {
            unsigned char c;
            SDL_RWread(io, &c, 1, 1);
            unsigned char add = encryptionKey[i % encryptionKey.length()];

            imageData.push_back(c - add + i);
        }
        SDL_FreeRW(io);

        io = SDL_RWFromMem(imageData.data(), (int)imageData.size());
        if (!io)
        {
            SDG_Err("Failed to create RWops from memory: {}", SDL_GetError());
            return false;
        }

        GPU_Image *tempImage = GPU_LoadImage_RW(io, true);
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
