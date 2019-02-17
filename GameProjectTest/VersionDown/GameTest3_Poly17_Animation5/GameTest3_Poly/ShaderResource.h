#pragma once
#include "main.h"
#include <string>

//無駄に複雑にしすぎている気がするので　一旦凍結

#ifndef STR_TO_WSTR
#define STR_TO_WSTR
std::wstring StrToWstr(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);//確保する長さの確認
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);

	std::wstring rstr(buf);
	delete[] buf;
	return rstr;
}
#endif

class ShaderResource {
public:
	ShaderResource() : m_Num(0), Prev(NULL), ThisType(eNone), m_pPixelShader(NULL), m_pVertexShader(NULL), Next(NULL) {};
	enum eShaderType{
		eNone,
		ePixelShader,
		eVertexShader,
	};
	HRESULT CreateShaderFromFile(ID3D11Device* inDevice,std::string filename, std::string shadername, std::string version, int *num, eShaderType type, D3D11_INPUT_ELEMENT_DESC layout[],UINT numelements);

private:
	
	//template <typename SHADER_RESOURCE>;
	ShaderResource* Prev;
	eShaderType ThisType;
	int m_Num;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout* m_pVertexLayout;
	//SHADER_RESOURCE * m_pResource;
	ShaderResource* Next;
};