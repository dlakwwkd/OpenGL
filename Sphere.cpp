#include "Sphere.h"
#include "gl/glut.h"


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

void Sphere::Init()
{
    Object::Init();

    m_Pos[0]    = 0.0f;    m_Pos[1] = 0.0f;    m_Pos[2]   = 0.0f;
    m_Color[0]  = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 10.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    LoadTexture("Texture/texture.png", true);

    m_Qobj = gluNewQuadric();
    gluQuadricDrawStyle(m_Qobj, GLU_FILL);
    gluQuadricTexture(m_Qobj, GL_TRUE);
    gluQuadricNormals(m_Qobj, GLU_SMOOTH);
}

void Sphere::Release()
{
    Object::Release();
    gluDeleteQuadric(m_Qobj);
}

void Sphere::Update(float dt)
{
    Object::Update(dt);

}

void Sphere::Render()
{
    glPushMatrix();
    {
        Object::Render();
        gluSphere(m_Qobj, m_Size, m_Size * 10, m_Size * 10);
    }
    glPopMatrix();
}

void Sphere::LoadTexture(const std::string& file, bool mipmapOn)
{
    Object::LoadTexture(file, mipmapOn);
}
