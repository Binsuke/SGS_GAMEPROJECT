//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#include "CD3DXMESH.h"

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�萔��`
#define WINDOW_WIDTH 640 //�E�B���h�E��
#define WINDOW_HEIGHT 480 //�E�B���h�E����
#define APP_NAME L"���o��i����j"

#define RAY_DISTANCE 1
#define SPEED 0.04f

//
//
//
class MAIN
{
public:
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCWSTR);
	HRESULT InitD3D();
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
	void Loop();
	void App();
	void Render();
	void DestroyD3D();
	bool RayIntersect(CD3DXMESH* pMeshA ,D3DXVECTOR3&,CD3DXMESH* pMeshB,float* pfDistance,D3DXVECTOR3*);
	HRESULT FindVerticesOnPoly(LPD3DXMESH,DWORD,D3DXVECTOR3*);
	D3DXVECTOR3 Slip(D3DXVECTOR3 L,D3DXVECTOR3 N);

	HWND m_hWnd;									//�E�B���h�E�n���h��
	ID3D11Device* m_pDevice;						//�f�o�C�X�{��
	ID3D11DeviceContext *m_pDeviceContext;			//�f�o�C�X�R���e�L�X�g�{��
	IDXGISwapChain* m_pSwapChain;					//�X���b�v�`�F�C��
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[�i�o�b�N�o�b�t�@�[
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;	//�f�v�X�X�e���V���r���[(�o�b�N�o�b�t�@�[
	ID3D11Texture2D* m_pBackBuffer_DSTex;			//�o�b�N�o�b�t�@�[�p�̃e�N�X�`��
	
	CD3DXMESH* m_pRobotMesh;						//RobotMesh
	CD3DXMESH* m_pSlopeMesh;						//SlopeMesh
};
