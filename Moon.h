#pragma once
#include "Planet.h"

class Moon : public Planet
{
public:
    Moon();
    virtual ~Moon();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();
};

