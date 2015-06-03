#include "Teapot.h"
#include "gl/glut.h"


Teapot::Teapot()
{
}


Teapot::~Teapot()
{
}

void Teapot::Init()
{
    Object::Init();

    m_Pos[0]    = 0.0f;    m_Pos[1]    = 0.0f;    m_Pos[2]     = 0.0f;
    m_Color[0]  = 0.0f;    m_Color[1]   = 0.0f;    m_Color[2]   = 0.0f;
    m_Size = 10.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    LoadTexture("Texture/texture2.png", true);
}

void Teapot::Release()
{
    Object::Release();
}

void Teapot::Update(float dt)
{
    Object::Update(dt);

}

void Teapot::Render()
{
    glPushMatrix();
    {
        Object::Render();
        glutSolidTeapot(m_Size);
    }
    glPopMatrix();
}

void Teapot::LoadTexture(const std::string& file, bool mipmapOn)
{
    Object::LoadTexture(file, mipmapOn);
}
