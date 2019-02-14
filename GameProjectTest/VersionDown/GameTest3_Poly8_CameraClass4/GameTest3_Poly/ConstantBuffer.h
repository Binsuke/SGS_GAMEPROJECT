#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

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
													//�}�N���ōs���Ă��邯�ǁA�e���v���[�g�ōs���ق��������Ƃ͎v��
#endif SAFE_RELEASE

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

class MyConstantBuffer {
public:
	void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	HRESULT CreateConstantBuffer(D3D11_BUFFER_DESC cb);
	void SetConstantBuffer(D3DXMATRIX world,D3DXMATRIX view, D3DXMATRIX proj);
	void SetCBtoVS();
	void SetCBtoPS();
	void Release();
private:
	ID3D11Buffer* m_pConstantBuffer;			//�R���X�^���g�o�b�t�@�[����邽�߂̃o�b�t�@
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	//static int Num;
};
#endif