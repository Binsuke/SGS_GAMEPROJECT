#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include "GroundPanel.h"


//この関数はのちに　マップを作るときに
//マップ情報をもとに　パネル枚数とかをいじれるようにできたらいいね
#ifndef MY_GROUND_H
#define MY_GROUND_H
class MyGround {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);

	//ポジションイニシャライズ
	void PosInit();

	//レンダー関数
	void Render(D3DXMATRIX view, D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation, D3DXMATRIX scale);
	//キューブ描画用のクラス
	//MyPoly::Poly m_Cube;
	GroundPanel m_Ground;
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー
	MyConstantBuffer m_ConstantBuffer;

	enum {
		Modelx = 10,
		Modelz = 10,
	};

	//float GetGroundRight() { return Modelx * GroundPanel::PanelSize; }
private:
	//デバイス
	ID3D11Device* m_pDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_pDeviceContext;



	D3DXMATRIX m_World;
	
	//ローカル座標のポス保持変数
	D3DXMATRIX ModelPos[Modelx][Modelz];
};

#endif  MY_GROUND_H
