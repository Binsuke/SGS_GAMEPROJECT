#include "Enemy.h"


MyEnemy::MyEnemy() : m_bSearchPlayer(false),m_bThinkInitflg(false){

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
}

//自分より小さなキューブがいなければ　移動する
//自分より小さなキューブはSearchOtherLowEnemyでサーチする
//その後移動できるなら移動
bool MyEnemy::CheckForward() {
	bool Check = false;
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
		this->AnimationLocalForwardR(g_pMain->m_pFPS->GetDeltaTime());
		return true;
	}
	return false;
}

bool MyEnemy::CheckBackward() {
	bool Check = false;
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
		this->AnimationLocalBackwardR(g_pMain->m_pFPS->GetDeltaTime());
		return true;
	}
	return false;
}


bool MyEnemy::CheckRight() {
	bool Check = false;
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
		this->AnimationLocalRightR(g_pMain->m_pFPS->GetDeltaTime());
		return true;
	}
	return false;
}

bool MyEnemy::CheckLeft()
{
	bool Check = false;
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
		this->AnimationLocalLeftR(g_pMain->m_pFPS->GetDeltaTime());
		return true;
	}
	return false;
}

bool MyEnemy::CanThink() {
	if (!m_bThinkInitflg) {
		m_bThinkInitflg = true;
		dwThinkTime = timeGetTime();
	}

	if (timeGetTime() - dwThinkTime >= m_iLV * 2000) {//2秒＊レベルの時間思考停止する
		m_bThinkInitflg = false;
		return true;
	}
	return false;
}