#include "Box.h"
#include "gl/glut.h"


Box::Box()
{
}


Box::~Box()
{
}

void Box::Init()
{
    Object::Init();

    m_Pos[0]    = 15.0f;    m_Pos[1]    = 0.0f;    m_Pos[2]     = 15.0f;
    m_Color[0]  = 0.0f;    m_Color[1]   = 0.0f;    m_Color[2]   = 0.0f;
    m_Size = 10.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    //LoadTexture("Texture/texture2.png", true);
}

void Box::Release()
{
    Object::Release();
}

void Box::Update(float dt)
{
    Object::Update(dt);

}

void Box::Render()
{
    glPushMatrix();
    {
        Object::Render();
        glutSolidCube(m_Size);
    }
    glPopMatrix();
}

void Box::LoadTexture(const std::string& file, bool mipmapOn)
{
    Object::LoadTexture(file, mipmapOn);
}
