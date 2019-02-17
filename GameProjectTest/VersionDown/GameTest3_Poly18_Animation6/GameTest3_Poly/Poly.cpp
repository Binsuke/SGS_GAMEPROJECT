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
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};

	D3D11_BUFFER_DESC bd; //������
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
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(PolyHalfSize,-PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,-PolyHalfSize),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(PolyHalfSize,PolyHalfSize,PolyHalfSize),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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
	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc; //�T���v���[�p�̐�����
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;//�ǂ������ݒ肾�낤�H
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; //���b�v����@�J��Ԃ����Ǝv��
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; //U,V,W �ǂ̕��������b�v����

	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);//����������T���v���[���쐬

	//�e�N�X�`���[�쐬
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, filename.c_str(), NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBox(NULL, "TextureLoadError", "errot", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void MyPoly::Poly::Render() {

	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	//UINT stride = sizeof(SimpleVertex);
	//UINT offset = 0;
	//

	//m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	////�e�N�X�`���̃T���v���[��o�^
	//m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	////�e�N�X�`�����V�F�[�_�[�ɓn��
	//m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	////�g�|���W�[���Z�b�g
	//m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	////�|���S����`��
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
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferFront, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderBack()
{
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferBack, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderTop()
{
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferTop, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderDown()
{
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferDown, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::RenderRight()
{
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferRight, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}


void MyPoly::Poly::RenderLeft()
{
	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;


	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferLeft, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}

