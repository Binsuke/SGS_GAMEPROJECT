#include "MyModel.h"


MyModel::MyModel() : m_vForward(0, 0, 1), m_vUp(0, 1, 0), m_vRight(1, 0, 0)
, m_fPolySize(MyPoly::Poly::PolySize), m_fPolyHalfSize(MyPoly::Poly::PolyHalfSize)
, m_vCenter(0, 0, 0), m_vPos(0, 0, 0)
, m_vLocalForward(0, 0, 1), m_vLocalRight(1, 0, 0), m_vLocalUp(0, 1, 0)
, m_fAnimTime(0.1f), m_bAnimeFlg(false), m_fAnimeWaitTime(0.0f)
, m_fAnimationRotX(0.0f), m_fAnimationRotZ(0.0f),m_fAnimationMargineY(0.0f)
,m_vAnimePos(0,0,0),m_fAnimTimeDelay(0.005)
,m_bRenderflg(true)
{
	D3DXMATRIX tran;
	D3DXMatrixTranslation(&tran, 0, 0, 0);
	m_mAnimeRot = tran;
	/*m_pCube = new MyPoly::Poly;*/
}

MyModel::~MyModel() {
	
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
	D3DXVECTOR3 vCenter = m_vPos + m_vAnimePos;
	D3DXVec3TransformCoord(&m_vCenter, &vCenter,&m_mAdjustment);	
}




void MyModel::Render(D3DXMATRIX view,D3DXMATRIX proj)
{
	if (m_bRenderflg) {
		m_VertexShader.SetShader(0);
		m_VertexShader.SetLayout();
		m_PixelShader.SetShader(0);

		D3DXMATRIX mTran;
		D3DXMatrixTranslation(&mTran, m_vPos.x, m_vPos.y, m_vPos.z);

		D3DXMATRIX mW = m_mAnimeRot * mTran * m_mAdjustment;
		for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
		{
			D3DXMATRIX tmpmatrix;
			tmpmatrix = (*itr) * mW;
			m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
			m_ConstantBuffer.SetCBtoPS();
			m_ConstantBuffer.SetCBtoVS();
			m_Cube.Render();
		}
	}
	//UpdateCenter();
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


bool MyModel::MoveA(float deltaTime, const D3DXVECTOR3& cvForwardVec)
{
	if (cvForwardVec == m_vLocalForward) {
		return AnimationLocalForwardA(deltaTime);
	}
	if (cvForwardVec == -m_vLocalForward) {
		return AnimationLocalBackwardA(deltaTime);
	}
	if (cvForwardVec == m_vLocalRight) {
		return AnimationLocalRightA(deltaTime);
	}
	if (cvForwardVec == -m_vLocalRight) {
		return AnimationLocalLeftA(deltaTime);
	}
	return false;
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
	//D3DXVECTOR3 vTmp(m_fPolySize, 0, m_fPolySize);

	//m_vPos += vTmp;
	ModelSizeUp();
	InitAdjustment();
	UpdateCenter();


}

void MyModel::LVDown()
{
	if (m_iLV == 1) {//死んだりする処理を入れる
		m_bRenderflg = false;
		m_iLV = 0;
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
	D3DXVECTOR3 vTmp(m_fPolySize, 0, m_fPolySize);

	m_vPos += vTmp;

	ModelSizeDown();
	InitAdjustment();
	UpdateCenter();
	

}

D3DXVECTOR3 MyModel::GetCenter() { 
	UpdateCenter();
	return m_vCenter; 
}

D3DXVECTOR3 MyModel::GetColisionPos() { return m_vPos + m_vAnimePos; }


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

float MyModel::GetSize()
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

void MyModel::AnimationMargineY(float deltaTime)
{
	//正直ここのアニメーションの高さの調整はイマイチわからん状態
		//ただいい感じになったからこれでいく
	
	if (m_vPos.y < -m_fAnimationMargineY / 2.0f) {
		m_vPos.y = m_vAnimationPrevPos.y - m_fAnimationMargineY / 2.0f;
	}

	if ((m_fAnimTime)* m_iModelSizeX / 2 < m_fAnimeWaitTime)
	{
		m_vPos.y += -m_fAnimationMargineY * deltaTime / (m_fAnimTime) / m_iModelSizeX;
	}
	else
	{
		m_vPos.y += +m_fAnimationMargineY * deltaTime / (m_fAnimTime) / m_iModelSizeX;
	}
	
}

void MyModel::AnimationMargineSet() {
	
	//test

	//綺麗なアニメーションをやるなら
	//デルタYとデルタXを求める必要があるけれど
	//とりあえず今はこれで妥協する
	float HalfLineX = m_iModelSizeX * m_fPolySize;
	float HalfLineY = m_iModelSizeY * m_fPolySize;
	
	m_fAnimationMargineY = sqrt(pow(HalfLineX, 2) + pow(HalfLineY, 2)) / 2;
	m_fAnimationMargineY -= m_vPos.y;
}

bool MyModel::AnimationLocalRight(float deltaTime) {
	
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
		AnimationMargineSet();
	}
	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;

		if ((m_fAnimTime) * m_iModelSizeX <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeX * m_vLocalRight;
			m_fAnimationRotX = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;

			return true;
		}

		m_vPos += m_fPolySize * m_iModelSizeX * m_vLocalRight * deltaTime / (m_fAnimTime) / m_iModelSizeX;

		m_fAnimationRotX += -90.0f * deltaTime / (m_fAnimTime) / m_iModelSizeX;
		
		AnimationMargineY(deltaTime);
		
		
	}
	UpdateCenter();
	return false;
}

