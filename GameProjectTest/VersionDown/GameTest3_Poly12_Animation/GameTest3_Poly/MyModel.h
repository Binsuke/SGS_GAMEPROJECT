#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include <list>

#ifndef MYMODEL_DEF
#define MYMODEL_DEF

//memo
//PosInit���g���čŏ��\�����s���Ă�����
//���f���N���X�͕ύX���s���ALV��n�����ƂŃ��f�����쐬
//PosInit�͏������s��InitLv�Ń��x���Ə����ʒu��n����������
//
class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//�|�W�V�����C�j�V�����C�Y
	MyModel();
	
	//�����_�[�֐�
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	


	D3DXVECTOR3 GetCenter() { return m_vCenter; }
	void SetPos(D3DXVECTOR3 vPos);
	void SetPos(float x, float y, float z);

	
	void Move(float deltaTime, const D3DXVECTOR3& cvForwardVec);

	void InitLv(int Lv);
	void LVUp();
	void LVDown();

	D3DXVECTOR3 GetCameraMargin();

	D3DXVECTOR3 GetCameraTarget();

	float GetSizeY();

	int GetLV() { return m_iLV; }

	bool AnimationLocalRight(float deltaTime);

	//void KeyInput(float deltaTime);

	//�L���[�u�`��p�̃N���X
	MyPoly::Poly m_Cube;
	//�o�[�e�b�N�X�V�F�[�_�[
	VertexShaderUtil m_VertexShader;
	//�s�N�Z���V�F�[�_�[
	PixelShaderUtil m_PixelShader;
	//�R���X�^���g�o�b�t�@�[
	MyConstantBuffer m_ConstantBuffer;


private:

	void MoveLocalForward(float deltaTime);
	void MoveLocalBackward(float deltaTime);
	void MoveLocalRight(float deltaTime);
	void MoveLocalLeft(float deltaTime);


	//bool MoveLocalForwardA(float deltaTime);
	//bool MoveLocalBackwardA(float deltaTime);
	//bool MoveLocalRightA(float deltaTime);
	//bool MoveLocalLeftA(float deltaTime);


	void SetLV1();

	void InitAdjustment();

	void UpdateCenter();

	void ModelSizeUp();
	void ModelSizeDown();

	
	float m_fAnimationRotX;
	float m_fAnimationRotZ;
	float m_fAnimationMargineY;

	float m_fAnimTime;//second
	bool m_bAnimeFlg;
	float m_fAnimeWaitTime;

	D3DXVECTOR3 m_vAnimationPrevPos;

	//D3DXMATRIX m_mAnimationRotX;
	//D3DXMATRIX m_mAnimationRotY;
	//�f�o�C�X
	ID3D11Device* m_pDevice;
	//�f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_pDeviceContext;

	D3DXVECTOR3 m_vForward;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vRight;

	D3DXVECTOR3 m_vLocalForward;
	D3DXVECTOR3 m_vLocalUp;
	D3DXVECTOR3 m_vLocalRight;

	int m_iLV;
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

	
	D3DXVECTOR3 m_vCenter;
	D3DXVECTOR3 m_vPos;
	//���[�J�����W�̃|�X�ێ��ϐ�
	std::list<D3DXMATRIX> m_lmModelMat;
};
#endif