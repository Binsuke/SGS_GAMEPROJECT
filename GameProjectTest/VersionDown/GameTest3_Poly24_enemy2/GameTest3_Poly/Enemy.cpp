#include "Enemy.h"


MyEnemy::MyEnemy() : m_bSearchPlayer(false),m_bThinkInitflg(false),m_eMoveVec(None)
,m_bDeadflg(false)
{
	unsigned int now = (unsigned int)time(0);
	srand(now);
}
//プレイヤーを和してあげて　範囲内にプレイヤーがいるのかをサーチする
//見つけたらそのプレイヤーの位置を保存する
void MyEnemy::SearchPlayer(MyModel* pModel) {
	D3DXVECTOR3 vLength = this->GetCenter() - pModel->GetCenter();
	
	float Length = D3DXVec3Length(&vLength);

	if (Length <= (this->GetSize() * 5) + pModel->GetSize())
	{
		m_bSearchPlayer = true;
		m_vSearchPlayerPos = pModel->GetPos();
	}
}

//次に自分の周りに自分よりもレベルの低いキューブがいないかを検索
//周りにいたらそのデータをリストに保存
void MyEnemy::SearchOtherLowEnemy(MyEnemy* pModel) {
	D3DXVECTOR3 vLength = this->GetCenter() - pModel->GetCenter();
	float Length = D3DXVec3Length(&vLength);

	if (Length <= (this->GetSize() * 2) + pModel->GetSize())
	{
		LowEnemyData Pushtmp;
		Pushtmp.vPos = pModel->GetPos();
		Pushtmp.size = pModel->GetSize();
		LowLevelOtherEnemyList.push_back(Pushtmp);
	}
}

void MyEnemy::RootAndMove(MyModel* pModel)
{
	if (m_bSearchPlayer) {
		//プレイヤーに向かっていく
		SelectMoveVectoPlayer();
	}
	//DWORD select = timeGetTime();

	int selectvec = rand() % 4;//select % 4;

	if (selectvec == 0) {
		CheckCanMove(eMoveVecEnemys::Right);
	}
	if (selectvec == 1) {
		CheckCanMove(eMoveVecEnemys::Left);
	}
	if (selectvec == 2) {
		CheckCanMove(eMoveVecEnemys::Forward);
	}
	if (selectvec == 3) {
		CheckCanMove(eMoveVecEnemys::Backward);
	}
}


//プレイヤーが見つかっている時はこの関数を呼び出す
//これによってプレイヤーの位置に置いて
//進行方向を決める
//場合によっては動かない　本来は動こうと決定したルートが
//もしもダメだった場合は　別のルートを検索にしたかったが
//今できる範囲でやってみる
void MyEnemy::SelectMoveVectoPlayer() {
	eMoveVecEnemys MoveLR;
	if (this->GetPos().x < m_vSearchPlayerPos.x) {
		MoveLR = Right;
	}
	else if (this->GetPos().x > m_vSearchPlayerPos.x)
	{
		MoveLR = Left;
	}
	eMoveVecEnemys MoveFB;
	if (this->GetPos().z < m_vSearchPlayerPos.z) {
		MoveFB = Forward;
	}
	else if (this->GetPos().z > m_vSearchPlayerPos.z) {
		MoveFB = Backward;
	}

	float LRLength;
	if (MoveLR == Right) {
		 LRLength = m_vSearchPlayerPos.x - this->GetPos().x;
	}
	else if (MoveLR == Left) {
		LRLength = this->GetPos().x - m_vSearchPlayerPos.x;
	}

	float FBLength;
	if (MoveFB == Forward) {
		FBLength = m_vSearchPlayerPos.z - this->GetPos().z;
	}
	else if (MoveFB == Backward){
		FBLength = this->GetPos().z - m_vSearchPlayerPos.z;
	}

	if (LRLength >= FBLength) {
		if (!CheckCanMove(MoveLR)) {
			CheckCanMove(MoveFB);
		}
	}
	else {
		if (!CheckCanMove(MoveFB)) {
			CheckCanMove(MoveLR);
		}
	}
}

//進むベクトルごとにちぇっく関数を呼び出して　進むことができたらトゥルーを返す
bool MyEnemy::CheckCanMove(eMoveVecEnemys eLocalVec) {
	switch (eLocalVec) {
	case Forward:
		return CheckForward();
		break;
	case Backward:
		return CheckBackward();
		break;
	case Right:
		return CheckRight();
		break;
	case Left:
		return CheckLeft();
		break;
	}
	return false;
}

