//
// Created by Aaron Ishibashi on 4/29/22.
//

#pragma once
#include "Color.h"
#include "Texture2D.h"
#include "SDG/Math/Rectangle.h"
#include "Window.h"

namespace SDG
{

    class GraphicsMgr
    {
        struct Impl;
    public:
        GraphicsMgr();
        ~GraphicsMgr();

        bool Initialize();
        void Close();

        void Clear();
        void Clear(float r, float g, float b);

        void DrawTexture(Texture2D texture, float x, float y, Color color);
        void DrawRectangle(Rectangle rectangle, Color color);
        void DrawLine(float x1, float y1, float x2, float y2, Color color);

        Ref<Window> Window();
    private:
        // Private implementation to wrap GPU functions.
        Impl *impl;
    };
}
