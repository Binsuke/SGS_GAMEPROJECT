#include "MAIN.h"
//グローバル変数
MAIN* g_pMain=NULL;
//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//
//
//アプリケーションのエントリー関数 
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
{
	g_pMain=new MAIN;
	if(g_pMain != NULL)
	{
		if(SUCCEEDED(g_pMain->InitWindow(hInstance,0,0,WINDOW_WIDTH,
			WINDOW_HEIGHT,APP_NAME)))
		{
			if(SUCCEEDED(g_pMain->InitD3D()))
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
//
//
//OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd,uMsg,wParam,lParam);
}
//
//
//ウィンドウ作成
HRESULT MAIN::InitWindow(HINSTANCE hInstance,
		INT iX,INT iY,INT iWidth,INT iHeight,LPCWSTR WindowName)
 {
	 // ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	m_hWnd=CreateWindow(WindowName,WindowName,WS_OVERLAPPEDWINDOW,
		0,0,iWidth,iHeight,0,0,hInstance,0);
	 if(!m_hWnd) 
	 {
		 return E_FAIL;
	 }
	 //ウインドウの表示
	 ShowWindow(m_hWnd,SW_SHOW);
	 UpdateWindow(m_hWnd) ;

	 return S_OK;
 }
//
//
//ウィンドウプロシージャー
 LRESULT MAIN::MsgProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_KEYDOWN:
		switch((char)wParam)
		{
			case VK_ESCAPE://ESCキーで修了
			PostQuitMessage(0);
			break;
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc (hWnd, iMsg, wParam, lParam);
 }
//
//
//メッセージループとアプリケーション処理の入り口
void MAIN::Loop()
{
	//メッシュ作成
	m_pRobotMesh=new CD3DXMESH;
	m_pRobotMesh->Init(m_hWnd,m_pDevice,m_pDeviceContext,"robotB.x");
	m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,1);
	m_pRobotMesh->m_vPos=D3DXVECTOR3(0,0.5,-10);

	m_pSlopeMesh=new CD3DXMESH;
	m_pSlopeMesh->Init(m_hWnd,m_pDevice,m_pDeviceContext,"slope.x");

	 // メッセージループ
	 MSG msg={0};
	 ZeroMemory(&msg,sizeof(msg));
	 while(msg.message!=WM_QUIT)
	 {
		 if( PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		 {
			 TranslateMessage(&msg);
			 DispatchMessage(&msg);
		 }
		 else
		 {
			 //アプリケーションの処理はここから飛ぶ。
			 App();			 
		 }
	 }
	 //アプリケーションの終了
 }
//
//
//アプリケーション処理。アプリのメイン関数。
 void MAIN::App()
 {
	 Render();
 }
//
//
//
HRESULT MAIN::InitD3D()
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
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

    if( FAILED( D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL, 
		0,&pFeatureLevels,1,D3D11_SDK_VERSION,&sd,&m_pSwapChain,&m_pDevice,
		pFeatureLevel,&m_pDeviceContext )) )
	{
		return FALSE;
	}
	//各種テクスチャーと、それに付帯する各種ビューを作成

	//バックバッファーテクスチャーを取得（既にあるので作成ではない）
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ),(LPVOID*)&pBackBuffer_Tex);
	//そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
	m_pDevice->CreateRenderTargetView( pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV );
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
	m_pDevice->CreateTexture2D( &descDepth, NULL, &m_pBackBuffer_DSTex );
	//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	m_pDevice->CreateDepthStencilView( m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV,m_pBackBuffer_DSTexDSV);
	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports( 1, &vp );
	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc,sizeof(rdc));
	rdc.CullMode=D3D11_CULL_NONE;
	rdc.FillMode=D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr=NULL;
	m_pDevice->CreateRasterizerState(&rdc,&pIr);
	m_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	return S_OK;
}
//
//
//
void MAIN::DestroyD3D()
{
	SAFE_DELETE(m_pRobotMesh);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDevice);
}
//
//
//シーンを画面にレンダリング
void MAIN::Render()
{	
	//ロボット操作
	m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,0);
	if(GetKeyState('W') & 0x80)
	{
		m_pRobotMesh->m_Dir=m_pRobotMesh->m_AxisZ*0.05;
	}
	if(GetKeyState('S') & 0x80)
	{
		m_pRobotMesh->m_Dir=-m_pRobotMesh->m_AxisZ*0.05;
	}
	if(GetKeyState('A') & 0x80)
	{
		m_pRobotMesh->m_Dir=-m_pRobotMesh->m_AxisX*0.05;
	}
	if(GetKeyState('D') & 0x80)
	{
		m_pRobotMesh->m_Dir=m_pRobotMesh->m_AxisX*0.05;
	}
	if(GetKeyState(VK_LEFT) & 0x80)
	{
		m_pRobotMesh->m_fYaw-=0.05;
	}
	if(GetKeyState(VK_RIGHT) & 0x80)
	{
		m_pRobotMesh->m_fYaw+=0.05;
	}

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = {0,0,1,1};// クリア色作成　RGBAの順
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV,ClearColor);//画面クリア
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV,D3D11_CLEAR_DEPTH,1.0f,0);//深度バッファクリア

	// ビュートランスフォーム（視点座標変換）
	D3DXVECTOR3 vEyePt; 
	D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	//カメラをロボットの後ろに配置。
	D3DXVECTOR3 v(0,1,-3);
	D3DXVec3TransformCoord(&v,&v,&m_pRobotMesh->m_World);
	vEyePt=v;
	vLookatPt=m_pRobotMesh->m_vPos+D3DXVECTOR3(0,0.5,0);//ロボットの方を向くようにする

	D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookatPt, &vUpVec );
	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4, (FLOAT)WINDOW_WIDTH/(FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f );
	//レンダリング
	m_pRobotMesh->Render(mView,mProj,D3DXVECTOR3(1,1,-1),vEyePt);
	m_pSlopeMesh->Render(mView,mProj,D3DXVECTOR3(1,1,-1),vEyePt);
	//画面更新（バックバッファをフロントバッファに）
	m_pSwapChain->Present(0,0);
	
	//重力（下方向のベクトルを加算）
	m_pRobotMesh->m_Dir+=D3DXVECTOR3(0,-0.02,0);

	//当たり判定
	float fDistance=0;
	D3DXVECTOR3 vNormal;
	if( RayIntersect(m_pRobotMesh,m_pRobotMesh->m_Dir,m_pSlopeMesh,&fDistance,&vNormal) && fDistance<=0.3)	
	{
		//当たり状態なので、滑らせる
		m_pRobotMesh->m_Dir=Slip(m_pRobotMesh->m_Dir,vNormal);//滑りベクトルを計算

		//滑りベクトル先の壁とのレイ判定 ２重に判定	
		if( RayIntersect(m_pRobotMesh,m_pRobotMesh->m_Dir,m_pSlopeMesh,&fDistance,&vNormal)&& fDistance<=0.2)			
		{				
			m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,0);//止める
		}		
	}	
	
	//ロボット　位置更新
	m_pRobotMesh->m_vPos+=m_pRobotMesh->m_Dir;
	if(m_pRobotMesh->m_vPos.y-0.5<=0) m_pRobotMesh->m_vPos.y=0.5;

	//60FPS上限
	static int time=0;
	time=timeGetTime();
	while(timeGetTime()-time<16.667);
}

