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

class Camera {
public:

	//func
	Camera();
	Camera(D3DXVECTOR3 Pos);
	Camera(float x, float y, float z);
	~Camera();

	void MoveForward(float delta);
	void MoveBackward(float delta);
	void MoveRight(float delta);
	void MoveLeft(float delta);
	void MoveUp(float delta);
	void MoveDown(float delta);


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

private:
	//data
	D3DXMATRIX m_mTransform;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;

	float m_fTransDir;
	float m_fRotSize;

	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vForward;

	D3DXVECTOR3 m_vEyePt;
	D3DXVECTOR3 m_vLookat;

	D3DXMATRIX m_mPoseMat;
	D3DXMATRIX m_mDeltaMat;

	//Entity TargetObject = null
};