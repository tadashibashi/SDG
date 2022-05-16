#include "Font.h"
#include <SDL_ttf.h>
#include <SDL_gpu.h>
#include <SDG/Debug/Logging.h>

class SDG::Font::Impl
{
public:
    Impl() : font(), pointSize(), filepath() { }
    TTF_Font *font;
    int pointSize;
    Path filepath;
};

SDG::Font::Font() : impl(new Impl)
{

}

SDG::Font::~Font()
{
    Close();
    delete impl;
}

bool
SDG::Font::Load(const Path &filepath, int pointSize)
{
    TTF_Font *font = TTF_OpenFont(filepath.String().c_str(), pointSize);
    if (!font)
    {
        SDG_Err("Failed to load font from path {}", filepath.String());
        return false;
    }

    impl->font = font;
    impl->pointSize = pointSize;
    impl->filepath = filepath;
    return true;
}

void
SDG::Font::Close()
{
    if (IsLoaded())
    {
        TTF_CloseFont(impl->font);
        impl->font = nullptr;
        impl->pointSize = 0;
        impl->filepath = Path();
    }
}

bool
SDG::Font::IsLoaded() const
{
    return impl->font;
}

const SDG::Path &
SDG::Font::Filepath() const
{
    return impl->filepath;
}

SDG::CRef<TTF_Font>
SDG::Font::InnerFont() const
{
    return CRef<TTF_Font>(impl->font);
}

int SDG::Font::PointSize() const
{
    return impl->pointSize;
}

SDG::Font::operator bool()
{
    return impl->font;
}

static SDG::Texture2D *
SurfaceToTexture(SDL_Surface *surf, const SDG::Path &path)
{
    if (!surf)
    {
        SDG_Err("RenderTextBlended: failed to render text: {}", TTF_GetError());
        return nullptr;
    }

    GPU_Image *image = GPU_CopyImageFromSurface(surf);
    SDL_FreeSurface(surf);

    if (!image)
    {
        SDG_Err("RenderTextBlended: failure while copying text image data: {}", TTF_GetError());
        return nullptr;
    }

    return new SDG::Texture2D(image, path);
}

SDG::Texture2D *
SDG::Font::RenderTextBlended(const std::string &text, Color color, bool wrapped, uint32_t wrapLength) const
{
    SDL_Color sdlColor = {color.R(), color.G(), color.B(), color.A()};
    SDL_Surface *surf = wrapped ?
            TTF_RenderText_Blended_Wrapped(impl->font, text.c_str(), sdlColor, wrapLength) :
            TTF_RenderText_Blended(impl->font, text.c_str(), sdlColor);
    return SurfaceToTexture(surf, impl->filepath);
}

SDG::Texture2D *
SDG::Font::RenderTextShaded(const std::string &text, Color fgColor, Color bgColor, bool wrapped, uint32_t wrapLength) const
{
    SDL_Color fg { fgColor.R(), fgColor.G(), fgColor.B(), fgColor.A() };
    SDL_Color bg { bgColor.R(), bgColor.G(), bgColor.B(), bgColor.A() };
    SDL_Surface *surf = wrapped ?
                        TTF_RenderText_Shaded_Wrapped(impl->font, text.c_str(), fg, bg, wrapLength) :
                        TTF_RenderText_Shaded(impl->font, text.c_str(), fg, bg);
    return SurfaceToTexture(surf, impl->filepath);
}

SDG::Texture2D *
SDG::Font::RenderTextSolid(const std::string &text, Color color, bool wrapped, uint32_t wrapLength) const
{
    SDL_Color sdlColor = {color.R(), color.G(), color.B(), color.A()};
    SDL_Surface *surf = wrapped ?
                        TTF_RenderText_Solid_Wrapped(impl->font, text.c_str(), sdlColor, wrapLength) :
                        TTF_RenderText_Solid(impl->font, text.c_str(), sdlColor);
    return SurfaceToTexture(surf, impl->filepath);
}
