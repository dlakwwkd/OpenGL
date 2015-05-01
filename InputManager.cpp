#include "InputManager.h"
#include <gl/glut.h>


InputManager::InputManager()
{
    SetKeyState();
    m_MouseState[GLUT_LEFT_BUTTON]      = false;
    m_MouseState[GLUT_MIDDLE_BUTTON]    = false;
    m_MouseState[GLUT_RIGHT_BUTTON]     = false;
    m_PrevMousePos = { 0, 0 };
    m_LastMousePos = { 0, 0 };
}


InputManager::~InputManager()
{
}

void InputManager::SetKeyState()
{
    BYTE byKey[256];
    if (GetKeyboardState(byKey))
    {
        for (int i = 0; i < 256; ++i)
        {
            if (byKey[i] & 0x80)
                m_KeyState[i] = true;
            else
                m_KeyState[i] = false;
        }
    }
}
