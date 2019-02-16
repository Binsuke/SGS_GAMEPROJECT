#include "ShaderResource.h"

//複雑になりすぎてる気がするので　いったん凍結

HRESULT ShaderResource::CreateShaderFromFile(ID3D11Device* inDevice, std::string filename, std::string shadername, std::string version, int *num, eShaderType type, D3D11_INPUT_ELEMENT_DESC layout[], UINT numelements)
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	ThisType = type;
	/*std::wstring wFileName, wVersion, wShaderName;
	wFileName = StrToWstr(filename);
	wVersion = StrToWstr(version);
	wShaderName = StrToWstr(shadername);
	*/
	switch (ThisType) {
	case ePixelShader:
		if (FAILED(D3DX11CompileFromFile(filename.c_str(), NULL, NULL, shadername.c_str(), version.c_str(), 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
		{
			MessageBox(0, "hlsl読み込み失敗", NULL, MB_OK);
			return E_FAIL;
		}
		SAFE_RELEASE(pErrors);
		if (FAILED(inDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
		{
			SAFE_RELEASE(pCompiledShader);
			MessageBox(0, "ピクセルシェーダー作成失敗", NULL, MB_OK);
			return E_FAIL;
		}
		SAFE_RELEASE(pCompiledShader);
		m_Num++;
		*num = m_Num;
		ThisType = type;
		break;
	case eVertexShader:
		if (numelements != 0) {
			if (FAILED(D3DX11CompileFromFile(filename.c_str(), NULL, NULL, shadername.c_str(), version.c_str(), 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
			{
				MessageBox(0, (LPCSTR)"hlsl読み込み失敗", NULL, MB_OK);
				return E_FAIL;
			}
			SAFE_RELEASE(pErrors);

			if (FAILED(inDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
			{
				SAFE_RELEASE(pCompiledShader);
				MessageBox(0, "バーテックスシェーダー作成失敗", NULL, MB_OK);
				return E_FAIL;
			}
			if (FAILED(inDevice->CreateInputLayout(layout, numelements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
			{
				return FALSE;
			}
			m_Num++;
			*num = m_Num;
			ThisType = type;
		}

			break;
	}
	return S_OK;
}
