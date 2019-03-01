#include "main.h"
#ifndef HPUI_H
#define HPUI_H

#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"

//#include "Poly.h"
//#include "ConstantBuffer.h"
#ifndef ALIGN16
#define ALIGN16 _declspec(align(16))
#endif
struct HPUI_SimpleVertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR2 UV;//テクスチャー座標
};

struct HPUI_SIMPLESHADER_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX mW;
	ALIGN16 float ViewPortWidth;
	ALIGN16 float ViewPortHeight;
};


class MyHPUI {
public:
	MyHPUI();
	~MyHPUI();
	HRESULT Init();
	void Render(float deltaTime);

	void RenderStackCubeNum(int Num);

	void RenderNextCubeNum(int Num);


private:
	HRESULT InitModel();

	HRESULT CreateVBTop();
	HRESULT CreateVBDown();
	HRESULT CreateVBLeft();
	HRESULT CreateVBRight();
	HRESULT CreateVBFront();
	HRESULT CreateVBBack();

	void RenderTop();
	void RenderDown();
	void RenderLeft();
	void RenderRight();
	void RenderFront();
	void RenderBack();

	void RenderNumber(int num, D3DXVECTOR3 vPos);

	void RenderSrush(D3DXVECTOR3 vPos);


	ID3D11Buffer* m_pVertexBufferTop;				//バーテックスバッファー
	ID3D11Buffer* m_pVertexBufferDown;				//バーテックスバッファー
	ID3D11Buffer* m_pVertexBufferLeft;				//バーテックスバッファー
	ID3D11Buffer* m_pVertexBufferRight;				//バーテックスバッファー
	ID3D11Buffer* m_pVertexBufferFront;				//バーテックスバッファー
	ID3D11Buffer* m_pVertexBufferBack;				//バーテックスバッファー


	static float HPUISize;

	ID3D11Buffer* m_pVertexBuffer;
	D3DXVECTOR3 m_vUILeftPos;

	
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー

	ID3D11Buffer* m_pConstantBuffer;


	ID3D11SamplerState* m_pSampler;
	ID3D11ShaderResourceView* m_pTexture;

	D3DXVECTOR3 m_vPos;

	//ID3D11SamplerState* m_pNumSampler[9];

	ID3D11ShaderResourceView* m_pNumTexture[10];

	ID3D11ShaderResourceView* m_pSrushTexture;
};

#endif