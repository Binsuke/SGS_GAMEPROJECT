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
//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//警告非表示
#pragma warning(disable:4305)
#pragma warning(disable:4005)

//定数定義
#define WINDOW_WIDTH	640 //window 幅
#define WINDOW_HEIGHT	480 //window高さ
#define APP_NAME L"テクスチャーを張る"

//マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //渡されたオブジェクトのリリース関数を呼び出してそのあとにNULLを入れている
													//マクロで行っているけど、テンプレートで行うほうがいいとは思う
#endif SAFE_RELEASE
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

	//モデルの種類ごとに必要、というよりモデルに使うシェーダーごとにレイアウトなどが変わるので
	//その時に必要になるはず
	//ID3D11InputLayout* m_pVertexLayout;			//バーテックスのレイアウトを作る際に使う、このレイアウトをもとに頂点の形を決める
	//ID3D11VertexShader* m_pVertexShader;		//Vertexシェーダーの本体
	//ID3D11PixelShader* m_pPixelShader;			//Pixelシェーダーの本体
	//ID3D11Buffer* m_pConstantBuffer;			//コンスタントバッファーを作るためのバッファ

private:
	MyPoly::Poly* m_pTestPoly;
	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	MyConstantBuffer m_ConstantBuffer;
};

#endif