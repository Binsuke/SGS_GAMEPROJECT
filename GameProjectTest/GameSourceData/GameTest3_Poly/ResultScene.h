#include "BASE_SCENE.h"
#include "main.h"

#include "VertexShaderUtility.h"
#include "PixelShaderUtility.h"

#include "TimeUI.h"

#include "HPUI.h"

#ifndef RESULTSCENE_H
#define RESULTSCENE_H



struct RESULTUI_SimpleVertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR2 UV;//テクスチャー座標
};

struct RESULTUI_SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};


class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	BaseScene::eScene App();
	void Release();
private:
	void Init();
	void Render();
	void Input();

	void InitVertexBuffer();

	bool m_bEnterFlg;

	BaseScene::eScene ReturnScene;

	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11Buffer* m_pVertexBuffer;

	ID3D11SamplerState* m_pSampler;
	ID3D11ShaderResourceView* m_pTexture;

	D3DXVECTOR3 m_vPos;

	//MyHPUI* m_pHPUI;
	//TimeUI* m_pTimeUI;
};

#endif

