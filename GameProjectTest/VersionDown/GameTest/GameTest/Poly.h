#ifndef POLY_H
#define POLY_H
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

struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 vTex;
};

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

namespace MyPoly{
class Poly {
public:
	Poly();
	void Init(ID3D11Device* inDevice,ID3D11DeviceContext* inDeviceContext);
	void Release();
	//void SetConstantBuffer();
	void Render(D3DXMATRIX mWVP);//world�̕ϊ��s���n�����ƂŁ@�����Ɉړ�����
	HRESULT CreateVertexBuffer();//�o�[�e�b�N�X�o�b�t�@�[�쐬�p
	HRESULT CreateTexture();
protected:
private:
	void SetConstantBuffer(D3DXMATRIX WVP);
	void InitConstantBuffer();
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	bool InitFlg;
	SimpleVertex *m_pVertices;
	ID3D11Buffer* m_pVertexBuffer;				//�o�[�e�b�N�X�o�b�t�@�[

	ID3D11SamplerState* m_pSampleLinear;			//�e�N�X�`���[�̃T���v���[
												//�T���v���[�Ƃ̓e�N�X�`�����ǂ̂悤�Ɉ������A�e�N�X�`���̉摜�����O�ɂ���[�͂ǂ̂悤�Ɉ�����
												//�Ⴆ�΃~���[�⓯���F�œh��Ԃ��Ȃǂ̐ݒ������Ă����ā@�����邽�߂̏��

	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�{�́@�@�V�F�[�_�[�ɓn�����\�[�X

	ID3D11Buffer* m_pConstantBuffer;			//�R���X�^���g�o�b�t�@�[����邽�߂̃o�b�t�@

};
}
#endif