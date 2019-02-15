#include "Camera.h"

float Camera::ms_fRotSize = 180.0f;
float Camera::ms_fRotMargine = 8.0f;

D3DXVECTOR3 Camera::ms_vLocalForward = D3DXVECTOR3(0, 0, 1);
D3DXVECTOR3 Camera::ms_vLocalBackward = D3DXVECTOR3(0, 0, -1);
D3DXVECTOR3 Camera::ms_vLocalRight = D3DXVECTOR3(1, 0, 0);
D3DXVECTOR3 Camera::ms_vLocalLeft = D3DXVECTOR3(-1, 0, 0);


//初期化式で初期化を書いていたけど
//これだけ量が増えてくるとinit関数を作ったほうがいい気がする
//あとたぶんこの状態だとコピーコンストラクターで初期化式通らないとおもう
Camera::Camera()/* : m_vPos(0, 0, 0), m_vRot(0, 0, 0)
,m_vRight(1,0,0),m_vUp(0,1,0), m_vForward(0, 0, 1)
, m_vLookat(0, 0, 1), m_vEyePt(0,0,-3.0f)
,m_fTransDir(1.0f),m_fLookUp(0.0f),m_bLookFlg(false)
,m_vPrevForward(0,0,1),m_vPrevBackward(0,0,-1)
,m_vPrevRight(1,0,0),m_vPrevLeft(-1,0,0)
,m_bMoveFlg(false)*/
{
	D3DXMATRIX mPose(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	m_mPoseMat = mPose;

	D3DXMATRIX mDelta(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	m_mDeltaMat = mDelta;
;}


Camera::Camera(D3DXVECTOR3 inPos) /*: m_vRot(0,0,0)
, m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1)
, m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f)
, m_fTransDir(1.0f), m_fLookUp(0.0f), m_bLookFlg(false)//, m_fRotSize(30.0f)
, m_vPrevForward(0, 0, 1), m_vPrevBackward(0, 0, -1)
, m_vPrevRight(1, 0, 0), m_vPrevLeft(-1, 0, 0)*/
{
	m_vPos = inPos;
}

Camera::Camera(float x, float y, float z)/* : m_vRot(0, 0, 0)
, m_vRight(1, 0, 0), m_vUp(0, 1, 0), m_vForward(0, 0, 1)
, m_vLookat(0, 0, 1), m_vEyePt(0, 0, -3.0f)
, m_fTransDir(1.0f), m_fLookUp(0.0f), m_bLookFlg(false)//, m_fRotSize(30.0f)
, m_vPrevForward(0, 0, 1), m_vPrevBackward(0, 0, -1)
, m_vPrevRight(1, 0, 0), m_vPrevLeft(-1, 0, 0)*/
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}

void Camera::InitCamera()
{
	m_vPos = D3DXVECTOR3(0, 0, 0);
	m_vRot = D3DXVECTOR3(0, 0, 0);
	m_vRight = D3DXVECTOR3(1, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);
	m_vForward = D3DXVECTOR3(0, 0, 1);
	m_vLookat = D3DXVECTOR3(0, 0, 1);
	m_vEyePt = D3DXVECTOR3(0, 0, -3.0f);
	m_fTransDir = 1.0f;
	m_fLookUp = 0.0f;
	m_bLookFlg = false;
	m_vPrevForward = D3DXVECTOR3(0, 0, 1);
	m_vPrevBackward = D3DXVECTOR3(0, 0, -1);
	m_vPrevRight = D3DXVECTOR3(1, 0, 0);
	m_vPrevLeft = D3DXVECTOR3(-1, 0, 0);
	m_bMoveFlg = false;
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
	if (!m_bMoveFlg) {
		m_vRot.y += ms_fRotSize * delta;
		if (m_vRot.y >= 360.0f) {
			m_vRot.y -= 360.0f;
		}
	}
	m_bMoveFlg = false;
}

void Camera::RotLeft(float delta)
{
	if (!m_bMoveFlg)
	{
		m_vRot.y -= ms_fRotSize * delta;
		if (m_vRot.y <= 0.0f) {
			m_vRot.y = 360.0f - m_vRot.y;
		}
	}

	m_bMoveFlg = false;
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

	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, (m_vRot.y / 180 * D3DX_PI));
	D3DXVec3TransformCoord(&vCameraPosVec, &vCameraPosVec, &mRot);
	m_vEyePt = vCameraPosVec + vTarget;
	m_vLookat = vTarget;

	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

}

