#include "Poly.h"

MyPoly::Poly::Poly() : InitFlg(false),m_pVertexBuffer(NULL) {

}
void MyPoly::Poly::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext) {
	
	m_pDevice = inDevice;
	m_pDeviceContext = inDeviceContext;

	//InitConstantBuffer();
	/*if (!InitFlg) {
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
	}*/
}

void MyPoly::Poly::Release() {
	//delete[] m_pVertices;
}
HRESULT MyPoly::Poly::CreateVertexBuffer() {

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-0.5f,-0.5f,0.0f),D3DXVECTOR2(0,1),//���_�P
		D3DXVECTOR3(-0.5f,0.5f,0.0f),D3DXVECTOR2(0,0),//���_�Q
		D3DXVECTOR3(0.5f,-0.5f,0.0f),D3DXVECTOR2(1,1),//���_�R
		D3DXVECTOR3(0.5f,0.5f,0.0f),D3DXVECTOR2(1,0),//���_�S
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

HRESULT MyPoly::Poly::CreateTexture()
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
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, (LPCSTR)"Sprite.jpg", NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBox(NULL, "TextureLoadError", "errot", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void MyPoly::Poly::Render( D3DXMATRIX mW) {
	
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,&stride,&offset);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	m_pDeviceContext->Draw(4, 0);
}

void MyPoly::Poly::SetConstantBuffer(D3DXMATRIX WVP)
{
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�@�J�����@�ˉe�s���n��
		D3DXMATRIX m = WVP;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		//�J���[��n��
		D3DXVECTOR4 vColor(1, 0, 0, 1);
		cb.vColor = vColor;
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
}



void MyPoly::Poly::InitConstantBuffer()
{
	D3D11_BUFFER_DESC cb;//������
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU�ɃA�N�Z�X����t���O�ݒ�
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//�g�p�@

	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		MessageBox(NULL, "ConstantBuffer Create Failed", "CreateError", MB_OK);
		return;
	}
}
