/*!
 * @file AssetMgr.h -- SDG_Engine
 * @class AssetMgr
 * Object that manages the loading and unloading of asset files.
 * You can use separate managers and treat them as separate banks.
 * TODO: make a singleton source of asset files that multiple asset managers
 * can share. Perhaps use shared_ptr to store the assets, and then when the
 * last ptr instance gets unloaded/deleted then it gets removed from memory.
 */
#pragma once

#include <Engine/Filesys/Path.h>
#include <Engine/Graphics/Texture.h>
#include <Engine/Lib/Ref.h>

#include <map>

namespace SDG
{
    class Window;

    class AssetMgr {
    public:
        ~AssetMgr();

        /// Sets the context window to load Textures with.
        auto Initialize(Ref<Window> context)->void;

        /**
         * Retrieves a texture already cached in the AssetMgr or loads a new one at the given path.
         * Nullptr if there was none at the path.
         * Supported file types: png, bmp, tga
         * @param path
         * @return
         */
        auto LoadTexture(const Path &path)->Texture;

        /**
         * Unloads the Texture from memory. Unloaded texture ptr/references are valid for the
         * the lifecycle of the app, but only the inner ptr will be freed and null.
         * @param path
         */
        auto UnloadTexture(const Path &path)->void;

        /**
         * Unloads the Texture from memory. Unloaded texture ptr/references are valid for the
         * the lifecycle of the app, but only the inner ptr will be freed and null.
         * @param path
         */
        auto UnloadTexture(const Texture &texture)->void;


        /**
         * Unloads every Texture currently cached in the AssetMgr.
         * All pointers are invalidated, so any object attempting to
         * use them will experience undefined behavior.
         */
        auto UnloadTextures()->void;

        /**
         * Unloads every piece of content loaded in the AssetMgr.
         */
        auto UnloadAll()->void;
    private:
        std::map<uint64_t, Texture> textures;
        Ref<Window> context;
    };
}

