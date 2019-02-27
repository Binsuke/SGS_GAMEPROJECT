#ifndef BASE_SCENE
#define BASE_SCENE

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <Windows.h>	
//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx�n��
#include <d3dx11.h>		
//d3dx�n��
#include <d3dcompiler.h>


class BaseScene {
public:
	enum eScene {//�����������@���v�����Ȃ�����
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