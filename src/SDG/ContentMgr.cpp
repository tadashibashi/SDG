//
// Created by Aaron Ishibashi on 4/16/22.
//
#include "ContentMgr.h"
#include <SDL_gpu.h>
#include "FileSys.h"

SDG::ContentMgr::~ContentMgr()
{

}

void
SDG::ContentMgr::UnloadTextures()
{
    if (!textures.empty())
    {
        for (auto &[k, v] : textures)
        {
             v->Close();
             delete v;
        }
        textures.clear();
    }
}

void
SDG::ContentMgr::UnloadAll()
{
    UnloadTextures();
}

const SDG::Texture2D *
SDG::ContentMgr::LoadTexture(const std::string &path)
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
SDG::ContentMgr::UnloadTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it != textures.end())
    {
        textures.erase(it);
        delete it->second;
    }
}

void 
SDG::ContentMgr::UnloadTexture(Texture2D *texture)
{
    UnloadTexture(texture->GetPath());
}

