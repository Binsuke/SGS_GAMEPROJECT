#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include <list>


#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#endif

#ifndef MYMODEL_DEF
#define MYMODEL_DEF

//memo
//PosInitを使って最初表示を行っていたが
//モデルクラスは変更を行い、LVを渡すことでモデルを作成
//PosInitは消去を行いInitLvでレベルと初期位置を渡し生成する
//
class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//ポジションイニシャライズ
	MyModel();
	~MyModel();
	//レンダー関数
	//void Init();
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	


	D3DXVECTOR3 GetCenter() { return m_vCenter; }
	void SetPos(D3DXVECTOR3 vPos);
	void SetPos(float x, float y, float z);

	D3DXVECTOR3 GetColisionPos(){ return m_vPos + m_vAnimePos; }

	
	void Move(float deltaTime, const D3DXVECTOR3& cvForwardVec);
	bool MoveA(float deltaTime, const D3DXVECTOR3& cvForwardVec);


	void InitLv(int Lv);
	void LVUp();
	void LVDown();

	D3DXVECTOR3 GetCameraMargin();

	D3DXVECTOR3 GetCameraTarget();

	float GetSize();

	int GetLV() { return m_iLV; }

	bool AnimationLocalRight(float deltaTime);
	bool AnimationLocalLeft(float deltaTime);

	bool AnimationLocalForward(float deltaTime);
	bool AnimationLocalBackward(float deltaTime);


	bool AnimationLocalRightA(float deltaTime);
	bool AnimationLocalLeftA(float deltaTime);

	bool AnimationLocalForwardA(float deltaTime);
	bool AnimationLocalBackwardA(float deltaTime);
	//void KeyInput(float deltaTime);


	//ここをポインターにしたときに問題がでるんじゃないか？と思ったのだけれど
	//コピーコンストラクターが呼び出されたときにどうする？と思ったが
	//そもそもPOSのようにモデル毎に必要なものではないため
	//コピーコンストラクターが呼ばれればもとになったデータのポインターがコピーされるはず
	//と思ったがこれはポインターにはできないな
	//コピーが行われるのでもとになったデータの情報のポインターもコピー
	//されるわけなんだけれど　コピー先のデータが消えた場合
	//元のデータになっていたm_Cubeのデータが消えてしまう
	//なのでもとに戻す；コピーを行わないの前提なら問題はないけれど
	//何があるかわからないのでポインターにするのはやめておこう

	//キューブ描画用のクラス
	MyPoly::Poly m_Cube;
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー
	MyConstantBuffer m_ConstantBuffer;


private:

	void MoveLocalForward(float deltaTime);
	void MoveLocalBackward(float deltaTime);
	void MoveLocalRight(float deltaTime);
	void MoveLocalLeft(float deltaTime);


	void AnimationMargineSet();
	void AnimationMargineY(float deltaTime);
	void SetLV1();

	void InitAdjustment();

	void UpdateCenter();

	void ModelSizeUp();
	void ModelSizeDown();

	
	D3DXVECTOR3 m_vAnimePos;
	D3DXMATRIX m_mAnimeRot;

	float m_fAnimationRotX;
	float m_fAnimationRotZ;
	float m_fAnimationMargineY;

	float m_fAnimTime;//second
	float m_fAnimTimeDelay;
	bool m_bAnimeFlg;
	float m_fAnimeWaitTime;

	bool m_bRenderflg;

	//D3DXMATRIX AnimationRotz;

	D3DXVECTOR3 m_vAnimationPrevPos;

	//D3DXMATRIX m_mAnimationRotX;
	//D3DXMATRIX m_mAnimationRotY;
	//デバイス
	ID3D11Device* m_pDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_pDeviceContext;

	D3DXVECTOR3 m_vForward;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vRight;

	D3DXVECTOR3 m_vLocalForward;
	D3DXVECTOR3 m_vLocalUp;
	D3DXVECTOR3 m_vLocalRight;

	int m_iLV;
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

	
	D3DXVECTOR3 m_vCenter;
	D3DXVECTOR3 m_vPos;
	//ローカル座標のポス保持変数
	std::list<D3DXMATRIX> m_lmModelMat;
};
#endif