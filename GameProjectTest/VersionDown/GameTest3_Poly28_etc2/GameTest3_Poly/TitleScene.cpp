#include "TitleScene.h"

TitleScene::TitleScene() :m_vPos(0,0,0){
	m_bInitFlg = false;
	//m_bKeyFlg = false;
}

TitleScene::~TitleScene() {
	Release();
}

void TitleScene::Init() {
	m_vPos = D3DXVECTOR3(0, 0, 0);
	eStartOrEndCheck = eStart;
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	//貯点インプットレイアウトを定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	m_VertexShader.CreateShaderFromFileV("HPUI.hlsl", "VS_2D", "vs_5_0", 0, layout, numElements);

	m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_PixelShader.CreateShaderFromFile("HPUI.hlsl", "PS_2D", "ps_5_0", 0);

	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(UI_SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return;
	}
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	g_pMain->m_pDevice->CreateSamplerState(&SamDesc, &m_pSampler);

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"title_start.png", NULL, NULL, &m_pTexture[0], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return;
	}
	//
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"title_end.png", NULL, NULL, &m_pTexture[1], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return;
	}

	InitVertexBuffer();
	
}

void TitleScene::InitVertexBuffer() {
	UI_SimpleVertex vertices[] =
	{
		D3DXVECTOR3(0,480,0),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(0,0,0),D3DXVECTOR2(0,0),
		D3DXVECTOR3(640,480,0),D3DXVECTOR2(1,1),
		D3DXVECTOR3(640,0,0),D3DXVECTOR2(1,0),
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UI_SimpleVertex) * 4;

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return;
	}
}

BaseScene::eScene TitleScene::App()
{

	if (m_bInitFlg == false)
	{
		Init();
		m_bInitFlg = true;
	}
	ReturnScene = BaseScene::eScene::Title;

	Input();
	Render();

	return ReturnScene;
}

void TitleScene::Release()
{
	m_bInitFlg = false;
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pSampler);
	SAFE_RELEASE(m_pTexture[0]);
	SAFE_RELEASE(m_pTexture[1]);
}

void TitleScene::Render()
{
	float ClearColor[4] = { 0,0,0,1 };//クリアーカラー

	g_pMain->m_pDeviceContext->ClearRenderTargetView(g_pMain->m_pBackBuffer_TexRTV, ClearColor);
	g_pMain->m_pDeviceContext->ClearDepthStencilView(g_pMain->m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	D3DXMATRIX World;
	D3DXMATRIX Tran;

	D3DXMatrixTranslation(&Tran, m_vPos.x, m_vPos.y, m_vPos.z);

	World = Tran;

	D3D11_MAPPED_SUBRESOURCE pData;
	HPUI_SIMPLESHADER_CONSTANT_BUFFER cb;

	if (SUCCEEDED(g_pMain->m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド行列を渡す
		cb.mW = World;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = WINDOW_WIDTH;
		cb.ViewPortHeight = WINDOW_HEIGHT;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		g_pMain->m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}

	g_pMain->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	g_pMain->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);


	//バーテックスバッファーセット
	UINT stride = sizeof(UI_SimpleVertex);
	UINT offset = 0;

	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture[eStartOrEndCheck]);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
	g_pMain->m_pSwapChain->Present(0, 0);
}

void TitleScene::Input()
{
	if (GetKeyState(VK_UP) & 0x80) {
		eStartOrEndCheck = eStart;
	}
	else if (GetKeyState(VK_DOWN) & 0x80) {
		eStartOrEndCheck = eEnd;
	}

	if (GetKeyState(VK_RETURN) & 0x80)
	{
		switch (eStartOrEndCheck) {
		case eStart:
			ReturnScene = BaseScene::eScene::Game;
			break;
		case eEnd:
			ReturnScene = BaseScene::eScene::End;
			break;
		}//ReturnScene = BaseScene::eScene::Game;
	}
	/*else if (GetKeyState(VK_SPACE) & 0x80) {
		ReturnScene = BaseScene::eScene::End;}
	*/
}