bool MyModel::AnimationLocalRightA(float deltaTime)
{
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
	}

	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		float AnimTime = m_fAnimTime + m_fAnimTimeDelay * m_iLV;
		if ((AnimTime)* m_iModelSizeX <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeX * m_vLocalRight;
			m_fAnimationRotX = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			D3DXMATRIX tran;
			D3DXMatrixTranslation(&tran, 0, 0, 0);
			m_mAnimeRot = tran;

			m_vAnimePos = D3DXVECTOR3(0, 0, 0);
			return true;
		}

		m_vAnimePos += m_fPolySize * m_iModelSizeX * m_vLocalRight * deltaTime / (AnimTime) / m_iModelSizeX;

		m_fAnimationRotX += -90.0f * deltaTime / (AnimTime) / m_iModelSizeX;


		D3DXMATRIX mPipotTran;
		D3DXMatrixTranslation(&mPipotTran, -m_iModelSizeX * m_fPolyHalfSize, m_iModelSizeY * m_fPolyHalfSize, 0);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse, NULL, &mPipotTran);
		D3DXMATRIX mRotZ;
		D3DXMatrixRotationZ(&mRotZ, m_fAnimationRotX / 180 * D3DX_PI);

		m_mAnimeRot = mPipotTran * mRotZ * mInverse;
	}
	UpdateCenter();
	return false;
}


bool MyModel::AnimationLocalLeft(float deltaTime) {
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
		AnimationMargineSet();
	}
	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		float AnimTime = m_fAnimTime + m_fAnimTimeDelay * m_iLV;
		if ((m_fAnimTime) * m_iModelSizeX <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos +  m_fPolySize * m_iModelSizeX * -m_vLocalRight;
			m_fAnimationRotX = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			return true;
		}

		m_vPos += m_fPolySize * m_iModelSizeX * -m_vLocalRight * deltaTime / AnimTime / m_iModelSizeX;

		m_fAnimationRotX += 90.0f * deltaTime / (AnimTime) / m_iModelSizeX;

		AnimationMargineY(deltaTime);
	}
	UpdateCenter();
	return false;
}

bool MyModel::AnimationLocalLeftA(float deltaTime)
{
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
	}

	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		float AnimTime = m_fAnimTime + m_fAnimTimeDelay * m_iLV;

		if ((AnimTime)* m_iModelSizeX <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeX * -m_vLocalRight;
			m_fAnimationRotX = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			D3DXMATRIX tran;
			D3DXMatrixTranslation(&tran, 0, 0, 0);
			m_mAnimeRot = tran;

			m_vAnimePos = D3DXVECTOR3(0, 0, 0);
			return true;
		}

		m_vAnimePos += m_fPolySize * m_iModelSizeX * -m_vLocalRight * deltaTime / (AnimTime)/ m_iModelSizeX;

		m_fAnimationRotX += 90.0f * deltaTime / (AnimTime) / m_iModelSizeX;


		D3DXMATRIX mPipotTran;
		D3DXMatrixTranslation(&mPipotTran, m_iModelSizeX * m_fPolyHalfSize, m_iModelSizeY * m_fPolyHalfSize, 0);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse, NULL, &mPipotTran);
		D3DXMATRIX mRotZ;
		D3DXMatrixRotationZ(&mRotZ, m_fAnimationRotX / 180 * D3DX_PI);

		m_mAnimeRot = mPipotTran * mRotZ * mInverse;
	}
	UpdateCenter();
	return false;
}





bool MyModel::AnimationLocalForward(float deltaTime) {
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotZ = 0;
		AnimationMargineSet();
	}
	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;

		if ((m_fAnimTime) * m_iModelSizeZ <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeX * m_vLocalForward;
			m_fAnimationRotZ = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			return true;
		}

		m_vPos += m_fPolySize * m_iModelSizeZ * m_vLocalForward * deltaTime / (m_fAnimTime) / m_iModelSizeX;

		m_fAnimationRotZ += 90.0f * deltaTime / (m_fAnimTime) / m_iModelSizeX;

		AnimationMargineY(deltaTime);
	}
	UpdateCenter();
	return false;
}


