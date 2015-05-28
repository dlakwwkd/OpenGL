#pragma once
#include "gltools.h"
#include <string>

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

    virtual void    LoadTexture(const std::string& file, bool mipmapOn);

private:
    void            BindTexture2D(GLuint texID, const std::string& file, bool mipmapOn);

protected:
    GLfloat m_Pos[3];
    GLfloat m_Color[3];
    GLfloat m_Size;

    GLuint  m_TexID;
    GLint   m_TexEnv;
};

