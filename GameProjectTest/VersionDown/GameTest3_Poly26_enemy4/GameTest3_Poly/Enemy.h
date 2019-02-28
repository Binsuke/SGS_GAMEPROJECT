#include "MyModel.h"
#include <list>
#include "main.h"
#include <stdio.h>
#include <time.h>
#ifndef ENEMY_H
#define ENEMY_H

class MyEnemy : public MyModel 
{
public:

	MyEnemy();
	
	bool CanThink();
	
	void SelectMove();

	void MoveIsEnable();

	bool isMoveCheck();

	bool isDead() { return m_bDeadflg; }

	void InitLv(int iLV);
	//void LVUp();
	int LVDown();

	void SearchPlayer(MyModel* pModel);


	enum eMoveVecEnemys {
		None,
		Forward,
		Backward,
		Left,
		Right,
	};

	eMoveVecEnemys GetMoveVec() { return m_eMoveVec; }

	bool GetAnimeFlg() { return m_bAnimeFlg; }

	void ColisionFalse() { m_bColision = false; }

	bool GetColisionFlg() { return m_bColision; }

	//これは使わない
	void SearchOtherLowEnemy(MyEnemy* pModel);
	void RootAndMove();
	void MoveUpdate();
	
private:
	
	void SelecMoveToPlayerA();




	eMoveVecEnemys m_eMoveVec;
	void SelectMoveVectoPlayer();


	//これも使わない
	bool CheckCanMove(eMoveVecEnemys eLocalVec);
	bool CheckForward();
	bool CheckBackward();
	bool CheckLeft();
	bool CheckRight();
	bool m_bSearchPlayer;


	bool m_bColision;


	bool m_bThinkInitflg;

	DWORD dwThinkTime;

	int m_iThinkRand;
	struct LowEnemyData {
		D3DXVECTOR3 vPos;
		float size;
	};

	//作り変える　仮にこの方法でやるにしても、ここはキューにしたほうがいい
	std::list<LowEnemyData> LowLevelOtherEnemyList;
	D3DXVECTOR3 m_vSearchPlayerPos;

	bool m_bDeadflg;


};


#endif