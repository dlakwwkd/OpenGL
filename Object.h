#pragma once
#include "gltools.h"
#include <string>
#include <vector>

class Object
{
public:
    struct Vertex
    {
        Vertex(){}
        Vertex(
            GLfloat px, GLfloat py, GLfloat pz,
            GLfloat nx, GLfloat ny, GLfloat nz,
            GLfloat cr, GLfloat cg, GLfloat cb)
        {
            Position[0] = px; Position[1] = py; Position[2] = pz;
            Normal[0] = nx; Normal[1] = ny; Normal[2] = nz;
            Color[0] = cr; Color[1] = cg; Color[2] = cb;
        }
        GLfloat Position[3];
        GLfloat Normal[3];
        GLfloat Color[3];
    };
    struct MeshData
    {
        std::vector<Vertex> Vertices;
        std::vector<UINT> Indices;
    };
public:
    Object();
    virtual ~Object();

    GLfloat         GetPosX() const { return m_Pos[0]; }
    GLfloat         GetPosY() const { return m_Pos[1]; }
    GLfloat         GetPosZ() const { return m_Pos[2]; }
    GLfloat         GetSize() const { return m_Size; }

    virtual void    Init();
    virtual void    Release();
    virtual void    Update(float dt);
    virtual void    Render();

    virtual void    LoadTexture(const std::string& file, bool mipmapOn);

private:
    void            BindTexture2D(GLuint texID, const std::string& file, bool mipmapOn);

protected:
    GLfloat     m_Pos[3];
    GLfloat     m_Color[3];
    GLfloat     m_Size;

    GLuint      m_TexID;
    GLint       m_TexEnv;

    MeshData    m_Mesh;
};

