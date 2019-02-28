#include "MoveUI.h"


//void MoveUI::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext)
//{
//	m_pDevice = inDevice;
//	m_pDeviceContext = inDeviceContext;
//}
float MoveUI::m_sfScale = 0.65f;

float MoveUI::m_sfLengthPer = 0.4f;

void MoveUI::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos)
{
	D3DXVECTOR3 vW = pos;
	vW.z += 0.5;
	RenderW(view, proj, vW);

	D3DXVECTOR3 vS = pos;
	vS.z += -0.5;
	RenderS(view, proj, vS);

	D3DXVECTOR3 vA = pos;
	vA.x += -0.5;
	RenderA(view, proj, vA);

	D3DXVECTOR3 vD = pos;
	vD.x += 0.5;
	RenderD(view, proj, vD);
}


void MoveUI::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 vCenter, float length, D3DXVECTOR3 vForward, int iLV)
{
	D3DXVECTOR3 vLocalForward(0, 0, 1);
	D3DXVECTOR3 vLocalRight(1, 0, 0);
	D3DXVECTOR3 vW, vS, vA, vD;
	if (vForward == vLocalForward) {
		vW = vCenter + vLocalForward * length;
		vS = vCenter - vLocalForward * length;
		vA = vCenter - vLocalRight * length;
		vD = vCenter + vLocalRight * length;
	}
	if (vForward == -vLocalForward) {
		vW = vCenter - vLocalForward * length;
		vS = vCenter + vLocalForward * length;
		vA = vCenter + vLocalRight * length;
		vD = vCenter - vLocalRight * length;
	}


	if (vForward == vLocalRight) {
		vW = vCenter + vLocalRight * length;
		vS = vCenter - vLocalRight * length;
		vA = vCenter + vLocalForward * length;
		vD = vCenter - vLocalForward * length;
	}

	if (vForward == -vLocalRight) {
		vW = vCenter - vLocalRight * length;
		vS = vCenter + vLocalRight * length;
		vA = vCenter - vLocalForward * length;
		vD = vCenter + vLocalForward * length;
	}

	vW.y += length * m_sfLengthPer;
	vA.y += length * m_sfLengthPer;
	vS.y += length * m_sfLengthPer;
	vD.y += length * m_sfLengthPer;

	RenderW(view, proj, vW,iLV);
	RenderA(view, proj, vA,iLV);
	RenderD(view, proj, vD,iLV);
	RenderS(view, proj, vS,iLV);

	/*std::list<eWASD> leRenderSort;
	Sort(&leRenderSort, vW.z, vA.z, vS.z, vD.z);

	for (auto itr = leRenderSort.begin(); itr != leRenderSort.end(); itr++) {
		switch ((*itr)) {
		case eW:
			RenderW(view, proj, vW);
			break;
		case eA:
			RenderA(view, proj, vA);
			break;
		case eS:
			RenderS(view, proj, vS);
			break;
		case eD:
			RenderD(view, proj, vD);
			break;
		}
	}*/

}

void MoveUI::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 vCenter, float length, D3DXVECTOR3 vForward)
{
	D3DXVECTOR3 vLocalForward(0, 0, 1);
	D3DXVECTOR3 vLocalRight(1, 0, 0);
	D3DXVECTOR3 vW, vS, vA, vD;
	if (vForward == vLocalForward) {
		vW = vCenter + vLocalForward * length;
		vS = vCenter - vLocalForward * length;
		vA = vCenter - vLocalRight * length;
		vD = vCenter + vLocalRight * length;
	}
	if (vForward == -vLocalForward) {
		vW = vCenter - vLocalForward * length;
		vS = vCenter + vLocalForward * length;
		vA = vCenter + vLocalRight * length;
		vD = vCenter - vLocalRight * length;
	}


	if (vForward == vLocalRight) {
		vW = vCenter + vLocalRight * length;
		vS = vCenter - vLocalRight * length;
		vA = vCenter + vLocalForward * length;
		vD = vCenter - vLocalForward * length;
	}

	if (vForward == -vLocalRight) {
		vW = vCenter - vLocalRight * length;
		vS = vCenter + vLocalRight * length;
		vA = vCenter - vLocalForward * length;
		vD = vCenter + vLocalForward * length;
	}
	vW.y += length * m_sfLengthPer;
	vA.y += length * m_sfLengthPer;
	vS.y += length * m_sfLengthPer;
	vD.y += length * m_sfLengthPer;

	RenderW(view, proj, vW);
	RenderA(view, proj, vA);
	RenderD(view, proj, vD);
	RenderS(view, proj, vS);

}

