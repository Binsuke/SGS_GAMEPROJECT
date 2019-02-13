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
		D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(1.0f,0.0f,-1.0f),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR2(1,0),//���_�S
	};
	D3D11_BUFFER_DESC bd; //������
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

void GroundPanel::Render() {

	//�o�[�e�b�N�X�o�b�t�@�[�Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	

	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//�e�N�X�`���̃T���v���[��o�^
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//�e�N�X�`�����V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�|���S����`��
	m_pDeviceContext->Draw(4, 0);
}
