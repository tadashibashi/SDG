//
// Created by Aaron Ishibashi on 4/16/22.
//
#pragma once
#include <string>

class GPU_Image;
class GPU_Target;

namespace SDG
{
    class Texture2D
    {
    public:
        Texture2D();
        ~Texture2D();

        /// @abstract Gets the inner GPU_Image object ptr.
        ///     Please make sure to include SDL_gpu.h to any file that attempts to access
        ///     this pointer's internals.
        const GPU_Image *GetImage() { return image; }
        bool LoadImage(const std::string &path);
        void Close();

        /// @abstract Get the image's anchor points
        void GetAnchor(float *x, float *y) const;

        bool WasLoaded() const;

        void Render(GPU_Target *target, float x, float y, float rotation);
    private:
        GPU_Image *image;

        // Sub-image data, to translate relative to the image
        int width, height, anchorX, anchorY, offsetX, offsetY;
        bool rotated;
    };
}