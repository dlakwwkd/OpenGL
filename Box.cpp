#include "Box.h"
#include "gl/glut.h"


Box::Box()
{
}


Box::~Box()
{
}

void Box::Init()
{
    Object::Init();

    m_Pos[0]    = 0.0f;    m_Pos[1]    = 0.0f;    m_Pos[2]     = 0.0f;
    m_Color[0]  = 0.0f;    m_Color[1]   = 0.0f;    m_Color[2]   = 0.0f;
    m_Size = 20.0f;
    m_TexID = 0;
    m_TexEnv = GL_MODULATE;

    //LoadTexture("Texture/texture2.png", true);
    CreateVertex();
}

void Box::Release()
{
    Object::Release();
}

void Box::Update(float dt)
{
    Object::Update(dt);

}

void Box::Render()
{
    glPushMatrix();
    {
        Object::Render();
        DrawVertex();
        //glutSolidCube(m_Size);
    }
    glPopMatrix();
}

void Box::LoadTexture(const std::string& file, bool mipmapOn)
{
    Object::LoadTexture(file, mipmapOn);
}

void Box::DrawVertex()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
    {
        for (UINT i = 0; i < m_Mesh.Indices.size(); i += 3)
        {
            Vertex v1 = m_Mesh.Vertices[m_Mesh.Indices[i]];
            Vertex v2 = m_Mesh.Vertices[m_Mesh.Indices[i + 1]];
            Vertex v3 = m_Mesh.Vertices[m_Mesh.Indices[i + 2]];

            glColor3f(v1.Color[0], v1.Color[1], v1.Color[2]);
            glVertex3f(v1.Position[0], v1.Position[1], v1.Position[2]);

            glColor3f(v2.Color[0], v2.Color[1], v2.Color[2]);
            glVertex3f(v2.Position[0], v2.Position[1], v2.Position[2]);

            glColor3f(v3.Color[0], v3.Color[1], v3.Color[2]);
            glVertex3f(v3.Position[0], v3.Position[1], v3.Position[2]);
        }
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void Box::CreateVertex()
{
    GLfloat width = m_Size;
    GLfloat height = m_Size;
    GLfloat depth = m_Size;

    Vertex v[24];

    GLfloat w2 = 0.5f*width;
    GLfloat h2 = 0.5f*height;
    GLfloat d2 = 0.5f*depth;

    v[0] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    v[1] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    v[2] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    v[3] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f);

    v[4] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
    v[5] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f);
    v[6] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f);
    v[7] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);

    v[8] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[9] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    v[10] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    v[11] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    v[12] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[13] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    v[14] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    v[15] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    v[16] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    v[17] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    v[18] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[19] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    v[20] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    v[21] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    v[22] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    v[23] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    m_Mesh.Vertices.assign(&v[0], &v[24]);


    UINT i[36];

    // Fill in the front face index data
    i[0] = 0; i[1] = 1; i[2] = 2;
    i[3] = 0; i[4] = 2; i[5] = 3;

    // Fill in the back face index data
    i[6] = 4; i[7] = 5; i[8] = 6;
    i[9] = 4; i[10] = 6; i[11] = 7;

    // Fill in the top face index data
    i[12] = 8; i[13] = 9; i[14] = 10;
    i[15] = 8; i[16] = 10; i[17] = 11;

    // Fill in the bottom face index data
    i[18] = 12; i[19] = 13; i[20] = 14;
    i[21] = 12; i[22] = 14; i[23] = 15;

    // Fill in the left face index data
    i[24] = 16; i[25] = 17; i[26] = 18;
    i[27] = 16; i[28] = 18; i[29] = 19;

    // Fill in the right face index data
    i[30] = 20; i[31] = 21; i[32] = 22;
    i[33] = 20; i[34] = 22; i[35] = 23;

    m_Mesh.Indices.assign(&i[0], &i[36]);
}
