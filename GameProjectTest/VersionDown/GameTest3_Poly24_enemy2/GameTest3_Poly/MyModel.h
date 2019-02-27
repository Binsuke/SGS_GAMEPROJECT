#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"
#include <list>
#include "Ground.h"
//#include "GameScene.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#endif

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
	~MyModel();
	//�����_�[�֐�
	
	//���󃌃��_�����O����̂͂���
	//�ق��͎̂g��Ȃ��̂ō폜�\��
	virtual void Render(D3DXMATRIX view,D3DXMATRIX proj);

	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	

	//�Z���^�[��Ԃ�
	D3DXVECTOR3 GetCenter();// { return m_vCenter; }
	//�|�W�V�������Z�b�g
	void SetPos(D3DXVECTOR3 vPos);
	//�|�W�V�����Z�b�g
	void SetPos(float x, float y, float z);

	D3DXVECTOR3 GetPos() { return m_vPos; }

	//����g���ĂȂ�
	//D3DXVECTOR3 GetColisionPos();// { return m_vPos + m_vAnimePos; }

	//����̃��[���h���W�̃x�N�g����������Ă���ɑ΂��郍�[�J���̈ړ����s��
	//void Move(float deltaTime, const D3DXVECTOR3& cvForwardVec);
	//�A�j���[�V�����o�[�W����
	bool MoveA(float deltaTime, const D3DXVECTOR3& cvForwardVec);

	//���o�[�X�A�j���[�V����
	//bool MoveReverceA(float deltaTime, const D3DXVECTOR3& cvForwardVec);

	//���f���̃��x�����Z�b�g����
	virtual void InitLv(int Lv);
	//���x�����ǔ�

	//void InitLv()

	//���x����1�グ��
	void LVUp();

	//���x���A�b�v����
	void LVUpA(MyModel* pModel);


	void ReverceOn() { m_bAnimeReverceFlg = true; }


	//���x�����P������
	virtual int LVDown();


	//�����蔻��
	bool Colision(MyModel* pModel);



	bool Colision(MyModel* pModelA, MyModel* pModelB);


	//�J�����ɂǂ̂��炢�J�����������邩�̃}�[�W����Ԃ�
	D3DXVECTOR3 GetCameraMargin();
	//�J�����̃^�[�Q�b�g�ꏊ��Ԃ�
	D3DXVECTOR3 GetCameraTarget();

	//����̃T�C�Y��Ԃ�
	float GetSize();

	//���x����Ԃ�
	int GetLV() { return m_iLV; }

	//�R���W�����̌v�Z�i���f��������́j
	//bool ColisionCalc(MyModel* pModel);

	bool GroundCheck(float deltaTime);

	//void KeyInput(float deltaTime);
	//�������|�C���^�[�ɂ����Ƃ��ɖ�肪�ł�񂶂�Ȃ����H�Ǝv�����̂������
	//�R�s�[�R���X�g���N�^�[���Ăяo���ꂽ�Ƃ��ɂǂ�����H�Ǝv������
	//��������POS�̂悤�Ƀ��f�����ɕK�v�Ȃ��̂ł͂Ȃ�����
	//�R�s�[�R���X�g���N�^�[���Ă΂��΂��ƂɂȂ����f�[�^�̃|�C���^�[���R�s�[�����͂�
	//�Ǝv����������̓|�C���^�[�ɂ͂ł��Ȃ���
	//�R�s�[���s����̂ł��ƂɂȂ����f�[�^�̏��̃|�C���^�[���R�s�[
	//�����킯�Ȃ񂾂���ǁ@�R�s�[��̃f�[�^���������ꍇ
	//���̃f�[�^�ɂȂ��Ă���m_Cube�̃f�[�^�������Ă��܂�
	//�Ȃ̂ł��Ƃɖ߂��G�R�s�[���s��Ȃ��̑O��Ȃ���͂Ȃ������
	//�������邩�킩��Ȃ��̂Ń|�C���^�[�ɂ���̂͂�߂Ă�����
	//�{���́A�V�[����������ۂɃ��[�h������Ȃǂ̎��Ƀ��������m�ۂ������̂�
	//�|�C���^�[�ɂ��āA�ǂݍ��݂Ȃǂ͂��ׂ�init�֐��ōs���悤�ɂ���Ȃǂ�����
	//�܂��A�|�C���^�[�̉�����f�X�g���N�^�[�ōs���̂ł͂Ȃ���
	//�����[�X�֐��ōs���̂��]�܂���
	//�Ȃ����Ƃ����ƁA�������|�C���^�[�ɂ����ۂɁA�R�s�[�R���X�g���N�^�������Ă��܂���
	//�|�C���^�[�̎Q�Ɛ悪�R�s�[����Ă��܂����ƂɂȂ�
	//�f�X�g���N�^�[�Ń|�C���^�[���������Ă��܂���
	//�������R�s�[�R���X�g���N�^�[�Ńf�[�^���R�s�[���Ă��܂����Ƃ���
	//�R�s�[��̃f�[�^���������ꂽ�ۂ�
	//�R�s�[���ɂȂ����f�[�^�܂ŏ�������Ă��܂��Ƃ����o�O���N���肩�˂Ȃ�
	//�Ȃ̂Ń|�C���^�[�ɂ���͔̂�����ׂ��Ȃ̂��Ƃ͎v�������
	//�Ƃ肠�����R�s�[�R���X�g���N�^�[�����������v���C�x�[�g�ɂ��đΉ�����Ȃ�
	//���낢��Ή����@�͂��邯���
	//�����̌o���s���ł���������Ă��鎞�Ԃ��Ȃ�����
	//�������񃁃����͐H������ǃ|�C���^�[�ŕێ�����̂͂�߂Ă������Ƃɂ���
	//�����A���̏�w�̃V�[���N���X�ł��̃N���X���g���f�[�^��
	//�|�C���^�[�ɂ��Ă������init,release�֐���p�ӂ���
	//�����I�Ƀ|�C���^�[�̉�����s���悤�ɂ��邱�Ƃ�
	//����ł���̂�������Ȃ�
	//�����������Ɋւ���m���������s�����Ă��镔��������̂�
	//�׋����Ȃ���΂Ȃ�Ȃ��ȂƊ�����
	//�����A���̕ӂ�̓p�\�R���̃X�y�b�N�̌���Ȃǂ�����
	//�̂قǃ�������؂�l�߂ăf�[�^�����K�v������̂���
	//����̃Q�[�������������Ȃ��̂ł킩��Ȃ�
	//�����ǂ̂��炢�̃������������Ă��̂����̂ǂ̂��炢�̃��������g���Ă�����
	//�Ȃǂ��v�Z���Ă��Ȃ��ƃI�[�o�[�t���[���N�����\��������̂�
	//�����������Ƃ���̊J�����s�����ƂɂȂ�����@�׋�����ׂ�

	//�L���[�u�`��p�̃N���X
	MyPoly::Poly m_Cube;
	//�o�[�e�b�N�X�V�F�[�_�[
	VertexShaderUtil m_VertexShader;
	//�s�N�Z���V�F�[�_�[
	PixelShaderUtil m_PixelShader;
	//�R���X�^���g�o�b�t�@�[
	MyConstantBuffer m_ConstantBuffer;


