//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>

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

	void RotRight(float delta);
	void RotLeft(float delta);

	void SetCamera(D3DXMATRIX* mViewOut,D3DXMATRIX* mProjectionOut);
	

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