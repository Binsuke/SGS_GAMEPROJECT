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
		g_pMain->m_Camera = new Camera;
		g_pMain->m_FPS = new FPS;
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
	view = -2;
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
		case VK_UP:
			view += 0.001;
			break;
		case VK_DOWN:
			view -= 0.001;
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
	g_pMain->m_FPS->Run();
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
	sd.OutputWindow = m_hWnd;//どのウィンドウを表示するのか
	sd.SampleDesc.Count = 1;//Descとは説明、サンプルの説明がいくつある課だと思う
	sd.SampleDesc.Quality = 0;//これは解像度の細かさとかに関係するものかな？

	sd.Windowed = TRUE; //ウィンドウモードかどうか

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;//FEATUREとは特徴
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel, &m_pDeviceContext)))
	{
		return FALSE;
	}

	//各種テクスチャーとそれに付随する各種ビューを作成

	//バックバッファーとテクスチャーを取得 (すでにあるのでっ作成ではない

	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);//スワップチェーンからテクスチャーを取得

	//そのテクスチャーに対してレンダーターゲットビューを作成

	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV); //先ほど取得したテクスチャをもとにレンダーターゲットビューを作成

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

	SAFE_RELEASE(pIr);

	//シェーダー初期化を行う　　

	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}

	//ポリゴン作成
	if (FAILED(InitPolygon()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT MAIN::InitShader()
{

	
	//hlslファイル読み込み　ブロブ作成　
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//ブロブからバーテックスシェーダーを作成

	int tmpnum;
	
	m_TestModel.m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	}

	m_Ground.m_VertexShader.Init(m_pDevice, m_pDeviceContext);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //この作業を行うのは　本来はシェーダーの情報をもとにレイアウトを作る必要がでてくるため、シェーダーごとに

	//m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);

	for (int i = 0; i < 3; i++) {
		m_EnemyModel[i].m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	}
	m_TestModel.m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_Ground.m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	


	////頂点インプットレイアウトを定義
	////今回ここは VS_OUTPUTのレイアウトをもとに　　POSITION と UVになるTEXCOORDを設定
	

	
	//ブロブからピクセルシェーダー作成

	m_TestModel.m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_TestModel.m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_PixelShader.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);
	}

	m_Ground.m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	m_TestModel.m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);

	
	//コンスタントバッファー作成　　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;//説明書
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPUにアクセスするフラグ設定
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//使用法

	m_TestModel.m_ConstantBuffer.CreateConstantBuffer(cb);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_ConstantBuffer.CreateConstantBuffer(cb);
	}

	m_Ground.m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_ConstantBuffer.CreateConstantBuffer(cb);

	return S_OK;
}


HRESULT MAIN::InitPolygon()
{
	m_TestModel.PosInit();
	m_TestModel.m_Cube.Init(m_pDevice, m_pDeviceContext);
	m_TestModel.m_Cube.CreateVertexBuffer();
	m_TestModel.m_Cube.CreateTexture("white.jpg");

	for (int i = 0; i < 3; i++) {
		m_EnemyModel[i].PosInit();
		m_EnemyModel[i].m_Cube.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_Cube.CreateVertexBuffer();
		m_EnemyModel[i].m_Cube.CreateTexture("red.jpg");
	}

	m_Ground.PosInit();
	m_Ground.m_Ground.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_Ground.CreateVertexBuffer();
	m_Ground.m_Ground.CreateTexture("white.jpg");

	return S_OK;
}

