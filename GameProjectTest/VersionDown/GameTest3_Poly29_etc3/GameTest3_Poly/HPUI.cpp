#include "HPUI.h"

float MyHPUI::HPUISize = 25;

MyHPUI::MyHPUI():m_vPos(HPUISize+15,HPUISize+15,0),m_vUILeftPos(HPUISize*3,HPUISize+15,0)
{

}

MyHPUI::~MyHPUI() {
	SAFE_RELEASE(m_pConstantBuffer);
	//SAFE_RELEASE(m_pVertexShader);
	//SAFE_RELEASE(m_pPixelShader);
	//SAFE_RELEASE(m_pVertexLayout);
	//SAFE_RELEASE(m_pVertexBuffer);
}

HRESULT MyHPUI::Init() {

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
	cb.ByteWidth = sizeof(HPUI_SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}


	if (FAILED(InitModel())) {
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

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"white.png", NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//


	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_0.png", NULL, NULL, &m_pNumTexture[0], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}

	
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_1.png", NULL, NULL, &m_pNumTexture[1], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_2.png", NULL, NULL, &m_pNumTexture[2], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_3.png", NULL, NULL, &m_pNumTexture[3], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_4.png", NULL, NULL, &m_pNumTexture[4], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_5.png", NULL, NULL, &m_pNumTexture[5], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_6.png", NULL, NULL, &m_pNumTexture[6], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_7.png", NULL, NULL, &m_pNumTexture[7], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_8.png", NULL, NULL, &m_pNumTexture[8], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_9.png", NULL, NULL, &m_pNumTexture[9], NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//

	//テクスチャー読み込み
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(g_pMain->m_pDevice, (LPCSTR)"UI_SRUSH.png", NULL, NULL, &m_pSrushTexture, NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	//
	return S_OK;
}

HRESULT MyHPUI::InitModel()
{
	HPUI_SimpleVertex vertices[] =
	{
		D3DXVECTOR3(0,HPUISize,0),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(0,0,0),D3DXVECTOR2(0,0),
		D3DXVECTOR3(HPUISize,HPUISize,0),D3DXVECTOR2(1,1),
		D3DXVECTOR3(HPUISize,0,0),D3DXVECTOR2(1,0),
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer))) 
	{
		return E_FAIL;
	}
	CreateVBTop();
	CreateVBDown();
	CreateVBLeft();
	CreateVBRight();
	CreateVBFront();
	CreateVBBack();

	return S_OK;
}
static float rot = 0;
void MyHPUI::Render(float deltaTime)
{
	//バーテックスっバっファーをセット

	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	rot += 15.0f * deltaTime;;
	D3DXMATRIX RotZ;

	D3DXMatrixRotationZ(&RotZ, 25.0f / 180.0f*D3DX_PI);

	D3DXMATRIX Rot;
	D3DXMatrixRotationY(&Rot, rot / 180 * D3DX_PI);


	D3DXMATRIX World;

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, m_vPos.x, m_vPos.y, 0);

	World = RotZ * Rot * Tran;
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

	RenderFront();
	RenderBack();
	RenderLeft();
	RenderRight();
	RenderTop();
	RenderDown();

}




HRESULT MyHPUI::CreateVBFront() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(1,0),//頂点４
	};

	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferFront)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyHPUI::CreateVBBack() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-HPUISize,HPUISize,HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(HPUISize,HPUISize,HPUISize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferBack)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyHPUI::CreateVBLeft() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(-HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(-HPUISize,HPUISize,HPUISize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferLeft)))
	{
		return E_FAIL;
	}
	return S_OK;
}



HRESULT MyHPUI::CreateVBRight()
{
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(HPUISize,HPUISize,HPUISize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferRight)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyHPUI::CreateVBTop()
{

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(HPUISize,-HPUISize,-HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(HPUISize,-HPUISize,HPUISize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferTop)))
	{
		return E_FAIL;
	}
	return S_OK;
}


HRESULT MyHPUI::CreateVBDown()
{

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-HPUISize,HPUISize,HPUISize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(HPUISize,HPUISize,-HPUISize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(HPUISize,HPUISize,HPUISize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(HPUI_SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(g_pMain->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferDown)))
	{
		return E_FAIL;
	}
	return S_OK;
}



void MyHPUI::RenderFront()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferFront, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}

void MyHPUI::RenderBack()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferBack, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}

void MyHPUI::RenderTop()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferTop, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}

void MyHPUI::RenderDown()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferDown, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}

void MyHPUI::RenderRight()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferRight, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}


void MyHPUI::RenderLeft()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(HPUI_SimpleVertex);
	UINT offset = 0;


	g_pMain->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferLeft, &stride, &offset);

	//テクスチャのサンプラーを登録
	g_pMain->m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	//テクスチャをシェーダーに渡す
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}


void MyHPUI::RenderStackCubeNum(int Num)
{
	int tmp = Num;

	int RightNum = tmp % 10;

	tmp /= 10;

	int CenterRightNum = tmp % 10;

	tmp /= 10;

	//int CenterNum = tmp % 10;
	//tmp /= 10;

	int CenterLeftNum = tmp % 10;
	tmp /= 10;

	int LeftNum = tmp % 10;
	
	D3DXVECTOR3 vtmp = m_vUILeftPos;
	RenderNumber(LeftNum, vtmp);

	vtmp.x += HPUISize;
	RenderNumber(CenterLeftNum, vtmp);

	vtmp.x += HPUISize;
	RenderNumber(CenterRightNum, vtmp);
	vtmp.x += HPUISize;
	RenderNumber(RightNum, vtmp);
}


void MyHPUI::RenderNextCubeNum(int Num)
{
	int tmp = Num;

	int RightNum = tmp % 10;

	tmp /= 10;

	int CenterRightNum = tmp % 10;

	tmp /= 10;

	int CenterLeftNum = tmp % 10;
	tmp /= 10;

	int LeftNum = tmp % 10;

	D3DXVECTOR3 vtmp = m_vUILeftPos;
	vtmp.x += HPUISize * 4;

	RenderSrush(vtmp);

	vtmp.x += HPUISize;

	RenderNumber(LeftNum, vtmp);
	vtmp.x += HPUISize;
	RenderNumber(CenterLeftNum, vtmp);

	vtmp.x += HPUISize;
	RenderNumber(CenterRightNum, vtmp);
	vtmp.x += HPUISize;
	RenderNumber(RightNum, vtmp);
}





void MyHPUI::RenderNumber(int num, D3DXVECTOR3 vPos)
{
	if (num >= 10) {
		MessageBoxA(g_pMain->m_hWnd, "RenderNumberError", "", MB_OK);
		return;
	}
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	

	D3DXMATRIX World;

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, vPos.x, vPos.y, vPos.z);

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
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pNumTexture[num]);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}



void MyHPUI::RenderSrush(D3DXVECTOR3 vPos)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);


	D3DXMATRIX World;

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, vPos.x, vPos.y, vPos.z);

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
	g_pMain->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pSrushTexture);

	//トポロジーをセット
	g_pMain->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	g_pMain->m_pDeviceContext->Draw(4, 0);
}

void MyHPUI::RenderPos(D3DXVECTOR3 vPos, int num, float deltaTime)
{
	m_vPos = vPos;
	m_vUILeftPos = vPos;// +HPUISIZE * 2;
	m_vUILeftPos.x += HPUISize * 2;

	Render(deltaTime);
	RenderStackCubeNum(num);
}