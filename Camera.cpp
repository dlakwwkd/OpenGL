//***************************************************************************************
// Camera.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "Camera.h"
#include "InputManager.h"

Camera::Camera()
{
    m_Position[0]   = 0.0f; m_Position[1]   = 0.0f; m_Position[2]   = 100.0f;
    m_Right[0]      = 1.0f; m_Right[1]      = 0.0f; m_Right[2]      = 0.0f;
    m_Up[0]         = 0.0f; m_Up[1]         = 1.0f; m_Up[2]         = 0.0f;
    m_Look[0]       = 0.0f; m_Look[1]       = 0.0f; m_Look[2]       = 1.0f;
    SetLens(45.0f, 1.0f, 1.0f, 1000.0f);
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
    glGetFloatv(GL_PROJECTION_MATRIX, m_Proj);

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

void Camera::LookAt(GLTVector3 pos, GLTVector3 target, GLTVector3 worldUp)
{
    gltCopyVector(pos, m_Position);

    gltSubtractVectors(target, pos, m_Look);
    gltNormalizeVector(m_Look);

    gltVectorCrossProduct(worldUp, m_Look, m_Right);
    gltNormalizeVector(m_Right);

    gltVectorCrossProduct(m_Look, m_Right, m_Up);
}

void Camera::Strafe(GLfloat d)
{
    GLTVector3 r;
    gltCopyVector(m_Right, r);
    gltScaleVector(r, d);
    gltAddVectors(m_Position, r, m_Position);
}

void Camera::Walk(GLfloat d)
{
    GLTVector3 l;
    gltCopyVector(m_Look, l);
    gltScaleVector(l, -d);
    gltAddVectors(m_Position, l, m_Position);
}

void Camera::Jump(GLfloat d)
{
    GLTVector3 u;
    gltCopyVector(m_Up, u);
    gltScaleVector(u, d);
    gltAddVectors(m_Position, u, m_Position);
}

void Camera::Pitch(GLfloat angle)
{
    GLTMatrix R;
    gltRotationMatrix(-angle, m_Right[0], m_Right[1], m_Right[2], R);
    gltRotateVector(m_Up, R, m_Up);
    gltRotateVector(m_Look, R, m_Look);
}

void Camera::RotateY(GLfloat angle)
{
    GLTMatrix R;
    gltRotationMatrix(-angle, 0, 1, 0, R);
    gltRotateVector(m_Right, R, m_Right);
    gltRotateVector(m_Up, R, m_Up);
    gltRotateVector(m_Look, R, m_Look);
}

void Camera::UpdateViewMatrix()
{
    gltNormalizeVector(m_Look);
    gltVectorCrossProduct(m_Look, m_Right, m_Up);
    gltNormalizeVector(m_Up);
    gltVectorCrossProduct(m_Up, m_Look, m_Right);

    GLfloat x = -gltVectorDotProduct(m_Position, m_Right);
    GLfloat y = -gltVectorDotProduct(m_Position, m_Up);
    GLfloat z = -gltVectorDotProduct(m_Position, m_Look);

    m_View[0] = m_Right[0];
    m_View[1] = m_Right[1];
    m_View[2] = m_Right[2];
    m_View[3] = x;

    m_View[4] = m_Up[0];
    m_View[5] = m_Up[1];
    m_View[6] = m_Up[2];
    m_View[7] = y;

    m_View[8] = m_Look[0];
    m_View[9] = m_Look[1];
    m_View[10] = m_Look[2];
    m_View[11] = z;

    m_View[12] = 0.0f;
    m_View[13] = 0.0f;
    m_View[14] = 0.0f;
    m_View[15] = 1.0f;

    gltTransposeMatrix(m_View);
}


