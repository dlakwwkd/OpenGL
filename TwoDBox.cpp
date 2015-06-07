#include "TwoDBox.h"


TwoDBox::TwoDBox()
{
}

TwoDBox::TwoDBox(GLfloat posX, GLfloat size)
{
    m_Pos[0] = posX; m_Pos[1] = 0; m_Pos[2] = 0;
    m_Size = size;
}


TwoDBox::~TwoDBox()
{
}

void TwoDBox::Init()
{
    Object::Init();
    static int rColor = 1;

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

    m_Color[0] = r;    m_Color[1] = g;    m_Color[2] = b;
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
    for (auto& child : m_Children)
    {
        child->Update(dt);
    }
}

void TwoDBox::Render()
{
    glBindTexture(GL_TEXTURE_2D, m_TexID);
    glPushMatrix();
    {
        if (m_Parents)
        {
            glTranslatef(m_Parents->GetPosX(), m_Parents->GetPosY(), m_Parents->GetPosZ());
        }
        glColor3f(m_Color[0], m_Color[1], m_Color[2]);
        glRectf(m_Pos[0] - m_Size, m_Pos[1] - m_Size,
                m_Pos[0] + m_Size, m_Pos[1] + m_Size);

        for (auto& child : m_Children)
        {
            child->Render();
        }
    }
    glPopMatrix();
}

void TwoDBox::ChildCollisionCheck()
{
    for (auto& child : m_Children)
    {
        auto box = dynamic_cast<TwoDBox*>(child);

        auto r = box->GetPosX() + box->GetSize();
        auto l = box->GetPosX() - box->GetSize();
        auto t = box->GetPosY() + box->GetSize();
        auto b = box->GetPosY() - box->GetSize();

        if (r > m_Size)         box->SetMoveDirX(-1.0f);
        else if (l < -m_Size)   box->SetMoveDirX(+1.0f);
        else if (t > m_Size)    box->SetMoveDirY(-1.0f);
        else if (b < -m_Size)   box->SetMoveDirY(+1.0f);

        for (auto& others : m_Children)
        {
            if (others == box)
                continue;

            auto r2 = others->GetPosX() + others->GetSize();
            auto l2 = others->GetPosX() - others->GetSize();
            auto t2 = others->GetPosY() + others->GetSize();
            auto b2 = others->GetPosY() - others->GetSize();

            if (r > l2 &&
                l < r2 &&
                t > b2 &&
                b < t2)
            {
                auto gap = 20.0f;
                if (r - l2 < gap)      box->SetMoveDirX(-1.0f);
                else if (r2 - l < gap) box->SetMoveDirX(+1.0f);
                else if (t - b2 < gap) box->SetMoveDirY(-1.0f);
                else if (t2 - b < gap) box->SetMoveDirY(+1.0f);
                box->Collision();
            }
        }
    }
}

void TwoDBox::Collision()
{
    m_MoveSpeed += 50.0f;
    if (m_MoveSpeed > 500.0f)
        m_MoveSpeed = 200.0f;
}
