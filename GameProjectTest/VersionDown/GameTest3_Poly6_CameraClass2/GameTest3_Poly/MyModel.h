#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include <list>

#ifndef MYMODEL_DEF
#define MYMODEL_DEF
class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//�|�W�V�����C�j�V�����C�Y
	MyModel();
	void PosInit();
	void PosInit(int x, int y, int z);
	void PosInit(int NumPoly);

	//�����_�[�֐�
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	
	/*void MoveForward(float delta);
	void MoveBackForward(float delta);
	void MoveLeft(float delta);
	void MoveRight(float delta);*/

	//�L���[�u�`��p�̃N���X
	MyPoly::Poly m_Cube;
	//�o�[�e�b�N�X�V�F�[�_�[
	VertexShaderUtil m_VertexShader;
	//�s�N�Z���V�F�[�_�[
	PixelShaderUtil m_PixelShader;
	//�R���X�^���g�o�b�t�@�[
	MyConstantBuffer m_ConstantBuffer;
private:
	void InitAdjustment();
	//�f�o�C�X
	ID3D11Device* m_pDevice;
	//�f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_pDeviceContext;

	D3DXVECTOR3 m_vForward;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vRight;

	float m_fTransDir;
	float m_fRotSize;

	D3DXMATRIX m_mTransform;
	D3DXMATRIX m_mRotation;

	D3DXMATRIX m_mAdjustment;

	

	D3DXMATRIX m_World;
	enum {
		Modelx = 5,
		Modely = 5,
		Modelz = 5,
		ModelSize = 5,
		Halfx = 3,
		Halfy = 3,
		Halfz = 3,
	};

	int m_iModelSizeX;
	int m_iModelSizeY;
	int m_iModelSizeZ;

	int m_iModelHalfSizeX;//��{�I�Ɋ�ɂ���A���S���v�Z����̂��߂�ǂ���������
	int m_iModelHalfSizeY;
	int m_iModelHalfSizeZ;

	float m_fPolySize;
	float m_fPolyHalfSize;
	//���[�J�����W�̃|�X�ێ��ϐ�
	//D3DXMATRIX m_mModelMat[Modelx][Modely][Modelz];
	//D3DXMATRIX* m_mpModelMat;

	std::list<D3DXMATRIX> m_lmModelMat;
};
#endif