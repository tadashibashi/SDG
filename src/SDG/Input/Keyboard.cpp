#include "Keyboard.h"
#include <SDL_events.h>
#include <cstdlib>
#include <SDG/Debug.hpp>
#include <SDG/Memory.h>

using SDG::Key;

/**
 * Translates SDG::Key to corresponding SDL_SCANCODE_*
 */
static Uint16 KeyToScanCode(Key key);

// If we populate and use an array like a "dictionary", lookup times can be up to 40 times+ faster
// https://blog.demofox.org/2016/09/26/is-code-faster-than-data-switch-statements-vs-arrays/
static Uint16 Scancodes[(int)Key::_MaxCount] = {0};

namespace SDG
{
    struct Keyboard::Impl {
        Impl() : state(), lastState(), numKeys(), stateChanged()
        {}

        ~Impl()
        {
            if (lastState)
            {
                free(lastState);
            }
        }

        const Uint8 *state;
        Uint8 *lastState;
        int numKeys;
        bool stateChanged;
    };
}




SDG::Keyboard::Keyboard() : impl(new Impl)
{

}




SDG::Keyboard::~Keyboard()
{
    delete impl;
}




bool
SDG::Keyboard::InitializeImpl()
{
    if (!impl->state) // only initialize if it has not been yet
    {
        impl->state = SDL_GetKeyboardState(&impl->numKeys);
        impl->lastState = Malloc<Uint8>(impl->numKeys);
        memcpy(impl->lastState, impl->state, impl->numKeys);

        // Populate the scancodes array if it hasn't already been set
        if (Scancodes[(unsigned)Key::D] != KeyToScanCode(Key::D))
        {
            for (unsigned i = 0; i < (unsigned)Key::_MaxCount; ++i)
            {
                Scancodes[i] = KeyToScanCode((Key)i);
                SDG_Assert(Scancodes[i] < SDL_NUM_SCANCODES);
            }
        }
    }

    return true;
}




void
SDG::Keyboard::ProcessInputImpl(const SDL_Event &ev)
{
    impl->stateChanged = true;
}




bool
SDG::Keyboard::Release(SDG::Key key) const
{
    SDG_Assert(impl->lastState);
    return !impl->state[Scancodes[(unsigned)key]];
}




bool
SDG::Keyboard::Press(SDG::Key key) const
{
    SDG_Assert(impl->lastState);
    return impl->state[Scancodes[(unsigned)key]];
}




bool
SDG::Keyboard::Pressed(SDG::Key key) const
{
    SDG_Assert(impl->lastState);
    auto scancode = Scancodes[(unsigned)key];
    //SDG_Core_Log("Check: this state {} ... last state {}", mImpl->state[scancode], mImpl->lastState[scancode]);
    return impl->state[scancode] &&
           !impl->lastState[scancode];
}



bool
SDG::Keyboard::Released(SDG::Key key) const
{
    SDG_Assert(impl->lastState);
    auto scancode = Scancodes[(unsigned)key];
    return !impl->state[scancode] &&
           impl->lastState[scancode];
}



void
SDG::Keyboard::UpdateLastStatesImpl()
{
    if (impl->stateChanged)
    {
        memcpy(impl->lastState, impl->state, sizeof(Uint8) * impl->numKeys);
        impl->stateChanged = false;
    }
}



void
SDG::Keyboard::CloseImpl()
{
    if (impl->lastState)
    {
        free(impl->lastState);
        impl->lastState = nullptr;
    }
}



const char *SDG::Keyboard::KeyName(Key key)
{
    return SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode)Scancodes[(int)key]));
}



// ====== Static Implementations ======

