//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once

namespace SDG
{
    // Keyboard Keys
    enum class Key {
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Add, Apps, Attn, Back, BrowserBack, BrowserFavorites, BrowserForward, BrowserHome,
        BrowserRefresh, BrowserSearch, BrowserStop, CapsLock, Decimal, Delete, Divide, Down,
        End, Enter, EraseEof, Escape, Execute, Exsel, F1, F10, F11, F12, F13, F14, F15, F16,
        F17, F18, F19, F2, F3, F4, F5, F6, F7, F8, F9, Help, Home, ImeConvert, ImeNoConvert,
        Insert, Kana, Kanji, LaunchApplication1, LaunchApplication2, LaunchMail, Left,
        LeftAlt, LeftControl, LeftShift, LeftWindows, MediaNextTrack, MediaPlayPause,
        MediaPreviousTrack, MediaStop, Multiply, None, NumLock, Num0, Num1, Num2, Num3,
        Num4, Num5, Num6, Num7, Num8, Num9, NumPad0, NumPad1, NumPad2,
        NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9, Oem8, OemAuto,
        OemBackslash, OemClear, OemCloseBrackets, OemComma, OemCopy, OemEnlW, OemMinus,
        OemOpenBrackets, OemPeriod, OemPipe, OemPlus, OemQuestion, OemQuotes, OemSemicolon,
        OemTilde, Pa1, PageDown, PageUp, Pause, Play, Print, PrintScreen, ProcessKey, Return, Right,
        RightAlt, RightControl, RightShift, RightWindows, Scroll, Select, SelectMedia,
        Separator, Sleep, Space, Subtract, Tab, Up, VolumeDown, VolumeMute, VolumeUp, Zoom
    };

    class Input {
    public:
        // Call this before the main loop begins
        static void Initialize();

        // Call this before the call to SDL_PollEvents
        static void Update();

        // Clean up, called when the app is shut down
        static void Close();

        static bool KeyPressed(Key key);
        static bool KeyPress(Key key);
        static bool KeyReleased(Key key);
        static bool KeyRelease(Key key);
    };
}
