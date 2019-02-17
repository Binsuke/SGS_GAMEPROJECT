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
		g_pMain->m_pCamera = new Camera;
		g_pMain->m_pFPS = new FPS;
		g_pMain->InitModel();
		g_pMain->m_pCamera->InitCamera();
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME))) //ウィンドウの作成　成功していたら中に入る
		{
			if (SUCCEEDED(g_pMain->InitD3D()))//D3D系列の初期化　成功していたらループに入る
			{
				g_pMain->Loop();	//メインループ
			}
		}
		//アプリの終了
		g_pMain->ReleaseModel();
		g_pMain->DestroyD3D();
		delete g_pMain;
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);//メインのメッセージプロセスを実行　そして結果を返す
}

void MAIN::InitModel()
{
	m_pTestModel = new MyModel;
	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i] = new MyModel;
	}
	m_pGround = new MyGround;
	m_pMoveUI = new MoveUI;
}

void MAIN::ReleaseModel()
{
	//m_pTestModel->m_Cube.Release();

	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pFPS);
	SAFE_DELETE(m_pTestModel);
	
	//SAFE_DELETE_ARRAY(m_pEnemyModel);
	for (int i = 0; i < 3; i++) {
		SAFE_DELETE(m_pEnemyModel[i]);
	}

	SAFE_DELETE(m_pGround);
	SAFE_DELETE( m_pMoveUI);
}
//コンストラクタ
MAIN::MAIN()
{
	ZeroMemory(this, sizeof(MAIN));
	m_eMoveVec = MAIN::eMoveVec::None;
	//view = -2;
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
			//view += 0.001;
			break;
		case VK_DOWN:
			//view -= 0.001;
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
	g_pMain->m_pFPS->Run();
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

	//アルファブレンド用ブレンドステート作成
	//pngファイル内にアルファ情報がある。アルファにより透過するよう指定している
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&bd, &m_pBlendState)))
	{
		return E_FAIL;
	}

	UINT mask = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, mask);


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
	
	m_pTestModel->m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	}

	m_pGround->m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //この作業を行うのは　本来はシェーダーの情報をもとにレイアウトを作る必要がでてくるため、シェーダーごとに

	//m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);

	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i]->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	}
	m_pTestModel->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pGround->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pMoveUI->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);


	////頂点インプットレイアウトを定義
	////今回ここは VS_OUTPUTのレイアウトをもとに　　POSITION と UVになるTEXCOORDを設定
	

	
	//ブロブからピクセルシェーダー作成

	m_pTestModel->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pTestModel->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);
	}

	m_pGround->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	m_pMoveUI->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);


	m_pTestModel->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);

	
	//コンスタントバッファー作成　　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;//説明書
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPUにアクセスするフラグ設定
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//使用法

	m_pTestModel->m_ConstantBuffer.CreateConstantBuffer(cb);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_ConstantBuffer.CreateConstantBuffer(cb);
	}

	m_pGround->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_ConstantBuffer.CreateConstantBuffer(cb);

	m_pMoveUI->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_ConstantBuffer.CreateConstantBuffer(cb);


	return S_OK;
}


HRESULT MAIN::InitPolygon()
{
	m_pTestModel->InitLv(3);
	m_pTestModel->m_Cube.Init(m_pDevice, m_pDeviceContext);
	m_pTestModel->m_Cube.CreateVertexBuffer();
	m_pTestModel->m_Cube.CreateTexture("white.jpg");

	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i]->InitLv(i+3);
		m_pEnemyModel[i]->m_Cube.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_Cube.CreateVertexBuffer();
		m_pEnemyModel[i]->m_Cube.CreateTexture("red.jpg");
	}

	m_pGround->PosInit();
	m_pGround->m_Ground.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_Ground.CreateVertexBuffer();
	m_pGround->m_Ground.CreateTexture("white.jpg");

	/*m_pMoveUI->m_PanelW.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_PanelW.CreateVertexBuffer();
	m_pMoveUI->m_PanelW.CreateTexture("UI_W.png");
*/
	m_pMoveUI->MovePanelInit(m_pDevice,m_pDeviceContext);
	return S_OK;
}

