#pragma once
#include "Object.h"

class TwoDBox : public Object
{
public:
    TwoDBox();
    TwoDBox(GLfloat posX, GLfloat size);
    virtual ~TwoDBox();

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

    virtual void    LoadTexture(const std::string& file, bool mipmapOn){}

    void SetMoveDirX(GLfloat x){ m_MoveDir[0] = x; }
    void SetMoveDirY(GLfloat y){ m_MoveDir[1] = y; }

    void ChildCollisionCheck();
    void Collision();

private:
    GLfloat m_MoveDir[2];
    GLfloat m_MoveSpeed;
};

