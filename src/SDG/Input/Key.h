#pragma once

namespace SDG
{
    /**
     * An enumeration representing Keyboard Key values used in Keyboard check functions.
     */
    enum class Key : unsigned {
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
        Return, Escape, Backspace, Tab, Space,

        Minus, Equals, LeftBracket, RightBracket, Backslash,
        SemiColon, Apostraphe, Grave, Comma, Period, Slash,
        CapsLock,

        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,

        PrintScreen, ScrollLock, Pause, Insert,
        Home, PageUp, Delete, End, PageDown, Right, Left, Down, Up,
        NumLockClear,

        KpDivide, KpMultiply, KpMinus, KpPlus, KpEnter,
        Kp1, Kp2, Kp3, Kp4, Kp5, Kp6, Kp7, Kp8, Kp9, Kp0, Kp00, Kp000,
        KpPeriod, KpEquals, KpComma, KpEqualsAs400, KpLeftParen, KpRightParen, KpLeftBrace, KpRightBrace, KpTab, KpBackspace,
        KpA, KpB, KpC, KpD, KpE, KpF, KpXOR, KpPower, KpPercent, KpLess, KpGreater, KpAmpersand, KpDblAmpersand,
        KpVerticalBar, KpDblVerticalBar, KpColon, KpHash, KpSpace, KpAt, KpExclam,
        KpMemStore, KpMemRecall, KpMemClear, KpMemAdd, KpMemSubtract, KpMemMultiply, KpMemDivide, KpPlusMinus,
        KpClear, KpClearEntry, KpBinary, KpOctal, KpDecimal, KpHexadecimal,

        NonUsBackslash,

        Application, Power,
        Execute, Help, Menu, Select, Stop, Again, Undo, Cut, Copy, Paste, Find, Mute, VolumeUp, VolumeDown,
        International1, International2, International3, International4, International5, International6,
        International7, International8, International9,
        Lang1, Lang2, Lang3, Lang4, Lang5, Lang6, Lang7, Lang8, Lang9,

        AltErase, SysReq, Cancel, Clear, Prior, Return2, Separator, Out, Oper, ClearAgain, CrSel, ExSel,
        ThousandsSeparator, DecimalSeparator, CurrencyUnit, CurrencySubUnit,

        LeftControl, LeftShift, LeftAlt, LeftGui, RightControl, RightShift, RightAlt, RightGui,

        Mode,

        AudioNext, AudioPrev, AudioStop, AudioPlay, AudioMute, MediaSelect, Www, Mail, Calculator, Computer,
        BrowserBack, BrowserBookmarks, BrowserForward, BrowserHome, BrowserRefresh, BrowserSearch, BrowserStop,

        BrightnessDown, BrightnessUp, DisplaySwitch, KeyboardIllumToggle, KeyboardIllumDown, KeyboardIllumUp,
        Eject, Sleep,
        App1, App2,
        AudioRewind, AudioFastForward,

        // Used to determine the size of this enum. It must always be the last member.
        _MaxCount
    };
}
