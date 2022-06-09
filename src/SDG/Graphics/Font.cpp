#include "Font.h"
#include "Private/NFont.h"

#include <SDG/Exceptions/InvalidArgumentException.h>

#include <SDG/FileSys/File.h>

#include <SDG/Graphics/Window.h>
#include <SDG/Graphics/RenderTarget.h>

#include <cstdarg>

namespace SDG
{
    struct Font::Impl
    {
        Impl() : font(), filepath(), isLoaded() { }

        NFont *font;
        Path filepath;
        bool isLoaded;
    };

    Font::Font() : impl(new Impl)
    {
    }

    Font::Font(Ref<Window> context, const Path &filepath, uint32_t pointSize, FontStyle style)
    {
        Load(context, filepath, pointSize, style);
    }

    Font::~Font()
    {
        Close();
        delete impl;
    }

    bool Font::Load(Ref<class Window> context, const Path &filepath, uint32_t pointSize, FontStyle style)
    {
        Close();

        File file;
        if (!file.Open(filepath))
        {
            SDG_Core_Err("Font::Load: failed to open font file: {}", file.GetError());
            return false;
        }
        
        SDL_RWops *io = SDL_RWFromConstMem(file.Data(), file.Size());
        if (!io)
        {
            SDG_Core_Err("Font::Load: failed to transfer loaded file data for {}: {}", 
                filepath.Filename(), SDL_GetError());
            return false;
        }
        
        // this may not be necessary, but may be for supporting multiple windows
        context->MakeCurrent();

        NFont *font = new NFont;
        if (!font->load(io, true, pointSize, { 255, 255, 255, 255 }, (int)style))
        {
            SDG_Core_Err("Font::Load: failed to load font data for {}", filepath.Filename());
            delete font;
            return false;
        }

        impl->font = font;
        impl->filepath = filepath;

        return true;
    }

    bool Font::IsLoaded() const
    {
        return impl->font;
    }

    void Font::Close()
    {
        if (IsLoaded())
        {
            impl->font->free();
            delete impl->font;
            impl->font = nullptr;
        }
    }

    void Font::DrawImpl(Ref<class RenderTarget> target, Vector2 position,
        Vector2 scale, FontAlign alignment, Color color, const char *str)
    {
        NFont::AlignEnum nAlign;
        switch (alignment)
        {
        case FontAlign::Left: nAlign = NFont::LEFT; break;
        case FontAlign::Center: nAlign = NFont::CENTER; break;
        case FontAlign::Right: nAlign = NFont::RIGHT; break;
        default:
            throw InvalidArgumentException("Font::Draw", "alignment");
        }

        NFont::Effect effect(nAlign, {scale.X(), scale.Y()}, {color.R(), color.G(), color.B(), color.A()});

        impl->font->draw(target->Target().Get(), position.X(), position.Y(), effect, "%s", str);
    }

    int Font::Spacing() const
    {
        return impl->font->getSpacing();
    }

    Font &Font::Spacing(int spacing)
    {
        impl->font->setSpacing(spacing);
        return *this;
    }

    int Font::LineSpacing() const
    {
        return impl->font->getLineSpacing();
    }

    Font &Font::LineSpacing(int spacing)
    {
        impl->font->setLineSpacing(spacing);
        return *this;
    }

    int Font::MaxWidth() const
    {
        return impl->font->getMaxWidth();
    }

    Font &Font::Baseline(uint16_t baseline)
    {
        impl->font->setBaseline(baseline);
        return *this;
    }

    uint16_t Font::Baseline() const
    {
        return impl->font->getBaseline();
    }

    Font &Font::FilterMode(FontFilter mode)
    {
        impl->font->setFilterMode(mode == FontFilter::Linear ? NFont::LINEAR : NFont::NEAREST);
        return *this;
    }

    FontFilter Font::FilterMode() const
    {
        return impl->font->getFilterMode() == NFont::LINEAR ? 
            FontFilter::Linear : FontFilter::Nearest;
    }

    uint16_t Font::Ascent() const
    {
        return impl->font->getAscent();
    }

    uint16_t Font::Ascent(const char *formatted, ...)
    {
        va_list args;
        va_start(args, formatted);

        uint16_t ascent = impl->font->getAscent(formatted, args);
        va_end(args);

        return ascent;
    }

    uint16_t Font::Ascent(char c)
    {
        return impl->font->getAscent(c);
    }

    int Font::Descent() const
    {
        return impl->font->getDescent();
    }

    int Font::Descent(const char *formatted, ...)
    {
        va_list args;
        va_start(args, formatted);
        
        int descent = impl->font->getDescent(formatted, args);
        va_end(args);

        return descent;
    }

    int Font::Descent(char c)
    {
        return impl->font->getDescent(c);
    }

    FRectangle Font::CheckBoundsImpl(Vector2 position, const char *text) const
    {
        auto bounds = impl->font->getBounds(position.X(), 
            position.Y(), "%s", text);
        return {bounds.x, bounds.y, bounds.w, bounds.h};
    }

    uint16_t Font::CheckColumnHeightImpl(uint16_t width, const char *text) const
    {
        return impl->font->getColumnHeight(width, "%s", text);
    }

    


}