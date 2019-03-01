#include "BASE_SCENE.h"
#include "main.h"
#include "VertexShaderUtility.h"
#include "PixelShaderUtility.h"
#ifndef TITLESCENE_H
#define TITLESCENE_H

#ifndef ALIGN16
#define ALIGN16 _declspec(align(16))
#endif
struct UI_SimpleVertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR2 UV;//テクスチャー座標
};

struct UI_SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};


class TitleScene : public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	BaseScene::eScene App();
	void Release();
private:
	void Init();
	void Render();
	void Input();

	void InitVertexBuffer();

	BaseScene::eScene ReturnScene;

	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11Buffer* m_pVertexBuffer;

	ID3D11SamplerState* m_pSampler;
	ID3D11ShaderResourceView* m_pTexture[2];

	D3DXVECTOR3 m_vPos;
	
	enum eStartOrEnd{
		eStart = 0,
		eEnd = 1,
	};

	eStartOrEnd eStartOrEndCheck;
};

#endif
