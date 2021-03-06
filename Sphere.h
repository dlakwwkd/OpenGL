#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    Sphere();
    virtual ~Sphere();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

private:
    GLUquadricObj* m_Qobj;
};

