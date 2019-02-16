#pragma once
#pragma once
#ifndef MAIN_H
#define MAIN_H
//ヘッダーファイルのインクルード
#include <Windows.h>	
//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>
//シェーダーファイルの読み込み関連が入ってたはず
#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"

#include "MyModel.h"
#include "Ground.h"
#include "Camera.h"
#include "MoveUI.h"

#include "FPS.h"
//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//警告非表示
#pragma warning(disable:4305)
//#pragma warning(disable:4005)

//定数定義
#ifndef WINDOW_SIZE
#define WINDOW_SIZE
#define WINDOW_WIDTH	640 //window 幅
#define WINDOW_HEIGHT	480 //window高さ
#define APP_NAME L"テクスチャーを張る"
#endif
//マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //渡されたオブジェクトのリリース関数を呼び出してそのあとにNULLを入れている

													//マクロで行っているけど、テンプレートで行うほうがいいとは思う
#endif SAFE_RELEASE

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#endif
//class MAIN
//MAIN クラス

class MAIN
{
public:
	MAIN();
	~MAIN();
	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT InitD3D();
	HRESULT InitPolygon();
	HRESULT InitShader();

	void Loop();
	void App();
	void Render();
	void DestroyD3D();

	HWND m_hWnd;				//ウィンドウハンドル　ウィンドウを扱うためのもの
	ID3D11Device* m_pDevice;	//D3D11デバイスの本体　これにアクセスしていろいろな操作を行う
	ID3D11DeviceContext* m_pDeviceContext;	//上のデバイスと似たような感じのもの　こちらもシェーダーなどの情報を扱う際に使っていたはず
	IDXGISwapChain* m_pSwapChain;			//スワップチェーン　デュアルバッファによって画面のちらつきを減らすために作られる二つのバッファを扱うためのものかな
											//描画の最後にスワップしてあげることによってダブルバッファを実装する
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;	//スワップチェーンで使うためのバックバッファのレンダーターゲットを決めるためのビュー
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;	//スワップチェーンで使うためのバックバッファーの深度バッファー　Zテストなどに用いられるはず

	ID3D11Texture2D* m_pBackBuffer_DSTex;		//バックバッファーの深度バッファーに使うためのテクスチャ

	ID3D11BlendState* m_pBlendState;

	//モデルの種類ごとに必要、というよりモデルに使うシェーダーごとにレイアウトなどが変わるので
	//その時に必要になるはず
	

	Camera* m_pCamera;
	FPS* m_pFPS;
	void InitModel();//この辺はステージなんかを作った場合はシーンごとに分けてシーンにモデルを持たせて、初期化するようにするのがいいかな
	void ReleaseModel();

	enum eMoveVec {
		None = 0,
		Forward = 1,
		Backward = 2,
		Right = 3,
		Left = 4,
	};
	eMoveVec m_eMoveVec;
	void MoveUpdate(eMoveVec Vec);

private:
	
	MyModel* m_pTestModel;
	MyModel* m_pEnemyModel[3];
	MyGround* m_pGround;
	
	MoveUI* m_pMoveUI;
	float view;
	
};

#endif