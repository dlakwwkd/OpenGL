#include "GLManager.h"
#include "InputManager.h"
#include "GameTimer.h"
#include "Camera.h"
#include "Light.h"
#include "Teapot.h"
#include "Sphere.h"
#include "Box.h"


// 콜백 함수
void ChangeSize(int w, int h)                           { GLManager::getInstance()->Resize(w, h); }
void RenderScene()                                      { GLManager::getInstance()->Render(); }
void IdleFunc()                                         { GLManager::getInstance()->MainLoop();}
void DoMouseClick(int button, int state, int x, int y)  { InputManager::getInstance()->SetMouseState(button, state ^ 1); }
void DoMouseDrag(int x, int y)                          { InputManager::getInstance()->SetMousePos(x, y); }
void DoMouseMove(int x, int y)                          { InputManager::getInstance()->SetMousePos(x, y); }


GLManager::GLManager()
:   m_Timer(nullptr),
    m_Camera(nullptr),
    m_Title("OpenGL Templete"),
    m_ClientWidth(800),
    m_ClientHeight(600)
{
}


GLManager::~GLManager()
{
    Release();
}

void GLManager::Init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_ClientWidth, m_ClientHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(m_Title.c_str());

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(IdleFunc);

    glutMouseFunc(DoMouseClick);
    glutMotionFunc(DoMouseDrag);
    glutPassiveMotionFunc(DoMouseMove);

    // 키보드 입력은 콜백함수 대신 윈도우API의 GetKeyboardState()를 이용함
    // glutSpecialFunc(KeyControl);
    // glutKeyboardFunc(NormalkeyInput);

    m_Timer = new GameTimer();
    m_Camera = new Camera();

    SetupRC();
    SetLight();
    SetObject();
}

void GLManager::Release()
{
    delete m_Timer;
    delete m_Camera;
    delete m_Light;
    for (auto& object : m_ObjectList)
    {
        delete object;
    }
    m_ObjectList.clear();
}

void GLManager::Run()
{
    Init();
    m_Timer->Reset();
    glutMainLoop();
}

void GLManager::MainLoop()
{
    InputManager::getInstance()->SetKeyState();
    m_Timer->Tick();
    Update(m_Timer->DeltaTime());
    Render();
}


void GLManager::Update(float dt)
{
    m_Camera->Update(dt);

    if (InputManager::getInstance()->GetMouseState(GLUT_RIGHT_BUTTON))
        return;

    m_Light->Update(dt);
    for (auto& object : m_ObjectList)
    {
        object->Update(dt);
    }
}

void GLManager::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    {
        glMultMatrixf(m_Camera->View());
        m_Light->Render();
        for (auto& object : m_ObjectList)
        {
            object->Render();
        }
    }
    glPopMatrix();
    glutSwapBuffers();
}

void GLManager::Resize(int w, int h)
{
    glViewport(0, 0, w, h);
    m_ClientWidth = w;
    m_ClientHeight = h;

    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    m_Camera->SetLens(45.0f, fAspect, 1.0f, 1000.0f);
}



void GLManager::SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
//     glEnable(GL_CULL_FACE);
//     glFrontFace(GL_CW);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void GLManager::SetLight()
{
    m_Light = new Light();

    GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat pos[] = { -50.0f, 50.0f, 100.0f, 1.0f };

    m_Light->Init(GL_LIGHT0, amb, dif, pos);
}

void GLManager::SetObject()
{
    m_ObjectList.push_back(new Teapot());
    m_ObjectList.push_back(new Sphere());
    m_ObjectList.push_back(new Box());

    for (auto& object : m_ObjectList)
    {
        object->Init();
    }
}

