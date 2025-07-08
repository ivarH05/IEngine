#include "Input.h"

std::unordered_map<byte, bool> Input::currentKeys;
std::unordered_map<byte, bool> Input::previousKeys;

void Input::Update()
{
    previousKeys = currentKeys;

    for (byte k = 0; k < 255; ++k)
    {
        SHORT state = GetAsyncKeyState(k);
        bool isDown = (state & 0x8000) != 0;
        currentKeys[k] = isDown;
    }
}

bool Input::GetKey(KeyCode key)
{
    return currentKeys[static_cast<byte>(key)];
}

bool Input::GetKeyDown(KeyCode key)
{
    int k = static_cast<byte>(key);
    return currentKeys[k] && !previousKeys[k];
}

bool Input::GetKeyUp(KeyCode key)
{
    int k = static_cast<byte>(key);
    return !currentKeys[k] && previousKeys[k];
}
