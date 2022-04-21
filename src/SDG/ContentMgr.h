#pragma once
#include <string>
#include <map>
#include "Texture2D.h"

namespace SDG
{
    class ContentMgr {
    public:
        ~ContentMgr();

        /**
         * Retrieves a texture already cached in the ContentMgr or loads a new one at the given path.
         * Nullptr if there was none at the path.
         * Supported file types: png, bmp, tga
         * @param path
         * @return
         */
        const Texture2D *LoadTexture(const std::string &path);
        
        void UnloadTexture(const std::string &path);
        void UnloadTexture(Texture2D *texture);


        /**
         * Unloads every Texture2D currently cached in the ContentMgr.
         * All pointers are invalidated, so any object attempting to
         * use them will experience undefined behavior.
         */
        void UnloadTextures();


        /**
         * Unloads every piece of content loaded in the ContentMgr.
         */
        void UnloadAll();
    private:
        std::map<std::string, Texture2D *> textures;
    };
}

