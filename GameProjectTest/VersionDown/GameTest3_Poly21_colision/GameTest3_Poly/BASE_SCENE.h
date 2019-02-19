#ifndef BASE_SCENE
#define BASE_SCENE

//ヘッダーファイルのインクルード
#include <Windows.h>	
//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>


class BaseScene {
public:
	enum eScene {//正直いい方法が思いつかなかった
		Game,
	};
	virtual BaseScene::eScene App() = 0;
protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	//virtual void InitD3D() = 0;
	bool m_bInitFlg;
};

#endif