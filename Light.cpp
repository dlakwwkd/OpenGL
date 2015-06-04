#include "Light.h"
#include <math.h>

Light::Light()
{
}


Light::~Light()
{
}

void Light::Init(GLenum id, GLfloat* amb, GLfloat* dif, GLfloat* pos)
{
    m_ID = id;
    m_Amb[0] = amb[0]; m_Amb[1] = amb[1]; m_Amb[2] = amb[2]; m_Amb[3] = amb[3];
    m_Dif[0] = dif[0]; m_Dif[1] = dif[1]; m_Dif[2] = dif[2]; m_Dif[3] = dif[3];
    m_Pos[0] = pos[0]; m_Pos[1] = pos[1]; m_Pos[2] = pos[2]; m_Pos[3] = pos[3];
}

void Light::Update(float dt)
{
//     static float t = 0.0f;
//     t += dt;
//     float moveValue = cosf(t)*1.0f;
// 
//     m_Pos[0] += moveValue;
//     m_Pos[1] += moveValue;
//     m_Pos[2] += moveValue;
}

void Light::Render()
{
    glLightfv(m_ID, GL_AMBIENT, m_Amb);
    glLightfv(m_ID, GL_DIFFUSE, m_Dif);
    glLightfv(m_ID, GL_POSITION, m_Pos);
    glEnable(m_ID);
}
