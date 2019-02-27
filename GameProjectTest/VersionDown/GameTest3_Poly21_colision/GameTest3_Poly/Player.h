#ifndef PLAYER_H
#define PLAYER_H

#include "MyModel.h"

class MyPlayer : public MyModel {
public:
	MyPlayer();
	//~MyPlayer();
	void GlowStackCube(int CubeNum);
	bool Damage(int iLV);

	void Render(D3DXMATRIX view, D3DXMATRIX proj);

	bool GetDamegaFlg();

	void InitDamagePolygon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	void SameCubeColisionCheck(MyModel* pModel);
	void SameCubeColisionCheckEnd();

	int GetCubeStack() { return m_iCubeStack; }
	int GetNextLevel() { return m_iNextLevel; }
private:
	bool GlowInitFlg;
	int m_iNextLevel;
	int m_iCubeStack;
	
	bool m_bDamageInitFlg;
	bool m_bDamageFlg;

	bool m_bDamageEndFlg;
	float m_fDamageAnimationTime;

	bool m_bGlowFlg;

	DWORD m_dwDamageAnimationWaitTime;

	float m_fPrevAnimTime;

	MyPoly::Poly m_DamageCube;

	void DamageRender(D3DXMATRIX view, D3DXMATRIX proj);

};
#endif