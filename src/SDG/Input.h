//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once

namespace SDG
{
    class Input {
    public:
        // Call this before the main loop begins
        static void Initialize();

        // Call this before the call to SDL_PollEvents
        static void Update();

        // Clean up, called when the app is shut down
        static void Close();

        static bool KeyPressed(int key);
        static bool KeyPress(int key);
        static bool KeyReleased(int key);
        static bool KeyRelease(int key);
    };
}
