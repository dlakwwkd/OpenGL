#pragma once
#include "Object.h"

class Box : public Object
{
public:
    Box();
    virtual ~Box();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

private:
    void DrawVertex();
    void CreateVertex();
};

