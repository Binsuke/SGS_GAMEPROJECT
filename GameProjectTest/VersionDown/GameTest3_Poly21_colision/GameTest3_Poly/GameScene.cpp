#include "GameScene.h"
#include "main.h"

GameScene::GameScene() {
	m_bInitFlg = false;
}
GameScene::~GameScene() {
	ReleaseModel();
}
//ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, IDXGISwapChain* pSwapChain, ID3D11RenderTargetView* pBackBuffer_TexRTV, ID3D11DepthStencilView* pBackBuffer_DSTexDSV, ID3D11Texture2D* pBackBuffer_DSTex, ID3D11BlendState* pBlendState
void GameScene::Init() {
	/*ID3D11Device* m_pDevice = pDevice;
	ID3D11DeviceContext* m_pDeviceContext = pDeviceContext;
	IDXGISwapChain* m_pSwapChain = pSwapChain;
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV = pBackBuffer_TexRTV;
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV = pBackBuffer_DSTexDSV;
	ID3D11Texture2D* m_pBackBuffer_DSTex = pBackBuffer_DSTex;
	ID3D11BlendState* m_pBlendState = pBlendState;*/
	m_eMoveVec = eMoveVec::None;
	UI_RenderFlg = true;
	m_pCamera = new Camera;
	
	InitModel();
	m_pCamera->InitCamera();

}

void GameScene::Release() {
	ReleaseModel();
}


//ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, IDXGISwapChain* pSwapChain, ID3D11RenderTargetView* pBackBuffer_TexRTV, ID3D11DepthStencilView* pBackBuffer_DSTexDSV, ID3D11Texture2D* pBackBuffer_DSTex, ID3D11BlendState* pBlendState
BaseScene::eScene GameScene::App()
{
	if (m_bInitFlg == false) {
		//Init(pDevice,pDeviceContext, pSwapChain, pBackBuffer_TexRTV, pBackBuffer_DSTexDSV, pBackBuffer_DSTex, pBlendState);
		Init();
		m_pTestModel->InitDamagePolygon(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_bInitFlg = true;
	}

	Input();

	for (int i = 0; i < EnemyNum && m_pTestModel->GetDamegaFlg() == false; i++) {
		//if (m_pTestModel->GetDamegaFlg() == false) {
			if (m_pTestModel->GetLV() > m_pEnemyModel[i]->GetLV()) {
				if (m_pTestModel->Colision(m_pEnemyModel[i])) {
					m_pTestModel->GlowStackCube(m_pEnemyModel[i]->LVDown());
				}
			}
			else if (m_pTestModel->GetLV() == 1 && m_pEnemyModel[i]->GetLV() == 1) {
				if (m_pTestModel->Colision(m_pEnemyModel[i])) {
					m_pTestModel->GlowStackCube(m_pEnemyModel[i]->LVDown());
				}
			}
			else if (m_pTestModel->GetLV() == m_pEnemyModel[i]->GetLV()) {
				if (m_pTestModel->Colision(m_pEnemyModel[i])) {
					m_pTestModel->ReverceOn();
				}
			}
			else{
				if (m_pTestModel->Colision(m_pEnemyModel[i])) {
					m_pTestModel->Damage(m_pEnemyModel[i]->GetLV());
					m_pTestModel->ReverceOn();
				}
			}
		//}
	}


	//本当はレベルアップの時に同じレベルの敵のポインターをスタックしておいてそれを渡す
	//if(m_pTestModel->GetDamegaFlg==false)
	for (int i = 0; i < EnemyNum && m_pTestModel->GetDamegaFlg() == false; i++) {
		m_pTestModel->SameCubeColisionCheck(m_pEnemyModel[i]);
	}
	m_pTestModel->SameCubeColisionCheckEnd();

	Render();//アプリケーションの中身は現状レンダーのみ
	return BaseScene::Game;
}

void GameScene::InitModel()
{
	m_pTestModel = new MyPlayer;
	m_pTestModel->InitLv(1);
	for (int i = 0; i < EnemyNum; i++) {
		m_pEnemyModel[i] = new MyModel;
		m_pEnemyModel[i]->InitLv(i % 3 + 1);
		float Size = (m_pEnemyModel[i]->GetSize());
		if (i % 3 == 0) {
			m_pEnemyModel[i]->SetPos(0, 0, Size * (i+2));
		}
		else if (i % 3 == 1) {
			m_pEnemyModel[i]->SetPos(Size * (i + 3), 0, 0);
		}
		else {
			m_pEnemyModel[i]->SetPos(Size*(i + 1), 0, Size*(i + 1));
		}
	}
	m_pGround = new MyGround;
	m_pMoveUI = new MoveUI;

	InitPolygon();
	InitShader();
}

bool GameScene::ColisionA(MyModel* pModelA, MyModel* pModelB)
{
	if (Colision(pModelA, pModelB)) {
		return true;
	}
	return false;
}


bool GameScene::Colision(MyModel* pModelA, MyModel* pModelB)
{
	//D3DXVECTOR3 vLength = pModelB->GetCenter() - pModelA->GetCenter();
	//float fLength = D3DXVec3Length(&vLength);
	//float fModelArad = pModelA->GetSize() *0.49;//sqrt(pow(pModelA->GetSize(), 2) + pow(pModelA->GetSize(), 2))*0.49;
	//float fModelBrad = sqrt(pow(pModelB->GetSize(), 2) + pow(pModelB->GetSize(), 2))*0.49;
	//if (fLength < fModelArad + fModelBrad)
	//{
	//	return true;
	//}

	D3DXVECTOR3 vModelA = pModelA->GetCenter();
	D3DXVECTOR3 vModelB = pModelB->GetCenter();

	D3DXVECTOR2 vTopRightA;

	float SizeA = pModelA->GetSize() * 0.98;
	float SizeB = pModelB->GetSize() * 0.98;

	vTopRightA.x = vModelA.x + SizeA / 2.0f;
	vTopRightA.y = vModelA.z + SizeA / 2.0f;
	D3DXVECTOR2 vTopLeftA;
	vTopLeftA.x = vModelA.x - SizeA / 2.0f;
	vTopLeftA.y = vModelA.z + SizeA / 2.0f;
	D3DXVECTOR2 vUnderRightA;
	vUnderRightA.x = vModelA.x + SizeA / 2.0f;
	vUnderRightA.y = vModelA.z - SizeA / 2.0f;
	D3DXVECTOR2 vUnderLeftA;
	vUnderLeftA.x = vModelA.x - SizeA / 2.0f;
	vUnderLeftA.y = vModelA.z - SizeA / 2.0f;


	D3DXVECTOR2 vTopRightB;
	vTopRightB.x = vModelB.x + SizeB / 2.0f;
	vTopRightB.y = vModelB.z + SizeB / 2.0f;
	D3DXVECTOR2 vTopLeftB;
	vTopLeftB.x = vModelB.x - SizeB / 2.0f;
	vTopLeftB.y = vModelB.z + SizeB / 2.0f;
	D3DXVECTOR2 vUnderRightB;
	vUnderRightB.x = vModelB.x + SizeB / 2.0f;
	vUnderRightB.y = vModelB.z - SizeB / 2.0f;
	D3DXVECTOR2 vUnderLeftB;
	vUnderLeftB.x = vModelB.x - SizeB; // 2.0f;
	vUnderLeftB.y = vModelB.z - SizeB; // 2.0f;

	if (vTopLeftA.x < vUnderRightB.x && vTopLeftA.y > vUnderRightB.y
		&& vTopRightA.x > vUnderLeftB.x && vTopRightA.y > vUnderLeftB.y
		&& vUnderLeftA.x < vTopRightB.x && vUnderLeftA.y < vTopRightB.y
		&& vUnderRightA.x > vTopLeftB.x && vUnderRightA.y < vTopLeftB.y
		)
	{
		return true;
	}

	return false;
}

void GameScene::ReleaseModel()
{
	//m_pTestModel->m_Cube.Release();

	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pTestModel);

	//SAFE_DELETE_ARRAY(m_pEnemyModel);
	for (int i = 0; i < EnemyNum; i++) {
		SAFE_DELETE(m_pEnemyModel[i]);
	}

	SAFE_DELETE(m_pGround);
	SAFE_DELETE(m_pMoveUI);
}



