//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#include "CD3DXMESH.h"

//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//定数定義
#define WINDOW_WIDTH 640 //ウィンドウ幅
#define WINDOW_HEIGHT 480 //ウィンドウ高さ
#define APP_NAME L"坂を登る（滑る）"

#define RAY_DISTANCE 1
#define SPEED 0.04f

//
//
//
class MAIN
{
public:
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCWSTR);
	HRESULT InitD3D();
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
	void Loop();
	void App();
	void Render();
	void DestroyD3D();
	bool RayIntersect(CD3DXMESH* pMeshA ,D3DXVECTOR3&,CD3DXMESH* pMeshB,float* pfDistance,D3DXVECTOR3*);
	HRESULT FindVerticesOnPoly(LPD3DXMESH,DWORD,D3DXVECTOR3*);
	D3DXVECTOR3 Slip(D3DXVECTOR3 L,D3DXVECTOR3 N);

	HWND m_hWnd;									//ウィンドウハンドル
	ID3D11Device* m_pDevice;						//デバイス本体
	ID3D11DeviceContext *m_pDeviceContext;			//デバイスコンテキスト本体
	IDXGISwapChain* m_pSwapChain;					//スワップチェイン
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;	//レンダーターゲットビュー（バックバッファー
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;	//デプスステンシルビュー(バックバッファー
	ID3D11Texture2D* m_pBackBuffer_DSTex;			//バックバッファー用のテクスチャ
	
	CD3DXMESH* m_pRobotMesh;						//RobotMesh
	CD3DXMESH* m_pSlopeMesh;						//SlopeMesh
};
