#pragma once
#include "Sphere.h"

class Planet : public Sphere
{
public:
    Planet();
    virtual ~Planet();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();


    GLfloat GetRotX() const { return m_Rotation[0]; }
    GLfloat GetRotY() const { return m_Rotation[1]; }
    GLfloat GetRotZ() const { return m_Rotation[2]; }

protected:

    GLfloat                 m_Rotation[3];
};

