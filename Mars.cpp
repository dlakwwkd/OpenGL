#include "Mars.h"


Mars::Mars()
{
}


Mars::~Mars()
{
}

void Mars::Init()
{
    Planet::Init();

    m_Pos[0] = 240.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 15.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    LoadTexture("Texture/mars.png", true);
}

void Mars::Release()
{
    Planet::Release();
}

void Mars::Update(float dt)
{
    m_Rotation[1] += 20.0f * dt;
    if (m_Rotation[1] > 360.0f)
        m_Rotation[1] = 0.0f;

    Planet::Update(dt);
}

void Mars::Render()
{
    Planet::Render();
}