//
//
//レイによる衝突判定　レイが相手メッシュと交差する場合は、pfDistanceに距離を入れてtrueを返す
//交差しているポリゴンも返す
bool MAIN::RayIntersect(CD3DXMESH* pMeshA,D3DXVECTOR3& Dir,CD3DXMESH* pMeshB,float* pfDistance,D3DXVECTOR3* pvNormal)
{
	BOOL boHit=false;
	D3DXMATRIX Inv;
	D3DXVECTOR3 vStart,vEnd,vDirection;
	//レイを出すメッシュの位置・回転をレイに適用
	vStart=pMeshA->m_vPos+D3DXVECTOR3(0,-0.4,0);
	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixInverse(&Inv,NULL,&pMeshB->m_World);
	D3DXVec3TransformCoord(&vStart,&vStart,&Inv);

	D3DXVECTOR3 Direction=Dir;
	D3DXVec3Normalize(&Direction,&Direction);
	DWORD dwIndex=0;
	D3DXIntersect(pMeshB->m_pMesh,&vStart,&Direction,&boHit,&dwIndex,NULL,NULL, pfDistance,NULL,NULL);
	if(boHit)
	{
		//交差しているポリゴンの頂点を見つける
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pMeshB->m_pMesh,dwIndex,vVertex);
		D3DXPLANE p;
		//その頂点から平面方程式を得る
		D3DXPlaneFromPoints(&p,&vVertex[0],&vVertex[1],&vVertex[2]);
		//平面方程式の係数が法線の成分
		pvNormal->x=p.a;
		pvNormal->y=p.b;
		pvNormal->z=p.c;

		return true;
	}
	return false;
}
//
//
// L:入射ベクトル（レイ） N:ポリゴンの法線
D3DXVECTOR3 MAIN::Slip(D3DXVECTOR3 L,D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //滑りベクトル（滑る方向）

	//滑りベクトル S=L-(N * L)/(|N|^2)*N
	S=L-((D3DXVec3Dot(&N,&L))/(pow(D3DXVec3Length(&N),2)))*N;

	return S;
}
//
//
//そのポリゴンの頂点を見つける
HRESULT MAIN::FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvVertices)
{
	DWORD i,k;
	DWORD dwStride=pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum=pMesh->GetNumVertices();
	DWORD dwPolyNum=pMesh->GetNumFaces();
	DWORD* pwPoly=NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY,(VOID**)&pwPoly);	

	BYTE *pbVertices=NULL;
	FLOAT* pfVetices=NULL;
	LPDIRECT3DVERTEXBUFFER9 VB=NULL;
	pMesh->GetVertexBuffer(&VB);
	if(SUCCEEDED(VB->Lock(0,0,(VOID**)&pbVertices,0)))
	{
		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex* 3] ];
		pvVertices[0].x=pfVetices[0];
		pvVertices[0].y=pfVetices[1];
		pvVertices[0].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+1] ];
		pvVertices[1].x=pfVetices[0];
		pvVertices[1].y=pfVetices[1];
		pvVertices[1].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+2] ];
		pvVertices[2].x=pfVetices[0];
		pvVertices[2].y=pfVetices[1];
		pvVertices[2].z=pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
	}
	return S_OK;
}
