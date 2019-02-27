#include "MapData.h"

void MapData::Init() {
	//�܂��̓x�N�^�[�N���X�ɂ���ē��I�ɔz����m��
	//2�����z������B�x�N�^�[�N���X����
	//���ۂɂ�2�����z��̂悤�Ɉ������Ƃ��ł���
	m_MapInfo.resize(MAP_DATA_STATIC::MapSizeX);

	for (int i = 0; i < MAP_DATA_STATIC::MapSizeX; i++) {
		m_MapInfo[i].resize(MAP_DATA_STATIC::MapSizeZ);
	}
	
	//nsModelData::ModelData InitData;
	//InitData.eType = nsModelData::None;
	//for (int x = 0; x < MAP_DATA_STATIC::MapSizeX; x++) {
	//	for (int z = 0; z < MAP_DATA_STATIC::MapSizeZ; z++) {
	//		m_MapInfo[x][z] = InitData;
	//	}
	//}
	unsigned int now = (unsigned int)time(0);
	srand(now);

	MapInit();
}
//
//void MapData::InitMapTip() {
//	/*for (int MapTipNumx = 0; MapTipNumx < MyGround::Modelx; MapTipNumx++) {
//		for (int MapTipNumz = 0; MapTipNumz < MyGround::Modelz; MapTipNumz++) {
//			m_MapTip[MapTipNumx][MapTipNumz].resize(100);
//		}
//	}
//	for (int MapTipNumx = 0; MapTipNumx < MyGround::Modelx; MapTipNumx++) {
//		for (int MapTipNumz = 0; MapTipNumz < MyGround::Modelz; MapTipNumz++) {
//			for (int MapTipSizeX = 0; MapTipSizeX < 100; MapTipSizeX++) {
//				m_MapTip[MapTipNumx][MapTipNumz][MapTipSizeX].resize(100);
//			}
//		}
//	}
//
//	for (int MapTipNumx = 0; MapTipNumx < MyGround::Modelx; MapTipNumx++) {
//		for (int MapTipNumz = 0; MapTipNumz < MyGround::Modelz; MapTipNumz++) {
//			for (int MapTipSizeX = 0; MapTipSizeX < 100; MapTipSizeX++) {
//				for (int MapTipSizeZ = 0; MapTipSizeZ < 100; MapTipSizeZ++) {
//					m_MapTip[MapTipNumx][MapTipNumz][MapTipSizeX][MapTipSizeZ].eType = nsModelData::None;
//				}
//			}
//		}
//	}*/
//}

int MapData::GetNumModels() {
	return m_InitEnemyDataQue.size();
}

bool MapData::GetInitEnemyData(nsModelData::EnemyModelInitData*const pOut) {
	if (m_InitEnemyDataQue.empty()) {
		return true;
	}

	*pOut = m_InitEnemyDataQue.front();
	m_InitEnemyDataQue.pop();
	//pOut
	return false;
}

void MapData::MapInit() {
	for (int x = 0; x < MyGround::Modelx; x++) {
		for (int z = 0; z < MyGround::Modelz; z++)
		{
			if (x == 0 && z == 0) {
				MapRandomizeMaptip(MapTip0_0::LV1_0_0, MapTip0_0::LV2_0_0, MapTip0_0::LV3_0_0, MapTip0_0::LV4_0_0, MapTip0_0::LV6_0_0, x, z);
			}
			else if (x == 1 && z == 1) {
				MapRandomizeMaptip(MapTip1_1::LV1_1_1, MapTip1_1::LV2_1_1, MapTip1_1::LV3_1_1, MapTip1_1::LV4_1_1, MapTip1_1::LV6_1_1, x, z);
			}
			else {
				MapRandomizeMaptip(MapTipElse::LV1_ELSE, MapTipElse::LV2_ELSE, MapTipElse::LV3_ELSE, MapTipElse::LV4_ELSE, MapTipElse::LV6_ELSE, x, z);
			}
		}
	}
}

