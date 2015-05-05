#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "gltools.h"

class Camera
{
public:
    Camera();
    ~Camera();

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

    GLfloat* View(){ return m_View; }

public:
    void SetLens(GLfloat fovY, GLfloat aspect, GLfloat zn, GLfloat zf);
    void Update(float dt);

    void LookAt(GLTVector3 pos, GLTVector3 target, GLTVector3 worldUp);

    void Strafe(GLfloat d);
    void Walk(GLfloat d);
    void Jump(GLfloat d);

    void Pitch(GLfloat angle);
    void RotateY(GLfloat angle);

	void UpdateViewMatrix();

private:
    GLTVector3  m_Position;
    GLTVector3  m_Right;
    GLTVector3  m_Up;
    GLTVector3  m_Look;

    GLfloat     m_NearZ;
    GLfloat     m_FarZ;
    GLfloat     m_Aspect;
    GLfloat     m_FovY;

    GLfloat     m_NearWindowHeight;
    GLfloat     m_FarWindowHeight;

    GLTMatrix   m_View;
    GLTMatrix   m_Proj;
};

#endif // CAMERA_H