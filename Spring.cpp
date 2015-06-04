#include "Spring.h"


Spring::Spring()
{
}


Spring::~Spring()
{
}

void Spring::Init()
{
    m_Pos[0] = 0.0f;    m_Pos[1] = 0.0f;    m_Pos[2] = 0.0f;
    m_Color[0] = 0.0f;    m_Color[1] = 1.0f;    m_Color[2] = 0.0f;
    m_Size = 30.0f;
    m_TexID = 0;
    m_TexEnv = 0;
}

void Spring::Release()
{
}

void Spring::Update(float dt)
{
}

void Spring::Render()
{
    glBindTexture(GL_TEXTURE_2D, m_TexID);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        glBegin(GL_POINTS);
        {
            glColor3f(m_Color[0], m_Color[1], m_Color[2]);

            GLfloat x, y, z, angle;
            z = -50.0f;
            int i = 0;
            for (angle = 0.0f; angle <= (2.0f*GLT_PI)*m_Size; angle += 0.1f)
            {
                x = ++i*0.1f*sin(angle);
                y = i*0.1f*cos(angle);
                glVertex3f(x, y, z);
                z += 0.1f;
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}