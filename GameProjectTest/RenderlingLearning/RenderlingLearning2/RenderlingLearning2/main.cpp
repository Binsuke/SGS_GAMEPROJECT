////必要なヘッダーファイルのインクルード
//#include <stdio.h>
//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx10.h>
//#include <d3dx11.h>
//#include <d3dCompiler.h>
//#include "MyMesh.h"
////必要なライブラリファイルのロード
//#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"d3dx10.lib")
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"d3dx11.lib")
//#pragma comment(lib,"d3dCompiler.lib")
//
//#pragma comment(lib,"libfbxsdk_md.lib")
//#pragma comment(lib,"libfbxml2_md.lib")
//#pragma comment(lib,"zlib_md.lib")
//
////定数
//#define WINDOW_WIDTH 640
//#define WINDOW_HEIGHT 480
////マクロ
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
////グローバル
//HWND g_hWnd;
//ID3D11Device* g_pDevice;
//IDXGISwapChain*			g_pSwapChain;
//ID3D11RenderTargetView* g_pRenderTargetView;
//ID3D11DepthStencilView* g_pDepthStencilView;
//ID3D11InputLayout*      g_pVertexLayout;
//ID3D11Texture2D*		g_pDepthStencil;
//
//ID3D11DeviceContext	 *g_pDeviceContext = NULL;
//ID3D11VertexShader *g_pVertexShader = NULL;//effectではなく、個別にバーテックスシェーダー
//ID3D11PixelShader *g_pPixelShader = NULL;//effectではなく、個別にピクセルシェーダー
//
//ID3D11Buffer* g_pConstantBuffer0 = NULL;//アプリ←→シェーダー架け橋　コンスタントバッファー 
//ID3D11Buffer* g_pConstantBuffer1 = NULL;//アプリ←→シェーダー架け橋　コンスタントバッファー　
//
//ID3D11SamplerState* g_pSampleLinear = NULL;//テクスチャーのサンプラー 全マテリアルテクスチャー共通
//
////シェーダーに渡す値
//struct SHADER_GLOBAL0
//{
//	D3DXVECTOR4 vLightDir;//ライト方向
//	D3DXVECTOR4 vEye;//カメラ位置
//};
//
//D3DXVECTOR3 g_vLightDir(-1, 1, -1);
//MY_MESH* g_pMesh;
//
////関数プロトタイプの宣言
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HRESULT InitD3d(HWND);
//void Render();
//
////
////INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
////アプリケーションのエントリー関数
//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
//{
//	//メッシュのインスタンス生成
//	g_pMesh = new MY_MESH;
//	// ウィンドウの初期化
//	static WCHAR szAppName[] = L"D3D11　FBXからスタティックメッシュ";
//	WNDCLASSEX  wndclass;
//
//	wndclass.cbSize = sizeof(wndclass);
//	wndclass.style = CS_HREDRAW | CS_VREDRAW;
//	wndclass.lpfnWndProc = WndProc;
//	wndclass.cbClsExtra = 0;
//	wndclass.cbWndExtra = 0;
//	wndclass.hInstance = hInst;
//	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wndclass.lpszMenuName = NULL;
//	wndclass.lpszClassName = szAppName;
//	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
//	RegisterClassEx(&wndclass);
//
//	g_hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
//		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL);
//	ShowWindow(g_hWnd, SW_SHOW);
//	UpdateWindow(g_hWnd);
//	// ダイレクト３Dの初期化関数を呼ぶ
//	if (FAILED(InitD3d(g_hWnd)))
//	{
//		return 0;
//	}
//	// メッセージループ
//	MSG msg;
//	ZeroMemory(&msg, sizeof(msg));
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			Render();
//		}
//	}
//	//アプリケーションを終了する時には、Direct3Dオブジェクトをリリースする
//	delete g_pMesh;
//	SAFE_RELEASE(g_pSampleLinear);
//	SAFE_RELEASE(g_pDepthStencilView);
//	SAFE_RELEASE(g_pDepthStencil);
//	SAFE_RELEASE(g_pVertexShader);
//	SAFE_RELEASE(g_pPixelShader);
//	SAFE_RELEASE(g_pConstantBuffer0);
//	SAFE_RELEASE(g_pConstantBuffer1);
//	SAFE_RELEASE(g_pSwapChain);
//	SAFE_RELEASE(g_pRenderTargetView);
//	SAFE_RELEASE(g_pVertexLayout);
//	SAFE_RELEASE(g_pDeviceContext);
//	SAFE_RELEASE(g_pDevice);
//
//	return (INT)msg.wParam;
//}
////
////LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
//// ウィンドウプロシージャー関数
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hWnd, iMsg, wParam, lParam);
//}
////
////HRESULT InitD3d(HWND hWnd)
////ダイレクト3Dの初期化
//HRESULT InitD3d(HWND hWnd)
//{
//	// デバイスとスワップチェーンの作成
//	DXGI_SWAP_CHAIN_DESC sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.BufferCount = 1;
//	sd.BufferDesc.Width = WINDOW_WIDTH;
//	sd.BufferDesc.Height = WINDOW_HEIGHT;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = 60;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.OutputWindow = g_hWnd;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.Windowed = TRUE;
//
//	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
//	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;
//
//	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
//		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pDevice,
//		pFeatureLevel, &g_pDeviceContext)))
//	{
//		return FALSE;
//	}
//	//レンダーターゲットビューの作成
//	ID3D11Texture2D *pBackBuffer;
//	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
//	g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
//	pBackBuffer->Release();
//
//	//深度ステンシルビューの作成
//	D3D11_TEXTURE2D_DESC descDepth;
//	descDepth.Width = WINDOW_WIDTH;
//	descDepth.Height = WINDOW_HEIGHT;
//	descDepth.MipLevels = 1;
//	descDepth.ArraySize = 1;
//	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
//	descDepth.SampleDesc.Count = 1;
//	descDepth.SampleDesc.Quality = 0;
//	descDepth.Usage = D3D11_USAGE_DEFAULT;
//	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	descDepth.CPUAccessFlags = 0;
//	descDepth.MiscFlags = 0;
//	g_pDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);
//
//	g_pDevice->CreateDepthStencilView(g_pDepthStencil, NULL, &g_pDepthStencilView);
//	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド	
//	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
//
//	//ビューポートの設定
//	D3D11_VIEWPORT vp;
//	vp.Width = WINDOW_WIDTH;
//	vp.Height = WINDOW_HEIGHT;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//	g_pDeviceContext->RSSetViewports(1, &vp);
//
//	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
//	ID3DBlob *pCompiledShader = NULL;
//	ID3DBlob *pErrors = NULL;
//	//ブロブからバーテックスシェーダー作成
//	if (FAILED(D3DX11CompileFromFile(L"Geometry_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
//	{
//		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pErrors);
//
//	if (FAILED(g_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &g_pVertexShader)))
//	{
//		SAFE_RELEASE(pCompiledShader);
//		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	//頂点インプットレイアウトを定義	
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//	UINT numElements = sizeof(layout) / sizeof(layout[0]);
//
//	//頂点インプットレイアウトを作成
//	if (FAILED(g_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &g_pVertexLayout)))
//		return FALSE;
//	//頂点インプットレイアウトをセット
//	g_pDeviceContext->IASetInputLayout(g_pVertexLayout);
//
//	//ブロブからピクセルシェーダー作成
//	if (FAILED(D3DX11CompileFromFile(L"Geometry_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
//	{
//		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pErrors);
//	if (FAILED(g_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &g_pPixelShader)))
//	{
//		SAFE_RELEASE(pCompiledShader);
//		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pCompiledShader);
//	//ラスタライズ設定
//	D3D11_RASTERIZER_DESC rdc;
//	ZeroMemory(&rdc, sizeof(rdc));
//	rdc.CullMode = D3D11_CULL_NONE;
//	rdc.FillMode = D3D11_FILL_SOLID;
//
//	ID3D11RasterizerState* pIr = NULL;
//	g_pDevice->CreateRasterizerState(&rdc, &pIr);
//	g_pDeviceContext->RSSetState(pIr);
//	SAFE_RELEASE(pIr);
//	//コンスタントバッファー0作成
//	D3D11_BUFFER_DESC cb;
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.ByteWidth = sizeof(SHADER_GLOBAL0);
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//
//	if (FAILED(g_pDevice->CreateBuffer(&cb, NULL, &g_pConstantBuffer0)))
//	{
//		return E_FAIL;
//	}
//	//コンスタントバッファー1作成  
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.ByteWidth = sizeof(SHADER_GLOBAL1);
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//
//	if (FAILED(g_pDevice->CreateBuffer(&cb, NULL, &g_pConstantBuffer1)))
//	{
//		return E_FAIL;
//	}
//	//テクスチャー用サンプラー作成
//	D3D11_SAMPLER_DESC SamDesc;
//	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
//
//	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//	g_pDevice->CreateSamplerState(&SamDesc, &g_pSampleLinear);
//
//	//	メッシュクラスにデバイス関連情報を渡す
//	g_pMesh->m_pDevice = g_pDevice;
//	g_pMesh->m_pDeviceContext = g_pDeviceContext;
//	g_pMesh->m_pSampleLinear = g_pSampleLinear;
//	g_pMesh->m_pConstantBuffer = g_pConstantBuffer1;
//
//	//FBXファイル読み込み
//	g_pMesh->CreateFromFBX("chips.fbx");
//
//	return S_OK;
//}
//
////
////void Render()
////レンダリングする関数
//void Render()
//{
//	float ClearColor[4] = { 0,0,1,1 }; // クリア色作成　RGBAの順
//	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);//画面クリア 
//	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア
//
//	D3DXMATRIX mView;
//	D3DXMATRIX mProj;
//	//ビュー行列
//	D3DXVECTOR3 Eye(0.0f, 0.0f, -0.5f);
//	D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
//	D3DXMatrixLookAtLH(&mView, &Eye, &At, &Up);
//	g_pMesh->m_mView = mView;
//
//	//プロジェクション行列
//	D3DXMatrixPerspectiveFovLH(&mProj, (float)D3DX_PI / 4, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1100.0f);
//	g_pMesh->m_mProj = mProj;
//
//	//ライトベクトルをシェーダーに渡す	
//	//カメラ位置をシェーダーに渡す
//	D3D11_MAPPED_SUBRESOURCE pData;
//	if (SUCCEEDED(g_pDeviceContext->Map(g_pConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
//	{
//		SHADER_GLOBAL0 sg;
//		sg.vLightDir = D3DXVECTOR4(g_vLightDir.x, g_vLightDir.y, g_vLightDir.z, 0.0f);
//		sg.vEye = D3DXVECTOR4(Eye.x, Eye.y, Eye.z, 0);
//		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL0));
//		g_pDeviceContext->Unmap(g_pConstantBuffer0, 0);
//	}
//	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer0);
//	g_pDeviceContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer0);
//	//使用するシェーダーの登録　（effectの”テクニック”に相当）
//	g_pDeviceContext->VSSetShader(g_pVertexShader, NULL, 0);
//	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);
//	//レンダー
//	D3DXMATRIX mWorld;
//	static float fAngle = 0;
//	fAngle += 0.0003f;
//	D3DXMatrixRotationY(&mWorld, fAngle);
//	g_pMesh->RenderMesh(&mWorld);
//
//	g_pSwapChain->Present(0, 0);//画面更新（バックバッファをフロントバッファに）	
//}