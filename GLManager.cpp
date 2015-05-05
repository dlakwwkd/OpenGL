#include "GLManager.h"
#include "InputManager.h"
#include "GameTimer.h"
#include "Camera.h"


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
    LoadTexture();
}

void GLManager::Release()
{
    delete m_Timer;
    delete m_Camera;
}

void GLManager::Run()
{
    Init();
    {
        m_Timer->Reset();
        glutMainLoop();
    }
    Release();
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
}

void GLManager::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {
        glMultMatrixf(m_Camera->View());

//         glEnable(GL_LIGHTING);
//         glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
//         glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
//         glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//         glEnable(GL_LIGHT0);

        glColor3f(1.0f, 1.0f, 1.0f);

        glPushMatrix();
        {
            glTranslatef(-10.0f, 0.0f, 0.0f);
            glBindTexture(GL_TEXTURE_2D, m_TextureIDList[0]);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glutSolidTeapot(10.0f);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(+10.0f, 0.0f, 0.0f);
            glBindTexture(GL_TEXTURE_2D, m_TextureIDList[1]);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            glutSolidTeapot(10.0f);
        }
        glPopMatrix();
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
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void GLManager::LoadTexture()
{
    int textureNum = 2;

    glGenTextures(textureNum, m_TextureIDList);

    BindTexture2D(m_TextureIDList[0], "Texture/texture.png", false);
    BindTexture2D(m_TextureIDList[1], "Texture/texture2.png", true);
}

void GLManager::BindTexture2D(GLuint texID, const std::string& file, bool mipmapOn)
{
    std::vector<unsigned char> image;
    unsigned int width, height, error;

    error = lodepng::decode(image, width, height, file);
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    printf("\nimage size is %i", image.size());

    glBindTexture(GL_TEXTURE_2D, texID);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (mipmapOn)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }
}


