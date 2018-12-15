#pragma once

#ifndef __SHADER_UTIL_H__
#endif __SHADER_UTIL_H__

#include <d3dcompiler.h>

//   compile the shader form the file 

// param[in]  szFileName		ShaderFileName
// param[in]  szEntryPoint      EntryPoint
// param[in]  szShaderModel     ShaderModel
// param[out] ppBlobOut			It is the address of ID3DBlob that stores the compiled code.

HRESULT CompileShaderFromFile(
	WCHAR*			szFileName,
	LPCSTR			szEntryPoint,
	LPCSTR			szShaderModel,
	ID3DBlob**		ppBlobOut
);



