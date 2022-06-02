#include "AssetMgr.h"
#include <SDL_gpu.h>
#include <SDG/Debug/Assert.h>

namespace SDG
{
    AssetMgr::~AssetMgr()
    {

    }

    void
    AssetMgr::UnloadTextures()
    {
        if (!textures.empty())
        {
            for (auto &[k, v] : textures)
            {
                v->Free();
            }
        }
    }

    void
    AssetMgr::UnloadAll()
    {
        UnloadTextures();
        // add other unloading stuff here.
    }

    CRef<Texture>
    AssetMgr::LoadTexture(const Path &path)
    {
        SDG_Assert(context); // Please make sure to set the context via Initialize() before loading textures.

        uint64_t hash = path.Hash();
        auto it = textures.find(hash);

        if (it != textures.end())
            return CRef{it->second};
        else
        {
            auto tex = new Texture;
            if (tex->Load(context, path))
            {
                textures[hash] = tex;
                return CRef{tex};
            }
            else
            {
                delete tex;
                return CRef<Texture>{}; // nullptr
            }
        }
    }

    void 
    AssetMgr::UnloadTexture(const Path &path)
    {
        auto it = textures.find(path.Hash());
        if (it != textures.end())
        {
            textures.erase(it);
            delete it->second;
        }
    }

    void 
    AssetMgr::UnloadTexture(Ref<Texture> texture)
    {
        SDG_Assert(texture);
        UnloadTexture(texture->Filepath());
    }

    void AssetMgr::Initialize(Ref<Window> context)
    {
        this->context = context;
    }

} /* end namespace SDG */
