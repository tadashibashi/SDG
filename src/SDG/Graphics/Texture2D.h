//
// Created by Aaron Ishibashi on 4/16/22.
//
#pragma once
#include <string>
#include "SDG/Math/Vector2.h"
#include "SDG/FileSys/FileInfo.h"

class GPU_Image;
class GPU_Target;

namespace SDG
{
    /// Wrapper around a GPU_Image. Meant to be copied.
    class Texture2D
    {
        struct Impl;
    public:
        Texture2D();
        explicit Texture2D(const std::string &path);
        ~Texture2D();
        

        /// Gets the inner GPU_Image object ptr.
        GPU_Image *Image();

        /// <summary>
        /// Load an image into the Texture2D.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        bool LoadImage(const std::string &path);
        void Free();

        /// @abstract Get the image's anchor points
        Point Anchor() const;
        Point Offset() const;
        bool WasLoaded() const;
        std::string Path() const;
        
    private:
        Impl *impl;
    };
}