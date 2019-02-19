#include "Player.h"

MyPlayer::MyPlayer() : GlowInitFlg(false),m_iNextLevel(3*3*3-1),m_iCubeStack(0)
,m_bDamageFlg(false),m_fDamageAnimationTime(3.0),m_bDamageInitFlg(false)
,m_bGlowFlg(false),m_bDamageEndFlg(false)
{

}

void MyPlayer::InitDamagePolygon(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext) {
	m_DamageCube.Init(pDevice, pDeviceContext);
	m_DamageCube.CreateVertexBuffer();
	m_DamageCube.CreateTexture("damage.png");
}

void MyPlayer::GlowStackCube(int CubeCnt) {

	m_iCubeStack += CubeCnt;

	if (m_iCubeStack >= m_iNextLevel) {
		this->LVUp();
		m_iCubeStack -= m_iNextLevel;
		int NowSize = m_iModelSizeX * m_iModelSizeY * m_iModelSizeZ;
		int NextSize = (m_iModelSizeX + 2) * (m_iModelSizeY + 2)*(m_iModelSizeZ + 2);
		m_iNextLevel = NextSize - NowSize;
		m_bGlowFlg = true;
	}
}

bool MyPlayer::Damage(int iLV) {
	if (!m_bDamageFlg) {
		m_bDamageFlg = true;
		m_fPrevAnimTime = m_fAnimTime;
		m_fAnimTime *= 0.5f;//アニメーション速度を上げて　移動速度を上げる
		m_iCubeStack -= iLV * 2;
		m_bRenderflg = false;
		if (m_iCubeStack < 0) {
			int PrevSize = m_iModelSizeX * m_iModelSizeY * m_iModelSizeZ;
			int num = this->LVDown();
			if (num == 0) {
				return true;
			}
			int NowSize = m_iModelSizeX * m_iModelSizeY * m_iModelSizeZ;
			m_iNextLevel = PrevSize;
			m_iCubeStack = m_iNextLevel + m_iCubeStack;
		}
	}
	return false;
}

void MyPlayer::SameCubeColisionCheck(MyModel* pModel) {
	if (m_bGlowFlg||m_bDamageEndFlg) {
		if (this->GetLV() == pModel->GetLV()) {
			if (this->Colision(pModel)) {
				this->Damage(0);
			}
		}
		//m_bDamageEndFlg = false;
		//m_bGlowFlg = false;
	}
}

void MyPlayer::SameCubeColisionCheckEnd() {
	m_bDamageEndFlg = false;
	m_bGlowFlg = false;
}


void MyPlayer::Render(D3DXMATRIX view, D3DXMATRIX proj)
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
	else {
		DamageRender(view, proj);
	}
	//UpdateCenter();
}

void MyPlayer::DamageRender(D3DXMATRIX view, D3DXMATRIX proj)
{
	if (!m_bDamageInitFlg) {
		m_dwDamageAnimationWaitTime = timeGetTime();
		m_bDamageInitFlg = true;
	}

	if (m_bDamageFlg) {
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
			m_DamageCube.Render();
		}
	}

	if (timeGetTime() - m_dwDamageAnimationWaitTime > (1000 * m_fDamageAnimationTime)) {
		m_bDamageFlg = false;
		m_bRenderflg = true;
		m_fAnimTime = m_fPrevAnimTime;
		m_bDamageInitFlg = false;
		m_bGlowFlg = false;
		m_bDamageEndFlg = true;
	}
}

bool MyPlayer::GetDamegaFlg() {
	return m_bDamageFlg;
}