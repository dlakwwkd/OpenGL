#pragma once
#include <gl/glut.h>

class Light
{
public:
    Light();
    ~Light();

    void Init(GLenum id, GLfloat* amb, GLfloat* dif, GLfloat* pos);
    void Update(float dt);
    void Render();

private:
    GLenum  m_ID;
    GLfloat m_Amb[4];
    GLfloat m_Dif[4];
    GLfloat m_Pos[4];
};