HRESULT GameScene::InitShader()
{


	//hlslファイル読み込み　ブロブ作成　
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//ブロブからバーテックスシェーダーを作成

	int tmpnum;

	m_pTestModel->m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);

	for (int i = 0; i < EnemyNum; i++)
	{
		m_pEnemyModel[i]->m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	}

	m_pGround->m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pMoveUI->m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //この作業を行うのは　本来はシェーダーの情報をもとにレイアウトを作る必要がでてくるため、シェーダーごとに

	for (int i = 0; i < EnemyNum; i++) {
		m_pEnemyModel[i]->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	}
	m_pTestModel->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pGround->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pMoveUI->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);


	////頂点インプットレイアウトを定義
	////今回ここは VS_OUTPUTのレイアウトをもとに　　POSITION と UVになるTEXCOORDを設定

	//ブロブからピクセルシェーダー作成

	m_pTestModel->m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pTestModel->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	for (int i = 0; i < EnemyNum; i++)
	{
		m_pEnemyModel[i]->m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_pEnemyModel[i]->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);
	}

	m_pGround->m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pGround->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	m_pMoveUI->m_PixelShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pMoveUI->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);


	m_pTestModel->m_ConstantBuffer.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);


	//コンスタントバッファー作成　　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;//説明書
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPUにアクセスするフラグ設定
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//使用法

	m_pTestModel->m_ConstantBuffer.CreateConstantBuffer(cb);

	for (int i = 0; i < EnemyNum; i++)
	{
		m_pEnemyModel[i]->m_ConstantBuffer.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_pEnemyModel[i]->m_ConstantBuffer.CreateConstantBuffer(cb);
	}

	m_pGround->m_ConstantBuffer.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pGround->m_ConstantBuffer.CreateConstantBuffer(cb);

	m_pMoveUI->m_ConstantBuffer.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pMoveUI->m_ConstantBuffer.CreateConstantBuffer(cb);


	return S_OK;
}



HRESULT GameScene::InitPolygon()
{
	m_pTestModel->m_Cube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pTestModel->m_Cube.CreateVertexBuffer();
	m_pTestModel->m_Cube.CreateTexture("white.png");

	for (int i = 0; i < EnemyNum; i++) {
		m_pEnemyModel[i]->m_Cube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_pEnemyModel[i]->m_Cube.CreateVertexBuffer();
		m_pEnemyModel[i]->m_Cube.CreateTexture("red.jpg");
	}

	m_pGround->PosInit();
	m_pGround->m_Ground.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pGround->m_Ground.CreateVertexBuffer();
	m_pGround->m_Ground.CreateTexture("white.jpg");

	m_pMoveUI->MovePanelInit(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	return S_OK;
}




void GameScene::Render()
{
	float ClearColor[4] = { 0,0,0.0,1 }; //クリア色　RGBA

	//画面クリア
	g_pMain->m_pDeviceContext->ClearRenderTargetView(g_pMain->m_pBackBuffer_TexRTV, ClearColor);//カラー
	g_pMain->m_pDeviceContext->ClearDepthStencilView(g_pMain->m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//デプスステンシル

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;


	//Inputs
	//static MAIN::eMoveVec Vec = MAIN::eMoveVec;;None;

	

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, 0.0f, 0.0f, 0.0f);
	m_pCamera->SetCameraA(&mView, &mProjection, m_pTestModel->GetCameraTarget(), m_pTestModel->GetCameraMargin());




	m_pGround->Render(mView, mProjection);

	for (int i = 0; i < EnemyNum; i++)
	{
		m_pEnemyModel[i]->Render(mView, mProjection);
	}

	m_pTestModel->Render(mView, mProjection);

	if (UI_RenderFlg) {
		m_pMoveUI->Render(mView, mProjection, m_pTestModel->GetCenter(), m_pTestModel->GetSize() * 1.1, m_pCamera->GetWorldForward(), m_pTestModel->GetLV());
	}
	//g_pMain->m_pFPS->PrintFps(m_hWnd);

	g_pMain->m_pSwapChain->Present(0, 0);//画面更新

}


void GameScene::MoveUpdate(eMoveVec eVec)
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
		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalLeftVec);
		break;
	}
}


