#ifndef MOVEUI_PANEL_H
#define MOVEUI_PANEL_H

//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
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

#include <string>

#include "Poly.h"
//#include "VertexShaderUtility.h"
//
//#include "PixelShaderUtility.h"
//
//#include "ConstantBuffer.h"


//�}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //�n���ꂽ�I�u�W�F�N�g�̃����[�X�֐����Ăяo���Ă��̂��Ƃ�NULL�����Ă���
#endif

#ifndef SIMPLE_VERTEX
#define SIMPLE_VERTEX
struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 vTex;
};
#endif

#ifndef SIMPLESHADER_CONSTANT_BUFFER_DEF
#define SIMPLESHADER_CONSTANT_BUFFER_DEF
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
#endif


class MoveUIPanel {
public:
	MoveUIPanel();
	~MoveUIPanel();
	void Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext);
	//void Release();

	//void Render(const D3DXVECTOR3& cvCenter, const D3DXVECTOR3& cvLength, const D3DXVECTOR3& cvForward, const D3DXVECTOR3& cvRight, const D3DXMATRIX& cmView);
	void Render();

	HRESULT CreateVertexBuffer();

	HRESULT CreateTexture(std::string filename);

private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	//�o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer* m_pVertexBuffer;
	//�T���v���[
	ID3D11SamplerState* m_pSampleLinear;

	//�e�N�X�`���[
	ID3D11ShaderResourceView* m_pTexture;

};

#endif