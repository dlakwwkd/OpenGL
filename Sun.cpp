#include "Sun.h"
#include "Earth.h"
#include "Mars.h"


Sun::Sun()
{
}


Sun::~Sun()
{
}

void Sun::Init()
{
    Planet::Init();

    m_Pos[0] = 0.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 0.0f;    m_Color[2] = 0.0f;
    m_Size = 20.0f;
    m_TexID = 0;
    m_TexEnv = GL_DECAL;

    LoadTexture("Texture/sun.png", true);

    m_Children.push_back(new Earth());
    m_Children.push_back(new Mars());
    for (auto& child : m_Children)
    {
        child->Init();
        child->SetParents(this);
    }
}

void Sun::Release()
{
    Planet::Release();
}

void Sun::Update(float dt)
{
    Planet::Update(dt);
}

void Sun::Render()
{
    Planet::Render();
}
