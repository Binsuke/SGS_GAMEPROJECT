#include "MyModel.h"


MyModel::MyModel() : m_vForward(0, 0, 1), m_vUp(0, 1, 0), m_vRight(1, 0, 0)
, m_fPolySize(MyPoly::Poly::PolySize), m_fPolyHalfSize(MyPoly::Poly::PolyHalfSize)
, m_vCenter(0, 0, 0), m_vPos(0, 0, 0)
, m_vLocalForward(0, 0, 1), m_vLocalRight(1, 0, 0), m_vLocalUp(0, 1, 0)
, m_fAnimTime(0.2f), m_bAnimeFlg(false), m_fAnimeWaitTime(0.0f)
, m_fAnimationRotX(0.0f), m_fAnimationRotZ(0.0f),m_fAnimationMargineY(0.0f)
{

}

void MyModel::InitAdjustment()
{
	float tmpx = (float)((m_iModelHalfSizeX ) * m_fPolySize) + m_fPolyHalfSize;
	float tmpy = (float)((m_iModelHalfSizeY ) * m_fPolySize) + m_fPolyHalfSize;
	float tmpz = (float)((m_iModelHalfSizeZ ) * m_fPolySize) + m_fPolyHalfSize;

	D3DXMatrixTranslation(&m_mAdjustment, tmpx, tmpy, tmpz);
}

void MyModel::SetLV1()
{
	m_iLV = 1;
	m_iModelSizeX = 1;
	m_iModelSizeY = 1;
	m_iModelSizeZ = 1;
	m_iModelHalfSizeX = 0;
	m_iModelHalfSizeY = 0;
	m_iModelHalfSizeZ = 0;
	InitAdjustment();
	D3DXMATRIX tran;
	D3DXMatrixTranslation(&tran,0, 0, 0);
	m_lmModelMat.push_back(tran);

	//debug  localZ
	//D3DXMatrixTranslation(&tran, 0, 0.5, 1);
	//m_lmModelMat.push_back(tran);
	UpdateCenter();
}
void MyModel::InitLv(int LV)
{
	SetLV1();
	for (int i = 1; i < LV; i++)
	{
		LVUp();
	}
}

void MyModel::UpdateCenter()
{
	D3DXVec3TransformCoord(&m_vCenter, &m_vPos,&m_mAdjustment);
}




void MyModel::Render(D3DXMATRIX view,D3DXMATRIX proj)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	D3DXMATRIX mTran;
	D3DXMatrixTranslation(&mTran,m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMATRIX mRot;
	D3DXMatrixRotationZ(&mRot, m_fAnimationRotX / 180 * D3DX_PI);
	D3DXMATRIX mW = mRot * mTran * m_mAdjustment;
	for (auto itr=m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
				D3DXMATRIX tmpmatrix;
				tmpmatrix = (*itr) * mW;
				m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Cube.Render();
	}
	UpdateCenter();
}

void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran) 
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	
	D3DXMATRIX mW = tran * m_mAdjustment;
	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = (*itr) * mW;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
	UpdateCenter();
}
void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	
	D3DXMATRIX mW = rotation * tran * m_mAdjustment;

	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = (*itr) * mW;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
	UpdateCenter();
}


void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation,D3DXMATRIX scale)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	D3DXMATRIX mW = rotation * tran * m_mAdjustment;
	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = scale * (*itr) * mW ;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
	UpdateCenter();
}

void MyModel:: SetPos(D3DXVECTOR3 vPos) {
	m_vPos = vPos;
}
void MyModel::SetPos(float x, float y, float z) {
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}

void MyModel::MoveLocalForward(float deltaTime)
{
	m_vPos += m_fPolySize * m_iModelSizeZ * m_vLocalForward * deltaTime / m_fAnimTime;

	//if (!m_bAnimeFlg) {
	//	m_bAnimeFlg = true; 
	//	m_vPos += m_fPolySize * m_iModelSizeZ * m_vLocalForward;
	//}
	//if (m_bAnimeFlg) {
	//	m_fAnimeWaitTime += deltaTime * m_fAnimTime;
	//	if (m_fAnimTime <= m_fAnimeWaitTime) {
	//		m_fAnimeWaitTime = 0;
	//		m_bAnimeFlg = false;
	//	}
	//}
}

void MyModel::MoveLocalBackward(float deltaTime)
{
	m_vPos += m_fPolySize * m_iModelSizeZ * -m_vLocalForward * deltaTime / m_fAnimTime;

	//if (!m_bAnimeFlg) {
	//	m_bAnimeFlg = true;
	//	m_vPos += m_fPolySize * m_iModelSizeZ * -m_vLocalForward;
	//}
	//if (m_bAnimeFlg) {
	//	m_fAnimeWaitTime += deltaTime * m_fAnimTime;
	//	if (m_fAnimTime <= m_fAnimeWaitTime) {
	//		m_fAnimeWaitTime = 0;
	//		m_bAnimeFlg = false;
	//	}
	//}
}

