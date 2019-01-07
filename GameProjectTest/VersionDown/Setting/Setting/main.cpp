#include "main.h"
//#include <string>
//グローバル変数
MAIN* g_pMain = NULL;

//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wPram, LPARAM lParam);

//INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
//アプリケーションのエントリー関数 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN;// mainのインスタンスを作成

	if (g_pMain != NULL)//インスタンスの作成に成功しているか
	{
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME))) //ウィンドウの作成　成功していたら中に入る
		{
			if (SUCCEEDED(g_pMain->InitD3D()))//D3D系列の初期化　成功していたらループに入る
			{
				g_pMain->Loop();	//メインループ
			}
		}
		//アプリの終了
		g_pMain->DestroyD3D();
		delete g_pMain;
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);//メインのメッセージプロセスを実行　そして結果を返す
}

//コンストラクタ
MAIN::MAIN()
{
	ZeroMemory(this, sizeof(MAIN));
}


//デストラクタ
MAIN::~MAIN()
{

}

//
//std::wstring StrToWstr(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);//確保する長さの確認
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//
//	std::wstring rstr(buf);
//	delete[] buf;
//	return rstr;
//}


HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	//ウィンドウの定義

	WNDCLASSEX wc;//Windowのもとになる設定用のクラス？
	ZeroMemory(&wc, sizeof(wc));//ゼロ初期化

	wc.cbSize = sizeof(wc); //自分自身のサイズを設定
	wc.style = CS_HREDRAW | CS_VREDRAW;  //スタイル設定　どういう設定かはわかっていないがHREDRAWとVREDRAWというフラグを合成して代入している

	wc.lpfnWndProc = WndProc;//よくはわからないけど　コールバック関数のWndProc関数をここで代入している？

	wc.hInstance = hInstance;//インスタンスを渡している

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//IDI_APPLICATIONというウィンドウ標準のアイコンをロードして設定していると思う

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//こちらもウィンドウ標準のカーソルデータをロードして代入していると思う

	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);  //こちらもバックグラウンドをどういう風に塗りつぶすかの設定？

	wc.lpszClassName = (LPCSTR)WindowName;//ウィンドウの名前をクラス名に設定

	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//アイコンをまた設定？

	RegisterClassEx(&wc);//今まで設定していたものを登録している？

	//ウィンドウの作成
	m_hWnd = CreateWindow((LPCSTR)WindowName, (LPCSTR)WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);//ウィンドウ作成

	
	if (!m_hWnd)//ウィンドウが作成されているか
	{
		return E_FAIL;
	}

	ShowWindow(m_hWnd, SW_SHOW);//ウィンドウを表示
	UpdateWindow(m_hWnd);//ウィンドウのアップデート

	return S_OK;
}

//LRESULT MAIN::MsgProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
//ウィンドウプロシージャー
LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://エスケープキーが押されていたら　終了をするコールバックめーっせーじを送りプログラムを終了する
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY://ウィンドウの破棄メッセージが届いたら　終了をするコールバックメッセージを送る
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);//そのほかはデフォルトのウィンドウのプロセスを行う
}

void MAIN::Loop()
{
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)//終了メッセージが届いていなければ　ループ
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //メッセージをもとに処理を選択
		{
			TranslateMessage(&msg);			//待ち行列内のウィンドウの優先順位の高いプロセスを処理
			DispatchMessage(&msg);
		}
		else {
			//アプリケーションを処理する時間がきたらアプリケーションの処理

			App();
		}
	}
	//アプリケーションの終了

}

//void MAIN::App()
//アプリケーション処理。アプリのメイン関数

void MAIN::App()
{
	Render();//アプリケーションの中身は現状レンダーのみ
}


//HRESULT MAIN::InitD3D()
//Direct3D初期化

