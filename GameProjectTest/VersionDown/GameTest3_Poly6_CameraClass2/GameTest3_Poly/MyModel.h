#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include <list>

#ifndef MYMODEL_DEF
#define MYMODEL_DEF
class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//ポジションイニシャライズ
	MyModel();
	void PosInit();
	void PosInit(int x, int y, int z);
	void PosInit(int NumPoly);

	//レンダー関数
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	
	/*void MoveForward(float delta);
	void MoveBackForward(float delta);
	void MoveLeft(float delta);
	void MoveRight(float delta);*/

	//キューブ描画用のクラス
	MyPoly::Poly m_Cube;
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー
	MyConstantBuffer m_ConstantBuffer;
private:
	void InitAdjustment();
	//デバイス
	ID3D11Device* m_pDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_pDeviceContext;

	D3DXVECTOR3 m_vForward;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vRight;

	float m_fTransDir;
	float m_fRotSize;

	D3DXMATRIX m_mTransform;
	D3DXMATRIX m_mRotation;

	D3DXMATRIX m_mAdjustment;

	

	D3DXMATRIX m_World;
	enum {
		Modelx = 5,
		Modely = 5,
		Modelz = 5,
		ModelSize = 5,
		Halfx = 3,
		Halfy = 3,
		Halfz = 3,
	};

	int m_iModelSizeX;
	int m_iModelSizeY;
	int m_iModelSizeZ;

	int m_iModelHalfSizeX;//基本的に奇数にする、中心を計算するのがめんどくさいだけ
	int m_iModelHalfSizeY;
	int m_iModelHalfSizeZ;

	float m_fPolySize;
	float m_fPolyHalfSize;
	//ローカル座標のポス保持変数
	//D3DXMATRIX m_mModelMat[Modelx][Modely][Modelz];
	//D3DXMATRIX* m_mpModelMat;

	std::list<D3DXMATRIX> m_lmModelMat;
};
#endif