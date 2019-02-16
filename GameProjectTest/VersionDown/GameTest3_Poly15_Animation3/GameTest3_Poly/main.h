#pragma once
#pragma once
#ifndef MAIN_H
#define MAIN_H
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
//�V�F�[�_�[�t�@�C���̓ǂݍ��݊֘A�������Ă��͂�
#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"

#include "MyModel.h"
#include "Ground.h"
#include "Camera.h"
#include "MoveUI.h"

#include "FPS.h"
//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�x����\��
#pragma warning(disable:4305)
//#pragma warning(disable:4005)

//�萔��`
#ifndef WINDOW_SIZE
#define WINDOW_SIZE
#define WINDOW_WIDTH	640 //window ��
#define WINDOW_HEIGHT	480 //window����
#define APP_NAME L"�e�N�X�`���[�𒣂�"
#endif
//�}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //�n���ꂽ�I�u�W�F�N�g�̃����[�X�֐����Ăяo���Ă��̂��Ƃ�NULL�����Ă���

													//�}�N���ōs���Ă��邯�ǁA�e���v���[�g�ōs���ق��������Ƃ͎v��
#endif SAFE_RELEASE

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
#endif
//class MAIN
//MAIN �N���X

class MAIN
{
public:
	MAIN();
	~MAIN();
	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT InitD3D();
	HRESULT InitPolygon();
	HRESULT InitShader();

	void Loop();
	void App();
	void Render();
	void DestroyD3D();

	HWND m_hWnd;				//�E�B���h�E�n���h���@�E�B���h�E���������߂̂���
	ID3D11Device* m_pDevice;	//D3D11�f�o�C�X�̖{�́@����ɃA�N�Z�X���Ă��낢��ȑ�����s��
	ID3D11DeviceContext* m_pDeviceContext;	//��̃f�o�C�X�Ǝ����悤�Ȋ����̂��́@��������V�F�[�_�[�Ȃǂ̏��������ۂɎg���Ă����͂�
	IDXGISwapChain* m_pSwapChain;			//�X���b�v�`�F�[���@�f���A���o�b�t�@�ɂ���ĉ�ʂ̂���������炷���߂ɍ�����̃o�b�t�@���������߂̂��̂���
											//�`��̍Ō�ɃX���b�v���Ă����邱�Ƃɂ���ă_�u���o�b�t�@����������
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;	//�X���b�v�`�F�[���Ŏg�����߂̃o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g�����߂邽�߂̃r���[
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;	//�X���b�v�`�F�[���Ŏg�����߂̃o�b�N�o�b�t�@�[�̐[�x�o�b�t�@�[�@Z�e�X�g�Ȃǂɗp������͂�

	ID3D11Texture2D* m_pBackBuffer_DSTex;		//�o�b�N�o�b�t�@�[�̐[�x�o�b�t�@�[�Ɏg�����߂̃e�N�X�`��

	ID3D11BlendState* m_pBlendState;

	//���f���̎�ނ��ƂɕK�v�A�Ƃ�����胂�f���Ɏg���V�F�[�_�[���ƂɃ��C�A�E�g�Ȃǂ��ς��̂�
	//���̎��ɕK�v�ɂȂ�͂�
	

	Camera* m_pCamera;
	FPS* m_pFPS;
	void InitModel();//���̕ӂ̓X�e�[�W�Ȃ񂩂�������ꍇ�̓V�[�����Ƃɕ����ăV�[���Ƀ��f�����������āA����������悤�ɂ���̂���������
	void ReleaseModel();

	enum eMoveVec {
		None = 0,
		Forward = 1,
		Backward = 2,
		Right = 3,
		Left = 4,
	};
	eMoveVec m_eMoveVec;
	void MoveUpdate(eMoveVec Vec);

private:
	
	MyModel* m_pTestModel;
	MyModel* m_pEnemyModel[3];
	MyGround* m_pGround;
	
	MoveUI* m_pMoveUI;
	float view;
	
};

#endif