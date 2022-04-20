//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once

class GPU_Target;

namespace SDG
{
    class Game {
    public:
        Game();
        ~Game();
        void RunOneFrame();
        void Run();

        /// <summary>
        /// Gets the window's GPU_Target. Please make sure to include the SDL_gpu.h header before using it.
        /// </summary>
        const GPU_Target *Window() { return window; }
        void Exit();
    private:
        int Initialize();
        void ProcessInput();
        void Update();
        void Render();
        void Close();
        GPU_Target *window;
        bool isRunning;
    };
}
