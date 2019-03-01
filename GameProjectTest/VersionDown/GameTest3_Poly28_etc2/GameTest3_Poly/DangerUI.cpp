#include "DangerUI.h"

void DangerUI::Init() {
	Rot = 0;
	DangerCube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	DangerCube.CreateVertexBuffer();
	DangerCube.CreateTexture("Danger.png");

	KingCube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	KingCube.CreateVertexBuffer();
	KingCube.CreateTexture("KingCube.png");
	m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //この作業を行うのは　本来はシェーダーの情報をもとにレイアウトを作る必要がでてくるため、シェーダーごとに

	m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", NULL, layout, numElements);

	m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", NULL);


	m_ConstantBuffer.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);

	//コンスタントバッファー作成　　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;//説明書
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPUにアクセスするフラグ設定
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//使用法

	m_ConstantBuffer.CreateConstantBuffer(cb);

}

void DangerUI::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 vCenter,float size) {
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mTran;
	D3DXMatrixTranslation(&mTran, vCenter.x, vCenter.y + size, vCenter.z);

	Rot += 0.5 * g_pMain->m_pFPS->GetDeltaTime();

	if (Rot > 360.0f) {
		Rot -= 360.0f;
	}
	D3DXMATRIX mRot;

	D3DXMatrixRotationY(&mRot, Rot / 180 * D3DX_PI);

	float ScaleSize = size / MyPoly::Poly::PolySize  * 0.3;

	D3DXMATRIX mScale;

	D3DXMatrixScaling(&mScale, ScaleSize, ScaleSize, ScaleSize);

	D3DXMATRIX mW = mScale * mRot * mTran;
	m_ConstantBuffer.SetConstantBuffer(mW, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	DangerCube.Render();
}


void DangerUI::RenderKing(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 vCenter, float size) {
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	D3DXMATRIX mTran;
	D3DXMatrixTranslation(&mTran, vCenter.x, vCenter.y + size, vCenter.z);

	Rot += 0.5 * g_pMain->m_pFPS->GetDeltaTime();

	if (Rot > 360.0f) {
		Rot -= 360.0f;
	}
	D3DXMATRIX mRot;

	D3DXMatrixRotationY(&mRot, Rot / 180 * D3DX_PI);


	float ScaleSize = size / MyPoly::Poly::PolySize  * 0.3;

	D3DXMATRIX mScale;

	D3DXMatrixScaling(&mScale, ScaleSize,ScaleSize, ScaleSize);
	D3DXMATRIX mW = mScale * mRot * mTran;

	m_ConstantBuffer.SetConstantBuffer(mW, view, proj);
	m_ConstantBuffer.SetCBtoPS();
	m_ConstantBuffer.SetCBtoVS();
	KingCube.Render();
}
