#include "PixelShaderUtility.h"

#include "ConstantBuffer.h"
#include "Poly.h"
#include "main.h"
#ifndef DANGER_UI_H
#define DANGER_UI_H
class DangerUI {
public:
	void Init();
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 PosCenter,float Size);
	void RenderKing(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 PosCenter, float Size);
private:
	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	MyConstantBuffer m_ConstantBuffer;
	MyPoly::Poly DangerCube;

	MyPoly::Poly KingCube;
	float Rot;
};

#endif