#pragma once

#include <windows.h>
#include <unordered_map>

///KeyCode class has been written by chat GPT as i was too lazy to add every character myself

enum class KeyCode
{
    A = 'A', B = 'B', C = 'C', D = 'D', E = 'E',
    F = 'F', G = 'G', H = 'H', I = 'I', J = 'J',
    K = 'K', L = 'L', M = 'M', N = 'N', O = 'O',
    P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T',
    U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z',

    Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3', Num4 = '4',
    Num5 = '5', Num6 = '6', Num7 = '7', Num8 = '8', Num9 = '9',

    Escape = VK_ESCAPE,
    Space = VK_SPACE,
    Enter = VK_RETURN,
    Backspace = VK_BACK,
    Tab = VK_TAB,
    Shift = VK_SHIFT,
    Control = VK_CONTROL,
    Alt = VK_MENU,
    CapsLock = VK_CAPITAL,

    Left = VK_LEFT,
    Right = VK_RIGHT,
    Up = VK_UP,
    Down = VK_DOWN,

    F1 = VK_F1, F2 = VK_F2, F3 = VK_F3, F4 = VK_F4,
    F5 = VK_F5, F6 = VK_F6, F7 = VK_F7, F8 = VK_F8,
    F9 = VK_F9, F10 = VK_F10, F11 = VK_F11, F12 = VK_F12,

    Insert = VK_INSERT,
    Delete = VK_DELETE,
    Home = VK_HOME,
    End = VK_END,
    PageUp = VK_PRIOR,
    PageDown = VK_NEXT,

    NumLock = VK_NUMLOCK,
    ScrollLock = VK_SCROLL,
};

class Input
{
public:
    static void Update();
    static bool GetKey(KeyCode key);
    static bool GetKeyDown(KeyCode key);
    static bool GetKeyUp(KeyCode key);

private:
    static std::unordered_map<byte, bool> currentKeys;
    static std::unordered_map<byte, bool> previousKeys;
};
