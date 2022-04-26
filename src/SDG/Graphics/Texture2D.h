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
        explicit Texture2D(const std::string &path);
        ~Texture2D();
        
        // Prevent copying.
        Texture2D(const Texture2D &) = delete;
        Texture2D &operator=(const Texture2D &) = delete;
        
        /// <summary>
        /// Gets the inner GPU_Image object ptr.
        /// </summary>
        /// <returns></returns>
        GPU_Image *GetImage() { return mImage; }

        /// <summary>
        /// Load an image into the Texture2D.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        bool LoadImage(const std::string &path);
        void Close();

        /// @abstract Get the image's anchor points
        void GetAnchor(int *x, int *y) const;
        void GetOffset(int *x, int *y) const;
        bool WasLoaded() const;
        std::string GetPath() const { return mPath; }
        
    private:
        GPU_Image *mImage;

        // Sub-image data, to translate relative to the image
        int mWidth, mHeight, mAnchorX, mAnchorY, mOffsetX, mOffsetY;
        bool mRotated;
        std::string mPath;
    };
}