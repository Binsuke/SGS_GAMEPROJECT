#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"

class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//ポジションイニシャライズ
	void PosInit();

	//レンダー関数
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	//キューブ描画用のクラス
	MyPoly::Poly m_Cube;
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー
	MyConstantBuffer m_ConstantBuffer;
private:
	//デバイス
	ID3D11Device* m_pDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_pDeviceContext;

	

	D3DXMATRIX m_World;
	enum {
		Modelx = 5,
		Modely = 5,
		Modelz = 5,
	};
	//ローカル座標のポス保持変数
	D3DXMATRIX ModelPos[Modelx][Modely][Modelz];
};