void MoveUI::Sort(std::list<eWASD>*lepOut, float fWz, float fAz, float fSz, float fDz) {
	eWASD etmp[4] = { eW,eA,eS,eD };

	float ftmp[4] = { fWz,fAz,fSz,fDz };
	for (int top = 0; top < 4; top++) {
		for (int next = 1; next < 4; next++) {
			if (ftmp[top] < ftmp[next]) {
				float fback = ftmp[top];
				ftmp[top] = ftmp[next];
				ftmp[next] = fback;

				eWASD ebackup = etmp[top];
				etmp[top] = etmp[next];
				etmp[next] = ebackup;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		lepOut->push_back(etmp[i]);
	}
}



void MoveUI::RenderW(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	D3DXMATRIX mWC = CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelW.Render();
}

void MoveUI::RenderW(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos,int iLV)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);
	float fscale = m_sfScale;
	if (iLV == 1) {
		fscale = 0.5f;
	}
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, iLV*fscale, iLV*fscale, 1);

	D3DXMATRIX mWC = mScale * CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelW.Render();
}

void MoveUI::RenderA(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	D3DXMATRIX mWC = CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelA.Render();
}

void MoveUI::RenderA(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos,int iLV)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	float fscale = m_sfScale;
	if (iLV == 1) {
		fscale = 0.5f;
	}
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, iLV*fscale, iLV*fscale, 1);

	D3DXMATRIX mWC = mScale * CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelA.Render();
}


void MoveUI::RenderS(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos,int iLV)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);
	
	float fscale = m_sfScale;
	if (iLV == 1) {
		fscale = 0.5f;
	}
	
	D3DXMATRIX mScale;

	D3DXMatrixScaling(&mScale, iLV*fscale, iLV*fscale, 1);

	D3DXMATRIX mWC = mScale * CancelRotation * mW;

	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelS.Render();
}
void MoveUI::RenderS(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	D3DXMATRIX mWC = CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelS.Render();
}


void MoveUI::RenderD(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	D3DXMATRIX mWC = CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelD.Render();
}


void MoveUI::RenderD(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos,int iLV)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mW;
	D3DXMatrixTranslation(&mW, pos.x, pos.y, pos.z);
	D3DXMATRIX CancelRotation = view;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);

	float fscale = m_sfScale;
	if (iLV == 1) {
		fscale = 0.5f;
	}	
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, iLV*fscale, iLV*fscale, 1);

	D3DXMATRIX mWC = mScale * CancelRotation * mW;
	m_ConstantBuffer.SetConstantBuffer(mWC, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	m_PanelD.Render();
}


void MoveUI::MovePanelInit(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext) {
	m_PanelW.Init(inDevice, inDeviceContext);
	m_PanelW.CreateVertexBuffer();
	m_PanelW.CreateTexture("UI_W.png");

	m_PanelA.Init(inDevice, inDeviceContext);
	m_PanelA.CreateVertexBuffer();
	m_PanelA.CreateTexture("UI_A.png");

	m_PanelS.Init(inDevice, inDeviceContext);
	m_PanelS.CreateVertexBuffer();
	m_PanelS.CreateTexture("UI_S.png");

	m_PanelD.Init(inDevice, inDeviceContext);
	m_PanelD.CreateVertexBuffer();
	m_PanelD.CreateTexture("UI_D.png");


}
