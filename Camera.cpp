//***************************************************************************************
// Camera.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "Camera.h"
#include "gltools.h"
#include "InputManager.h"

Camera::Camera()
:   m_PosX(0.0f), m_PosY(0.0f), m_PosZ(-100.0f), m_RotX(0.0f), m_RotY(0.0f), m_RotZ(0.0f)
{
    SetLens(0.25f*GLT_PI, 1.0f, 1.0f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::SetLens(GLfloat fovY, GLfloat aspect, GLfloat zn, GLfloat zf)
{
	m_FovY = fovY;
	m_Aspect = aspect;
	m_NearZ = zn;
	m_FarZ = zf;

	m_NearWindowHeight = 2.0f * m_NearZ * tanf( 0.5f*m_FovY );
	m_FarWindowHeight  = 2.0f * m_FarZ * tanf( 0.5f*m_FovY );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(m_FovY, m_Aspect, m_NearZ, m_FarZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::Update(float dt)
{
    auto input = InputManager::getInstance();
    
    if (input->GetKeyState('Q'))
        dt *= 10;
    if (input->GetKeyState('W'))
        Walk(10.0f*dt);
    if (input->GetKeyState('S'))
        Walk(-10.0f*dt);
    if (input->GetKeyState('A'))
        Strafe(-10.0f*dt);
    if (input->GetKeyState('D'))
        Strafe(10.0f*dt);
    if (input->GetKeyState(VK_SPACE))
        Jump(10.0f*dt);
    if (input->GetKeyState(VK_SHIFT))
        Jump(-10.0f*dt);

    if (input->GetMouseState(GLUT_LEFT_BUTTON))
    {
        auto deltaPos = input->GetMouseDeltaPos();
        float dx = (0.25f * static_cast<float>(deltaPos.x)) * (GLT_PI / 180.0f);
        float dy = (0.25f * static_cast<float>(deltaPos.y)) * (GLT_PI / 180.0f);
        Pitch(dy);
        RotateY(dx);
    }
    UpdateViewMatrix();
}

void Camera::Strafe(GLfloat d)
{
    m_PosX += -d;
}

void Camera::Walk(GLfloat d)
{
    m_PosZ += d;

}

void Camera::Jump(GLfloat d)
{
    m_PosY += -d;

}

void Camera::Pitch(GLfloat angle)
{
    m_RotX += angle;
}

void Camera::RotateY(GLfloat angle)
{
    m_RotY += angle;
}

void Camera::UpdateViewMatrix()
{
	
}


