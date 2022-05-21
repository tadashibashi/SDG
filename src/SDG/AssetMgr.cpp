#include "AssetMgr.h"
#include <SDL_gpu.h>
#include <SDG/Debug/Assert.h>

SDG::AssetMgr::~AssetMgr()
{

}

void
SDG::AssetMgr::UnloadTextures()
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
SDG::AssetMgr::UnloadAll()
{
    UnloadTextures();
    // add other unloading stuff here.
}

SDG::CRef<SDG::Texture2D>
SDG::AssetMgr::LoadTexture(const Path &path)
{
    SDG_Assert(context); // Please make sure to set the context via Initialize() before loading textures.

    uint64_t hash = path.Hash();
    auto it = textures.find(hash);

    if (it != textures.end())
        return CRef{it->second};
    else
    {
        auto tex = new Texture2D;
        if (tex->Load(context, path))
        {
            textures[hash] = tex;
            return CRef{tex};
        }
        else
        {
            delete tex;
            return CRef<Texture2D>{}; // nullptr
        }
    }
}

void 
SDG::AssetMgr::UnloadTexture(const Path &path)
{
    auto it = textures.find(path.Hash());
    if (it != textures.end())
    {
        textures.erase(it);
        delete it->second;
    }
}

void 
SDG::AssetMgr::UnloadTexture(Ref<Texture2D> texture)
{
    SDG_Assert(texture);
    UnloadTexture(texture->Filepath());
}

void SDG::AssetMgr::Initialize(SDG::Ref<SDG::Window> context)
{
    this->context = context;
}
