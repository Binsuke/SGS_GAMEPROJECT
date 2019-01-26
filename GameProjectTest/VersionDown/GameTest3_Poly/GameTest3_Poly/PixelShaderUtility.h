#pragma once

#ifndef PIXEL_SHADER_UTILITY_H
#define PIXEL_SHADER_UTILITY_H
#include "ShaderUtility.h"
//#include <vector>



//マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //渡されたオブジェクトのリリース関数を呼び出してそのあとにNULLを入れている
#endif

//クラス化してリストにしたほうがよさそう
//struct PIXEL_SHADER_RESOURCE : BASE_SHADER_RESOURCE {
//	PIXEL_SHADER_RESOURCE* pPrev;
//	ID3D11PixelShader* pPixelShader;
//	PIXEL_SHADER_RESOURCE* pNext;
//};

class PixelShaderUtil{
public:
	void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	HRESULT CreateShaderFromFile(std::string filename, std::string shadername, std::string version, int* num);

	//指定された識別子のシェーダーをセットする
	void SetShader(int Num);
	void Release();
private:
	//std::vector<PIXEL_SHADER_RESOURCE> m_vResource;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
};

#endif