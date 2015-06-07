#include "GLManager.h"
#include "InputManager.h"
#include "GameTimer.h"
#include "Camera.h"
#include "Light.h"
#include "Teapot.h"
#include "Sphere.h"
#include "Box.h"
#include "TwoDBox.h"
#include "Spring.h"
#include "Sun.h"


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
    m_ClientHeight(600),
    m_TestMode(1),
    m_Is3D(false)
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

    for (auto& type : m_ObjectTypeList)
    {
        for (auto& object : type)
        {
            delete object;
        }
    }
    m_ObjectTypeList.clear();
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
    ChangeMode();

    m_Timer->Tick();
    Update(m_Timer->DeltaTime());
    Render();
}


void GLManager::Update(float dt)
{
    if (m_Is3D)
    {
        m_Camera->Update(dt);
        m_Light->Update(dt);
    }

    if (m_TestMode == 1)
        CollisionCheckMove(dt);

    auto objectList = m_ObjectTypeList[m_TestMode];
    for (auto& object : objectList)
    {
        object->Update(dt);
    }
}

void GLManager::Render()
{
    if (m_Is3D) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else        glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    {
        if (m_Is3D)
        {
            glMultMatrixf(m_Camera->View());
            m_Light->Render();
        }
        auto objectList = m_ObjectTypeList[m_TestMode];
        for (auto& object : objectList)
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

    if (m_Is3D)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);

        GLfloat fAspect = (GLfloat)w / (GLfloat)h;
        m_Camera->SetLens(45.0f, fAspect, 1.0f, 1000.0f);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-m_ClientWidth, m_ClientWidth, -m_ClientHeight, m_ClientHeight, 1.0f, -1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
}



void GLManager::SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void GLManager::SetLight()
{
    m_Light = new Light();

    GLfloat amb[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat dif[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    m_Light->Init(GL_LIGHT0, amb, dif, pos);
}

void GLManager::SetObject()
{
    m_ObjectTypeList.resize(5);

    for (int i = 0; i < 3; ++i)
    {
        m_ObjectTypeList[1].push_back(new TwoDBox(400 * i - 400, 150.0f));
        for (int i = 0; i < 3; ++i)
        {
            m_ObjectTypeList[1].back()->AddChild(new TwoDBox(70 * i - 70, 30.0f));
        }
    }
    m_ObjectTypeList[2].push_back(new Spring());
    m_ObjectTypeList[3].push_back(new Box());
    m_ObjectTypeList[4].push_back(new Sun());

    for (auto& type : m_ObjectTypeList)
    {
        for (auto& object : type)
        {
            object->Init();
        }
    }
}

void GLManager::ChangeMode()
{
    auto input = InputManager::getInstance();

    if (input->GetKeyState('1'))        m_TestMode = 1;
    else if (input->GetKeyState('2'))   m_TestMode = 2;
    else if (input->GetKeyState('3'))   m_TestMode = 3;
    else if (input->GetKeyState('4'))   m_TestMode = 4;
    else return;

    if (m_TestMode > 1) m_Is3D = true;
    else                m_Is3D = false;

    Resize(m_ClientWidth, m_ClientHeight);
}

void GLManager::CollisionCheckMove(float dt)
{
    for (auto& object : m_ObjectTypeList[1])
    {
        auto box = dynamic_cast<TwoDBox*>(object);

        auto r = box->GetPosX() + box->GetSize();
        auto l = box->GetPosX() - box->GetSize();
        auto t = box->GetPosY() + box->GetSize();
        auto b = box->GetPosY() - box->GetSize();

        if (r > m_ClientWidth)          box->SetMoveDirX(-1.0f);
        else if (l < -m_ClientWidth)    box->SetMoveDirX(+1.0f);
        else if (t > m_ClientHeight)    box->SetMoveDirY(-1.0f);
        else if (b < -m_ClientHeight)   box->SetMoveDirY(+1.0f);
            
        for (auto& others : m_ObjectTypeList[1])
        {
            if (others == box)
                continue;

            auto r2 = others->GetPosX() + others->GetSize();
            auto l2 = others->GetPosX() - others->GetSize();
            auto t2 = others->GetPosY() + others->GetSize();
            auto b2 = others->GetPosY() - others->GetSize();

            if (r > l2 &&
                l < r2 &&
                t > b2 &&
                b < t2)
            {
                auto gap = 20.0f;
                if (r - l2 < gap)      box->SetMoveDirX(-1.0f);
                else if (r2 - l < gap) box->SetMoveDirX(+1.0f);
                else if (t - b2 < gap) box->SetMoveDirY(-1.0f);
                else if (t2 - b < gap) box->SetMoveDirY(+1.0f);
                box->Collision();
            }
        }
        box->ChildCollisionCheck();
    }
}

