//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>

class Camera {
public:
	Camera();
	Camera(D3DXVECTOR3 Pos);
	Camera(float x, float y, float z);
	~Camera();

	D3DXMATRIX m_Transform;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;

	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vForward;

	D3DXVECTOR3 m_vEyePt;
	D3DXVECTOR3 m_vLookat;

	D3DXMATRIX m_PoseMat;
	D3DXMATRIX m_DeltaMat;

	//Entity TargetObject = null
};