//自分より小さなキューブがいなければ　移動する
//自分より小さなキューブはSearchOtherLowEnemyでサーチする
//その後移動できるなら移動
bool MyEnemy::CheckForward() {
	bool Check = false;
	//移動中だったら動かない
	if (m_eMoveVec != None) {
		return false;
	}

	//前に進んだら　落ちる場合は進まない
	float CheckGround = this->GetCenter().z + this->GetSize();
	if (CheckGround > MyGround::Modelz * GroundPanel::PanelSize)
	{
		return false;
	}
	for (auto itr = LowLevelOtherEnemyList.begin(); itr != LowLevelOtherEnemyList.end(); itr++)
	{
		D3DXVECTOR3 vPos = itr->vPos;
		float size = itr->size;

		float LeftPos = this->GetCenter().x - this->GetSize() / 2.0f;
		float RightPos = this->GetCenter().x + this->GetSize() / 2.0f;

		float LowLeftPos = vPos.x - size / 2.0f;
		float LowRightPos = vPos.x + size / 2.0f;

		if (RightPos <= LowLeftPos && LeftPos >= RightPos) {
			float LowPosBack = vPos.z - size / 2.0f;
			float MovePos = this->GetCenter().z + this->GetSize() / 2.0f + this->GetSize();
			if (MovePos > LowPosBack) {
				
				Check = true;
				break;
				//this->AnimationLocalForwardR(g_pMain->m_pFPS->GetDeltaTime());
			}
		}
	}
	
	if (!Check) {
		m_eMoveVec = Forward;
		return true;
	}
	return false;
}

bool MyEnemy::CheckBackward() {
	bool Check = false;
	if (m_eMoveVec != None) {
		return false;
	}

	//落ちる場合は動かない
	float CheckGround = this->GetCenter().z - this->GetSize();
	if (CheckGround < 0)
	{
		return false;
	}

	for (auto itr = LowLevelOtherEnemyList.begin(); itr != LowLevelOtherEnemyList.end(); itr++)
	{
		D3DXVECTOR3 vPos = itr->vPos;
		float size = itr->size;

		float LeftPos = this->GetCenter().x - this->GetSize() / 2.0f;
		float RightPos = this->GetCenter().x + this->GetSize() / 2.0f;

		float LowLeftPos = vPos.x - size / 2.0f;
		float LowRightPos = vPos.x + size / 2.0f;

		if (RightPos <= LowLeftPos && LeftPos >= RightPos)
		{
			float LowPosForward = vPos.z + size / 2.0f;
			float MovePos = this->GetCenter().z - this->GetSize() / 2.0f - this->GetSize();
			if (MovePos < LowPosForward) {
				Check = true;
				break;
				//this->AnimationLocalBackwardR(g_pMain->m_pFPS->GetDeltaTime());
			}
		}
	}

	if (!Check) {
		//this->AnimationLocalBackwardR(g_pMain->m_pFPS->GetDeltaTime());
		m_eMoveVec = Backward;
		return true;
	}
	return false;
}


bool MyEnemy::CheckRight() {
	bool Check = false;
	if (m_eMoveVec != None) {
		return false;
	}
	float CheckGround = this->GetCenter().x + this->GetSize();
	if (CheckGround > MyGround::Modelx * GroundPanel::PanelSize)
	{
		return false;
	}
	for (auto itr = LowLevelOtherEnemyList.begin(); itr != LowLevelOtherEnemyList.end(); itr)
	{
		D3DXVECTOR3 vPos = itr->vPos;
		float size = itr->size;

		float ForwardPos = this->GetCenter().z + this->GetSize() / 2.0f;
		float BackwardPos = this->GetCenter().z - this->GetSize() / 2.0f;
		
		float LowForwardPos = vPos.z + size / 2.0f;
		float LowBackwardPos = vPos.z - size / 2.0f;

		if (ForwardPos <= LowBackwardPos && BackwardPos >= LowForwardPos) {
			float LowPosLeft = vPos.x - size / 2.0f;
			float MovePos = this->GetCenter().x + this->GetSize() / 2.0f + this->GetSize();
			if (LowPosLeft < MovePos) {//当たってたら
				Check = true;
				break;
			}
		}
	}
	if (!Check) {
		//this->AnimationLocalRightR(g_pMain->m_pFPS->GetDeltaTime());
		m_eMoveVec = Right;
		return true;
	}
	return false;
}

