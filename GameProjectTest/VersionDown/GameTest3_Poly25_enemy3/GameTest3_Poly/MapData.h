#include "MyModel.h"
#include "Ground.h"

#include <list>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <queue>
#include "main.h"

#include <math.h>
//�}�b�v��̃f�[�^�������ɒu���Ă�����
//�ړ��̍ۂɔ͈͓��ɓG�����邩���f�[�^���Q�Ƃ���
//�n���Ă�����݂����Ȃ��Ƃ��l���Ă����̂������
//�Ƃ肠�������̓A���t�@�����ق����悾�ƍl����̂�
//�y�ʉ��͌�񂵂ɂ��悤


//����AI���̂Ɂ@������x�̏�񂪂Ȃ��Ƙb�ɂȂ�Ȃ��Ƃ������Ƃ�
//�ȒP�ɏ���ۑ��ł�����̂����

#ifndef MAPDATA_H
#define MAPDATA_H
namespace nsModelData {
	//enum eModelType {
	//	None = 0,
	//	Player = 1,
	//	Enemy = 2,
	//};

	//struct ModelData {
	//	eModelType eType;
	//	//int iLV;
	//	int IndexNo;
	//	ModelData() {
	//		eType = eModelType::None;
	//		//iLV = 0;
	//		IndexNo = 0;
	//	}
	//};
	struct EnemyModelInitData {
	
		D3DXVECTOR3 vPos;
		int iLV;
		EnemyModelInitData() {
			vPos = D3DXVECTOR3(0, 0, 0);
			iLV = 0;
		}
	};
}
namespace MAP_DATA_STATIC {
	//1�ړ����̃p�l���T�C�Y
	static const int MapSizeX = MyGround::Modelx * GroundPanel::PanelSize / MyPoly::Poly::PolySize;//�ꖇ�̃}�b�v�T�C�Y����̃|���[�T�C�Y�Ŋ����Ă�����}�b�v�`�b�v�������p��
	static const int MapSizeZ = MyGround::Modelz * GroundPanel::PanelSize / MyPoly::Poly::PolySize;
}

class MapData {

public:	

	MapData();
	void Init();

	int GetNumModels();
	bool GetInitEnemyData(nsModelData::EnemyModelInitData*const pOut);//�|�C���^�[�̎Q�Ɛ��ς��Ȃ�

	
	bool SetInitMapData(int Index, const D3DXVECTOR3& vPos,int Size);
	
	
	//bool GetMapData()

	void GetMapData(std::queue<int> *pOut, float LeftX, float RightX, float ForwardZ, float BackwardZ);


	bool SortAndIndexCheck(int* IndexNum);

	//void isErrorNotIndextoRePositioningResize(D3DXVECTOR3*const vPos,int ErrorIndex);
	//1�̃}�b�v�`�b�v������Ƃ��āA���̒��Ŋ�����n���āA���ۂɂ����̂��̂��n���邩�킩��Ȃ�����ǁ@�z�u�ł�������v�Z������
	//���ꂪ1�̃}�b�v�`�b�v�ɂ͊�{�I�Ƀ��x�����Ⴄ��ނ�2����3�z�u����悤�ɂ���
	//bool InitializePosMapTip100_100(int MinSize,int MaxSize,float MinPercentage,std::list<nsModelData::EnemyModelInitData>* pOutList);
	//bool InitializePosMapTip100_100(int MinSize, int CenterSize,int MaxSize, float MinPercentage, std::list<nsModelData::EnemyModelInitData>* pOutList);

	//bool InitializeMapTip(int MapTipNumX, int MapTipNumY, int MinSize, int MaxSize, int MinModelNum, int MaxModelNum);
	//�܂��͂��̊֐��Ŕz�u�ł���̂��𒲂ׂ�
	//bool InitCanSetPos(float fPosxX, float fPosZ, int SizeX, int SizeZ);
	//���̌�z�u�A�������O�̂��߂ɖ{���Ƀf�[�^���Ȃ��̂��̓`�F�b�N������
	//bool InitSetPos(float fPosX, float fPosZ, int SizeX, int SizeZ,const nsModelData::ModelData& SetModelData);
private:
	
	//���I�z��Ŋm�ۂ����x�N�^�[�z��Ƀ��X�g�����Ă��肻�̃��X�g�f�[�^���̂�ModelData��ۗL����
	//��肽�����Ƃ��l�����ۂɂ��ꂪ��ԃx�X�g���Ǝv����
	//�������G�ɂȂ�Ȃ����S�z
	//std::vector< std::vector<std::list<nsModelData::ModelData>>> m_MapInfoList;
	std::vector< std::vector<int>> m_MapInfo;


	std::queue<nsModelData::EnemyModelInitData> m_InitEnemyDataQue;
	//unsigned int m_iNumModelsCnt;


	//void SetMapInfo(int x, int z, int size, int index);

	//�}�b�v�̔z�u����{���̓e�L�X�g�f�[�^�Ȃǂ���ǂݍ����
	//��������Ƃɂ������悤�ɂ��Ă���������
	//����m�F�ƁA�����܂ł���鎞�Ԃ����邩�킩��Ȃ��̂�
	//�Ƃ肠�����A����m�F�悤�Ƀf�[�^�����
	enum MapTip0_0 {
		LV1_0_0 = 70,
		LV2_0_0 = 15,
		LV3_0_0 = 0,
		LV4_0_0 = 0,
		LV6_0_0 = 0,//king
	};

	enum MapTip1_1 {
		LV1_1_1 = 0,
		LV2_1_1 = 9,
		LV3_1_1 = 14,
		LV4_1_1 = 3,
		LV6_1_1 = 1,
	};
	
	enum MapTipElse {
		LV1_ELSE = 10,
		LV2_ELSE = 19,
		LV3_ELSE = 2,
		LV4_ELSE = 1,
		LV6_ELSE = 0,
	};


	void MapInit();
	//void InitMapTip();
	//4�����z��ɂȂ��
	//std::vector< std::vector<nsModelData::ModelData>> m_MapTip[MyGround::Modelx][MyGround::Modelz];

	//����@�L���O�̃��x����5�Ɛݒ肷��Ƃ��āA�����_�}�C�Y������̂���낤

	//��������
	//void NoStartMapRandomizeMaptip(unsigned int LV1Num,unsigned int LV2Num,unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num,unsigned int MapTipNumX,unsigned int MapTipNumZ);

	void MapRandomizeMaptip(unsigned int LV1Num, unsigned int LV2Num, unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num, unsigned int MapTipNumX, unsigned int MapTipNumZ);

	
	std::list<int> IndexChecker;

	int m_iObjectNum;
	//void StartMapRandamizeMaptip(unsigned int LV1Num,unsigned int )
	//�����ʒu
	//enum InitMapTip0_0 {
	//	LV1Num = 12,
	//};
	//void InitMapTip0_0();
};
#endif