void MapData::MapRandomizeMaptip(unsigned int LV1Num, unsigned int LV2Num, unsigned int LV3Num, unsigned int LV4Num, unsigned int LV6Num, unsigned int MapTipNumX, unsigned int MapTipNumZ)
{
	if (MapTipNumX >= MyGround::Modelx) {
		return;
	}
	if (MapTipNumZ >= MyGround::Modelz) {
		return;
	}
	
	int MaxLV = 0;
	if (LV6Num != 0) {
		MaxLV = 6;
	}
	else if (LV4Num != 0) {
		MaxLV= 4;
	}
	else if (LV3Num != 0) {
		MaxLV=3;
	}
	else if (LV2Num != 0) {
		MaxLV=2;
	}
	else if (LV1Num == 0) {
		return;
	}
	int MaxSize = MaxLV * 2 - 1;

	int MapTipSizeX = 100;
	int MapTipSizeZ = 100;

	if (MapTipNumX == 0 && MapTipNumZ == 0) {
		MapTipSizeX = 90;
		MapTipSizeZ = 90;
		//�X�^�[�g�n�_�Ȃ炿����ƕύX
	}

	unsigned int NumCanSettingX = MapTipSizeX / MaxSize;//��ԑ傫�ȃT�C�Y�̕������Ƃɂ��ꂪX�����ɂȂ炢���ݒ�ł��邩
	unsigned int NumCanSettingZ = MapTipSizeZ / MaxSize;//��ԑ傫�ȃT�C�Y�̕������Ƃɂ��ꂪZ�����ɂȂ炢���ݒ�ł��邩

	unsigned int CanSettingMaxLVModelNum = NumCanSettingX * NumCanSettingZ;//X��Z�̌���������ƁA���̃}�b�v�T�C�Y�ɃZ�b�g�ł���}�b�N�X���x���̃T�C�Y�ŋ�؂�����悪�������邩�����߂��

	unsigned int SumNum = LV1Num + LV2Num + LV3Num + LV4Num + LV6Num;//�Z�b�g���������f���̐��͂�������̂�

	if (SumNum > CanSettingMaxLVModelNum)//�Z�b�g�ł���}�b�v�`�b�v�̐������Z�b�g���鐔������������@���^�[��
	{
		return;
	}
	std::vector<std::vector<nsModelData::EnemyModelInitData>> MapTip;//�ő�̑傫���̃��f�������ƂɃ}�b�v�`�b�v�Ƀf�[�^�𖄂ߍ���ł���
																//������V���b�t�����邱�Ƃɂ���āA�}�b�v�`�b�v�̃V���b�t�����s��

	MapTip.resize(NumCanSettingX);
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		MapTip[x].resize(NumCanSettingZ);//�}�b�v�`�b�v�̐������f�[�^���쐬
	}
	unsigned int Cnt = 0;
	//int iLV = 1;

	//�܂��̓f�[�^����ׂ�
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			if (Cnt < SumNum) {
				if (Cnt < LV1Num) {
					MapTip[x][z].iLV = 1;
				}
				else if (Cnt < LV1Num + LV2Num) {
					MapTip[x][z].iLV = 2;
				}
				else if (Cnt < LV1Num + LV2Num + LV3Num) {
					MapTip[x][z].iLV = 3;
				}
				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num) {
					MapTip[x][z].iLV = 4;
				}
				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num + LV6Num) {
					MapTip[x][z].iLV = 6;
				}
				Cnt++;
			}
		}
	}


	Cnt = 0;

	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++)
		{
			//�傫���ɂ���ă}�b�v�`�b�v���̈ʒu�𒲐�
			MapTip[x][z].vPos.x = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);
			MapTip[x][z].vPos.z = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);//�{���͉����c���Œ�������ׂ��Ȃ񂾂낤����
			Cnt++;
			if (Cnt >= SumNum) {
				x = NumCanSettingX;
				z = NumCanSettingZ;
				//���[�v�𔲂���
			}
		}
	}

	//�����ŃV���b�t��
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			int randamx = rand() % NumCanSettingX;
			int randamz = rand() % NumCanSettingZ;

			nsModelData::EnemyModelInitData Backup = MapTip[x][z];
			MapTip[x][z] = MapTip[randamx][randamz];
			MapTip[randamx][randamz] = Backup;
		}
	}


	//���ɃL���[�����ƂɎ��ۂ̃|�W�V�������v�Z����

	for (unsigned int maptipx = 0; maptipx < NumCanSettingX; maptipx++) {
		for (unsigned int maptipz = 0; maptipz < NumCanSettingZ; maptipz++)
		{
			if (MapTip[maptipx][maptipz].iLV != 0)
			{
				D3DXVECTOR3 tmpPos(0, 0, 0);
				tmpPos.x = maptipx * MyPoly::Poly::PolySize * MaxSize;//�܂��̓}�b�v�`�b�v�̓x�̈ʒu�Ȃ̂���c��
				tmpPos.z = maptipz * MyPoly::Poly::PolySize * MaxSize;
				tmpPos.x += MapTip[maptipx][maptipz].vPos.x * MyPoly::Poly::PolySize;//�}�b�v�`�b�v���̈ʒu�𑫂�����ł�����
				tmpPos.z += MapTip[maptipx][maptipz].vPos.z * MyPoly::Poly::PolySize;
				if (MapTipNumX == 0 && MapTipNumZ == 0) {//�X�^�[�g�n�_�̃}�b�v�`�b�v�̏ꍇ�̂�
					tmpPos.x += 10 * MyPoly::Poly::PolySize;
					tmpPos.z += 10 * MyPoly::Poly::PolySize;
				}
				else {
					tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//����ɑ傫�ȑS�̂̃}�b�v�̃}�b�v�`�b�v�̍��W�ɕϊ�
					tmpPos.z += MapTipNumZ * GroundPanel::PanelSize;
				}
				nsModelData::EnemyModelInitData PushData;
				//PushData.vPos.x = tmpx;
				PushData.vPos = tmpPos;
				PushData.iLV = MapTip[maptipx][maptipz].iLV;
				m_InitEnemyDataQue.push(PushData);
				//m_iNumModelsCnt++;
			}
		}
	}

}

