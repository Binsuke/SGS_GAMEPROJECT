#include "main.h"

#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"

#ifndef ALIGN16
#define ALIGN16 _declspec(align(16))
#endif


#ifndef CAMERA_UI_H
#define CAMERA_UI_H

struct CAMERAUI_SimpleVertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR2 UV;//テクスチャー座標
};

struct CAMERAUI_SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};

class CameraUI {
public:
	HRESULT Init();
	void Render();
private:

	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11SamplerState* m_pSampler;

	ID3D11ShaderResourceView* m_pTexture;

	D3DXVECTOR3 m_vPos;

	static float CameraUI_SIZE;
};

#endif
