#include "Planet.h"


Planet::Planet()
{
}


Planet::~Planet()
{
}

void Planet::Init()
{
    Sphere::Init();

    m_Pos[0] = 0.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 10.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;
    m_Parents = nullptr;
    m_Rotation[0] = 0.0f; m_Rotation[1] = 0.0f; m_Rotation[2] = 0.0f;
}

void Planet::Release()
{
    Sphere::Release();
}

void Planet::Update(float dt)
{
    Sphere::Update(dt);
    for (auto& child : m_Children)
    {
        child->Update(dt);
    }
}

void Planet::Render()
{
    glPushMatrix();
    {
        if (m_Parents)
        {
            glTranslatef(m_Parents->GetPosX(), m_Parents->GetPosY(), m_Parents->GetPosZ());
        }
        glRotatef(m_Rotation[0], 1.0f, 0.0f, 0.0f);
        glRotatef(m_Rotation[1], 0.0f, 1.0f, 0.0f);
        glRotatef(m_Rotation[2], 0.0f, 0.0f, 1.0f);

        Sphere::Render();
        for (auto& child : m_Children)
        {
            child->Render();
        }
    }
    glPopMatrix();
}
