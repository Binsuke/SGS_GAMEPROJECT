#include "MAIN.h"

//グローバル変数
MAIN* g_pMain = NULL;

//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN;
	if (g_pMain != NULL)
	{
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			if (SUCCEEDED(g_pMain->InitD3D()))
			{
				g_pMain->Loop();
			}
		}
		//アプリ終了
		g_pMain->DestroyD3D();
		delete g_pMain;
	}
	return 0;
}

//OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);
}


//ウィンドウ作成

HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	//ウィンドウの定義

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	m_hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);

	if (!m_hWnd)
	{
		return E_FAIL;
	}

	//ウィンドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}


//ウィンドウプロシージャー

LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://ESCキーで終了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

//メッセージループとアプリケーション処理の入り口
void MAIN::Loop()
{
	//メッシュ作成
	m_pMesh = new CD3DXMESH_ANIM;
	if (FAILED((m_pMesh->Init(m_hWnd, m_pDevice, m_pDeviceContext, (LPSTR)"Josh_Motion_Walk.x"))))
	{
		return;
	}

	m_pDomeMesh = new CD3DXMESH_ANIM;
	if (FAILED((m_pDomeMesh->Init(m_hWnd, m_pDevice, m_pDeviceContext, (LPSTR)"sky_city.x"))))
	{
		return;
	}

	//メッシュ作成終わり

	//メッセージループ

	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));//最初にメッセージを初期化　ピークメッセージでメッセージを受け取ったあとに
								//ループ処理に戻るから、これ以前に初期化処理を入れてあるってことかな
	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//アプリケーションの処理はここから飛ぶ
			App();
		}
	}
	//アプリケーションの終了
}

//アプリケーション処理　アプリのメイン関数
void MAIN::App()
{
	Render();
}


HRESULT MAIN::InitD3D()
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel, &m_pDeviceContext)))
	{
		return FALSE;
	}
	//各種テクスチャーと、それに付帯する各種ビューを作成

	//バックバッファーテクスチャーを取得（既にあるので作成ではない）
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);
	//そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV);
	SAFE_RELEASE(pBackBuffer_Tex);

	//デプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);
	//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV);
	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);
	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;
	m_pDevice->CreateRasterizerState(&rdc, &pIr);
	m_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	return S_OK;
}


void MAIN::DestroyD3D()
{
	SAFE_DELETE(m_pMesh);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDevice);
}

void MAIN::Render()
{
	//キャラ操作
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		m_pMesh->m_fYaw -= 0.001f;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		m_pMesh->m_fYaw += 0.001f;
	}

	if (GetKeyState('A') & 0x80)
	{
		m_pMesh->MoveStepLeft(0.001f);
	}
	if (GetKeyState('D') & 0x80)
	{
		m_pMesh->MoveStepRight(0.001f);
	}

	if (GetKeyState('W') & 0x80)
	{
		m_pMesh->MoveForward(0.001f);
	}
	if (GetKeyState('S') & 0x80)
	{
		m_pMesh->MoveBackward(0.001f);
	}

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//画面クリア（実際は単色で画面を塗りつぶす処理
	float ClearColor[4] = { 0,0,1,1 };//クリア色作成
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//画面クリア
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア

	//３人称視点処理　ビュートランスフォーム　　カメラをキャラの後ろにするだけ
	D3DXVECTOR3 vEyePt(0.0f, 2.0f, -4.0f); //カメラ
	D3DXVECTOR3 vLookatPt(0.0f, 1.7f, 0.0f);//注視位置
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	//視点と注視店の両方をキャラの姿勢（回転と位置）行列でまげて移動すればいい
	D3DXMATRIX OriMat, Tran, Yaw;
	D3DXMatrixTranslation(&Tran, m_pMesh->m_vPos.x, m_pMesh->m_vPos.y, m_pMesh->m_vPos.z);
	D3DXMatrixRotationY(&Yaw, m_pMesh->m_fYaw);
	OriMat = Yaw * Tran;

	D3DXVec3TransformCoord(&vEyePt, &vEyePt, &OriMat);
	D3DXVec3TransformCoord(&vLookatPt, &vLookatPt, &OriMat);

	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);

	//プロジェクショントランスフォーム（射影変換
	D3DXMatrixPerspectiveFovLH(&mProj, (float)(D3DX_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);

	D3DXVECTOR3 vLight = D3DXVECTOR3(1, 1, -1);
	D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, -1);
	//レンダリング
	m_pDomeMesh->Render(mView, mProj,vLight,vEye);
	m_pMesh->Render(mView, mProj, vLight, vEye);
	m_pMesh->m_pAnimController->AdvanceTime(0.00015, NULL);

	//画面更新
	m_pSwapChain->Present(0, 0);

}


