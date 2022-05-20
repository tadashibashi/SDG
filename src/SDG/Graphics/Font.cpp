/// Font implementation file
#include "Font.h"
#include "Private/Conversions.h"

#include <SDG/Debug/Logging.h>

#include <SDL_gpu.h>
#include <SDL_ttf.h>

namespace SDG
{
    /// Converts an SDL_Surface to a Texture2D. Handles surface's
    /// memory management, so the user is no longer responsible.
    static Texture2D *
    SurfaceToTexture(SDL_Surface *surf, const SDG::Path &path);

    // ===== Creation and closure =============================================
    class Font::Impl
    {
    public:
        Impl() : pointSize(), filepath(), font() { }
        int       pointSize;
        Path      filepath;
        TTF_Font *font;
    };

    Font::Font() : impl(new Impl)
    {

    }

    Font::~Font()
    {
        Close();
        delete impl;
    }

    bool
    Font::Load(const Path &filepath, int pointSize)
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
    Font::Close()
    {
        if (IsLoaded())
        {
            TTF_CloseFont(impl->font);
            impl->font = nullptr;
            impl->pointSize = 0;
            impl->filepath = Path();
        }
    }

    // ===== Getters ==========================================================
    bool
    Font::IsLoaded() const
    {
        return impl->font;
    }

    const SDG::Path &
    Font::Filepath() const
    {
        return impl->filepath;
    }

    CRef<TTF_Font>
    Font::InnerFont() const
    {
        return CRef<TTF_Font>(impl->font);
    }

    int
    Font::PointSize() const
    {
        return impl->pointSize;
    }

    Font::operator bool()
    {
        return impl->font;
    }

    // ===== Rendering ========================================================
    Texture2D *
    Font::RenderTextBlended(const std::string &text, Color color, bool wrapped, 
        uint32_t wrapLength) const
    {
        SDL_Color sdlColor = Conv::ToSDLColor(color);
        SDL_Surface *surf = wrapped ?
                TTF_RenderText_Blended_Wrapped(impl->font, text.c_str(), 
                    sdlColor, wrapLength) :
                TTF_RenderText_Blended(impl->font, text.c_str(), sdlColor);
        return SurfaceToTexture(surf, impl->filepath);
    }

    Texture2D *
    Font::RenderTextShaded(const std::string &text, Color fgColor, Color bgColor, 
        bool wrapped, uint32_t wrapLength) const
    {
        SDL_Color fg = Conv::ToSDLColor(fgColor);
        SDL_Color bg = Conv::ToSDLColor(bgColor);
        SDL_Surface *surf = wrapped ?
                            TTF_RenderText_Shaded_Wrapped(impl->font, text.c_str(),
                                fg, bg, wrapLength) :
                            TTF_RenderText_Shaded(impl->font, text.c_str(), fg, bg);
        return SurfaceToTexture(surf, impl->filepath);
    }

    Texture2D *
    Font::RenderTextSolid(const std::string &text, Color color, bool wrapped, 
        uint32_t wrapLength) const
    {
        SDL_Color sdlColor = Conv::ToSDLColor(color);
        SDL_Surface *surf = wrapped ?
                            TTF_RenderText_Solid_Wrapped(impl->font, text.c_str(), 
                                sdlColor, wrapLength) :
                            TTF_RenderText_Solid(impl->font, text.c_str(), sdlColor);
        return SurfaceToTexture(surf, impl->filepath);
    }

    Texture2D *
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
            SDG_Err("RenderTextBlended: failure while copying text image data: {}",
                TTF_GetError());
            return nullptr;
        }

        return new Texture2D(image, path);
    }

}