Uint16 KeyToScanCode(Key key)
{
    switch (key)
    {
        // Alphabetical keys
        case Key::A: return SDL_SCANCODE_A;
        case Key::B: return SDL_SCANCODE_B;
        case Key::C: return SDL_SCANCODE_C;
        case Key::D: return SDL_SCANCODE_D;
        case Key::E: return SDL_SCANCODE_E;
        case Key::F: return SDL_SCANCODE_F;
        case Key::G: return SDL_SCANCODE_G;
        case Key::H: return SDL_SCANCODE_H;
        case Key::I: return SDL_SCANCODE_I;
        case Key::J: return SDL_SCANCODE_J;
        case Key::K: return SDL_SCANCODE_K;
        case Key::L: return SDL_SCANCODE_L;
        case Key::M: return SDL_SCANCODE_M;
        case Key::N: return SDL_SCANCODE_N;
        case Key::O: return SDL_SCANCODE_O;
        case Key::P: return SDL_SCANCODE_P;
        case Key::Q: return SDL_SCANCODE_Q;
        case Key::R: return SDL_SCANCODE_R;
        case Key::S: return SDL_SCANCODE_S;
        case Key::T: return SDL_SCANCODE_T;
        case Key::U: return SDL_SCANCODE_U;
        case Key::V: return SDL_SCANCODE_V;
        case Key::W: return SDL_SCANCODE_W;
        case Key::X: return SDL_SCANCODE_X;
        case Key::Y: return SDL_SCANCODE_Y;
        case Key::Z: return SDL_SCANCODE_Z;

        // Numeric
        case Key::One:   return SDL_SCANCODE_1;
        case Key::Two:   return SDL_SCANCODE_2;
        case Key::Three: return SDL_SCANCODE_3;
        case Key::Four:  return SDL_SCANCODE_4;
        case Key::Five:  return SDL_SCANCODE_5;
        case Key::Six:   return SDL_SCANCODE_6;
        case Key::Seven: return SDL_SCANCODE_7;
        case Key::Eight: return SDL_SCANCODE_8;
        case Key::Nine:  return SDL_SCANCODE_9;
        case Key::Zero:  return SDL_SCANCODE_0;

        // Common to most keyboards
        case Key::Return:    return SDL_SCANCODE_RETURN;
        case Key::Escape:    return SDL_SCANCODE_ESCAPE;
        case Key::Backspace: return SDL_SCANCODE_BACKSPACE;
        case Key::Tab:       return SDL_SCANCODE_TAB;
        case Key::Space:     return SDL_SCANCODE_SPACE;

        case Key::Minus:        return SDL_SCANCODE_MINUS;
        case Key::Equals:       return SDL_SCANCODE_EQUALS;
        case Key::LeftBracket:  return SDL_SCANCODE_LEFTBRACKET;
        case Key::RightBracket: return SDL_SCANCODE_RIGHTBRACKET;
        case Key::Backslash:    return SDL_SCANCODE_BACKSLASH;
        case Key::SemiColon:    return SDL_SCANCODE_SEMICOLON;
        case Key::Apostraphe:   return SDL_SCANCODE_APOSTROPHE;
        case Key::Grave:        return SDL_SCANCODE_GRAVE;
        case Key::Comma:        return SDL_SCANCODE_COMMA;
        case Key::Period:       return SDL_SCANCODE_PERIOD;
        case Key::Slash:        return SDL_SCANCODE_SLASH;

        case Key::CapsLock: return SDL_SCANCODE_CAPSLOCK;

        // Common Function Keys
        case Key::F1:  return SDL_SCANCODE_F1;
        case Key::F2:  return SDL_SCANCODE_F2;
        case Key::F3:  return SDL_SCANCODE_F3;
        case Key::F4:  return SDL_SCANCODE_F4;
        case Key::F5:  return SDL_SCANCODE_F5;
        case Key::F6:  return SDL_SCANCODE_F6;
        case Key::F7:  return SDL_SCANCODE_F7;
        case Key::F8:  return SDL_SCANCODE_F8;
        case Key::F9:  return SDL_SCANCODE_F9;
        case Key::F10: return SDL_SCANCODE_F10;
        case Key::F11: return SDL_SCANCODE_F11;
        case Key::F12: return SDL_SCANCODE_F12;

        case Key::PrintScreen: return SDL_SCANCODE_PRINTSCREEN;
        case Key::ScrollLock:  return SDL_SCANCODE_SCROLLLOCK;
        case Key::Pause:       return SDL_SCANCODE_PAUSE;
        case Key::Insert:      return SDL_SCANCODE_INSERT;

        // Navigation
        case Key::Home:     return SDL_SCANCODE_HOME;
        case Key::PageUp:   return SDL_SCANCODE_PAGEUP;
        case Key::Delete:   return SDL_SCANCODE_DELETE;
        case Key::End:      return SDL_SCANCODE_END;
        case Key::PageDown: return SDL_SCANCODE_PAGEDOWN;
        case Key::Right:    return SDL_SCANCODE_RIGHT;
        case Key::Left:     return SDL_SCANCODE_LEFT;
        case Key::Down:     return SDL_SCANCODE_DOWN;
        case Key::Up:       return SDL_SCANCODE_UP;

        // Typical keypad
        case Key::NumLockClear: return SDL_SCANCODE_NUMLOCKCLEAR;

        case Key::KpDivide:   return SDL_SCANCODE_KP_DIVIDE;
        case Key::KpMultiply: return SDL_SCANCODE_KP_MULTIPLY;
        case Key::KpMinus:    return SDL_SCANCODE_KP_MINUS;
        case Key::KpPlus:     return SDL_SCANCODE_KP_PLUS;
        case Key::KpEnter:    return SDL_SCANCODE_KP_ENTER;
        case Key::Kp1:        return SDL_SCANCODE_KP_1;
        case Key::Kp2:        return SDL_SCANCODE_KP_2;
        case Key::Kp3:        return SDL_SCANCODE_KP_3;
        case Key::Kp4:        return SDL_SCANCODE_KP_4;
        case Key::Kp5:        return SDL_SCANCODE_KP_5;
        case Key::Kp6:        return SDL_SCANCODE_KP_6;
        case Key::Kp7:        return SDL_SCANCODE_KP_7;
        case Key::Kp8:        return SDL_SCANCODE_KP_8;
        case Key::Kp9:        return SDL_SCANCODE_KP_9;
        case Key::Kp0:        return SDL_SCANCODE_KP_0;
        case Key::KpPeriod:   return SDL_SCANCODE_KP_PERIOD;

        case Key::NonUsBackslash: return SDL_SCANCODE_NONUSBACKSLASH;

        case Key::Application: return SDL_SCANCODE_APPLICATION;
        case Key::Power: return SDL_SCANCODE_POWER;

        case Key::KpEquals: return SDL_SCANCODE_KP_EQUALS;
        case Key::F13: return SDL_SCANCODE_F13;
        case Key::F14: return SDL_SCANCODE_F14;
        case Key::F15: return SDL_SCANCODE_F15;
        case Key::F16: return SDL_SCANCODE_F16;
        case Key::F17: return SDL_SCANCODE_F17;
        case Key::F18: return SDL_SCANCODE_F18;
        case Key::F19: return SDL_SCANCODE_F19;
        case Key::F20: return SDL_SCANCODE_F20;
        case Key::F21: return SDL_SCANCODE_F21;
        case Key::F22: return SDL_SCANCODE_F22;
        case Key::F23: return SDL_SCANCODE_F23;
        case Key::F24: return SDL_SCANCODE_F24;

        case Key::Execute:       return SDL_SCANCODE_EXECUTE;
        case Key::Help:          return SDL_SCANCODE_HELP;
        case Key::Menu:          return SDL_SCANCODE_MENU;
        case Key::Select:        return SDL_SCANCODE_SELECT;
        case Key::Stop:          return SDL_SCANCODE_STOP;
        case Key::Again:         return SDL_SCANCODE_AGAIN;
        case Key::Undo:          return SDL_SCANCODE_UNDO;
        case Key::Cut:           return SDL_SCANCODE_CUT;
        case Key::Copy:          return SDL_SCANCODE_COPY;
        case Key::Paste:         return SDL_SCANCODE_PASTE;
        case Key::Find:          return SDL_SCANCODE_FIND;
        case Key::Mute:          return SDL_SCANCODE_MUTE;
        case Key::VolumeUp:      return SDL_SCANCODE_VOLUMEUP;
        case Key::VolumeDown:    return SDL_SCANCODE_VOLUMEDOWN;
        case Key::KpComma:       return SDL_SCANCODE_KP_COMMA;
        case Key::KpEqualsAs400: return SDL_SCANCODE_KP_EQUALSAS400;

        case Key::International1: return SDL_SCANCODE_INTERNATIONAL1;
        case Key::International2: return SDL_SCANCODE_INTERNATIONAL2;
        case Key::International3: return SDL_SCANCODE_INTERNATIONAL3;
        case Key::International4: return SDL_SCANCODE_INTERNATIONAL4;
        case Key::International5: return SDL_SCANCODE_INTERNATIONAL5;
        case Key::International6: return SDL_SCANCODE_INTERNATIONAL6;
        case Key::International7: return SDL_SCANCODE_INTERNATIONAL7;
        case Key::International8: return SDL_SCANCODE_INTERNATIONAL8;
        case Key::International9: return SDL_SCANCODE_INTERNATIONAL9;

        case Key::Lang1: return SDL_SCANCODE_LANG1;
        case Key::Lang2: return SDL_SCANCODE_LANG2;
        case Key::Lang3: return SDL_SCANCODE_LANG3;
        case Key::Lang4: return SDL_SCANCODE_LANG4;
        case Key::Lang5: return SDL_SCANCODE_LANG5;
        case Key::Lang6: return SDL_SCANCODE_LANG6;
        case Key::Lang7: return SDL_SCANCODE_LANG7;
        case Key::Lang8: return SDL_SCANCODE_LANG8;
        case Key::Lang9: return SDL_SCANCODE_LANG9;

        case Key::AltErase:   return SDL_SCANCODE_ALTERASE;
        case Key::SysReq:     return SDL_SCANCODE_SYSREQ;
        case Key::Cancel:     return SDL_SCANCODE_CANCEL;
        case Key::Clear:      return SDL_SCANCODE_CLEAR;
        case Key::Prior:      return SDL_SCANCODE_PRIOR;
        case Key::Return2:    return SDL_SCANCODE_RETURN2;
        case Key::Separator:  return SDL_SCANCODE_SEPARATOR;
        case Key::Out:        return SDL_SCANCODE_OUT;
        case Key::Oper:       return SDL_SCANCODE_OPER;
        case Key::ClearAgain: return SDL_SCANCODE_CLEARAGAIN;
        case Key::CrSel:      return SDL_SCANCODE_CRSEL;
        case Key::ExSel:      return SDL_SCANCODE_EXSEL;

        case Key::Kp00:       return SDL_SCANCODE_KP_00;
        case Key::Kp000:      return SDL_SCANCODE_KP_000;

        case Key::ThousandsSeparator: return SDL_SCANCODE_THOUSANDSSEPARATOR;
        case Key::DecimalSeparator:   return SDL_SCANCODE_DECIMALSEPARATOR;
        case Key::CurrencyUnit:       return SDL_SCANCODE_CURRENCYUNIT;
        case Key::CurrencySubUnit:    return SDL_SCANCODE_CURRENCYSUBUNIT;
        case Key::KpLeftParen:        return SDL_SCANCODE_KP_LEFTPAREN;
        case Key::KpRightParen:       return SDL_SCANCODE_KP_RIGHTPAREN;
        case Key::KpLeftBrace:        return SDL_SCANCODE_KP_LEFTBRACE;
        case Key::KpRightBrace:       return SDL_SCANCODE_KP_RIGHTBRACE;
        case Key::KpTab:              return SDL_SCANCODE_KP_TAB;
        case Key::KpBackspace:        return SDL_SCANCODE_KP_BACKSPACE;
        case Key::KpA:                return SDL_SCANCODE_KP_A;
        case Key::KpB:                return SDL_SCANCODE_KP_B;
        case Key::KpC:                return SDL_SCANCODE_KP_C;
        case Key::KpD:                return SDL_SCANCODE_KP_D;
        case Key::KpE:                return SDL_SCANCODE_KP_E;
        case Key::KpF:                return SDL_SCANCODE_KP_F;
        case Key::KpXOR:              return SDL_SCANCODE_KP_XOR;
        case Key::KpPower:            return SDL_SCANCODE_KP_POWER;
        case Key::KpPercent:          return SDL_SCANCODE_KP_PERCENT;
        case Key::KpLess:             return SDL_SCANCODE_KP_LESS;
        case Key::KpGreater:          return SDL_SCANCODE_KP_GREATER;
        case Key::KpAmpersand:        return SDL_SCANCODE_KP_AMPERSAND;
        case Key::KpDblAmpersand:     return SDL_SCANCODE_KP_DBLAMPERSAND;
        case Key::KpVerticalBar:      return SDL_SCANCODE_KP_VERTICALBAR;
        case Key::KpDblVerticalBar:   return SDL_SCANCODE_KP_DBLVERTICALBAR;
        case Key::KpColon:            return SDL_SCANCODE_KP_COLON;
        case Key::KpHash:             return SDL_SCANCODE_KP_HASH;
        case Key::KpSpace:            return SDL_SCANCODE_KP_SPACE;
        case Key::KpAt:               return SDL_SCANCODE_KP_AT;
        case Key::KpExclam:           return SDL_SCANCODE_KP_EXCLAM;
        case Key::KpMemStore:         return SDL_SCANCODE_KP_MEMSTORE;
        case Key::KpMemRecall:        return SDL_SCANCODE_KP_MEMRECALL;
        case Key::KpMemClear:         return SDL_SCANCODE_KP_MEMCLEAR;
        case Key::KpMemAdd:           return SDL_SCANCODE_KP_MEMADD;
        case Key::KpMemSubtract:      return SDL_SCANCODE_KP_MEMSUBTRACT;
        case Key::KpMemMultiply:      return SDL_SCANCODE_KP_MEMMULTIPLY;
        case Key::KpMemDivide:        return SDL_SCANCODE_KP_MEMDIVIDE;
        case Key::KpPlusMinus:        return SDL_SCANCODE_KP_PLUSMINUS;
        case Key::KpClear:            return SDL_SCANCODE_KP_CLEAR;
        case Key::KpClearEntry:       return SDL_SCANCODE_KP_CLEARENTRY;
        case Key::KpBinary:           return SDL_SCANCODE_KP_BINARY;
        case Key::KpOctal:            return SDL_SCANCODE_KP_OCTAL;
        case Key::KpDecimal:          return SDL_SCANCODE_KP_DECIMAL;
        case Key::KpHexadecimal:      return SDL_SCANCODE_KP_HEXADECIMAL;

        case Key::LeftControl:  return SDL_SCANCODE_LCTRL;
        case Key::LeftShift:    return SDL_SCANCODE_LSHIFT;
        case Key::LeftAlt:      return SDL_SCANCODE_LALT;
        case Key::LeftGui:      return SDL_SCANCODE_LGUI;
        case Key::RightControl: return SDL_SCANCODE_RCTRL;
        case Key::RightShift:   return SDL_SCANCODE_RSHIFT;
        case Key::RightAlt:     return SDL_SCANCODE_RALT;
        case Key::RightGui:     return SDL_SCANCODE_RGUI;

        case Key::Mode: return SDL_SCANCODE_MODE;

        case Key::AudioNext:   return SDL_SCANCODE_AUDIONEXT;
        case Key::AudioPrev:   return SDL_SCANCODE_AUDIOPREV;
        case Key::AudioStop:   return SDL_SCANCODE_AUDIOSTOP;
        case Key::AudioPlay:   return SDL_SCANCODE_AUDIOPLAY;
        case Key::AudioMute:   return SDL_SCANCODE_AUDIOMUTE;
        case Key::MediaSelect: return SDL_SCANCODE_MEDIASELECT;
        case Key::Www:         return SDL_SCANCODE_WWW;
        case Key::Mail:        return SDL_SCANCODE_MAIL;
        case Key::Calculator:  return SDL_SCANCODE_CALCULATOR;
        case Key::Computer:    return SDL_SCANCODE_COMPUTER;

        case Key::BrowserSearch:    return SDL_SCANCODE_AC_SEARCH;
        case Key::BrowserHome:      return SDL_SCANCODE_AC_HOME;
        case Key::BrowserBack:      return SDL_SCANCODE_AC_BACK;
        case Key::BrowserForward:   return SDL_SCANCODE_AC_FORWARD;
        case Key::BrowserStop:      return SDL_SCANCODE_AC_STOP;
        case Key::BrowserRefresh:   return SDL_SCANCODE_AC_REFRESH;
        case Key::BrowserBookmarks: return SDL_SCANCODE_AC_BOOKMARKS;

        case Key::BrightnessDown: return SDL_SCANCODE_BRIGHTNESSDOWN;
        case Key::BrightnessUp:   return SDL_SCANCODE_BRIGHTNESSUP;
        case Key::DisplaySwitch:  return SDL_SCANCODE_DISPLAYSWITCH;

        case Key::KeyboardIllumToggle: return SDL_SCANCODE_KBDILLUMTOGGLE;
        case Key::KeyboardIllumDown:   return SDL_SCANCODE_KBDILLUMDOWN;
        case Key::KeyboardIllumUp:     return SDL_SCANCODE_KBDILLUMUP;
        case Key::Eject:               return SDL_SCANCODE_EJECT;
        case Key::Sleep:               return SDL_SCANCODE_SLEEP;

        case Key::App1:                return SDL_SCANCODE_APP1;
        case Key::App2:                return SDL_SCANCODE_APP2;

        case Key::AudioRewind:      return SDL_SCANCODE_AUDIOREWIND;
        case Key::AudioFastForward: return SDL_SCANCODE_AUDIOFASTFORWARD;

        default:
            SDG_Core_Err("Unknown Key value was checked");
            return SDL_SCANCODE_UNKNOWN;
    }
}