void MAIN::Render()
{
	Camera* MainCamera = g_pMain->m_pCamera;	//Main Camera Pointer
	FPS* DeltaFPS = g_pMain->m_pFPS;
	float ClearColor[4] = { 0,0,0.0,1 }; //クリア色　RGBA

	//画面クリア
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//カラー
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//デプスステンシル

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;


	//Inputs
	//static MAIN::eMoveVec Vec = MAIN::eMoveVec;;None;

	
	if (DeltaFPS->DeltaReady())
	{
		if (GetKeyState('A') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Left)
			{
				m_eMoveVec = eMoveVec::Left;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Left) {
				//m_eMoveVec = eMoveVec::None;
			}
		}

		if (GetKeyState('D') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Right)
			{
				m_eMoveVec = MAIN::eMoveVec::Right;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Right) {
				//m_eMoveVec = eMoveVec::None;
			}
		}
		if (GetKeyState('W') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Forward)
			{
				m_eMoveVec = MAIN::eMoveVec::Forward;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Forward) {
				//m_eMoveVec = eMoveVec::None;
			}
		}
		if (GetKeyState('S') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Backward)
			{
				m_eMoveVec = MAIN::eMoveVec::Backward;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Backward) {
				//m_eMoveVec = eMoveVec::None;
			}
		}
		
		bool check = MoveUpdateA(m_eMoveVec);
		if (check) {
			m_eMoveVec = eMoveVec::None;
		}

		////right check
		//if (m_eMoveVec == eMoveVec::Right) {
		//	
		//	bool check = m_pTestModel->AnimationLocalRightA(DeltaFPS->GetDeltaTime());
		//	if (check) {

		//		m_eMoveVec = eMoveVec::None;
		//	}
		//}

		//if (m_eMoveVec == eMoveVec::Left) {

		//	bool check = m_pTestModel->AnimationLocalLeftA(DeltaFPS->GetDeltaTime());

		//	if (check) {

		//		m_eMoveVec = eMoveVec::None;
		//	}
		//}

		//if (m_eMoveVec == eMoveVec::Forward) {

		//	bool check = m_pTestModel->AnimationLocalForwardA(DeltaFPS->GetDeltaTime());

		//	if (check) {

		//		m_eMoveVec = eMoveVec::None;
		//	}
		//}

		//if (m_eMoveVec == eMoveVec::Backward) {

		//	bool check = m_pTestModel->AnimationLocalBackwardA(DeltaFPS->GetDeltaTime());

		//	if (check) {

		//		m_eMoveVec = eMoveVec::None;
		//	}
		//}



		//MoveUpdate(m_eMoveVec);
		
		//上を常に見れるようにするか　元のターゲットまで戻すかの処理
		MainCamera->UpDateLook(DeltaFPS->GetDeltaTime(),m_pTestModel->GetSizeY());
		if (GetKeyState(VK_UP) & 0x80) {
			MainCamera->LookUp(DeltaFPS->GetDeltaTime(), m_pTestModel->GetSizeY());

			//MainCamera->MoveUp(DeltaFPS->GetDeltaTime());
		}
		if (GetKeyState(VK_DOWN) & 0x80) {
			MainCamera->LookDown(DeltaFPS->GetDeltaTime(), m_pTestModel->GetSizeY());
			//MainCamera->MoveDown(DeltaFPS->GetDeltaTime());
		}
		if (GetKeyState(VK_RIGHT) & 0x80) {
			//MainCamera->RotRight(DeltaFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				MainCamera->RotRight(DeltaFPS->GetDeltaTime());
			}
		}
		if (GetKeyState(VK_LEFT) & 0x80) {
			//MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
			}
		}
		static bool flg = false;//レベルアップ確認用

		if (GetKeyState('E') & 0x80) {
			//MainCamera->RotRight(DeltaFPS->GetDeltaTime());
			if (!flg) {
				if (m_eMoveVec == None) {
					m_pTestModel->LVUp();
					flg = true;
				}
			}
		}
		else if (flg) {
			flg = false;
		}
		static bool flg2 = false;

		if (GetKeyState('Q') & 0x80) {
			//MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
			if (!flg2) {
				if (m_eMoveVec == None)
				{
					m_pTestModel->LVDown();
					flg2 = true;
				}
			}
		}
		else if (flg2) {
			flg2 = false;
		}
	}

	//popup message
	
	/*if (GetKeyState('E') & 0x80)
	{
		char testString[256];
		D3DXVECTOR3 tmp = m_pTestModel->GetCenter();
		sprintf_s(testString, "x = %f,y = %f,z=%f",tmp.x,tmp.y,tmp.z );
		MessageBox(m_hWnd, testString, "test", 0);
	}*/

	
	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, 0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 CameraPosVec(0, 0.7f, -1);
	//MainCamera->SetCamera(&mView, &mProjection, m_pTestModel->GetCameraTarget(),m_pTestModel->GetCameraMargin());
	//MainCamera->SetCamera(&mView, &mProjection, m_pTestModel->GetCameraTarget(), m_pTestModel->GetCameraMargin(),TargetMarg.y,TargetMarg.x);
	MainCamera->SetCameraA(&mView, &mProjection, m_pTestModel->GetCameraTarget(), m_pTestModel->GetCameraMargin());


	m_pTestModel->Render(mView, mProjection);
	for (int i = 0; i < 3; i++)
	{
		//D3DXMatrixTranslation(&Tran, (i+1)*1, 0, (i+1)*1);
		//m_pEnemyModel[i]->SetPos((i + 1) * m_pEnemyModel[i]->GetSizeY(), 0, (i + 1) * 1);
		m_pEnemyModel[i]->Render(mView, mProjection);
	}

	
	m_pGround->Render(mView, mProjection);

	
	m_pMoveUI->Render(mView, mProjection, m_pTestModel->GetCenter(),m_pTestModel->GetSizeY() * 1.1,MainCamera->GetWorldForward(),m_pTestModel->GetLV());
	
	g_pMain->m_pFPS->PrintFps(m_hWnd);

	m_pSwapChain->Present(0, 0);//画面更新

}

void MAIN::MoveUpdate(eMoveVec eVec)
{
	m_pCamera->UpDateWorldVec();
	D3DXVECTOR3 vLocalVec;
	switch (eVec)
	{
	//case eMoveVec::None:
		//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);

	case eMoveVec::Forward:
		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalLeftVec);
		break;
	}
}



bool MAIN::MoveUpdateA(eMoveVec eVec)
{
	m_pCamera->UpDateWorldVec();
	D3DXVECTOR3 vLocalVec;
	switch (eVec)
	{
	case eMoveVec::None:
			//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);
		return false;
	case eMoveVec::Forward:
		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalLeftVec);
	}

	return false;
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