#include "GameScene.h"
#include "main.h"


GameScene::GameScene() {
	m_bInitFlg = false;
	EnemyIndex = 0;
	
}
GameScene::~GameScene() {
	Release();
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

	m_pHpUI = new MyHPUI;
	m_pMapdata = new MapData;

	m_pMapdata->Init();

	m_pDangerUI = new DangerUI;
	m_pDangerUI->Init();

	m_pTimeUI = new TimeUI;
	m_pTimeUI->Init();

	InitModel();
	m_pCamera->InitCamera();
	m_pHpUI->Init();

	EndTime = 300;
}

void GameScene::Release() {
	ReleaseModel();
	m_bInitFlg = false;
}


//ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, IDXGISwapChain* pSwapChain, ID3D11RenderTargetView* pBackBuffer_TexRTV, ID3D11DepthStencilView* pBackBuffer_DSTexDSV, ID3D11Texture2D* pBackBuffer_DSTex, ID3D11BlendState* pBlendState
BaseScene::eScene GameScene::App()
{
	if (m_bInitFlg == false) {
		//Init(pDevice,pDeviceContext, pSwapChain, pBackBuffer_TexRTV, pBackBuffer_DSTexDSV, pBackBuffer_DSTex, pBlendState);
		Init();
		m_pTestModel->InitDamagePolygon(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_bInitFlg = true;
		PrevTime = timeGetTime();
		g_pMain->NumDamage = 0;
		g_pMain->Score = 0;
		g_pMain->NumTime = 0;
	}

	if (timeGetTime() - PrevTime > 1000) {
		EndTime--;
		PrevTime = timeGetTime();
		g_pMain->NumTime = EndTime;
		if (EndTime == 0) {
			return BaseScene::Result;
		}
	}

	Input();



	//for (int i = 0; i < m_iNumEnemy; i++) {
	//	if (m_pEnemyModel[i]->CanThink())
	//	{
	//		m_pEnemyModel[i]->RootAndMove(NULL);
	//	}
	//	m_pEnemyModel[i]->MoveUpdate();

	//	if (m_pEnemyModel[i]->GetLV() > 1 && m_pEnemyModel[i]->GetLV() == m_pTestModel->GetLV()) {
	//		if (m_pEnemyModel[i]->Colision(m_pTestModel)) {
	//			m_pEnemyModel[i]->ReverceOn();
	//		}
	//	}
	//	//m_pEnemyModel[i]->GroundCheck(g_pMain->m_pFPS->GetDeltaTime());
	//}

	//フレームレートが一気に下がってるから
	//軽量化の方法としては1フレームで全部の処理を行ってるのが原因だと思う
	//1フレーム内でfor分を回しまくってるから、こういうことになってる
	//仮にフレームを60で固定にするとして一回のフレームでやる処理を減らしてあげるなり
	//そういう作りをしないと、どんどんフレームが落ちていく
	//仮にAIと敵の当たり判定を作るってなったらさらにやばいことになりそう
	m_pMapdata->ClearMapData();
	for (int i = 0; i < m_iNumEnemy; i++)
	{
		if (m_pEnemyModel[i]->isDead() == false) {
			m_pMapdata->SetMapData(i, m_pEnemyModel[i]->GetPos(), m_pEnemyModel[i]->GetCubeNum());
		}
	}

	/*for (int i = 0; i < m_iNumEnemy; i++) {
		if (m_pEnemyModel[i]->isDead() == false) {
			if (m_pEnemyModel[i]->CanThink()) {
				if (m_pEnemyModel[i]->GetLV() == m_pTestModel->GetLV() + 1 || m_pEnemyModel[i]->GetLV() == 6 && m_pTestModel->GetLV() >= 4) {
					m_pEnemyModel[i]->SearchPlayer(m_pTestModel);
				}
				m_pEnemyModel[i]->SelectMove();
			}
			if (m_pEnemyModel[i]->isMoveCheck()) {
				MyEnemy::eMoveVecEnemys Vec = m_pEnemyModel[i]->GetMoveVec();
				switch (Vec) {
				case MyEnemy::Forward:
					if (!m_pMapdata->CanMoveForward(i,m_pEnemyModel[i]->GetCubeNum())) {
						m_pEnemyModel[i]->MoveIsEnable();
					}
					break;
				case MyEnemy::Backward:
					if (!m_pMapdata->CanMoveBackward(i, m_pEnemyModel[i]->GetCubeNum())) {
						m_pEnemyModel[i]->MoveIsEnable();
					}
					break;
				case MyEnemy::Left:
					if (!m_pMapdata->CanMoveLeft(i, m_pEnemyModel[i]->GetCubeNum())) {
						m_pEnemyModel[i]->MoveIsEnable();
					}
					break;
				case MyEnemy::Right:
					if (!m_pMapdata->CanMoveBackward(i, m_pEnemyModel[i]->GetCubeNum())) {
						m_pEnemyModel[i]->MoveIsEnable();
					}
					break;
				}
			}
			m_pEnemyModel[i]->MoveUpdate();
		}
	}*/
	for (int OneFrame = 0; OneFrame < 10; OneFrame++) {
		if (m_pEnemyModel[EnemyIndex]->isDead() == false) {
			std::queue<int> IndexBuffer;
			float LeftX = m_pEnemyModel[EnemyIndex]->GetCenter().x - m_pEnemyModel[EnemyIndex]->GetSize();
			float RightX = m_pEnemyModel[EnemyIndex]->GetCenter().x + m_pEnemyModel[EnemyIndex]->GetSize();
			float ForwardZ = m_pEnemyModel[EnemyIndex]->GetCenter().z + m_pEnemyModel[EnemyIndex]->GetSize();
			float BackwardZ = m_pEnemyModel[EnemyIndex]->GetCenter().z - m_pEnemyModel[EnemyIndex]->GetSize();
			m_pMapdata->GetMapData(&IndexBuffer, LeftX, RightX, ForwardZ, BackwardZ);
			while (!IndexBuffer.empty()) {
				int Index = IndexBuffer.front();
				IndexBuffer.pop();
				if (m_pEnemyModel[EnemyIndex]->GetAnimeFlg() == false) {
					if (EnemyIndex != Index) {
						if (m_pEnemyModel[EnemyIndex]->Colision(m_pEnemyModel[Index]))
						{
							m_pEnemyModel[EnemyIndex]->ColisionFalse();
							m_pEnemyModel[EnemyIndex]->SelectMove();
						}
					}
				}
			}
		}
		EnemyIndex++;
		EnemyIndex = EnemyIndex % m_iNumEnemy;
	}
	for (int i = 0; i < m_iNumEnemy; i++) {
		if (m_pEnemyModel[i]->isDead() == false) {
			
			if (m_pEnemyModel[i]->CanThink()) {
				if (m_pEnemyModel[i]->GetLV() == m_pTestModel->GetLV() + 1 || m_pEnemyModel[i]->GetLV() == 6 && m_pTestModel->GetLV() >= 4) {
					m_pEnemyModel[i]->SearchPlayer(m_pTestModel);
				}
				m_pEnemyModel[i]->SelectMove();
				
			}
			if (m_pEnemyModel[i]->GetColisionFlg() == false)
			{
				bool debug = false;
			}
			if (m_pEnemyModel[i]->isMoveCheck()) {
				std::queue<int> IndexBuffer;
				float LeftX = m_pEnemyModel[i]->GetCenter().x - m_pEnemyModel[i]->GetSize() * 2;
				float RightX = m_pEnemyModel[i]->GetCenter().x + m_pEnemyModel[i]->GetSize() * 2;
				float ForwardZ = m_pEnemyModel[i]->GetCenter().z + m_pEnemyModel[i]->GetSize() * 2;
				float BackwardZ = m_pEnemyModel[i]->GetCenter().z - m_pEnemyModel[i]->GetSize() * 2;
				m_pMapdata->GetMapData(&IndexBuffer, LeftX, RightX, ForwardZ, BackwardZ);
				while (!IndexBuffer.empty()) {
					int Index = IndexBuffer.front();
					IndexBuffer.pop();
					if (i != Index) {
						if (m_pEnemyModel[i]->GetColisionFlg()) {
							if (m_pEnemyModel[i]->Colision(m_pEnemyModel[Index])) {
								m_pEnemyModel[i]->ReverceOn();
							}
						}
					}
				}
				m_pEnemyModel[i]->MoveUpdate();//動く

				//動いたらデータを更新
			}

			//同じサイズの敵が動いたときにプレイヤーと当たったら
			if (m_pEnemyModel[i]->GetLV() != 1) {
				if (m_pEnemyModel[i]->GetLV() == m_pTestModel->GetLV()) {
					if (m_pEnemyModel[i]->Colision(m_pTestModel)) {
						m_pEnemyModel[i]->ReverceOn();
					}
				}
			}
			m_pMapdata->SetMapData(i, m_pEnemyModel[i]->GetPos(), m_pEnemyModel[i]->GetCubeNum());
		}
	}

	

	std::queue<int> IndexBuffer;


	//判定が行われないことがあって、原因がもしかしたらフロートのサイズの掛け算による
	//桁落ちなのでは？と考えて試してみる
	float LeftX = m_pTestModel->GetCenter().x - m_pTestModel->GetSize() * 2;
	float RightX = m_pTestModel->GetCenter().x + m_pTestModel->GetSize() * 2;
	float ForwardZ = m_pTestModel->GetCenter().z + m_pTestModel->GetSize() * 2;
	float BackwardZ = m_pTestModel->GetCenter().z - m_pTestModel->GetSize() * 2;
	m_pMapdata->GetMapData(&IndexBuffer, LeftX, RightX, ForwardZ, BackwardZ);

	while (!IndexBuffer.empty()) {
		int Index = IndexBuffer.front();
		IndexBuffer.pop();
		if (m_pTestModel->GetDamegaFlg() == false && m_pEnemyModel[Index]->isDead() == false) {
			//レベルが高ければ、当たったときにスタックを増やす
			if (m_pTestModel->GetLV() >= m_pEnemyModel[Index]->GetLV()) {
				if (m_pTestModel->Colision(m_pEnemyModel[Index])) {
					m_pTestModel->GlowStackCube(m_pEnemyModel[Index]->LVDown());
				}
			}//同じサイズの時は当たる
			//else if (m_pTestModel->GetLV() == 1 && m_pEnemyModel[Index]->GetLV() == 1) {
			//	if (m_pTestModel->Colision(m_pEnemyModel[Index])) {
			//		m_pTestModel->GlowStackCube(m_pEnemyModel[Index]->LVDown());
			//	}
			//}//サイズが同じだったら　リバース
			//else if (m_pTestModel->GetLV() == m_pEnemyModel[Index]->GetLV()) {
			//	if (m_pTestModel->Colision(m_pEnemyModel[Index])) {
			//		m_pTestModel->ReverceOn();
			//	}
			//}
			else {//それ以外（相手のほうがレベルが高い時
				if (m_pTestModel->Colision(m_pEnemyModel[Index])) {
					m_pTestModel->Damage(m_pEnemyModel[Index]->GetLV());
					m_pTestModel->ReverceOn();
					g_pMain->NumDamage++;
				}
			}
		}
	}

	//for (int i = 0; i < m_iNumEnemy && m_pTestModel->GetDamegaFlg() == false; i++) {
	//	//if (m_pTestModel->GetDamegaFlg() == false) {
	//		if (m_pTestModel->GetLV() > m_pEnemyModel[i]->GetLV()) {
	//			if (m_pTestModel->Colision(m_pEnemyModel[i])) {
	//				m_pTestModel->GlowStackCube(m_pEnemyModel[i]->LVDown());
	//			}
	//		}
	//		else if (m_pTestModel->GetLV() == 1 && m_pEnemyModel[i]->GetLV() == 1) {
	//			if (m_pTestModel->Colision(m_pEnemyModel[i])) {
	//				m_pTestModel->GlowStackCube(m_pEnemyModel[i]->LVDown());
	//			}
	//		}
	//		else if (m_pTestModel->GetLV() == m_pEnemyModel[i]->GetLV()) {
	//			if (m_pTestModel->Colision(m_pEnemyModel[i])) {
	//				m_pTestModel->ReverceOn();
	//			}
	//		}
	//		else{
	//			if (m_pTestModel->Colision(m_pEnemyModel[i])) {
	//				m_pTestModel->Damage(m_pEnemyModel[i]->GetLV());
	//				m_pTestModel->ReverceOn();
	//			}
	//		}
	//	//}
	//}


	//本当はレベルアップの時に同じレベルの敵のポインターをスタックしておいてそれを渡す
	//if(m_pTestModel->GetDamegaFlg==false)
	for (int i = 0; i < m_iNumEnemy && m_pTestModel->GetDamegaFlg() == false; i++) {
		m_pTestModel->SameCubeColisionCheck(m_pEnemyModel[i]);
	}
	
	if (m_pTestModel->GroundCheck(g_pMain->m_pFPS->GetDeltaTime()))
	{
		m_eMoveVec = eMoveVec::None;
		m_pTestModel->Damage(m_pTestModel->GetLV());
	}

	m_pTestModel->SameCubeColisionCheckEnd();

	if (m_pEnemyModel[0]->isDead()) {
		return BaseScene::Result;
	}
	
	if (m_pTestModel->CheckPlayerDead() == -1) {
		//リザルトに行く
		return BaseScene::Result;
	}
	Render();//アプリケーションの中身は現状レンダーのみ
	return BaseScene::Game;
}

void GameScene::InitModel()
{
	//SearchComment SearchCom
	m_pTestModel = new MyPlayer;
	m_pTestModel->InitLv(1);
	D3DXVECTOR3 Pos(0,0,0);
	Pos.x += m_pTestModel->GetSize() * 10;
	Pos.z += m_pTestModel->GetSize() * 10;
	m_pTestModel->SetPos(Pos);
	m_iNumEnemy = m_pMapdata->GetNumModels();
	m_pEnemyModel.resize(m_iNumEnemy);

	//本来はマックスレベルを受け取って　ベクター型でキューの配列を作って
	//レベルごとに配置してあげるのがいいんだけど。。。
	std::queue<nsModelData::EnemyModelInitData> LV1Que;
	std::queue<nsModelData::EnemyModelInitData> LV2Que;
	std::queue<nsModelData::EnemyModelInitData> LV3Que;
	std::queue<nsModelData::EnemyModelInitData> LV4Que;
	std::queue<nsModelData::EnemyModelInitData> KingQue;
	for (int i = 0; i < m_iNumEnemy; i++)
	{
		nsModelData::EnemyModelInitData tmp;
		m_pMapdata->GetInitEnemyData(&tmp);
		switch (tmp.iLV) {
		case 1:
			LV1Que.push(tmp);
			break;
		case 2:
			LV2Que.push(tmp);
			break;
		case 3:
			LV3Que.push(tmp);
			break;
		case 4:
			LV4Que.push(tmp);
			break;
		case 6:
			KingQue.push(tmp);
			break;
		}
	}
	int Cnt = 0;
	while (!KingQue.empty()) {
		m_pEnemyModel[Cnt] = new MyEnemy;
		m_pEnemyModel[Cnt]->InitLv(KingQue.front().iLV);
		m_pEnemyModel[Cnt]->SetPos(KingQue.front().vPos);
		KingQue.pop();
		Cnt++;
	}
	while (!LV4Que.empty()) {
		m_pEnemyModel[Cnt] = new MyEnemy;
		m_pEnemyModel[Cnt]->InitLv(LV4Que.front().iLV);
		m_pEnemyModel[Cnt]->SetPos(LV4Que.front().vPos);
		LV4Que.pop();
		Cnt++;
	}
	while (!LV3Que.empty()) {
		m_pEnemyModel[Cnt] = new MyEnemy;
		m_pEnemyModel[Cnt]->InitLv(LV3Que.front().iLV);
		m_pEnemyModel[Cnt]->SetPos(LV3Que.front().vPos);
		LV3Que.pop();
		Cnt++;
	}

	while (!LV2Que.empty()) {
		m_pEnemyModel[Cnt] = new MyEnemy;
		m_pEnemyModel[Cnt]->InitLv(LV2Que.front().iLV);
		m_pEnemyModel[Cnt]->SetPos(LV2Que.front().vPos);
		LV2Que.pop();
		Cnt++;
	}

	while (!LV1Que.empty()) {
		m_pEnemyModel[Cnt] = new MyEnemy;
		m_pEnemyModel[Cnt]->InitLv(LV1Que.front().iLV);
		m_pEnemyModel[Cnt]->SetPos(LV1Que.front().vPos);
		LV1Que.pop();
		Cnt++;
	}
	
	
	
	
	/*for (int i = 0; i < m_iNumEnemy; i++) {
		m_pEnemyModel[i] = new MyEnemy;
		nsModelData::EnemyModelInitData tmp;
		m_pMapdata->GetInitEnemyData(&tmp);
		m_pEnemyModel[i]->InitLv(tmp.iLV);
		m_pEnemyModel[i]->SetPos(tmp.vPos);
		m_pMapdata->SetInitMapData(i, m_pEnemyModel[i]->GetPos(), m_pEnemyModel[i]->GetCubeNum());
	}
*/
	int ErrorIndex;
	/*while (m_pMapdata->SortAndIndexCheck(&ErrorIndex)) {
		D3DXVECTOR3 Pos;
		m_pMapdata->isErrorNotIndextoRePositioningResize(&Pos,ErrorIndex);
		delete m_pEnemyModel[ErrorIndex];
		m_pEnemyModel[ErrorIndex] = new MyEnemy;
		m_pEnemyModel[ErrorIndex]->InitLv(1);
		m_pEnemyModel[ErrorIndex]->SetPos(Pos);

	}*/
	//if (m_pMapdata->SortAndIndexCheck(&ErrorIndex)) {
		//char testString[256];
		//sprintf_s(testString, "IndexNum = %d,x =%.5f z = %.5f",ErrorIndex,m_pEnemyModel[ErrorIndex]->GetPos().x ,m_pEnemyModel[ErrorIndex]->GetPos().z);
		//MessageBoxA(g_pMain->m_hWnd, testString, "", MB_OK);
	//}

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
//
//bool GameScene::SamePosColision(MyModel* pModelA, MyModel* pModelB) {
//	D3DXVECTOR3 vModelA = pModelA->GetCenter();
//	D3DXVECTOR3 vModelB = pModelB->GetCenter();
//
//	D3DXVECTOR2 vTopRightA;
//
//	float SizeA = pModelA->GetSize() * 0.98;
//	float SizeB = pModelB->GetSize() * 0.98;
//
//	vTopRightA.x = vModelA.x + SizeA / 2.0f;
//	vTopRightA.y = vModelA.z + SizeA / 2.0f;
//	D3DXVECTOR2 vTopLeftA;
//	vTopLeftA.x = vModelA.x - SizeA / 2.0f;
//	vTopLeftA.y = vModelA.z + SizeA / 2.0f;
//	D3DXVECTOR2 vUnderRightA;
//	vUnderRightA.x = vModelA.x + SizeA / 2.0f;
//	vUnderRightA.y = vModelA.z - SizeA / 2.0f;
//	D3DXVECTOR2 vUnderLeftA;
//	vUnderLeftA.x = vModelA.x - SizeA / 2.0f;
//	vUnderLeftA.y = vModelA.z - SizeA / 2.0f;
//
//
//	D3DXVECTOR2 vTopRightB;
//	vTopRightB.x = vModelB.x + SizeB / 2.0f;
//	vTopRightB.y = vModelB.z + SizeB / 2.0f;
//	D3DXVECTOR2 vTopLeftB;
//	vTopLeftB.x = vModelB.x - SizeB / 2.0f;
//	vTopLeftB.y = vModelB.z + SizeB / 2.0f;
//	D3DXVECTOR2 vUnderRightB;
//	vUnderRightB.x = vModelB.x + SizeB / 2.0f;
//	vUnderRightB.y = vModelB.z - SizeB / 2.0f;
//	D3DXVECTOR2 vUnderLeftB;
//	vUnderLeftB.x = vModelB.x - SizeB / 2.0f;
//	vUnderLeftB.y = vModelB.z - SizeB / 2.0f;
//
//	if (vTopLeftA.x < vUnderRightB.x && vTopLeftA.y > vUnderRightB.y
//		&& vTopRightA.x > vUnderLeftB.x && vTopRightA.y > vUnderLeftB.y
//		&& vUnderLeftA.x < vTopRightB.x && vUnderLeftA.y < vTopRightB.y
//		&& vUnderRightA.x > vTopLeftB.x && vUnderRightA.y < vTopLeftB.y
//		)
//	{
//		return true;
//	}
//
//	return false;
//
//}

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
	for (int i = 0; i < m_iNumEnemy; i++) {
		SAFE_DELETE(m_pEnemyModel[i]);
	}

	SAFE_DELETE(m_pGround);
	SAFE_DELETE(m_pMoveUI);

	SAFE_DELETE(m_pHpUI);
	SAFE_DELETE(m_pMapdata);

	SAFE_DELETE(m_pDangerUI);

	SAFE_DELETE(m_pTimeUI);
}



HRESULT GameScene::InitShader()
{


	//hlslファイル読み込み　ブロブ作成　
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//ブロブからバーテックスシェーダーを作成

	int tmpnum;

	m_pTestModel->m_VertexShader.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);


	//バーテックスシェーダーは正直使いまわしでいいし
	//同じバーテックスシェーダーの場合は使いまわすようにバーテックスシェーダーユーティリティを
	//作り変えたい。ただ時間がないのでこのまま
	for (int i = 0; i < m_iNumEnemy; i++)
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

	for (int i = 0; i < m_iNumEnemy; i++) {
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

	for (int i = 0; i < m_iNumEnemy; i++)
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

	for (int i = 0; i < m_iNumEnemy; i++)
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

	for (int i = 0; i < m_iNumEnemy; i++) {
		m_pEnemyModel[i]->m_Cube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
		m_pEnemyModel[i]->m_Cube.CreateVertexBuffer();
		m_pEnemyModel[i]->m_Cube.CreateTexture("red.jpg");
	}
	m_pEnemyModel[0]->m_KingCube.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pEnemyModel[0]->m_KingCube.CreateVertexBuffer();
	m_pEnemyModel[0]->m_KingCube.CreateTexture("King.png");

	m_pGround->PosInit();
	m_pGround->m_Ground.Init(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	m_pGround->m_Ground.CreateVertexBuffer();
	m_pGround->m_Ground.CreateTexture("ground.png");

	m_pMoveUI->MovePanelInit(g_pMain->m_pDevice, g_pMain->m_pDeviceContext);
	return S_OK;
}




void GameScene::Render()
{
	float ClearColor[4] = { 0,0,0.1 }; //クリア色　RGBA

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

	m_pEnemyModel[0]->RenderKing(mView, mProjection);
	m_pDangerUI->RenderKing(mView, mProjection, m_pEnemyModel[0]->GetCenter(), m_pEnemyModel[0]->GetSize());
	for (int i = 1; i < m_iNumEnemy; i++)
	{
		m_pEnemyModel[i]->Render(mView, mProjection);
		if (m_pEnemyModel[i]->GetLV() > m_pTestModel->GetLV()) {
			m_pDangerUI->Render(mView, mProjection, m_pEnemyModel[i]->GetCenter(), m_pEnemyModel[i]->GetSize());
		}
	}

	m_pTestModel->Render(mView, mProjection);

	if (UI_RenderFlg) {
		m_pMoveUI->Render(mView, mProjection, m_pTestModel->GetCenter(), m_pTestModel->GetSize() * 1.1, m_pCamera->GetWorldForward(), m_pTestModel->GetLV());
	}
	//g_pMain->m_pFPS->PrintFps(m_hWnd);

	//m_pHPUI->Render();

	m_pHpUI->Render(g_pMain->m_pFPS->GetDeltaTime());

	m_pHpUI->RenderStackCubeNum(m_pTestModel->GetCubeStack());

	m_pHpUI->RenderNextCubeNum(m_pTestModel->GetNextLevel());

	m_pTimeUI->RenderTime(EndTime);

	g_pMain->m_pSwapChain->Present(0, 0);//画面更新

}

//
//void GameScene::MoveUpdate(eMoveVec eVec)
//{
//	m_pCamera->UpDateWorldVec();
//	D3DXVECTOR3 vLocalVec;
//	switch (eVec)
//	{
//		//case eMoveVec::None:
//			//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);
//
//	case eMoveVec::Forward:
//		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
//		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
//		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
//		break;
//	case eMoveVec::Backward:
//		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
//		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
//		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
//		break;
//	case eMoveVec::Right:
//		//D3DXVECTOR3 vLocalRightVec(0,0,0);
//		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
//		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalVec);
//		break;
//	case Left:
//		D3DXVECTOR3 vLocalLeftVec;
//		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
//		m_pTestModel->Move(g_pMain->m_pFPS->GetDeltaTime(), vLocalLeftVec);
//		break;
//	}
//}


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

		//debug用
		//static bool flg = false;//レベルアップ確認用

		//if (GetKeyState('E') & 0x80) {
		//	//m_pCamera->RotRight(m_pFPS->GetDeltaTime());
		//	if (!flg) {
		//		if (m_eMoveVec == None) {
		//			m_pTestModel->GlowStackCube(5);
		//			flg = true;
		//		}
		//	}
		//}
		//else if (flg) {
		//	flg = false;
		//}
		//static bool flg2 = false;

		//if (GetKeyState('Q') & 0x80) {
		//	//m_pCamera->RotLeft(m_pFPS->GetDeltaTime());
		//	if (!flg2) {
		//		if (m_eMoveVec == None)
		//		{
		//			if (m_pTestModel->GetLV() >= 2) {
		//				m_pTestModel->Damage(1);
		//				flg2 = true;
		//			}
		//		}
		//	}
		//}
		//else if (flg2) {
		//	flg2 = false;
		//}
	}

	if (GetKeyState(VK_SPACE) & 0x80) {
		char testString[256];
		sprintf_s(testString, "%d", m_pTestModel->GetCubeStack());
		MessageBox(g_pMain->m_hWnd, testString, "test", 0);
	}

}

