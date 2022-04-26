#pragma once
#include <SDG/Graphics/Color.h>
#include <SDG/Graphics/Texture2D.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Math/Vector2.h>

namespace SDG
{
    /**
     * Base class for different renderer backends
     */
    class GraphicsDevice
    {
    public:
        virtual bool Initialize() = 0;

        // Shutdown logic
        virtual bool Close() = 0;

        // TODO: finish desired interface. DrawLine, DrawPixel, DrawFillRectangle
        virtual void DrawTexture(Texture2D *texture, Rectangle source, FRectangle dest, Vector2 anchor, float rotation, float depth, Color color) = 0;
        [[nodiscard]] virtual Texture2D *LoadTexture(const std::string &path) = 0;
        
        virtual void DrawRectangle(FRectangle dest, Color color);
    private:

    };
}
