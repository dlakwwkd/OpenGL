#pragma once
#include <windows.h>
#include <map>

class InputManager
{
public:
    static InputManager* getInstance()
    {
        static InputManager inputManager;
        return &inputManager;
    }

    inline bool     GetKeyState(int button) const { return m_KeyState.find(button)->second; }
    inline bool     GetMouseState(int button) const { return m_MouseState.find(button)->second; }
    inline POINT    GetMousePos() const { return m_LastMousePos; }
    inline POINT    GetMouseDeltaPos()
    {
        POINT pos = { m_LastMousePos.x - m_PrevMousePos.x, m_LastMousePos.y - m_PrevMousePos.y };
        m_PrevMousePos = m_LastMousePos;
        return pos;
    }

    void            SetKeyState();
    inline void     SetMouseState(int button, bool state){ m_MouseState[button] = state; }
    inline void     SetMousePos(int x, int y){ m_PrevMousePos = m_LastMousePos; m_LastMousePos.x = x; m_LastMousePos.y = y; }

private:
    InputManager();
    ~InputManager();

    std::map<int, bool>     m_KeyState;
    std::map<int, bool>     m_MouseState;
    POINT                   m_PrevMousePos;
    POINT                   m_LastMousePos;
};