protected:
	//�A�j���[�V�������Ȃ� ����g��Ȃ�
	//void MoveLocalForward(float deltaTime);
	//void MoveLocalBackward(float deltaTime);
	//void MoveLocalRight(float deltaTime);
	//void MoveLocalLeft(float deltaTime);

	//�쐬���Ă������g��Ȃ��Ă�������
	//bool AnimationLocalRight(float deltaTime);
//	bool AnimationLocalLeft(float deltaTime);
//	bool AnimationLocalForward(float deltaTime);
//	bool AnimationLocalBackward(float deltaTime);
	//------

	//���[�J�����W�̃A�j���[�V�����@//���o�[�X�Ȃ�
	//bool AnimationLocalRightA(float deltaTime);
	//bool AnimationLocalLeftA(float deltaTime);
	//bool AnimationLocalForwardA(float deltaTime);
	//bool AnimationLocalBackwardA(float deltaTime);

	//�A�j���[�V�����̃��o�[�X
	bool AnimationLocalRightR(float deltaTime);
	bool AnimationLocalLeftR(float deltaTime);
	bool AnimationLocalForwardR(float deltaTime);
	bool AnimationLocalBackwardR(float deltaTime);

	//����͍��͎g��Ȃ�
	//void AnimationMargineSet();
	//��������͎g��Ȃ�
	//void AnimationMargineY(float deltaTime);

	//�ŏ��̃��x�����Z�b�g
	void SetLV1();

	//���f���𒆐S��
	void InitAdjustment();

	//���f���̃Z���^�[���X�V
	void UpdateCenter();

	//���f���̃T�C�Y�A�b�v
	void ModelSizeUp();
	//���f���̃T�C�Y�_�E��
	void ModelSizeDown();

	

	//���݃A�j���[�V�����ɂ���Ĉړ����Ă����
	D3DXVECTOR3 m_vAnimePos;
	//�A�j���[�V�����ɂ���]��
	D3DXMATRIX m_mAnimeRot;

	//�E��]�p�̃A�j���[�V�����̉�]��
	float m_fAnimationRotX;
	//����]�p�̃A�j���[�V�����̉�]��
	float m_fAnimationRotZ;
	//���͎g���ĂȂ�
	float m_fAnimationMargineY;

	//�A�j���[�V�������鎞��
	float m_fAnimTime;//second
	//�A�j���[�V���������x���ɂ���ĕύX���邽�߂̃f�B���C�ݒ�p
	float m_fAnimTimeDelay;
	//�A�j���[�V�������Ă邩�̐ݒ�
	bool m_bAnimeFlg;

	//�A�j���[�V���������ǂ̂��炢���Ă�̂��̎���
	float m_fAnimeWaitTime;

	//���o�[�X�t���O
	bool m_bAnimeReverceFlg;

	bool m_bAnimeReverceInitFlg;

	float m_fAnimeReverceTime;

	float m_fAnimeReverceRot;

	D3DXVECTOR3 m_vAnimeRevercePos;

	//�����_�����O�t���O
	bool m_bRenderflg;


	//�A�j���[�V�������s���ۂ̍ŏ��̃|�W�V�����ۑ��p
	D3DXVECTOR3 m_vAnimationPrevPos;

	//�f�o�C�X
	ID3D11Device* m_pDevice;
	//�f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_pDeviceContext;

	//�t�H���[�h�@�i����g���ĂȂ�
	D3DXVECTOR3 m_vForward;
	//������@�i����g���ĂȂ�
	D3DXVECTOR3 m_vUp;
	//�E�����@�i����g���ĂȂ�
	D3DXVECTOR3 m_vRight;

	//���[�J�����W�ł̑O����
	D3DXVECTOR3 m_vLocalForward;
	//���[�J�����W�ł̏����
	D3DXVECTOR3 m_vLocalUp;
	//���[�J�����W�ł̉E����
	D3DXVECTOR3 m_vLocalRight;

	//���݂̃��x��
	int m_iLV;
	//����g���ĂȂ�
	//float m_fTransDir;
	//����g���ĂȂ�
	//float m_fRotSize;

	//����g���ĂȂ�
	//D3DXMATRIX m_mTransform;
	//����g���ĂȂ�
	//D3DXMATRIX m_mRotation;

	//�L���[�u��^�񒆂ɂ��炷���߂̍s��
	D3DXMATRIX m_mAdjustment;

	static float m_fAnimationDelayTimeRimit;

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

	//���f���̃T�C�Y
	int m_iModelSizeX;
	int m_iModelSizeY;
	int m_iModelSizeZ;

	//���f���̔����̃T�C�Y
	int m_iModelHalfSizeX;//��{�I�Ɋ�ɂ���A���S���v�Z����̂��߂�ǂ���������
	int m_iModelHalfSizeY;
	int m_iModelHalfSizeZ;

	//1�̃|���S���̃T�C�Y
	float m_fPolySize;

	//1�̃|���S���̔����̃T�C�Y
	float m_fPolyHalfSize;

	//�L���[�u�̃Z���^�[
	D3DXVECTOR3 m_vCenter;
	//�L���[�u�̃|�W�V����
	D3DXVECTOR3 m_vPos;
	//���[�J�����W��1�̃L���[�u�̃}�g���b�N�X�ϐ�
	//�������ꂪ������΁A�\�������L���[�u�̐���������
	std::list<D3DXMATRIX> m_lmModelMat;

	bool m_bFallFlg;
	//void FallAnimationRight(float deltaTime);
	bool FallAnimationLeft(float deltaTime);

	bool FallAnimationRight(float deltaTime);

	bool FallAnimationBackward(float deltaTime);
	bool FallAnimationForward(float deltaTime);


};
#endif