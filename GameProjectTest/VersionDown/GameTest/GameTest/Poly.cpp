#include "Poly.h"

MyPoly::Poly::Poly() : InitFlg(false),m_pVertexBuffer(NULL) {

}
void MyPoly::Poly::Init() {
	if (!InitFlg) {
		m_pVertices = new SimpleVertex[4];
		m_pVertices[0].Pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
		m_pVertices[0].vTex = D3DXVECTOR2(0, 1);

		m_pVertices[1].Pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
		m_pVertices[1].vTex = D3DXVECTOR2(0, 0);

		m_pVertices[2].Pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
		m_pVertices[2].vTex = D3DXVECTOR2(1, 1);

		m_pVertices[3].Pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
		m_pVertices[3].vTex = D3DXVECTOR2(1, 0);


		InitFlg = true;
	}
}

void MyPoly::Poly::Release() {
	//delete[] m_pVertices;
}
HRESULT MyPoly::Poly::CreateVertexBuffer(ID3D11Device * inDevice) {

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-0.5f,-0.5f,0.0f),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-0.5f,0.5f,0.0f),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(0.5f,-0.5f,0.0f),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(0.5f,0.5f,0.0f),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(inDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyPoly::Poly::CreateTexture(ID3D11Device* inDevice)
{
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc; //サンプラー用の説明書
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;//どういう設定だろう？
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; //ラップする　繰り返すだと思う
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; //U,V,W どの方向もラップする

	inDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);//説明書からサンプラーを作成

	//テクスチャー作成
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(inDevice, (LPCSTR)"Sprite.jpg", NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBox(NULL, "TextureLoadError", "errot", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void MyPoly::Poly::Render(ID3D11DeviceContext* inDeviceContext, D3DXMATRIX mW) {
	
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	inDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&stride,&offset);
	inDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	inDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	inDeviceContext->Draw(4, 0);
}
