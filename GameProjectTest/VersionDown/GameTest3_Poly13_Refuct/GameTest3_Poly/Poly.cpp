#include "Poly.h"

float MyPoly::Poly::PolySize = 0.1f;

float MyPoly::Poly::PolyHalfSize = MyPoly::Poly::PolySize / 2.0f;


MyPoly::Poly::Poly() : InitFlg(false){

}

MyPoly::Poly::~Poly() {
	//SAFE_RELEASE(m_pVertexBuffer);

	SAFE_RELEASE(m_pVertexBufferTop);
	SAFE_RELEASE(m_pVertexBufferDown);
	SAFE_RELEASE(m_pVertexBufferLeft);
	SAFE_RELEASE(m_pVertexBufferRight);
	SAFE_RELEASE(m_pVertexBufferFront);
	SAFE_RELEASE(m_pVertexBufferBack);

	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
}
void MyPoly::Poly::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext) {

	m_pDevice = inDevice;
	m_pDeviceContext = inDeviceContext;
	
}
//
//void MyPoly::Poly::Release() {
//	//delete[] m_pVertices;
//	/*SAFE_RELEASE(m_pVertexBuffer);
//
//	SAFE_RELEASE(m_pVertexBufferTop);
//	SAFE_RELEASE(m_pVertexBufferDown);
//	SAFE_RELEASE(m_pVertexBufferLeft);
//	SAFE_RELEASE(m_pVertexBufferRight);
//	SAFE_RELEASE(m_pVertexBufferFront);
//	SAFE_RELEASE(m_pVertexBufferBack);
//
//	SAFE_RELEASE(m_pSampleLinear);
//	SAFE_RELEASE(m_pTexture);*/
//
//}
HRESULT MyPoly::Poly::CreateVertexBuffer() {

	CreateVBTop();
	CreateVBDown();
	CreateVBLeft();
	CreateVBRight();
	CreateVBFront();
	CreateVBBack();
	return S_OK;
}

HRESULT MyPoly::Poly::CreateVBFront() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};

	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferFront)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyPoly::Poly::CreateVBBack() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferBack)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyPoly::Poly::CreateVBLeft() {
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferLeft)))
	{
		return E_FAIL;
	}
	return S_OK;
}



HRESULT MyPoly::Poly::CreateVBRight() 
{
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferRight)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MyPoly::Poly::CreateVBTop() 
{

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferTop)))
	{
		return E_FAIL;
	}
	return S_OK;
}


HRESULT MyPoly::Poly::CreateVBDown()
{

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//頂点１
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//頂点２
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//頂点３
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//頂点４
	};
	D3D11_BUFFER_DESC bd; //説明書
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferDown)))
	{
		return E_FAIL;
	}
	return S_OK;
}




HRESULT MyPoly::Poly::CreateTexture(std::string filename)
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

void MyPoly::Poly::Render() {

	//バーテックスバッファーセット
	//UINT stride = sizeof(SimpleVertex);
	//UINT offset = 0;
	//

	//m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	////テクスチャのサンプラーを登録
	//m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	////テクスチャをシェーダーに渡す
	//m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	////トポロジーをセット
	//m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	////板ポリゴンを描画
	//m_pDeviceContext->Draw(4, 0);

	RenderFront();
	RenderBack();
	RenderLeft();
	RenderRight();
	RenderTop();
	RenderDown();

}

void MyPoly::Poly::RenderFront()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferFront, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderBack()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferBack, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderTop()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferTop, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderDown()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferDown, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderRight()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferRight, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}


void MyPoly::Poly::RenderLeft()
{
	//バーテックスバッファーセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferLeft, &stride, &offset);

	//テクスチャのサンプラーを登録
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//テクスチャをシェーダーに渡す
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//線にするために変更

	//板ポリゴンを描画
	m_pDeviceContext->Draw(4, 0);
}

