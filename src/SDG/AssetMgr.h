#pragma once
#include <string>
#include <map>
#include "SDG/Graphics/Texture2D.h"

namespace SDG
{
    class AssetMgr {
    public:
        ~AssetMgr();

        /**
         * Retrieves a texture already cached in the AssetMgr or loads a new one at the given path.
         * Nullptr if there was none at the path.
         * Supported file types: png, bmp, tga
         * @param path
         * @return
         */
        const Texture2D *LoadTexture(const std::string &path);

        /**
         * Unloads the Texture2D from memory. Unloaded texture ptr/references are valid for the
         * the lifecycle of the app, but only the inner ptr will be freed and null.
         * @param path
         */
        void UnloadTexture(const std::string &path);

        /**
         * Unloads the Texture2D from memory. Unloaded texture ptr/references are valid for the
         * the lifecycle of the app, but only the inner ptr will be freed and null.
         * @param path
         */
        void UnloadTexture(Texture2D *texture);


        /**
         * Unloads every Texture2D currently cached in the AssetMgr.
         * All pointers are invalidated, so any object attempting to
         * use them will experience undefined behavior.
         */
        void UnloadTextures();


        /**
         * Unloads every piece of content loaded in the AssetMgr.
         */
        void UnloadAll();
    private:
        std::map<std::string, Texture2D *> textures;
    };
}
