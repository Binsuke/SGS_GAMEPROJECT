
#include "BASE_SCENE.h"
#include "MyModel.h"
#include "Ground.h"
#include "Camera.h"
#include "MoveUI.h"
#include "FPS.h"
#include "Poly.h"
#include "Player.h"
#include "HPUI.h"
#include "Enemy.h"

#include "MapData.h"
#include <vector>

#include "DangerUI.h"
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

//extern MAIN* g_pMain;

class GameScene: public BaseScene {
public:
	GameScene();
	~GameScene();
	BaseScene::eScene App();
	void Release();
private:
	void Init();
	//void InitD3D();
	void Render();
	HRESULT InitPolygon();
	HRESULT InitShader();

	enum eMoveVec {
		None = 0,
		Forward = 1,
		Backward = 2,
		Right = 3,
		Left = 4,
	};

	void Input();

	//void MoveUpdate(eMoveVec Vec);

	bool MoveUpdateA(eMoveVec Vec);

	//bool SamePosColision(MyModel* pModelA, MyModel* pModelB);

	bool Colision(MyModel* pModelA, MyModel* pModelB);

	bool ColisionA(MyModel* pModelA, MyModel* pModelB);

	//void CheckSameLVPolygonColision();

	Camera* m_pCamera;

	DangerUI* m_pDangerUI;

	void InitModel();//この辺はステージなんかを作った場合はシーンごとに分けてシーンにモデルを持たせて、初期化するようにするのがいいかな
	void ReleaseModel();


	eMoveVec m_eMoveVec;
	
	MyPlayer* m_pTestModel;
	enum {
		EnemyNumLV1 = 126,
		EnemyNumLV2 = 68,
		EnemyNumLV3 = 30,
		EnemyNumLV4 = 10,
		EnemyKing   = 1,
		EnemyNumMax = EnemyNumLV1 + EnemyNumLV2 + EnemyNumLV3 + EnemyNumLV4+ EnemyKing,
	};

	int EnemyIndex;
	int EnemyRenderIndex;
	//bool PresentFlg;
	//MyEnemy* m_pEnemyModel[EnemyNumMax];
	
	std::vector<MyEnemy*> m_pEnemyModel;
	int m_iNumEnemy;
	MyGround* m_pGround;

	MoveUI* m_pMoveUI;

	MyHPUI* m_pHpUI;

	MapData* m_pMapdata;

	bool UI_RenderFlg;

	float view;
};

#endif