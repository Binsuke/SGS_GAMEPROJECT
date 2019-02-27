#include "MyModel.h"
#include <list>
#include "main.h"
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
	
private:
	enum eMoveVecEnemys {
		None,
		Forward,
		Backward,
		Left,
		Right,
	};

	void SelectMoveVectoPlayer();

	bool CheckCanMove(eMoveVecEnemys eLocalVec);
	bool CheckForward();
	bool CheckBackward();
	bool CheckLeft();
	bool CheckRight();
	bool m_bSearchPlayer;



	bool m_bThinkInitflg;

	DWORD dwThinkTime;


	struct LowEnemyData {
		D3DXVECTOR3 vPos;
		float size;
	};
	std::list<LowEnemyData> LowLevelOtherEnemyList;
	D3DXVECTOR3 m_vSearchPlayerPos;
};


#endif