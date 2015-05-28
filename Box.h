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

    virtual void    LoadTexture(const std::string& file, bool mipmapOn);

private:

};

