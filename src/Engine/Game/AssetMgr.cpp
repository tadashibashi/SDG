#include "AssetMgr.h"
#include <SDL_gpu.h>
#include <Engine/Debug/Assert.h>
#include <Engine/Debug/Log.h>

namespace SDG
{
    AssetMgr::~AssetMgr()
    {

    }

    auto
    AssetMgr::UnloadTextures() -> void
    {
        textures.clear();
    }

    auto
    AssetMgr::UnloadAll() -> void
    {
        UnloadTextures();
        // add other unloading stuff here.
    }

    auto
    AssetMgr::LoadTexture(const Path &path) -> Texture
    {
        SDG_Assert(context); // Please make sure to set the context via Initialize() before loading textures.

        auto hash = path.Hash();
        auto it = textures.find(hash);

        if (it != textures.end())
            return it->second;
        else
        {
            auto tex = Texture{};
            if (tex.Load(context.Get(), path))
            {
                textures[hash] = tex;
                return tex;
            }
            else
            {
                SDG_Core_Err("AssetMgr::LoadTexture: failed to load Texture from {}", path.Str());
                return Texture{};
            }
        }
    }

    void 
    AssetMgr::UnloadTexture(const Path &path)
    {
        auto it = textures.find(path.Hash());
        if (it != textures.end())
            textures.erase(it);
    }

    void 
    AssetMgr::UnloadTexture(const Texture &texture)
    {
        SDG_Assert(texture);
        UnloadTexture(texture.Filepath());
    }

    void AssetMgr::Initialize(URef<Window> context)
    {
        this->context = context;
    }

} /* end namespace SDG */
