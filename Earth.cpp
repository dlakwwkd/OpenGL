#include "Earth.h"
#include "Moon.h"


Earth::Earth()
{
}


Earth::~Earth()
{
}

void Earth::Init()
{
    Planet::Init();

    m_Pos[0] = 120.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 10.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    LoadTexture("Texture/earth.png", true);

    m_Children.push_back(new Moon());
    for (auto& child : m_Children)
    {
        child->Init();
        child->SetParents(this);
    }
}

void Earth::Release()
{
    Planet::Release();
}

void Earth::Update(float dt)
{
    m_Rotation[1] += 30.0f * dt;
    if (m_Rotation[1] > 360.0f)
        m_Rotation[1] = 0.0f;
    
    Planet::Update(dt);
}

void Earth::Render()
{
    Planet::Render();
}