bool MyModel::AnimationLocalForwardA(float deltaTime)
{
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
	}

	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		float AnimTime = m_fAnimTime + m_fAnimTimeDelay * m_iLV;

		if ((AnimTime) * m_iModelSizeZ <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeZ * m_vLocalForward;
			m_fAnimationRotZ = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			D3DXMATRIX tran;
			D3DXMatrixTranslation(&tran, 0, 0, 0);
			m_mAnimeRot = tran;

			m_vAnimePos = D3DXVECTOR3(0, 0, 0);
			return true;
		}

		m_vAnimePos += m_fPolySize * m_iModelSizeZ * m_vLocalForward * deltaTime / (AnimTime)/ m_iModelSizeX;

		m_fAnimationRotZ += 90.0f * deltaTime / (AnimTime) / m_iModelSizeX;


		D3DXMATRIX mPipotTran;
		//回転する軸に動かしてるんだけど　ローカルで0,0,0がセンターだからYを動してキューブの下の辺がy=0にする
		//次に回転軸を奧にしてあげたいのでZをマイナスしてあげれば　ForwardUnderともいうべき場所が　ピポットの位置になる
		//そこを中心に回転させることで　綺麗に回転する
		//その後移動分の逆行列をかけてあげることで、回転だけを維持した状態で
		//元の位置に戻ってくる
		D3DXMatrixTranslation(&mPipotTran, 0, m_iModelSizeY * m_fPolyHalfSize, -m_iModelSizeZ * m_fPolyHalfSize);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse, NULL, &mPipotTran);
		D3DXMATRIX mRotX;
		D3DXMatrixRotationX(&mRotX, m_fAnimationRotZ / 180 * D3DX_PI);

		m_mAnimeRot = mPipotTran * mRotX * mInverse;
	}
	UpdateCenter();
	return false;
}


bool MyModel::AnimationLocalBackward(float deltaTime) {
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotZ = 0;
		AnimationMargineSet();
	}
	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;

		if ((m_fAnimTime)* m_iModelSizeZ <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeX * -m_vLocalForward;
			m_fAnimationRotZ = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			return true;
		}

		m_vPos += m_fPolySize * m_iModelSizeZ * -m_vLocalForward * deltaTime / (m_fAnimTime) / m_iModelSizeX;

		m_fAnimationRotZ += -90.0f * deltaTime / (m_fAnimTime) / m_iModelSizeX;

		AnimationMargineY(deltaTime);
	}
	UpdateCenter();
	return false;
}



bool MyModel::AnimationLocalBackwardA(float deltaTime)
{
	if (m_bAnimeFlg == false) {
		m_bAnimeFlg = true;
		m_vAnimationPrevPos = m_vPos;
		m_fAnimeWaitTime = 0;
		m_fAnimationRotX = 0;
	}

	if (m_bAnimeFlg == true) {
		m_fAnimeWaitTime += deltaTime;
		float AnimTime = m_fAnimTime + m_fAnimTimeDelay * m_iLV;

		if ((AnimTime)* m_iModelSizeZ <= m_fAnimeWaitTime) {
			m_vPos = m_vAnimationPrevPos + m_fPolySize * m_iModelSizeZ * -m_vLocalForward;
			m_fAnimationRotZ = 0;
			m_fAnimeWaitTime = 0;
			m_bAnimeFlg = false;
			D3DXMATRIX tran;
			D3DXMatrixTranslation(&tran, 0, 0, 0);
			m_mAnimeRot = tran;

			m_vAnimePos = D3DXVECTOR3(0, 0, 0);
			return true;
		}
		//このアニメポスはカメラ座標を更新するためにセンターを少しずらしてあげる必要があって
		//そのためのマージン、アニメーションをしてないときはこれは何の成分もないが
		//アニメーションをしてるときはこれがうまい具合にセンターを動かしてくれる
		m_vAnimePos += m_fPolySize * m_iModelSizeZ * -m_vLocalForward * deltaTime / (AnimTime) / m_iModelSizeX;

		m_fAnimationRotZ += -90.0f * deltaTime / (AnimTime) / m_iModelSizeX;


		D3DXMATRIX mPipotTran;
		//回転する軸に動かしてるんだけど　ローカルで0,0,0がセンターだからYを動してキューブの下の辺がy=0にする
		//次に回転軸を奧にしてあげたいのでZをマイナスしてあげれば　ForwardUnderともいうべき場所が　ピポットの位置になる
		//そこを中心に回転させることで　綺麗に回転する
		//その後移動分の逆行列をかけてあげることで、回転だけを維持した状態で
		//元の位置に戻ってくる
		D3DXMatrixTranslation(&mPipotTran, 0, m_iModelSizeY * m_fPolyHalfSize, m_iModelSizeZ * m_fPolyHalfSize);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse, NULL, &mPipotTran);
		D3DXMATRIX mRotX;
		D3DXMatrixRotationX(&mRotX, m_fAnimationRotZ / 180 * D3DX_PI);

		m_mAnimeRot = mPipotTran * mRotX * mInverse;
	}
	UpdateCenter();
	return false;
}

