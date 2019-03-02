#include "CameraUI.h"

float CameraUI::CameraUI_SIZE = 75;

HRESULT CameraUI::Init() {

	m_vPos = D3DXVECTOR3(WINDOW_WIDTH -  CameraUI_SIZE * 1.2, WINDOW_HEIGHT - CameraUI_SIZE * 1.2, 0);
	TIMEUI_SimpleVertex vertices[] =
	{
		D3DXVECTOR3(0,CameraUI_SIZE,0),D3DXVECTOR2(0,1),
		D3DXVECTOR3(0,0,0),D3DXVECTOR2(0,0),
		D3DXVECTOR3(CameraUI_SIZE,CameraUI_SIZE,0),D3DXVECTOR2(1,1),
		D3DXVECTOR3(CameraUI_SIZE,0,0),D3DXVECTOR2(1,0),
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CAMERAUI_SimpleVertex) * 4;

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;

	m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);

	//頂点インプットレイアウトを定義
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
	cb.ByteWidth = sizeof(TIMEUI_SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;

	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	g_pMain->m_pDevice->CreateSamplerState(&SamDesc, &m_pSampler);

	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"CameraUI.png", NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}


void CameraUI::Render() {
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);



	D3DXMATRIX World;

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, m_vPos.x, m_vPos.y, m_vPos.z);

	World = Tran;
	//シェーダーのコンスタントバッファーに各種データを渡す
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
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;

	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}