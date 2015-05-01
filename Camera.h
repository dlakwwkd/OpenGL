#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <gl/glut.h>
#include <math.h>

class Camera
{
public:
    Camera();
    ~Camera();

    GLfloat GetPosX(){ return m_PosX; }
    GLfloat GetPosY(){ return m_PosY; }
    GLfloat GetPosZ(){ return m_PosZ; }

    GLfloat GetRotX(){ return m_RotX; }
    GLfloat GetRotY(){ return m_RotY; }
    GLfloat GetRotZ(){ return m_RotZ; }

    GLfloat GetNearZ() const { return m_NearZ; }
    GLfloat GetFarZ() const { return m_FarZ; }
    GLfloat GetAspect(){ return m_Aspect; }
    GLfloat GetFovY() const { return m_FovY; }
    GLfloat GetFovX() const
    {
        GLfloat halfWidth = 0.5f*GetNearWindowWidth();
        return 2.0f*atan(halfWidth / m_NearZ);
    }

    GLfloat GetNearWindowWidth() const { return m_Aspect * m_NearWindowHeight; }
    GLfloat GetNearWindowHeight() const { return m_NearWindowHeight; }
    GLfloat GetFarWindowWidth() const { return m_Aspect * m_FarWindowHeight; }
    GLfloat GetFarWindowHeight() const { return m_FarWindowHeight; }


public:
    void SetLens(GLfloat fovY, GLfloat aspect, GLfloat zn, GLfloat zf);
    void Update(float dt);

    void Strafe(GLfloat d);
    void Walk(GLfloat d);
    void Jump(GLfloat d);

    void Pitch(GLfloat angle);
    void RotateY(GLfloat angle);

	void UpdateViewMatrix();

private:
    GLfloat m_PosX;
    GLfloat m_PosY;
    GLfloat m_PosZ;

    GLfloat m_RotX;
    GLfloat m_RotY;
    GLfloat m_RotZ;

    GLfloat m_NearZ;
    GLfloat m_FarZ;
    GLfloat m_Aspect;
    GLfloat m_FovY;

    GLfloat m_NearWindowHeight;
    GLfloat m_FarWindowHeight;
};

#endif // CAMERA_H