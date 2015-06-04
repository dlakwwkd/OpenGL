#pragma once
#include "Planet.h"

class Earth : public Planet
{
public:
    Earth();
    virtual ~Earth();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();
};