void MAIN::Render()
{
	Camera* MainCamera = g_pMain->m_Camera;	//Main Camera Pointer
	FPS* DeltaFPS = g_pMain->m_FPS;
	float ClearColor[4] = { 0,0,0.0,1 }; //クリア色　RGBA

	//画面クリア
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//カラー
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//デプスステンシル

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;


	//Inputs

	//getting delta position by inputs
	D3DXVECTOR3 deltaPosition(0, 0, 0);
	deltaPosition = MainCamera->m_Pos;
	D3DXVECTOR3 deltaRot(0,0,0);
	deltaRot = MainCamera->m_Rot;
	if (DeltaFPS->DeltaReady())
	{
		if (GetKeyState('A') & 0x80) {
			MainCamera->m_Pos += 1.0f * -MainCamera->m_vRight * DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('D') & 0x80) {
			MainCamera->m_Pos += 1.0f * MainCamera->m_vRight* DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('W') & 0x80) {
			MainCamera->m_Pos += 1.0f * MainCamera->m_vForward* DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('S') & 0x80) {
			MainCamera->m_Pos += 1.0f * -MainCamera->m_vForward* DeltaFPS->GetDeltaTime();
		}

		//getting delta rotation by inputs
		if (GetKeyState(VK_RIGHT) & 0x80) {
			MainCamera->m_Rot.y += 1.0f * DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState(VK_LEFT) & 0x80) {
			MainCamera->m_Rot.y -= 1.0f * DeltaFPS->GetDeltaTime();
		}
	}


	
	deltaPosition = (MainCamera->m_Pos - deltaPosition);
	//deltaRot = (MainCamera->m_Rot - deltaRot);
	//popup message
	if (GetKeyState(VK_SPACE))
	{
		char testString[256];
		sprintf_s(testString, "%f", MainCamera->m_Pos.x);
		MessageBox(m_hWnd, testString, "test", 0);
	}

	if (GetKeyState('E') & 0x80)
	{
		char testString[256];
		sprintf_s(testString, "%f", DeltaFPS->GetDeltaTime());
		MessageBox(m_hWnd, testString, "test", 0);
	}

	//ワールドトランスフォーム
	//Rotate and Translate main camera
	D3DXMatrixTranslation(&MainCamera->m_Transform, deltaPosition.x, deltaPosition.y, deltaPosition.z);

	D3DXVECTOR3 vRotTmp(MainCamera->m_PoseMat._21, MainCamera->m_PoseMat._22, MainCamera->m_PoseMat._23);
	D3DXMatrixRotationAxis(&MainCamera->m_DeltaMat, &vRotTmp, MainCamera->m_Rot.y);

	D3DXVECTOR3 vRight(1, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vForward(0, 0, 1);
	D3DXVec3TransformCoord(&MainCamera->m_vRight, &vRight, &MainCamera->m_DeltaMat);
	D3DXVec3TransformCoord(&MainCamera->m_vUp, &vUp, &MainCamera->m_DeltaMat);
	D3DXVec3TransformCoord(&MainCamera->m_vForward, &vForward, &MainCamera->m_DeltaMat);


	D3DXMATRIX mTransform = MainCamera->m_DeltaMat * MainCamera->m_Transform;

	//D3DXVec3TransformCoord(&MainCamera->m_vLookat, &MainCamera->m_vLookat, &MainCamera->m_Transform);
	//D3DXVec3TransformCoord(&MainCamera->m_vEyePt, &MainCamera->m_vEyePt, &MainCamera->m_Transform);


	//D3DXVec3TransformCoord(&MainCamera->m_vLookat, &MainCamera->m_vLookat, &mTransform);
	//D3DXVec3TransformCoord(&MainCamera->m_vEyePt, &MainCamera->m_vEyePt, &mTransform);

	D3DXVECTOR3 vEyePt = MainCamera->m_Pos;
	D3DXVECTOR3 vLookAtPt = vEyePt + MainCamera->m_vForward;

	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookAtPt, &MainCamera->m_vUp); //getting view matrix

	
	//プロジェクショントランスフォーム
	D3DXMatrixPerspectiveFovLH(&mProjection, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


	
	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, 0.0f, 0.0f, 0.0f);
	m_TestModel.Render(mView, mProjection,Tran);
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&Tran, (i+1)*1, 0, (i+1)*1);

		m_EnemyModel[i].Render(mView, mProjection, Tran);
	}
	
	m_Ground.Render(mView, mProjection);

	g_pMain->m_FPS->PrintFps(m_hWnd);

	m_pSwapChain->Present(0, 0);//画面更新

}


void MAIN::DestroyD3D()
{
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
}