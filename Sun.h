#pragma once
#include "Planet.h"

class Sun : public Planet
{
public:
    Sun();
    virtual ~Sun();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();
};

