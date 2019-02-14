#include "Camera.h"

Camera::Camera() : m_vPos(0, 0, 0), m_vRot(0, 0, 0),m_vRight(1,0,0),m_vUp(0,1,0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0,0,-3.0f),m_fTransDir(1.0f),m_fRotSize(1.0f)
{
	D3DXMATRIX mPose(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	m_mPoseMat = mPose;

	D3DXMATRIX mDelta(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	m_mDeltaMat = mDelta;
;}


Camera::Camera(D3DXVECTOR3 inPos) : m_vRot(0,0,0), m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f), m_fTransDir(1.0f), m_fRotSize(1.0f)
{
	m_vPos = inPos;
}

Camera::Camera(float x, float y, float z) : m_vRot(0, 0, 0), m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1), m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f), m_fTransDir(1.0f), m_fRotSize(1.0f)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}

Camera::~Camera()
{

}

void Camera::MoveLeft(float delta)
{
	m_vPos += 1.0f * -m_vRight * delta;
}

void Camera::MoveRight(float delta)
{
	m_vPos += 1.0f * m_vRight * delta;
}

void Camera::MoveForward(float delta)
{
	m_vPos += 1.0f * m_vForward * delta;
}

void Camera::MoveBackward(float delta)
{
	m_vPos += 1.0f * -m_vForward * delta;
}

void Camera::MoveUp(float delta)
{
	m_vPos += 0.1f * m_vUp * delta;
}

void Camera::MoveDown(float delta)
{
	m_vPos += -0.1f * m_vUp * delta;
}



void Camera::RotRight(float delta)
{
	m_vRot.y += m_fRotSize * delta;
}

void Camera::RotLeft(float delta)
{
	m_vRot.y -= m_fRotSize * delta;
}

void Camera::SetCamera(D3DXMATRIX* mViewOut,D3DXMATRIX* mProjectionOut)
{
	D3DXMatrixTranslation(&m_mTransform, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXVECTOR3 vRotTmp(m_mPoseMat._21, m_mPoseMat._22, m_mPoseMat._23);//ここD3DXVECTOR3(0,1,0)でもいいはず
	D3DXMatrixRotationAxis(&m_mDeltaMat, &vRotTmp, m_vRot.y);

	D3DXVECTOR3 vRight(1, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vForward(0, 0, 1);

	//回転マトリックスを使って　軸を更新する
	D3DXVec3TransformCoord(&m_vRight, &vRight, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vUp, &vUp, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vForward, &vForward, &m_mDeltaMat);


	D3DXMATRIX mTransform = m_mDeltaMat * m_mTransform;

	 m_vEyePt = m_vPos;
	 m_vLookat = m_vEyePt + m_vForward;

	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


}



void Camera::SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut,D3DXVECTOR3 vTarget)
{
	D3DXMatrixTranslation(&m_mTransform, m_vPos.x, m_vPos.y, m_vPos.z);

	//D3DXVECTOR3 vRotTmp(m_mPoseMat._21, m_mPoseMat._22, m_mPoseMat._23);//ここD3DXVECTOR3(0,1,0)でもいいはず
	//D3DXMatrixRotationAxis(&m_mDeltaMat, &vRotTmp, m_vRot.y);

	D3DXVECTOR3 vRight(1, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vForward(0, 0, 1);

	//回転マトリックスを使って　軸を更新する
	/*D3DXVec3TransformCoord(&m_vRight, &vRight, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vUp, &vUp, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vForward, &vForward, &m_mDeltaMat);
*/

	//D3DXMATRIX mTransform = m_mDeltaMat * m_mTransform;

	m_vEyePt = m_vPos;
	m_vLookat = vTarget;

	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


}


void Camera::SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget,D3DXVECTOR3 vCameraPosVec)
{
	D3DXMatrixTranslation(&m_mTransform, m_vPos.x, m_vPos.y, m_vPos.z);

	//D3DXVECTOR3 vRotTmp(m_mPoseMat._21, m_mPoseMat._22, m_mPoseMat._23);//ここD3DXVECTOR3(0,1,0)でもいいはず
	//D3DXMatrixRotationAxis(&m_mDeltaMat, &vRotTmp, m_vRot.y);

	D3DXVECTOR3 vRight(1, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vForward(0, 0, 1);

	//回転マトリックスを使って　軸を更新する
	/*D3DXVec3TransformCoord(&m_vRight, &vRight, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vUp, &vUp, &m_mDeltaMat);
	D3DXVec3TransformCoord(&m_vForward, &vForward, &m_mDeltaMat);
*/

//D3DXMATRIX mTransform = m_mDeltaMat * m_mTransform;
	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, m_vRot.y);
	D3DXVec3TransformCoord(&vCameraPosVec, &vCameraPosVec, &mRot);
	m_vEyePt = vCameraPosVec + vTarget;
	m_vLookat = vTarget;

	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


}