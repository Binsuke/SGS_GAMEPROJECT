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

//�}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //�n���ꂽ�I�u�W�F�N�g�̃����[�X�֐����Ăяo���Ă��̂��Ƃ�NULL�����Ă���
#endif

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

namespace MyPoly {
	class Poly {
	public:
		Poly();
		//�������@�f�o�C�X�{�̂�n���Ă����Ă��Ƃ���ĂԂƂ��ɂ��������f�o�C�X��n���Ȃ��Ă悭���Ă���
		void Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext);
		
		//��������A����Ȃ��Ȃ�����
		void Release();

		//���[���h�̃Z�b�g�Ȃǂ������������Ƃ��l���Ă������A
		//�R���X�^���g�o�b�t�@�[�������Ƃ��ł��Ȃ������̂ŁA���̃N���X�ł͌Ă΂ꂽ��L���[�u�������_�����O����݂̂ɂ���
		void Render();
		//�o�[�e�b�N�X�o�b�t�@�[�쐬�p
		HRESULT CreateVertexBuffer();
		//�e�N�X�`���[�ǂݍ��݁A����Ɋւ��Ă̓t�@�C�������w�肵�ēǂݍ��ނ悤�ɕύX���Ă����������
		//����A�L���[�u�݂̂ŃQ�[�������\��Ȃ̂ł����܂Ŏ�������K�v���Ȃ��Ɣ��f
		//�������̓e�N�X�`���[������Ă��邯��ǁA�e�N�X�`���[����K�v�ł͂Ȃ��Ȃ�Ǝv��
		//�����e�N�X�`���[���g����悤�ɂ��Ă����΁A��X���낢��ȉ��p�������Ƃ������̂�
		//�܂��ύX�̉\���͂���
		HRESULT CreateTexture();
	
	protected:
	private:
		
		//init�֐��Ńf�o�C�X�{�̂��󂯎���Ă������ƂŁA���Ƃł��������󂯎��K�v���Ȃ�
		//�����x�͂����邯��ǁA�f�o�C�X���Ȃ��Ɠ��삵�Ȃ����̂���{�Ȃ̂ŋC�ɂ��Ă��������Ȃ�
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

		//�������������Ƃ��Ă��邩�𔻒肷�邽�߂ɒǉ�
		bool InitFlg;

		//�o�[�e�b�N�X�o�b�t�@�[��������琳���K�v�͂Ȃ��Ȃ�Ǝv���̂�
		//�������������������
		SimpleVertex *m_pVertices;
		
		//�o�[�e�b�N�X�o�b�t�@�[
		ID3D11Buffer* m_pVertexBuffer;				//�o�[�e�b�N�X�o�b�t�@�[

		//�T���v���[
		ID3D11SamplerState* m_pSampleLinear;			//�e�N�X�`���[�̃T���v���[
													//�T���v���[�Ƃ̓e�N�X�`�����ǂ̂悤�Ɉ������A�e�N�X�`���̉摜�����O�ɂ���[�͂ǂ̂悤�Ɉ�����
													//�Ⴆ�΃~���[�⓯���F�œh��Ԃ��Ȃǂ̐ݒ������Ă����ā@�����邽�߂̏��

		//�e�N�X�`���[
		ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�{�́@�@�V�F�[�_�[�ɓn�����\�[�X

	};
}
#endif