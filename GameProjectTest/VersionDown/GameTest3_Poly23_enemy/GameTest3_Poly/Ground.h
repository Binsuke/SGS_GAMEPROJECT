#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include "GroundPanel.h"


//���̊֐��͂̂��Ɂ@�}�b�v�����Ƃ���
//�}�b�v�������ƂɁ@�p�l�������Ƃ����������悤�ɂł����炢����
#ifndef MY_GROUND_H
#define MY_GROUND_H
class MyGround {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);

	//�|�W�V�����C�j�V�����C�Y
	void PosInit();

	//�����_�[�֐�
	void Render(D3DXMATRIX view, D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation, D3DXMATRIX scale);
	//�L���[�u�`��p�̃N���X
	//MyPoly::Poly m_Cube;
	GroundPanel m_Ground;
	//�o�[�e�b�N�X�V�F�[�_�[
	VertexShaderUtil m_VertexShader;
	//�s�N�Z���V�F�[�_�[
	PixelShaderUtil m_PixelShader;
	//�R���X�^���g�o�b�t�@�[
	MyConstantBuffer m_ConstantBuffer;

	enum {
		Modelx = 10,
		Modelz = 10,
	};

	//float GetGroundRight() { return Modelx * GroundPanel::PanelSize; }
private:
	//�f�o�C�X
	ID3D11Device* m_pDevice;
	//�f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_pDeviceContext;



	D3DXMATRIX m_World;
	
	//���[�J�����W�̃|�X�ێ��ϐ�
	D3DXMATRIX ModelPos[Modelx][Modelz];
};

#endif  MY_GROUND_H
