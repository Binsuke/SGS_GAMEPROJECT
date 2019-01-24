#include "PixelShaderUtility.h"

void PixelShaderUtil::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext)
{
	m_pDevice = indevice;
	m_pDeviceContext = indevicecontext;
}

HRESULT PixelShaderUtil::CreateShaderFromFile(std::string filename, std::string shadername, std::string version, int *num) 
{
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(filename.c_str(), NULL, NULL, shadername.c_str(), version.c_str(), 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, "hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "ピクセルシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	return S_OK;
}

void PixelShaderUtil::SetShader(int num)
{
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}