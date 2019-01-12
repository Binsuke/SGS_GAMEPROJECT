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
//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�x����\��
#pragma warning(disable:4305)
#pragma warning(disable:4005)

//�萔��`
#define WINDOW_WIDTH	640 //window ��
#define WINDOW_HEIGHT	480 //window����
#define APP_NAME L"�e�N�X�`���[�𒣂�"

//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //�n���ꂽ�I�u�W�F�N�g�̃����[�X�֐����Ăяo���Ă��̂��Ƃ�NULL�����Ă���
													//�}�N���ōs���Ă��邯�ǁA�e���v���[�g�ōs���ق��������Ƃ͎v��


//���_�̍\����

//��������VS_OUTPUT�ƈ�v�@�@Pos ��Pos vTex�@�� Tex
//struct SimpleVertex
//{
//	D3DXVECTOR3 Pos; //�ʒu
//	D3DXVECTOR2 vTex;//UV
//	//SimpleVertex() :Pos(0, 0, 0) {};//�R���X�g���N�^���������ŏ�����
//};



//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[���A�v������`�@�@������̂��ɃV�F�[�_�[���Ƃ���肷�锠�Ƃ��Ďg��

//���ꂪcbuffer�@global�ƈ�v���ׂ����́@color�Ƃ����̂�diffuse����v
struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;   //world * view * projection �̍s���n��
						//����WVP�ɂ���ă��f���̍��W�����[�J�����W����ϊ�����
						//���[���h���W�@�r���[�s��@�v���W�F�N�V�����s��������������̂����f���̍s��ɂ������킹�邱�Ƃ�
						//�s��̌v�Z���������Ȃ����Ă���B�Ⴆ�Έړ��X�P�[����]�Ƃ����s�񂪂������ꍇ��
						//�ړ������@�X�P�[���Ɏg�������@��]�Ɏg�������́@�s����Ō����ɕ�����Ă��邽��
						//4*4�s��ɂ����Ă��܂����ƍ����������̂��ꊇ�ł����Čv�Z���������炷���Ƃ��ł���
						//�P�̒��_�ɑ΂��ā@�ړ��A�X�P�[���A��]�𖈉������
						//�܂Ƃ߂Ă�邱�Ƃɂ���Čv�Z�񐔂��R���̂P�H�ɂł���͂�
						//mWVP�ɂ����Ă����炩���ߍ������Ă������ƂŌv�Z�񐔂����炵�Ă����͂�
						//���_�̐����c��ɂȂ郂�f���ɂȂ�΂Ȃ�قǂ����������ׂ��Ȍv�Z�񐔂����炷���Ƃ����s���x�ɒ������Ă���炵��

	D3DXVECTOR4 vColor;

};


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
	/*HRESULT InitModel();
	HRESULT MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);
*/
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

	//���f���̎�ނ��ƂɕK�v�A�Ƃ�����胂�f���Ɏg���V�F�[�_�[���ƂɃ��C�A�E�g�Ȃǂ��ς��̂�
	//���̎��ɕK�v�ɂȂ�͂�
	ID3D11InputLayout* m_pVertexLayout;			//�o�[�e�b�N�X�̃��C�A�E�g�����ۂɎg���A���̃��C�A�E�g�����Ƃɒ��_�̌`�����߂�
	ID3D11VertexShader* m_pVertexShader;		//Vertex�V�F�[�_�[�̖{��
	ID3D11PixelShader* m_pPixelShader;			//Pixel�V�F�[�_�[�̖{��
	ID3D11Buffer* m_pConstantBuffer;			//�R���X�^���g�o�b�t�@�[����邽�߂̃o�b�t�@

	//���f�����ɕK�v�炵��
	ID3D11Buffer* m_pVertexBuffer;				//�o�[�e�b�N�X�o�b�t�@�[

	ID3D11SamplerState* m_pSampleLinear;			//�e�N�X�`���[�̃T���v���[
												//�T���v���[�Ƃ̓e�N�X�`�����ǂ̂悤�Ɉ������A�e�N�X�`���̉摜�����O�ɂ���[�͂ǂ̂悤�Ɉ�����
												//�Ⴆ�΃~���[�⓯���F�œh��Ԃ��Ȃǂ̐ݒ������Ă����ā@�����邽�߂̏��

	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�{�́@�@�V�F�[�_�[�ɓn�����\�[�X
											//���\�[�X�������ɓ���
private:
	MyPoly::Poly* m_pTestPoly;
};

#endif