#include "Moon.h"


Moon::Moon()
{
}


Moon::~Moon()
{
}

void Moon::Init()
{
    Planet::Init();

    m_Pos[0] = 30.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 5.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    LoadTexture("Texture/moon.png", true);
}

void Moon::Release()
{
    Planet::Release();
}

void Moon::Update(float dt)
{
    m_Rotation[1] += 180.0f * dt;
    if (m_Rotation[1] > 360.0f)
        m_Rotation[1] = 0.0f;

    Planet::Update(dt);
}

void Moon::Render()
{
    Planet::Render();
}