void MyModel::MoveLocalRight(float deltaTime)
{
	m_vPos += m_fPolySize * m_iModelSizeX * m_vLocalRight * deltaTime / m_fAnimTime;

	//if (!m_bAnimeFlg) {
	//	m_bAnimeFlg = true;
	//	//m_vPos += m_fPolySize * m_iModelSizeX * m_vLocalRight;
	//	//m_vAnimationPrevPos = m_vPos;
	//}
	//if (m_bAnimeFlg) {
	//	float fAnimeTime = deltaTime * m_fAnimTime; / m_iLV;
	//	m_fAnimeWaitTime += fAnimeTime;
	//	m_vPos += m_fPolySize * m_iModelSizeX * m_vLocalRight * fAnimeTime;

	//	if (m_fAnimTime <= m_fAnimeWaitTime) {
	//		m_fAnimeWaitTime = 0;
	//		m_bAnimeFlg = false;
	//	}
	//}
}

void MyModel::MoveLocalLeft(float deltaTime)
{
	m_vPos += m_fPolySize * m_iModelSizeX * -m_vLocalRight * deltaTime / m_fAnimTime;

	/*if (!m_bAnimeFlg) {
		m_bAnimeFlg = true;
		m_vPos += m_fPolySize * m_iModelSizeX * -m_vLocalRight;
	}
	if (m_bAnimeFlg) {
		m_fAnimeWaitTime += deltaTime * m_fAnimTime;
		if (m_fAnimTime <= m_fAnimeWaitTime) {
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
		}
	}*/
}


void MyModel::Move(float deltaTime, const D3DXVECTOR3& cvForwardVec)
{
	if (cvForwardVec == m_vLocalForward) {
		MoveLocalForward(deltaTime);
	}
	if (cvForwardVec == -m_vLocalForward) {
		MoveLocalBackward(deltaTime);
	}
	if (cvForwardVec == m_vLocalRight) {
		MoveLocalRight(deltaTime);
	}
	if (cvForwardVec == -m_vLocalRight) {
		MoveLocalLeft(deltaTime);
	}
}
void MyModel::LVUp()
{
	m_iLV++;
	int tmpx, tmpy, tmpz;

	tmpx = m_iModelHalfSizeX + 2;
	tmpy = m_iModelHalfSizeY + 2;
	tmpz = m_iModelHalfSizeZ + 2;

	for (int x = 0 ; x < (m_iModelSizeX + 2); x++)
	{
		for (int y = 0; y < (m_iModelSizeY + 2); y++) {
			for (int z = 0; z < (m_iModelSizeZ + 2); z++)
			{
				if (x == 0 || y == 0 || z == 0 || x == m_iModelSizeX + 1 || y == m_iModelSizeY +1 || z == m_iModelSizeZ + 1) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, (-m_fPolySize * tmpx + ((x + 1)*m_fPolySize)), (-m_fPolySize * tmpy + ((y + 1)*m_fPolySize)), (-m_fPolySize * tmpz + ((z + 1)*m_fPolySize)));

					m_lmModelMat.push_back(tran);
				}
			}
		}
	}

	ModelSizeUp();
	InitAdjustment();
	UpdateCenter();


}

void MyModel::LVDown()
{
	if (m_iLV == 1) {//Ž€‚ñ‚¾‚è‚·‚éˆ—‚ð“ü‚ê‚é
		return;
	}
	m_iLV--;
	for (int x = 0; x < m_iModelSizeX; x++)
	{
		for (int y = 0; y < m_iModelSizeY; y++) {
			for (int z = 0; z < m_iModelSizeZ; z++)
			{
				if (x == 0 || y == 0 || z == 0 || x == m_iModelSizeX - 1 || y == m_iModelSizeY - 1 || z == m_iModelSizeZ - 1) {
					m_lmModelMat.pop_back();
				}
			}
		}
	}
	ModelSizeDown();
	InitAdjustment();
	UpdateCenter();
	

}

void MyModel::ModelSizeUp()
{
	m_iModelSizeX += 2;
	m_iModelSizeY += 2;
	m_iModelSizeZ += 2;


	m_iModelHalfSizeX += 1;
	m_iModelHalfSizeY += 1;
	m_iModelHalfSizeZ += 1;	
}

void MyModel::ModelSizeDown() 
{
	m_iModelSizeX -= 2;
	m_iModelSizeY -= 2;
	m_iModelSizeZ -= 2;


	m_iModelHalfSizeX -= 1;
	m_iModelHalfSizeY -= 1;
	m_iModelHalfSizeZ -= 1;
}

float MyModel::GetSizeY()
{
	return m_iModelSizeY * m_fPolySize;
}

D3DXVECTOR3 MyModel:: GetCameraMargin()
{
	D3DXVECTOR3 retvec(0,0,0);
	retvec.y = m_iModelSizeY * m_fPolySize * 0.5f + m_iModelHalfSizeY * m_fPolySize * 0.65f;
	retvec.z = -(m_iModelSizeZ * m_fPolySize + m_iModelSizeZ * m_fPolySize * 1.3f);
	return retvec;
}

D3DXVECTOR3 MyModel::GetCameraTarget()
{
	D3DXVECTOR3 retvec = m_vCenter;
	retvec.y += m_iModelSizeY * m_fPolySize * 0.5;
	return retvec;
}


bool MyModel::AnimationLocalRight(float deltaTime) {
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;

		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
	}
	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		m_vPos += m_fPolySize * m_iModelSizeX * m_vLocalRight * deltaTime / (m_fAnimTime * m_iLV) / m_iModelSizeX;
		
		m_fAnimationRotX += -90.0f * deltaTime / (m_fAnimTime * m_iLV) / m_iModelSizeX ;

		if ((m_fAnimTime*m_iLV) * m_iModelSizeX  <= m_fAnimeWaitTime) {
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			return true;
		}
	}
	return false;
}
