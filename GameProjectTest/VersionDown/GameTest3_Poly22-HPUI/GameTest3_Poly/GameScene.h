#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "BASE_SCENE.h"
#include "MyModel.h"
#include "Ground.h"
#include "Camera.h"
#include "MoveUI.h"

#include "FPS.h"

#include "Poly.h"

#include "Player.h"

#include "HPUI.h"

//extern MAIN* g_pMain;

class GameScene: public BaseScene {
public:
	GameScene();
	~GameScene();
	BaseScene::eScene App();
private:
	void Init();
	void Release();
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

	void MoveUpdate(eMoveVec Vec);

	bool MoveUpdateA(eMoveVec Vec);

	bool Colision(MyModel* pModelA, MyModel* pModelB);

	bool ColisionA(MyModel* pModelA, MyModel* pModelB);

	//void CheckSameLVPolygonColision();

	Camera* m_pCamera;
		void InitModel();//この辺はステージなんかを作った場合はシーンごとに分けてシーンにモデルを持たせて、初期化するようにするのがいいかな
	void ReleaseModel();


	eMoveVec m_eMoveVec;
	
	MyPlayer* m_pTestModel;
	enum {
		EnemyNum = 120,
	};
	MyModel* m_pEnemyModel[EnemyNum];
	MyGround* m_pGround;

	MoveUI* m_pMoveUI;

	MyHPUI* m_pHpUI;

	bool UI_RenderFlg;

	float view;
};

#endif