HRESULT MAIN::InitD3D()
{
	//デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;  //スワップチェーンを作る際に設定をする構造体

	ZeroMemory(&sd, sizeof(sd));;//まずはメモリをクリア

	sd.BufferCount = 1; //バッファーがいくつあるか
	sd.BufferDesc.Width = WINDOW_WIDTH;//スワップチェーンの幅　基本的にウィンドウbのサイズと同じでいい
	sd.BufferDesc.Height = WINDOW_HEIGHT;//こちらは高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//フォーマットの設定
	sd.BufferDesc.RefreshRate.Numerator = 60;//リフレッシュレートの設定　今回は６０
	sd.BufferDesc.RefreshRate.Denominator = 1;//Denominatorとは分母という意味らしい　なので　60/1リフレッシュレートということになるのか？

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//Usageとは使用法という意味なので　これをどのように使用するかについて設定していると思う
	sd.OutputWindow - m_hWnd;//どのウィンドウを表示するのか
	sd.SampleDesc.Count = 1;//Descとは説明、サンプルの説明がいくつある課だと思う
	sd.SampleDesc.Quality = 0;//これは解像度の細かさとかに関係するものかな？

	sd.Windowed = TRUE; //ウィンドウモードかどうか

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;//FEATUREとは特徴
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if ( FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel,&m_pDeviceContext)))
	{
		return FALSE;
	}

	//各種テクスチャーとそれに付随する各種ビューを作成

	//バックバッファーとテクスチャーを取得 (すでにあるのでっ作成ではない

	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);//スワップチェーンからテクスチャーを取得
	
	//そのテクスチャーに対してレンダーターゲットビューを作成

	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL,&m_pBackBuffer_TexRTV); //先ほど取得したテクスチャをもとにレンダーターゲットビューを作成

	SAFE_RELEASE(pBackBuffer_Tex);//不要になったため破棄？

	//デプスステンシルビュー用のテクスチャーを作成

	D3D11_TEXTURE2D_DESC descDepth; //テクスチャ２Dの説明

	descDepth.Width = WINDOW_WIDTH;//深度テクスチャもウィンドウを同じ大きさにするほうがよい
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;		//Mipとは？
	descDepth.ArraySize = 1;		//配列のサイズ
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;//いくつあるのか
	descDepth.SampleDesc.Quality = 0;//クオリティはどの程度にするのか
	descDepth.Usage = D3D11_USAGE_DEFAULT;//使用法

	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;//どのようなものなのか

	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);//説明をもとにデップステクスチャーを作成

	//そのテクスチャーに対してデプスステンシルビューを作成

	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインドする
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV);

	//ビューポートの設定
	D3D11_VIEWPORT vp; //こちらも設定に関して説明のようなものかな
	vp.Width = WINDOW_WIDTH;//ビューポートも基本的にウィンドウのサイズと同じでいい？
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f; //ビューを作る際に、視野角をもとに描画範囲を決める際に　深度の一番小さいところと大きいところの幅を決める
						//基本的には　この深度などをもとに、視野角とを計算して描画するサイズを変える
						//この補間計算によってパースがかかる
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp); //ビューポートがいくつか　そして先ほどの設定した説明を渡して設定

	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;//ラスタライズに関する説明　この辺は結構毎回同じパターンのような気がする
								//何かを設定する場合は　まずは説明書を作成しそれをもとに設定する

	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE; //カルに関しては何か見た気がするが覚えてない
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;

	m_pDevice->CreateRasterizerState(&rdc, &pIr);//先ほど設定した説明書をもとに　pIrに作成したものをとりあえずいれる
	
	m_pDeviceContext->RSSetState(pIr);//先ほど説明書をもとに作ったラスタライザーを実際に設定してあげている

	//hlslファイル読み込み　ブロブ作成
	ID3DBlob* pCompileShader = NULL;//これも先ほどのD3D11系列の説明書で作っていたパターンと同じようなものだと思う

	//バーテックスシェーダー作成
	if (FAILED(MakeShader((LPSTR)"Point3D.hlsl", (LPSTR)"VS", (LPSTR)"vs_5_0", (void**)&m_pVertexShader, &pCompileShader)))
	{
		return E_FAIL;
	}

	//頂点インプットレイアウトを作成
	//これをもとに頂点のレイアウトをシェーダー側に知らせているはず
	//頂点のレイアウトが変わればここも変わる
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);//頂点レイアウトはその都度変わる可能性があるので　
															//全体のサイズを一つのサイズで割ることで
															//エレメント数を求めている

	//頂点インプットレイアウトを作成
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompileShader->GetBufferPointer(), pCompileShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return FALSE;
	}

	SAFE_RELEASE(pCompileShader);

	//ピクセルシェーダー作成
	if (FAILED(MakeShader((LPSTR)"Point3D.hlsl", (LPSTR)"PS", (LPSTR)"ps_5_0", (void**)&m_pPixelShader, &pCompileShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompileShader);

	//コンスタントバッファーを作成　変換行列渡しよう

	D3D11_BUFFER_DESC cb;//説明用のバッファ
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//どういった属性なのか
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);//バッファーのサイズ
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	
	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer))) //説明用のバッファをもとにコンスタントバッファーの設定
	{
		return E_FAIL;
	}
	
	//点としてのバーテックスバッファー作成
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}

	return S_OK;
}

