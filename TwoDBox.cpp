#include "TwoDBox.h"


TwoDBox::TwoDBox()
{
}


TwoDBox::~TwoDBox()
{
}

void TwoDBox::Init()
{
    static float rPos = -800.0f;
    static int rColor = 5;

    rPos += 230.0f;
    rColor += 1;
    rColor %= 6;

    float r = 0, g = 0, b = 0;
    switch (rColor)
    {
    case 0: r = 1.0f; break;
    case 1: g = 1.0f; break;
    case 2: b = 1.0f; break;
    case 3: r = 1.0f; g = 1.0f; break;
    case 4: r = 1.0f; b = 1.0f; break;
    case 5: g = 1.0f; b = 1.0f; break;
    }

    m_Pos[0] = rPos;    m_Pos[1] = 0;    m_Pos[2] = 0.0f;
    m_Color[0] = r;    m_Color[1] = g;    m_Color[2] = b;
    m_Size = 100.0f;
    m_TexID = 0;
    m_TexEnv = 0;

    m_MoveDir[0] = 1.0f; m_MoveDir[1] = 1.0f;
    m_MoveSpeed = 200.0f;
}

void TwoDBox::Release()
{
}

void TwoDBox::Update(float dt)
{
    m_Pos[0] += m_MoveDir[0] * m_MoveSpeed * dt;
    m_Pos[1] += m_MoveDir[1] * m_MoveSpeed * dt;
}

void TwoDBox::Render()
{
    glBindTexture(GL_TEXTURE_2D, m_TexID);
    glPushMatrix();
    {
        glColor3f(m_Color[0], m_Color[1], m_Color[2]);
        glRectf(m_Pos[0] - m_Size, m_Pos[1] - m_Size,
                m_Pos[0] + m_Size, m_Pos[1] + m_Size);
    }
    glPopMatrix();
}

void TwoDBox::Collision()
{
    m_MoveSpeed += 50.0f;
    if (m_MoveSpeed > 500.0f)
        m_MoveSpeed = 200.0f;
}
