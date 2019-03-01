#include "main.h"

#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"

#ifndef ALIGN16
#define ALIGN16 _declspec(align(16))
#endif


#ifndef TIME_H
#define TIME_H

struct TIMEUI_SimpleVertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR2 UV;//テクスチャー座標
};

struct TIMEUI_SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};

class TimeUI {
public:
	HRESULT Init();
	void RenderTime(int Time);
private:

	void RenderNumber(int num, D3DXVECTOR3 vPos);
	void RenderClock(D3DXVECTOR3 vPos);
	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pConstantBuffer;
	
	ID3D11SamplerState* m_pSampler;
	
	ID3D11ShaderResourceView* m_pNumTexture[10];

	ID3D11ShaderResourceView* m_pClockTexture;

	D3DXVECTOR3 m_vPos;

	static float TIMEUI_SIZE;
};





#endif