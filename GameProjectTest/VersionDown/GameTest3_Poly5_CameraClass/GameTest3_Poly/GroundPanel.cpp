#include "GroundPanel.h"

void GroundPanel::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext)
{
	m_pDevice = indevice;
	m_pDeviceContext = indevicecontext;
}

void GroundPanel::Release() {
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
}

HRESULT GroundPanel::CreateVertexBuffer() {

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}




HRESULT GroundPanel::CreateTexture(std::string filename)
{
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc; //サンプラー用の説明書
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;//どういう設定だろう？
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; //ラップする　繰り返すだと思う
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; //U,V,W どの方向もラップする

	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);//説明書からサンプラーを作成

	//テクスチャー作成
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, filename.c_str(), NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBox(NULL, "TextureLoadError", "errot", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void GroundPanel::Render() {

	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	

	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}
