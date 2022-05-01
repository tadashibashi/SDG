//
// Created by Aaron Ishibashi on 4/29/22.
//
#pragma once
#include <SDG/Math/Vector2.h>
#include "Camera.h"
#include "Color.h"

class GPU_Target;

namespace SDG
{
    class Window
    {
        struct Impl;
    public:
        Window();
        ~Window();

        bool Initialize(int width, int height, const char *title, unsigned flags = 0);
        void Close();

        void Clear(Color color = Color::CornflowerBlue());
        void SwapBuffers();

        // === Setters ===
        Window &Title(const char *title);
        Window &Size(Point size);
        Window &Fullscreen(bool fullscreen);
        Window &SetCamera(const Camera &camera);

        // === Getters ===

        const char *Title() const;
        Point Size() const;
        bool Fullscreen() const;
        GPU_Target *InnerWindow();

    private:
        Impl *impl;
    };
}