bool GameScene::MoveUpdateA(eMoveVec eVec)
{
	m_pCamera->UpDateWorldVec();
	D3DXVECTOR3 vLocalVec;
	switch (eVec)
	{
	case eMoveVec::None:
		//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);
		//UI_RenderFlg = true;
		return true;
	case eMoveVec::Forward:
		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
		return m_pTestModel->MoveA(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		return m_pTestModel->MoveA(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		return m_pTestModel->MoveA(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		return m_pTestModel->MoveA(g_pMain->m_pFPS->GetDeltaTime(), vLocalLeftVec);
	}

	return false;
}

void GameScene::Input() 
{

	int KeyStateCnt = 4;

	if (g_pMain->m_pFPS->DeltaReady())
	{
		if (GetKeyState('A') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Left)
			{
				m_eMoveVec = eMoveVec::Left;
				UI_RenderFlg = false;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Left) {
			}
			KeyStateCnt--;
		}

		if (GetKeyState('D') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Right)
			{
				m_eMoveVec = eMoveVec::Right;
				UI_RenderFlg = false;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Right) {
			}
			KeyStateCnt--;
		}
		if (GetKeyState('W') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Forward)
			{
				m_eMoveVec = eMoveVec::Forward;
				UI_RenderFlg = false;
			}

		}
		else {
			if (m_eMoveVec == eMoveVec::Forward) {

			}
			KeyStateCnt--;
		}
		if (GetKeyState('S') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Backward)
			{
				m_eMoveVec = eMoveVec::Backward;
				UI_RenderFlg = false;

			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Backward) {
			}
			KeyStateCnt--;
		}


		//上を常に見れるようにするか　元のターゲットまで戻すかの処理
		m_pCamera->UpDateLook(g_pMain->m_pFPS->GetDeltaTime(), m_pTestModel->GetSize());
		if (GetKeyState(VK_UP) & 0x80) {
			m_pCamera->LookUp(g_pMain->m_pFPS->GetDeltaTime(), m_pTestModel->GetSize());

		}
		if (GetKeyState(VK_DOWN) & 0x80) {
			m_pCamera->LookDown(g_pMain->m_pFPS->GetDeltaTime(), m_pTestModel->GetSize());
		}

		static bool bR = false;
		static bool bL = false;
		if (GetKeyState(VK_RIGHT) & 0x80) {
			//m_pCamera->RotRight(m_pFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				m_pCamera->RotRight(g_pMain->m_pFPS->GetDeltaTime());
				bR = true;
			}
		}
		else {
			if (m_eMoveVec == None)
			{
				bR = false;
			}
		}

		if (GetKeyState(VK_LEFT) & 0x80) {
			//m_pCamera->RotLeft(m_pFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				m_pCamera->RotLeft(g_pMain->m_pFPS->GetDeltaTime());
				bL = true;
			}
		}
		else {
			if (m_eMoveVec == None)
			{
				bL = false;
			}
		}

		bool check = MoveUpdateA(m_eMoveVec);
		if (check) {
			m_eMoveVec = eMoveVec::None;
		}

		//if (bL || bR) {
		//	UI_RenderFlg = false;
		//}
		/*else */if (KeyStateCnt == 0 && check) {
			UI_RenderFlg = true;
		}


		static bool flg = false;//レベルアップ確認用

		if (GetKeyState('E') & 0x80) {
			//m_pCamera->RotRight(m_pFPS->GetDeltaTime());
			if (!flg) {
				if (m_eMoveVec == None) {
					m_pTestModel->GlowStackCube(5);
					flg = true;
				}
			}
		}
		else if (flg) {
			flg = false;
		}
		static bool flg2 = false;

		if (GetKeyState('Q') & 0x80) {
			//m_pCamera->RotLeft(m_pFPS->GetDeltaTime());
			if (!flg2) {
				if (m_eMoveVec == None)
				{
					if (m_pTestModel->GetLV() >= 2) {
						m_pTestModel->Damage(1);
						flg2 = true;
					}
				}
			}
		}
		else if (flg2) {
			flg2 = false;
		}
	}
}