//
void MapData::NoStartMapRandomizeMaptip(unsigned int LV1Num,unsigned int LV2Num,unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num, unsigned int MapTipNumX, unsigned int MapTipNumZ)
{
	if (MapTipNumX >= MyGround::Modelx) {
		return;
	}
	if (MapTipNumZ >= MyGround::Modelz) {
		return;
	}
	if (MapTipNumX == 0 && MapTipNumZ == 0) {
		return;//�X�^�[�g�n�_�̐ݒ�͂��Ȃ�
	}
	int MaxLV = 5;
	if (LV5Num == 0) {
		MaxLV--;
	}else if (LV4Num == 0) {
		MaxLV--;
	}else if (LV3Num == 0) {
		MaxLV--;
	}else if (LV2Num == 0) {
		MaxLV--;
	}else if (LV1Num == 0) {
		return;
	}
	int MaxSize = MaxLV * 2 - 1;

	int MapTipSizeX = 100;
	int MapTipSizeZ = 100;

	unsigned int NumCanSettingX = MapTipSizeX / MaxSize;//��ԑ傫�ȃT�C�Y�̕������Ƃɂ��ꂪX�����ɂȂ炢���ݒ�ł��邩
	unsigned int NumCanSettingZ = MapTipSizeZ / MaxSize;//��ԑ傫�ȃT�C�Y�̕������Ƃɂ��ꂪZ�����ɂȂ炢���ݒ�ł��邩

	unsigned int CanSettingMaxLVModelNum = NumCanSettingX * NumCanSettingZ;//X��Z�̌���������ƁA���̃}�b�v�T�C�Y�ɃZ�b�g�ł���}�b�N�X���x���̃T�C�Y�ŋ�؂�����悪�������邩�����߂��

	unsigned int SumNum = LV1Num + LV2Num + LV3Num + LV4Num + LV5Num;//�Z�b�g���������f���̐��͂�������̂�

	if (SumNum > CanSettingMaxLVModelNum)//�Z�b�g�ł���}�b�v�`�b�v�̐������Z�b�g���鐔������������@���^�[��
	{
		return;
	}
	std::vector<std::vector<nsModelData::EnemyModelInitData>> MapTip;//�ő�̑傫���̃��f�������ƂɃ}�b�v�`�b�v�Ƀf�[�^�𖄂ߍ���ł���
																//������V���b�t�����邱�Ƃɂ���āA�}�b�v�`�b�v�̃V���b�t�����s��

	MapTip.resize(NumCanSettingX);
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		MapTip[x].resize(NumCanSettingZ);//�}�b�v�`�b�v�̐������f�[�^���쐬
	}
	unsigned int Cnt = 0;
	//int iLV = 1;

	//�܂��̓f�[�^����ׂ�
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			if (Cnt < SumNum) {
				if (Cnt < LV1Num) {
					MapTip[x][z].iLV = 1;
				}
				else if (Cnt < LV1Num + LV2Num) {
					MapTip[x][z].iLV = 2;
				}
				else if (Cnt < LV1Num + LV2Num+LV3Num) {
					MapTip[x][z].iLV = 3;
				}
				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num) {
					MapTip[x][z].iLV = 4;
				}
				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num + LV5Num) {
					MapTip[x][z].iLV = 5;
				}
			}
		}
	}
	

	Cnt = 0;

	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++)
		{
			//�傫���ɂ���ă}�b�v�`�b�v���̈ʒu�𒲐�
			MapTip[x][z].vPos.x = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);
			MapTip[x][z].vPos.z = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);//�{���͉����c���Œ�������ׂ��Ȃ񂾂낤����
			Cnt++;
			if (Cnt >= SumNum) {
				x = NumCanSettingX;
				z = NumCanSettingZ;
				//���[�v�𔲂���
			}
		}
	}

	//�����ŃV���b�t��
	for (unsigned int x = 0; x<NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			int randamx = rand() % NumCanSettingX;
			int randamz = rand() % NumCanSettingZ;

			nsModelData::EnemyModelInitData Backup = MapTip[x][z];
			MapTip[x][z] = MapTip[randamx][randamz];
			MapTip[randamx][randamz] = Backup;
		}
	}


	//���ɃL���[�����ƂɎ��ۂ̃|�W�V�������v�Z����

	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++)
		{
			if (MapTip[x][z].iLV != 0)
			{
				D3DXVECTOR3 tmpPos(0,0,0);
				tmpPos.x = x * MyPoly::Poly::PolySize * MaxSize;//�܂��̓}�b�v�`�b�v�̓x�̈ʒu�Ȃ̂���c��
				tmpPos.z = z * MyPoly::Poly::PolySize * MaxSize;
				tmpPos.x += MapTip[x][z].vPos.x * MyPoly::Poly::PolySize;//�}�b�v�`�b�v���̈ʒu�𑫂�����ł�����
				tmpPos.z += MapTip[x][z].vPos.z * MyPoly::Poly::PolySize;
				tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//����ɑ傫�ȑS�̂̃}�b�v�̃}�b�v�`�b�v�̍��W�ɕϊ�
				tmpPos.z += MapTipNumZ * GroundPanel::PanelSize;
				nsModelData::EnemyModelInitData PushData;
				//PushData.vPos.x = tmpx;
				PushData.vPos = tmpPos;
				PushData.iLV = MapTip[x][x].iLV;
				m_InitEnemyDataQue.push(PushData);
				//m_iNumModelsCnt++;
			}
		}
	}

}

