//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>

#include "MyModel.h"

#ifndef WINDOW_SIZE
#define WINDOW_SIZE
#define WINDOW_WIDTH	640 //window 幅
#define WINDOW_HEIGHT	480 //window高さ
#define APP_NAME L"テクスチャーを張る"
#endif

//struct LocalVector {
//	D3DXVECTOR3 slFoward;
//	
//};

class Camera {
public:

	//func
	Camera();
	Camera(D3DXVECTOR3 Pos);
	Camera(float x, float y, float z);
	~Camera();

	void InitCamera();
	void MoveForward(float delta);
	void MoveBackward(float delta);
	void MoveRight(float delta);
	void MoveLeft(float delta);
	void MoveUp(float delta);
	void MoveDown(float delta);


	void UpDateLook(float deltaTime, float size);
	void LookUp(float deltaTime,float size);
	void LookDown(float deltaTime,float size);

	//ローカル軸での回転の解決方法は一つの軸ごとの回転を行うことで行う方法があるがそれだと斜めの移動ができない
	//斜めのカメラの動きを行うためにはキューに入力情報をためて、フレームごとに処理する方法が考えられる
	//その場合、本来デルタ時間を取っているものでこちらは動かしているが
	//キューを３軸分用意、最初にチェックを行いデータが入っているのがx,y,z３つだった場合、全てのデルタ時間を＊３を行い一度の変化量を調整、その後の３回のフレームでｘ－＞ｙ－＞ｚのように変換を行う
	//仮に最初のチェックでキューのデータがｘ、ｙ軸のみの場合はデルタ時間を＊２を行い、同様に２フレームで処理を行う
	//これを行うことで、画面上では斜めの移動などにも対応できると考えられる
	//ただ、とりあえず現状はおいておく
	//左右方向への同時押しについてはif分でどちらも押されていたらスルーをすることで解決する
	void RotRight(float delta);
	void RotLeft(float delta);

	void SetCamera(D3DXMATRIX* mViewOut,D3DXMATRIX* mProjectionOut);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget,D3DXVECTOR3 vCameraPosVec);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec,float TargetMargineY,float TargetMargineX);

	void SetCameraA(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec);

	
	enum eGetLocalType{
		eGetForward = 0,
		eGetBackward =1,
		eGetRight = 2,
		eGetLeft  = 3,
	};

	void GetMoveLocalVec(D3DXVECTOR3* pvLocal,eGetLocalType eLocalType);

	void GetMoveLocalVecA(D3DXVECTOR3* pvLocal, eGetLocalType eLocalType);

	void UpDateWorldVec();

	void GetMoveLocalForwardVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalBackwardVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalRightVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalLeftVec(D3DXVECTOR3* pvLocal);

	//void UpdateLocalVec(float deltaTime);
	
	D3DXVECTOR3 GetWorldForward() {
		return m_vWorldForward;
	}


private:
	//func
	D3DXVECTOR3 SwitchVector(eGetLocalType eType,const D3DXVECTOR3& vForward,const D3DXVECTOR3& vRight);
	D3DXVECTOR3 SwitchVectorA(eGetLocalType eType,D3DXVECTOR3 vForward);

	//data
	D3DXVECTOR3 m_vWorldForward;

	bool m_bLookFlg;
	float m_fLookUp;
	D3DXMATRIX m_mTransform;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;

	float m_fTransDir;

	static D3DXVECTOR3 ms_vLocalRight;
	static D3DXVECTOR3 ms_vLocalLeft;
	static D3DXVECTOR3 ms_vLocalForward;
	static D3DXVECTOR3 ms_vLocalBackward;


	static float ms_fRotSize;

	static float ms_fRotMargine;

	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vForward;

	D3DXVECTOR3 m_vEyePt;
	D3DXVECTOR3 m_vLookat;

	D3DXMATRIX m_mPoseMat;
	D3DXMATRIX m_mDeltaMat;

	D3DXVECTOR3 m_vPrevForward;
	D3DXVECTOR3 m_vPrevBackward;

	D3DXVECTOR3 m_vPrevRight;
	D3DXVECTOR3 m_vPrevLeft;

	bool m_bMoveFlg;
	//Entity TargetObject = null
};