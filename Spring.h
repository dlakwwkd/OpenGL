#pragma once
#include "Object.h"

class Spring : public Object
{
public:
    Spring();
    virtual ~Spring();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

    virtual void    LoadTexture(const std::string& file, bool mipmapOn){}

};

