#pragma once
#include "Planet.h"

class Mars : public Planet
{
public:
    Mars();
    virtual ~Mars();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();
};