//bool MapData::InitializeMapTip(int MapTipNumX, int MapTipNumY, int MinSize, int MaxSize, int MinModelNum, int MaxModelNum)
//{
//	//int SumModelNum = MinModelNum + MaxModelNum;
//
//	//int OneMapSet = 100 / SumModelNum;//�}�b�v�`�b�v�̃T�C�Y��100������
//
//	//if (MaxSize > OneMapSet)	 {
//	//	return false;
//	//}
//	return true;
//}



//
//void MapData::InitMapTip0_0() {
//	unsigned int now = (unsigned int)time(0);
//	srand(now);
//	//for (int i = 0; i < InitMapTip0_0::LV1Num;)
//	//{
//		/*int tmpx = rand() % 90;
//		int tmpz = rand() % 90;
//
//		if (m_MapTip[0][0][tmpx][tmpz].eType == nsModelData::None)
//		{
//			m_MapTip[0][0][tmpx][tmpz].eType = nsModelData::Enemy;
//		}
//		else {
//			for(int x = tmpx,bool CanSet = false;)
//		}*/
//	//}
//}


//�v���C���[�̃f�[�^���ۑ����悤���Ǝv���������
//�����ŊǗ�����͓̂G�̃f�[�^�����ɂ��悤
//�G�͂��������}�b�v�O�ɑ̂��o�邱�Ƃ���ł��Ȃ��悤�ɂ���
//�Ë�����

//���傢�ƍl����

