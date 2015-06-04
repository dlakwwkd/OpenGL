#pragma once
#include "Object.h"

class Teapot : public Object
{
public:
    Teapot();
    virtual ~Teapot();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

private:

};

