#include "Object.h"
#include "lodepng.h"


Object::Object()
: m_TexID(0)
{
}


Object::~Object()
{
}

void Object::Init()
{

}

void Object::Release()
{

}

void Object::Update(float dt)
{

}

void Object::Render()
{
    glColor3f(m_Color[0], m_Color[1], m_Color[2]);
    glTranslatef(m_Pos[0], m_Pos[1], m_Pos[2]);
    glBindTexture(GL_TEXTURE_2D, m_TexID);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, m_TexEnv);
}


void Object::LoadTexture(const std::string& file, bool mipmapOn)
{
    if (m_TexID)
    {
        printf("\nimage is already loaded");
        return;
    }
    glGenTextures(1, &m_TexID);
    BindTexture2D(m_TexID, file, mipmapOn);
}

void Object::BindTexture2D(GLuint texID, const std::string& file, bool mipmapOn)
{
    std::vector<unsigned char> image;
    unsigned int width, height, error;

    error = lodepng::decode(image, width, height, file);
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    printf("\nimage size is %i", image.size());

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (mipmapOn)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }
}