//���̊֐��ł܂��̓}�b�v�͈̔͊O�ɂ͂ł邱�Ƃ͍l������
//���̏ꏊ�ɓG��z�u�ł��邩��T�����߂̊֐��ɂ���
//����œG�̔z�u�����������_���ɂ���
//�����A���x���̒Ⴂ���̂��Ȃ�ׂ��߂��ɒu������
//
//bool MapData::InitCanSetPos(float fPosX,float fPosZ,int SizeX,int SizeZ) {
//	int iPosX = fPosX / MyPoly::Poly::PolySize;//�ǂ�����T��
//	int iPosZ = fPosZ / MyPoly::Poly::PolySize;//
//
//	if (iPosX < 0 || iPosX + SizeX >= MAP_DATA_STATIC::MapSizeX) {
//		return false;
//	}
//	if (iPosZ < 0 || iPosZ + SizeZ >= MAP_DATA_STATIC::MapSizeZ) {
//		return false;
//	}
//
//	for (int x = iPosX; x < iPosX + SizeX; x++) {
//		for (int z = iPosZ; z < iPosZ + SizeZ; z++) {
//			if (m_MapInfo[iPosX][iPosZ].eType != nsModelData::None) {
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//
//
//bool MapData::InitSetPos(float fPosX, float fPosZ, int SizeX, int SizeZ, const nsModelData::ModelData& SetModelData) {
//	int iPosX = fPosX / MyPoly::Poly::PolySize;//�ǂ�����T��
//	int iPosZ = fPosZ / MyPoly::Poly::PolySize;//
//
//	if (iPosX < 0 || iPosX + SizeX >= MAP_DATA_STATIC::MapSizeX) {
//		return false;
//	}
//	if (iPosZ < 0 || iPosZ + SizeZ >= MAP_DATA_STATIC::MapSizeZ) {
//		return false;
//	}
//
//	for (int x = iPosX; x < iPosX + SizeX; x++) {
//		for (int z = iPosZ; z < iPosZ + SizeZ; z++) {
//			if (m_MapInfo[iPosX][iPosZ].eType != nsModelData::None) {
//				return false;
//			}
//		}
//	}
//
//	for (int x = iPosX; x < iPosX + SizeX; x++) {
//		for (int z = iPosZ; z < iPosZ + SizeZ; z++) {
//			m_MapInfo[iPosX][iPosZ] = SetModelData;//�󂯎���Ă������f�����������ɃZ�b�g
//		}
//	}
//	return true;
//}
//
////CanSetMaxSizePercentage��0~1.0�͈̔͂̒��Ŏw��
////����̓}�b�N�X�T�C�Y�̑傫���̃{�b�N�X���z�u�ł��邤���̉��p�[�Z���g��z�u���邩�Ƃ�����
////���Ɉ�����z�u�ł��Ȃ��ꍇ��0�p�[�Z���g�ȊO�͈��z�u����
////�t��10�z�u�ł���ꍇ�ɂ����̃p�[�Z���e�[�W��0.1�Ȃ�
////1��z�u����
////�����������̂����肽��
//bool InitializePosMapTip100_100(int MinSize, int MaxSize, float CanSetMaxSizePercentage, std::list<nsModelData::EnemyModelInitData>* pOutList) {
//	//int SumLV = MinSize + MaxSize;
//	int SumSize = MinSize * MinSize + MaxSize * MaxSize;
//
//	int CanSettingSize = 100 * 100 * 0.4;//������100�͒P���Ƀ��f���T�C�Y��100��100�̃T�C�Y�����ۂɃ}�b�v�p�l���̑傫���ɂȂ��Ă��邩��
//	if (SumSize > CanSettingSize) {
//		return false;  //�}�b�v�̃T�C�Y�̂U�O�������傫�Ȃ��͔̂z�u�ł��Ȃ�
//						//�}�b�v������Ƃ��đS���͋l�ߍ��ނ���͂Ȃ��̂�
//	}
//	if (CanSetMaxSizePercentage < 0) {
//		CanSetMaxSizePercentage = 0;
//	}
//	if (CanSetMaxSizePercentage > 1) {
//		CanSetMaxSizePercentage = 1;
//	}
//	int MaxSizeCanSetNum = CanSettingSize / (MaxSize * MaxSize);
//	float Check = MaxSizeCanSetNum * CanSetMaxSizePercentage;
//	int SetMaxSizeNum;
//	if (CanSetMaxSizePercentage != 0 && Check < 1) {
//		SetMaxSizeNum = 1;
//	}
//	else {
//		SetMaxSizeNum = (int)Check;
//	}
//
//
//}
//
