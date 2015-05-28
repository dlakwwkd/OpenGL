#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "lodepng.h"
class GameTimer;
class Camera;
class Object;
class Light;

class GLManager
{
public:
    static GLManager* getInstance()
    {
        static GLManager glManager;
        return &glManager;
    }

    void Init();
    void Release();
    void Run();
    void MainLoop();

    void Update(float dt);
    void Render();
    void Resize(int w, int h);

private:
    void SetupRC();
    void SetLight();
    void SetObject();

private:
    GLManager();
    ~GLManager();

    GameTimer*              m_Timer;
    Camera*                 m_Camera;
    Light*                  m_Light;

    std::vector<Object*>    m_ObjectList;

    std::string             m_Title;
    int                     m_ClientWidth;
    int                     m_ClientHeight;
};

