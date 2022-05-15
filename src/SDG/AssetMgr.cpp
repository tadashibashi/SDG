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
}

SDG::CRef<SDG::Texture2D>
SDG::AssetMgr::LoadTexture(const Path &path)
{
    std::string pathStr = path.String();
    auto it = textures.find(pathStr);

    if (it != textures.end())
        return CRef{it->second};
    else
    {
        auto tex = new Texture2D;
        if (tex->LoadImage(path))
        {
            textures[pathStr] = tex;
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
    auto it = textures.find(path.String());
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
