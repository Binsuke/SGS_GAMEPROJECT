#pragma once
#include "VertexShaderUtility.h"

//int VertexShaderUtil::Num = 0;
//
//HRESULT VertexShaderUtil::CreateShaderFromFile(std::string filename, std::string shadername, std::string version, int *num)
//{
//	ID3DBlob *pCompiledShader = NULL;
//	ID3DBlob *pErrors = NULL;
//	if (FAILED(D3DX11CompileFromFile(filename.c_str(), NULL, NULL, shadername.c_str(), version.c_str(), 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
//	{
//		MessageBox(0, "hlsl読み込み失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pErrors);
//	if (FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
//	{
//		SAFE_RELEASE(pCompiledShader);
//		MessageBox(0, "バーテックスシェーダー作成失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pCompiledShader);
//	return S_OK;
//}
VertexShaderUtil::~VertexShaderUtil()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pVertexLayout);
}

void VertexShaderUtil::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext)
{
	m_pDevice = indevice;
	m_pDeviceContext = indevicecontext;
}
HRESULT VertexShaderUtil::CreateShaderFromFileV(std::string filename, std::string shadername, std::string version, int *num, D3D11_INPUT_ELEMENT_DESC layout[], UINT numelements)
{
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(filename.c_str(), NULL, NULL, shadername.c_str(), version.c_str(), 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, "hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "バーテックスシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}

	if (FAILED(m_pDevice->CreateInputLayout(layout, numelements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return FALSE;
	}


	SAFE_RELEASE(pCompiledShader);
	return S_OK;
}

void VertexShaderUtil::SetShader(int num)
{
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
}

void VertexShaderUtil::SetLayout()
{
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
}


//
//void VertexShaderUtil::Release()
//{
//	SAFE_RELEASE(m_pVertexShader);
//	SAFE_RELEASE(m_pVertexLayout);
//}