bool MyEnemy::CheckLeft()
{
	bool Check = false;
	if (m_eMoveVec != None) {
		return false;
	}
	//落ちるときは動かない
	float CheckGround = this->GetCenter().x - this->GetSize();
	if (CheckGround < 0)
	{
		return false;
	}
	for (auto itr = LowLevelOtherEnemyList.begin(); itr != LowLevelOtherEnemyList.end(); itr++)
	{
		D3DXVECTOR3 vPos = itr->vPos;
		float size = itr->size;
		float ForwardPos = this->GetCenter().z + this->GetSize() / 2.0f;
		float BackwardPos = this->GetCenter().z - this->GetSize() / 2.0f;

		float LowForwardPos = vPos.z + size / 2.0f;
		float LowBackwardPos = vPos.z - size / 2.0f;

		if (ForwardPos <= LowBackwardPos && BackwardPos >= LowForwardPos) {
			float LowPosRight = vPos.x + size / 2.0f;
			float MovePos = this->GetCenter().x - this->GetSize() / 2.0f - this->GetSize();
			if (LowPosRight > MovePos) {//当たってたら
				Check = true;
				break;
			}
		}

	}
	if (!Check) {
		//this->AnimationLocalLeftR(g_pMain->m_pFPS->GetDeltaTime());
		m_eMoveVec = Left;
		return true;
	}
	return false;
}

bool MyEnemy::CanThink() {
	if (!m_bThinkInitflg) {
		m_bThinkInitflg = true;
		dwThinkTime = timeGetTime();
		m_iThinkRand = rand() % 5;
	}
	//m_iLVはunsignedにするほうがいいかもとりあえずおいとく
	if (timeGetTime() - dwThinkTime >= (m_iLV * m_iThinkRand)* 1000) {//2秒＊レベルの時間思考停止する
		m_bThinkInitflg = false;
		return true;
	}
	return false;
}

void MyEnemy::MoveUpdate() {
	switch (m_eMoveVec) 
	{
	case None:
		break;
	case Forward:
		if (this->AnimationLocalForwardR(g_pMain->m_pFPS->GetDeltaTime()))
		{
			m_eMoveVec = None;
		}
		break;
	case Backward:
		if (this->AnimationLocalBackwardR(g_pMain->m_pFPS->GetDeltaTime()))
		{
			m_eMoveVec = None;
		}
		break;
	case Right:
		if (this->AnimationLocalRightR(g_pMain->m_pFPS->GetDeltaTime()))
		{
			m_eMoveVec = None;
		}
		break;
	case Left:
		if (this->AnimationLocalLeftR(g_pMain->m_pFPS->GetDeltaTime()))
		{
			m_eMoveVec = None;
		}
		break;
	}
}

int MyEnemy::LVDown() {
	if (m_bDeadflg) {
		return 0;
	}
	m_bDeadflg = true;

	int Exp = m_iLV * m_iLV * 2;
	if (m_iLV == 1) {
		Exp = 3;
	}
	m_bRenderflg = false;
	//m_iLV = 0;

	return Exp;
}

void MyEnemy::InitLv(int iLV) {
	if (iLV == 0) {
		return;
	}
	m_iLV = iLV;
	m_iModelSizeX = iLV * 2 - 1;
	m_iModelSizeY = iLV * 2 - 1;
	m_iModelSizeZ = iLV * 2 - 1;

	m_iModelHalfSizeX = iLV - 1;
	m_iModelHalfSizeY = iLV - 1;
	m_iModelHalfSizeZ = iLV - 1;


	for (int x = 0; x < (m_iModelSizeX ); x++)
	{
		for (int y = 0; y < (m_iModelSizeY); y++) {
			for (int z = 0; z < (m_iModelSizeZ); z++)
			{
				if (x == 0 || y == 0 || z == 0 || x == m_iModelSizeX -1 || y == m_iModelSizeY -1 || z == m_iModelSizeZ -1 ) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, (-m_fPolySize * iLV + ((x + 1)*m_fPolySize)), (-m_fPolySize * iLV + ((y + 1)*m_fPolySize)), (-m_fPolySize * iLV + ((z + 1)*m_fPolySize)));

					m_lmModelMat.push_back(tran);
				}
			}
		}
	}
	InitAdjustment();
	UpdateCenter();
}
