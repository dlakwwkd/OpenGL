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

    virtual void    LoadTexture(const std::string& file, bool mipmapOn);

private:

};

