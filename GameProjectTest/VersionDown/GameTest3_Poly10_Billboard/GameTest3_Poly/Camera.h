//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx�n��
#include <d3dx11.h>		
//d3dx�n��
#include <d3dcompiler.h>

#include "MyModel.h"

#ifndef WINDOW_SIZE
#define WINDOW_SIZE
#define WINDOW_WIDTH	640 //window ��
#define WINDOW_HEIGHT	480 //window����
#define APP_NAME L"�e�N�X�`���[�𒣂�"
#endif

//struct LocalVector {
//	D3DXVECTOR3 slFoward;
//	
//};

class Camera {
public:

	//func
	Camera();
	Camera(D3DXVECTOR3 Pos);
	Camera(float x, float y, float z);
	~Camera();

	void InitCamera();
	void MoveForward(float delta);
	void MoveBackward(float delta);
	void MoveRight(float delta);
	void MoveLeft(float delta);
	void MoveUp(float delta);
	void MoveDown(float delta);


	void UpDateLook(float deltaTime, float size);
	void LookUp(float deltaTime,float size);
	void LookDown(float deltaTime,float size);

	//���[�J�����ł̉�]�̉������@�͈�̎����Ƃ̉�]���s�����Ƃōs�����@�����邪���ꂾ�Ǝ΂߂̈ړ����ł��Ȃ�
	//�΂߂̃J�����̓������s�����߂ɂ̓L���[�ɓ��͏������߂āA�t���[�����Ƃɏ���������@���l������
	//���̏ꍇ�A�{���f���^���Ԃ�����Ă�����̂ł�����͓������Ă��邪
	//�L���[���R�����p�ӁA�ŏ��Ƀ`�F�b�N���s���f�[�^�������Ă���̂�x,y,z�R�������ꍇ�A�S�Ẵf���^���Ԃ����R���s����x�̕ω��ʂ𒲐��A���̌�̂R��̃t���[���ł��|�����|�����̂悤�ɕϊ����s��
	//���ɍŏ��̃`�F�b�N�ŃL���[�̃f�[�^�����A�����݂̂̏ꍇ�̓f���^���Ԃ����Q���s���A���l�ɂQ�t���[���ŏ������s��
	//������s�����ƂŁA��ʏ�ł͎΂߂̈ړ��Ȃǂɂ��Ή��ł���ƍl������
	//�����A�Ƃ肠��������͂����Ă���
	//���E�����ւ̓��������ɂ��Ă�if���łǂ����������Ă�����X���[�����邱�Ƃŉ�������
	void RotRight(float delta);
	void RotLeft(float delta);

	void SetCamera(D3DXMATRIX* mViewOut,D3DXMATRIX* mProjectionOut);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget,D3DXVECTOR3 vCameraPosVec);

	void SetCamera(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec,float TargetMargineY,float TargetMargineX);

	void SetCameraA(D3DXMATRIX* mViewOut, D3DXMATRIX* mProjectionOut, D3DXVECTOR3 vTarget, D3DXVECTOR3 vCameraPosVec);

	
	enum eGetLocalType{
		eGetForward = 0,
		eGetBackward =1,
		eGetRight = 2,
		eGetLeft  = 3,
	};

	void GetMoveLocalVec(D3DXVECTOR3* pvLocal,eGetLocalType eLocalType);

	void GetMoveLocalVecA(D3DXVECTOR3* pvLocal, eGetLocalType eLocalType);

	void UpDateWorldVec();

	void GetMoveLocalForwardVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalBackwardVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalRightVec(D3DXVECTOR3* pvLocal);
	void GetMoveLocalLeftVec(D3DXVECTOR3* pvLocal);

	//void UpdateLocalVec(float deltaTime);
	
	D3DXVECTOR3 GetWorldForward() {
		return m_vWorldForward;
	}


private:
	//func
	D3DXVECTOR3 SwitchVector(eGetLocalType eType,const D3DXVECTOR3& vForward,const D3DXVECTOR3& vRight);
	D3DXVECTOR3 SwitchVectorA(eGetLocalType eType,D3DXVECTOR3 vForward);

	//data
	D3DXVECTOR3 m_vWorldForward;

	bool m_bLookFlg;
	float m_fLookUp;
	D3DXMATRIX m_mTransform;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;

	float m_fTransDir;

	static D3DXVECTOR3 ms_vLocalRight;
	static D3DXVECTOR3 ms_vLocalLeft;
	static D3DXVECTOR3 ms_vLocalForward;
	static D3DXVECTOR3 ms_vLocalBackward;


	static float ms_fRotSize;

	static float ms_fRotMargine;

	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vForward;

	D3DXVECTOR3 m_vEyePt;
	D3DXVECTOR3 m_vLookat;

	D3DXMATRIX m_mPoseMat;
	D3DXMATRIX m_mDeltaMat;

	D3DXVECTOR3 m_vPrevForward;
	D3DXVECTOR3 m_vPrevBackward;

	D3DXVECTOR3 m_vPrevRight;
	D3DXVECTOR3 m_vPrevLeft;

	bool m_bMoveFlg;
	//Entity TargetObject = null
};