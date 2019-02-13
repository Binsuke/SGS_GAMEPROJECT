#include "Camera.h"

Camera::Camera() : m_Pos(0, 0, 0), m_Rot(0, 0, 0),m_vRight(1,0,0),m_vUp(0,1,0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0,0,-3.0f)
{

;}


Camera::Camera(D3DXVECTOR3 inPos) : m_Rot(0,0,0), m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f)
{
	m_Pos = inPos;
}

Camera::Camera(float x, float y, float z) : m_Rot(0, 0, 0), m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

Camera::~Camera()
{

}