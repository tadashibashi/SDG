#include "AssetMgr.h"
#include <SDL_gpu.h>
#include "FileSys.h"

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
             v->Close();
        }
    }
}

void
SDG::AssetMgr::UnloadAll()
{
    UnloadTextures();
}

const SDG::Texture2D *
SDG::AssetMgr::LoadTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it != textures.end())
        return it->second;
    else
    {
        auto tex = new Texture2D;
        if (tex->LoadImage(path))
        {
            textures[path] = tex;
            return tex;
        }
        else
        {
            delete tex;
            return nullptr;
        }
    }
}

void 
SDG::AssetMgr::UnloadTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it != textures.end())
    {
        textures.erase(it);
        delete it->second;
    }
}

void 
SDG::AssetMgr::UnloadTexture(Texture2D *texture)
{
    UnloadTexture(texture->GetPath());
}
