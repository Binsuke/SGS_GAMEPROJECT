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
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //渡されたオブジェクトのリリース関数を呼び出してそのあとにNULLを入れている
													//マクロで行っているけど、テンプレートで行うほうがいいとは思う


//頂点の構造体

//こっちはVS_OUTPUTと一致　　Pos はPos vTex　は Tex
//struct SimpleVertex
//{
//	D3DXVECTOR3 Pos; //位置
//	D3DXVECTOR2 vTex;//UV
//	//SimpleVertex() :Pos(0, 0, 0) {};//コンストラクタ初期化式で初期化
//};



//Simpleシェーダー用のコンスタントバッファーをアプリ側定義　　これをのちにシェーダー側とやり取りする箱として使う

//これがcbuffer　globalと一致すべきもの　colorというのとdiffuseが一致
struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;   //world * view * projection の行列を渡す
						//このWVPによってモデルの座標をローカル座標から変換する
						//ワールド座標　ビュー行列　プロジェクション行列を合成したものをモデルの行列にかけ合わせることで
						//行列の計算処理を少なくしている。例えば移動スケール回転という行列があった場合に
						//移動成分　スケールに使う成分　回転に使う成分は　行列内で見事に分かれているため
						//4*4行列においてうまいこと合成したものを一括でかけて計算処理を減らすことができる
						//１つの頂点に対して　移動、スケール、回転を毎回やるよりも
						//まとめてやることによって計算回数を３分の１？にできるはず
						//mWVPにおいてもあらかじめ合成しておくことで計算回数を減らしていたはず
						//頂点の数が膨大になるモデルになればなるほどこういった細かな計算回数を減らすことが実行速度に直結してくるらしい

	D3DXVECTOR4 vColor;

};


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
	/*HRESULT InitModel();
	HRESULT MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);
*/
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
	ID3D11InputLayout* m_pVertexLayout;			//バーテックスのレイアウトを作る際に使う、このレイアウトをもとに頂点の形を決める
	ID3D11VertexShader* m_pVertexShader;		//Vertexシェーダーの本体
	ID3D11PixelShader* m_pPixelShader;			//Pixelシェーダーの本体
	ID3D11Buffer* m_pConstantBuffer;			//コンスタントバッファーを作るためのバッファ

	//モデル毎に必要らしい
	ID3D11Buffer* m_pVertexBuffer;				//バーテックスバッファー

	ID3D11SamplerState* m_pSampleLinear;			//テクスチャーのサンプラー
												//サンプラーとはテクスチャをどのように扱うか、テクスチャの画像よりも外にある端はどのように扱うか
												//例えばミラーや同じ色で塗りつぶすなどの設定をいれておいて　教えるための情報源

	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー本体　　シェーダーに渡すリソース
											//リソースがここに入る
private:
	MyPoly::Poly* m_pTestPoly;
};

#endif