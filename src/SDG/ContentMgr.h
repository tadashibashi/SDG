#pragma once
#include <string>
#include <map>
#include "Texture2D.h"

namespace SDG
{
    class ContentMgr {
    public:
        ~ContentMgr();

        /// <summary>
        /// Retrieves a texture already cached in the ContentMgr or loads a new one at the given path.
        /// Nullptr if there was none at the path.
        /// Filetypes supported: png, bmp,
        /// </summary>
        /// <param name="path">Path to the image.</param>
        const Texture2D *LoadTexture(const std::string &path);
        
        void UnloadTexture(const std::string &path);
        void UnloadTexture(Texture2D *texture);

        /// <summary>
        /// Unloads every Texture2D currently cached in the ContentMgr.
        /// All pointers are invalidated, so any object attempting to
        /// use them will experience undefined behavior.
        /// </summary>
        void UnloadTextures();
        void UnloadAll();
    private:
        std::map<std::string, Texture2D *> textures;
    };
}