void Camera::SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec,float TargetMargineY,float TargetMargineX)
{
	D3DXMatrixTranslation(&m_mTransform, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, (m_vRot.y / 180 * D3DX_PI));
	D3DXVec3TransformCoord(&vCameraPosVec, &vCameraPosVec, &mRot);
	
	D3DXVECTOR3 vLookMargine(0,0,0);
	vLookMargine.y = TargetMargineY;
	vLookMargine.x = TargetMargineX;
	m_vLookat = vTarget + vLookMargine;

	D3DXVECTOR3 vEyeMargine(0,0,0);
	vEyeMargine.y = -TargetMargineY;

	m_vEyePt = vCameraPosVec + vTarget + vEyeMargine;
	
	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

}


void Camera::SetCameraA(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec)
{
	D3DXMatrixTranslation(&m_mTransform, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, (m_vRot.y / 180 * D3DX_PI));
	D3DXVec3TransformCoord(&vCameraPosVec, &vCameraPosVec, &mRot);

	D3DXVECTOR3 vLookMargine(0, 0, 0);
	vLookMargine.y = m_fLookUp;
	m_vLookat = vTarget + vLookMargine;

	D3DXVECTOR3 vEyeMargine(0, 0, 0);
	vEyeMargine.y = -m_fLookUp;

	m_vEyePt = vCameraPosVec + vTarget + vEyeMargine;

	D3DXMatrixLookAtLH(mViewOut, &m_vEyePt, &m_vLookat, &m_vUp); //getting view matrix


	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(mProjectionOut, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

}

D3DXVECTOR3 Camera::SwitchVector(eGetLocalType eType,const  D3DXVECTOR3& vForward, const D3DXVECTOR3& vRight) {
	switch (eType) {
	case eGetForward:
		//m_vPrevForward = vForward;
		return vForward;
	case eGetBackward:
		//m_vPrevForward = -vForward;
		return -vForward;
	case eGetRight:
		//m_vPrevRight = vRight;
		return vRight;
	case eGetLeft:
		//m_vPrevRight = -vRight;
		return -vRight;
	}
}


D3DXVECTOR3 Camera::SwitchVectorA(eGetLocalType eType, D3DXVECTOR3 vForward) {
	m_vPrevForward = vForward;
	D3DXVECTOR3 vRight(0, 0, 0);
	
	//今回斜め移動をしないことを前提に作られているので
	//斜めに移動できるパターンになった場合は
	//フォワードベクトルとアップベクトルを受け取り
	//そこから外積を求めて、ライトベクトルを生み出して
	//そのベクトルを元に移動させればいい
	//ただ今回は斜め移動はしないため、簡略している
	//また外積で求めることで得られるメリットは
	//坂などで横移動を行いたいとなった場合にもフォワードが渡されるので
	//坂にめり込むようなこともない

	if (vForward == ms_vLocalForward) {
		vRight = ms_vLocalRight;
	}
	if (vForward == ms_vLocalRight) {
		vRight = ms_vLocalBackward;
	}
	if (vForward == ms_vLocalBackward) {
		vRight = ms_vLocalLeft;
	}
	if (vForward == ms_vLocalLeft) {
		vRight = ms_vLocalForward;
	}

	switch (eType) {
	case eGetForward:
		return vForward;
	case eGetBackward:
		return -vForward;
	case eGetRight:
		return vRight;
	case eGetLeft:
		return -vRight;
	}
}


void Camera::GetMoveLocalVec(D3DXVECTOR3* pOutLocalVec, eGetLocalType eType)
{
	m_bMoveFlg = true;
	if (360.0f - ms_fRotMargine < m_vRot.y && 0 + ms_fRotMargine > m_vRot.y
		|| 45.0f - ms_fRotMargine < m_vRot.y && 45.0f + ms_fRotMargine > m_vRot.y
		|| 90.0f - ms_fRotMargine < m_vRot.y && 90.0f + ms_fRotMargine > m_vRot.y
		|| 135.0f - ms_fRotMargine < m_vRot.y && 135.0f + ms_fRotMargine > m_vRot.y
		|| 180.0f - ms_fRotMargine < m_vRot.y && 180.0f + ms_fRotMargine > m_vRot.y
		|| 225.0f - ms_fRotMargine < m_vRot.y && 225.0f + ms_fRotMargine > m_vRot.y
		|| 270.0f - ms_fRotMargine < m_vRot.y && 270.0f + ms_fRotMargine > m_vRot.y
		|| 315.0f - ms_fRotMargine < m_vRot.y && 315.0f + ms_fRotMargine > m_vRot.y) {
		
		*pOutLocalVec = SwitchVectorA(eType,m_vPrevForward);
		return;
	}

	if (m_vRot.y <= 45.0f - ms_fRotMargine || m_vRot.y >= 360.0f - 45.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(0, 0, 1);
		//D3DXVECTOR3 vLocalRight(1, 0, 0);

		//*pOutLocalVec = SwitchVector(eType, vLocalForward, vLocalRight);
		*pOutLocalVec = SwitchVectorA(eType, vLocalForward);
	}

	if (m_vRot.y > 45.0f - ms_fRotMargine && m_vRot.y < 45.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(1, 0, 0);
		//D3DXVECTOR3 vLocalRight(0, 0, -1);
		//*pOutLocalVec = SwitchVector(eType, vLocalForward, vLocalRight);
		*pOutLocalVec = SwitchVectorA(eType, vLocalForward);
	}
	if (m_vRot.y >= 135.0f - ms_fRotMargine && m_vRot.y <= 135.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(0, 0, -1);
		//D3DXVECTOR3 vLocalRight(-1, 0, 0);
		//*pOutLocalVec = SwitchVector(eType, vLocalForward, vLocalRight);
		*pOutLocalVec = SwitchVectorA(eType, vLocalForward);
	}

	if (m_vRot.y > 225.0f - ms_fRotMargine && m_vRot.y < 225.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(-1, 0, 0);
		//D3DXVECTOR3 vLocalRight(0, 0, 1);
		//*pOutLocalVec = SwitchVector(eType, vLocalForward, vLocalRight);
		*pOutLocalVec = SwitchVectorA(eType, vLocalForward);
	}

}

void Camera::GetMoveLocalForwardVec(D3DXVECTOR3* pOutLocalVec)
{
	if (360.0f - ms_fRotMargine < m_vRot.y && 0 + ms_fRotMargine > m_vRot.y
		|| 45.0f - ms_fRotMargine < m_vRot.y && 45.0f + ms_fRotMargine > m_vRot.y
		|| 90.0f - ms_fRotMargine < m_vRot.y && 90.0f + ms_fRotMargine > m_vRot.y
		|| 135.0f - ms_fRotMargine < m_vRot.y && 135.0f + ms_fRotMargine > m_vRot.y
		|| 180.0f - ms_fRotMargine < m_vRot.y && 180.0f + ms_fRotMargine > m_vRot.y
		|| 225.0f - ms_fRotMargine < m_vRot.y && 225.0f + ms_fRotMargine > m_vRot.y
		|| 270.0f - ms_fRotMargine < m_vRot.y && 270.0f + ms_fRotMargine > m_vRot.y
		|| 315.0f - ms_fRotMargine < m_vRot.y && 315.0f + ms_fRotMargine > m_vRot.y) {
		*pOutLocalVec = m_vPrevForward;
		return;
	}
	if (m_vRot.y <= 45.0f - ms_fRotMargine || m_vRot.y >= 360.0f - 45.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(0, 0, 1);
		*pOutLocalVec = vLocalForward;
	}

	if (m_vRot.y > 45.0f - ms_fRotMargine && m_vRot.y < 45.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(1, 0, 0);
		*pOutLocalVec = vLocalForward;
	}
	if (m_vRot.y >= 135.0f - ms_fRotMargine && m_vRot.y <= 135.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(0, 0, 1);
		*pOutLocalVec = -vLocalForward;
	}

	if (m_vRot.y > 225.0f - ms_fRotMargine && m_vRot.y < 225.0f + 90.0f - ms_fRotMargine) {
		D3DXVECTOR3 vLocalForward(1, 0, 0);
		*pOutLocalVec = -vLocalForward;
	}

	
	m_vPrevForward = *pOutLocalVec;
}

void Camera::GetMoveLocalBackwardVec(D3DXVECTOR3* pOutLocalVec)
{
	if (360.0f - ms_fRotMargine < m_vRot.y && 0 + ms_fRotMargine > m_vRot.y
		|| 45.0f - ms_fRotMargine < m_vRot.y && 45.0f + ms_fRotMargine > m_vRot.y
		|| 90.0f - ms_fRotMargine < m_vRot.y && 90.0f + ms_fRotMargine > m_vRot.y
		|| 135.0f - ms_fRotMargine < m_vRot.y && 135.0f + ms_fRotMargine > m_vRot.y
		|| 180.0f - ms_fRotMargine < m_vRot.y && 180.0f + ms_fRotMargine > m_vRot.y
		|| 225.0f - ms_fRotMargine < m_vRot.y && 225.0f + ms_fRotMargine > m_vRot.y
		|| 270.0f - ms_fRotMargine < m_vRot.y && 270.0f + ms_fRotMargine > m_vRot.y
		|| 315.0f - ms_fRotMargine < m_vRot.y && 315.0f + ms_fRotMargine > m_vRot.y) {
		*pOutLocalVec = m_vPrevBackward;
		return;
	}

	if (m_vRot.y <= 45.0f || m_vRot.y >= 360.0f - 45.0f) {
		D3DXVECTOR3 vLocalForward(0, 0, 1);
		*pOutLocalVec = -vLocalForward;
	}

	if (m_vRot.y > 45.0f && m_vRot.y < 45.0f + 90.0f) {
		D3DXVECTOR3 vLocalForward(1, 0, 0);
		*pOutLocalVec = -vLocalForward;
	}
	if (m_vRot.y >= 135.0f && m_vRot.y <= 135.0f + 90.0f) {
		D3DXVECTOR3 vLocalForward(0, 0, 1);
		*pOutLocalVec = vLocalForward;
	}

	if (m_vRot.y > 225.0f && m_vRot.y < 225.0f + 90.0f) {
		D3DXVECTOR3 vLocalForward(1, 0, 0);
		*pOutLocalVec = vLocalForward;
	}

}


void Camera::GetMoveLocalRightVec(D3DXVECTOR3* pOutLocalVec)
{
	if (360.0f - ms_fRotMargine < m_vRot.y && 0 + ms_fRotMargine > m_vRot.y
		|| 45.0f - ms_fRotMargine < m_vRot.y && 45.0f + ms_fRotMargine > m_vRot.y
		|| 90.0f - ms_fRotMargine < m_vRot.y && 90.0f + ms_fRotMargine > m_vRot.y
		|| 135.0f - ms_fRotMargine < m_vRot.y && 135.0f + ms_fRotMargine > m_vRot.y
		|| 180.0f - ms_fRotMargine < m_vRot.y && 180.0f + ms_fRotMargine > m_vRot.y
		|| 225.0f - ms_fRotMargine < m_vRot.y && 225.0f + ms_fRotMargine > m_vRot.y
		|| 270.0f - ms_fRotMargine < m_vRot.y && 270.0f + ms_fRotMargine > m_vRot.y
		|| 315.0f - ms_fRotMargine < m_vRot.y && 315.0f + ms_fRotMargine > m_vRot.y) {
		*pOutLocalVec = m_vPrevRight;
		return;
	}

	if (m_vRot.y <= 45.0f || m_vRot.y >= 360.0f - 45.0f) {
		D3DXVECTOR3 vLocalRight(1, 0, 0);
		*pOutLocalVec = vLocalRight;
	}

	if (m_vRot.y > 45.0f && m_vRot.y < 45.0f + 90.0f) {
		D3DXVECTOR3 vLocalRight(0, 0, 1);
		*pOutLocalVec = -vLocalRight;
	}
	if (m_vRot.y >= 135.0f && m_vRot.y <= 135.0f + 90.0f) {
		D3DXVECTOR3 vLocalRight(1, 0, 0);
		*pOutLocalVec = -vLocalRight;
	}

	if (m_vRot.y > 225.0f && m_vRot.y < 225.0f + 90.0f) {
		D3DXVECTOR3 vLocalRight(0, 0, 1);
		*pOutLocalVec = vLocalRight;
	}

}



void Camera::GetMoveLocalLeftVec(D3DXVECTOR3* pOutLocalVec)
{
	if (360.0f - ms_fRotMargine < m_vRot.y && 0 + ms_fRotMargine > m_vRot.y
		|| 45.0f - ms_fRotMargine < m_vRot.y && 45.0f + ms_fRotMargine > m_vRot.y
		|| 90.0f - ms_fRotMargine < m_vRot.y && 90.0f + ms_fRotMargine > m_vRot.y
		|| 135.0f - ms_fRotMargine < m_vRot.y && 135.0f + ms_fRotMargine > m_vRot.y
		|| 180.0f - ms_fRotMargine < m_vRot.y && 180.0f + ms_fRotMargine > m_vRot.y
		|| 225.0f - ms_fRotMargine < m_vRot.y && 225.0f + ms_fRotMargine > m_vRot.y
		|| 270.0f - ms_fRotMargine < m_vRot.y && 270.0f + ms_fRotMargine > m_vRot.y
		|| 315.0f - ms_fRotMargine < m_vRot.y && 315.0f + ms_fRotMargine > m_vRot.y) {
		*pOutLocalVec = m_vPrevLeft;
		return;
	}

	if (m_vRot.y <= 45.0f || m_vRot.y >= 360.0f - 45.0f) {
		D3DXVECTOR3 vWorldForward(1, 0, 0);
		*pOutLocalVec = -vWorldForward;
	}

	if (m_vRot.y > 45.0f && m_vRot.y < 45.0f + 90.0f) {
		D3DXVECTOR3 vWorldForward(0, 0, 1);
		*pOutLocalVec = vWorldForward;
	}
	if (m_vRot.y >= 135.0f && m_vRot.y <= 135.0f + 90.0f) {
		D3DXVECTOR3 vWorldForward(1, 0, 0);
		*pOutLocalVec = vWorldForward;
	}

	if (m_vRot.y > 225.0f && m_vRot.y < 225.0f + 90.0f) {
		D3DXVECTOR3 vWorldForward(0, 0, 1);
		*pOutLocalVec = -vWorldForward;
	}

}
void Camera::UpDateLook(float deltaTime, float size)
{
	if (!m_bLookFlg) {
		if (m_fLookUp > 0.0f)
		{
			m_fLookUp += -size * deltaTime;
		}
		if (m_fLookUp < 0.0f)
		{
			m_fLookUp += size * deltaTime;
		}

		if (m_fLookUp <= size * deltaTime && m_fLookUp >= -size * deltaTime)
		{
			m_fLookUp = 0.0f;
		}
	}
	m_bLookFlg = false;
}
void Camera::LookUp(float deltaTime,float size) {

	m_bLookFlg = true;
	if (m_fLookUp < size)
	{
		m_fLookUp += size * deltaTime;
	}
	if (m_fLookUp > size)
	{
		m_fLookUp = size;
	}

}



void Camera::LookDown(float deltaTime, float size) {

	m_bLookFlg = true;
	if (m_fLookUp >  -size)
	{
		m_fLookUp -= size * deltaTime;
	}
	if (m_fLookUp < -size)
	{
		m_fLookUp = -size;
	}

}
