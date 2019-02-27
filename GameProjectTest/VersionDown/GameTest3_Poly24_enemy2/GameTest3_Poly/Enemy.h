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
	void SearchPlayer(MyModel* pModel);
	void SearchOtherLowEnemy(MyEnemy* pModel);
	void RootAndMove(MyModel* pModel);

	bool CanThink();

	void MoveUpdate();

	void InitLv(int iLV);
	//void LVUp();
	int LVDown();
	
private:
	enum eMoveVecEnemys {
		None,
		Forward,
		Backward,
		Left,
		Right,
	};


	eMoveVecEnemys m_eMoveVec;
	void SelectMoveVectoPlayer();

	bool CheckCanMove(eMoveVecEnemys eLocalVec);
	bool CheckForward();
	bool CheckBackward();
	bool CheckLeft();
	bool CheckRight();
	bool m_bSearchPlayer;



	bool m_bThinkInitflg;

	DWORD dwThinkTime;

	int m_iThinkRand;
	struct LowEnemyData {
		D3DXVECTOR3 vPos;
		float size;
	};
	std::list<LowEnemyData> LowLevelOtherEnemyList;
	D3DXVECTOR3 m_vSearchPlayerPos;

	bool m_bDeadflg;


};


#endif