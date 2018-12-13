
//Include
#include "ShaderUtil.h"

//Compile the shader from the file

HRESULT CompileShaderFromFile(
	WCHAR*		szFileName,
	LPCSTR		szEntryPoint,
	LPCSTR		szShaderModel,
	ID3DBlob**	ppBlobOut
)
{
	//return code Initialize

	HRESULT hr = S_OK;

	//Compile Flag

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
		dwShaderFlags |= D3DCOMPIKE_DEBUG;
#endif //defined(DEBUG) || defined(_DEBUG

#if defined(NDEBUG)  || defined(_NDEBUG)
		dwShaderFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif //defined(NDEBUG) || defined(_NDEBUG)

		ID3DBlob* pErrorBlob = NULL;

		//Compile the shader from the file

		hr = D3DCompileFromFile(
			szFileName,
			NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			szEntryPoint,
			szShaderModel,
			dwShaderFlags,
			0,
			ppBlobOut,
			&pErrorBlob
		);

		//error check

		if (FAILED(hr))
		{
			//error Message output
			if (pErrorBlob != NULL)
			{
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			}
		}

		// ReleaceProcess

		if (pErrorBlob)
		{
			pErrorBlob->Release();
			pErrorBlob = NULL;
		}

		//return code
		return hr;
}