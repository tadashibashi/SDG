/// SDG::Font implementation file
#include "Font.h"
#include "Private/Conversions.h"

#include <SDG/Debug/Logging.h>
#include <SDG/FileSys/File.h>
#include <SDG/Graphics/Window.h>

#include <SDL_gpu.h>
#include <SDL_ttf.h>

namespace SDG
{
    /// Converts an SDL_Surface to a Texture2D. Handles surface's
    /// memory management, so the user is no longer responsible.
    static Texture2D *
    SurfaceToTexture(Ref<Window> context, SDL_Surface *surf);

    // ===== Creation and closure =============================================
    class Font::Impl
    {
    public:
        Impl() : pointSize(), path(), font() { }
        int       pointSize;
        Path      path;
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
        Close();              // unloads any font loaded in this object
        File file;  // open the file
        if (!file.Open(filepath))
        {
            SDG_Err("Problem opening font ({}): {}", filepath.Filename(),
                    file.GetError());
            return false;
        }

        SDL_RWops *rwops = SDL_RWFromConstMem(file.Data(), file.Size());
        if (!rwops)
        {
            SDG_Err("Problem converting memory to SDL_RWops: {}", 
                SDL_GetError());
            return false;
        }

        // RWops memory needs to remain for the lifetime of the font. Passing
        // true to param "freesrc" here automatically frees it on TTF_CloseFont
        TTF_Font *font = TTF_OpenFontRW(rwops, true, pointSize);
        if (!font)
        {
            SDG_Err("Failed to load font from path {}", filepath.Str());
            SDL_RWclose(rwops);
            return false;
        }
        
        // Load was successful, commit changes
        impl->font = font;
        impl->pointSize = pointSize;
        impl->path = filepath;

        return true;
    }

    void
    Font::Close()
    {
        if (IsLoaded()) // safe to call if already unloaded
        {
            TTF_CloseFont(impl->font);
            impl->font = nullptr;
            impl->pointSize = 0;
            impl->path = Path();
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
        return impl->path;
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
    Font::CreateTextBlended(Ref<Window> context, const String &text, 
        Color color, uint32_t wrapLength) const
    {
        // Make the text surface
        SDL_Surface *surf = (wrapLength > 0) ?
            TTF_RenderText_Blended_Wrapped(impl->font, text.Cstr(), 
                Conv::ToSDLColor(color), wrapLength) :
            TTF_RenderText_Blended(impl->font, text.Cstr(), 
                Conv::ToSDLColor(color));
        SDG_Log("Creating text blended with text: \"{}\"", text);
        return SurfaceToTexture(context, surf);
    }

    Texture2D *
    Font::CreateTextShaded(Ref<Window> context, const String &text, 
        Color fgColor, Color bgColor, uint32_t wrapLength) const
    {
        SDL_Color fg = Conv::ToSDLColor(fgColor);
        SDL_Color bg = Conv::ToSDLColor(bgColor);

        // Make the text surface
        SDL_Surface *surf = (wrapLength > 0) ?
            TTF_RenderText_Shaded_Wrapped(impl->font, text.Cstr(), fg, bg, 
                wrapLength) :
            TTF_RenderText_Shaded(impl->font, text.Cstr(), fg, bg);
        
        return SurfaceToTexture(context, surf);
    }

    Texture2D *
    Font::CreateTextSolid(Ref<Window> context, const String &text, Color color,
                          uint32_t wrapLength) const
    {
        // Make the text surface
        SDL_Surface *surf = (wrapLength > 0) ?
            TTF_RenderText_Solid_Wrapped(impl->font, text.Cstr(), 
                Conv::ToSDLColor(color), wrapLength) :
            TTF_RenderText_Solid(impl->font, text.Cstr(), 
                Conv::ToSDLColor(color));

        return SurfaceToTexture(context, surf);
    }

    Texture2D *
    SurfaceToTexture(Ref<Window> context, SDL_Surface *surf)
    {
        if (!surf) // if null, the function that created the surface prior to this failed.
        {
            SDG_Err("TTF failed to render text: {}", TTF_GetError());
            return nullptr;
        }

        return new Texture2D(context, surf);
    }

}
