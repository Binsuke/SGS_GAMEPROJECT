#include "MapData.h"
MapData::MapData() :m_iObjectNum(0) {

}

void MapData::Init() {
	//まずはベクタークラスによって動的に配列を確保
	//2次元配列を作る。ベクタークラスだが
	//実際には2次元配列のように扱うことができる
	m_MapInfo.resize(MAP_DATA_STATIC::MapSizeX);

	for (int i = 0; i < MAP_DATA_STATIC::MapSizeX; i++) {
		m_MapInfo[i].resize(MAP_DATA_STATIC::MapSizeZ);
	}
	for (int x = 0; x < MAP_DATA_STATIC::MapSizeX; x++) {
		for (int z = 0; z < MAP_DATA_STATIC::MapSizeZ; z++) {
			m_MapInfo[x][z] = -1;
		}
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
//bool MapData::SortAndIndexCheck(int* IndexNum) {
//	IndexChecker.sort();
//
//	int CheckCnt = 0;
//	for (auto itr = IndexChecker.begin(); itr != IndexChecker.end(); itr++) {
//		if (CheckCnt != *itr) {
//			*IndexNum = CheckCnt;
//			return true;
//		}
//		CheckCnt++;
//	}
//
//	if (CheckCnt == m_iObjectNum) {
//		MessageBoxA(g_pMain->m_hWnd, "ok", "", MB_OK);
//	}
//	else {
//		MessageBoxA(g_pMain->m_hWnd, "error", "", MB_OK);
//	}
//	return false;
//}
//
//void MapData::isErrorNotIndextoRePositioningResize(D3DXVECTOR3*const vPos,int ErrorIndex) {
//	float tmpx = vPos->x;
//	float tmpz = vPos->z;
//	tmpx + MyPoly::Poly::PolySize;
//	tmpz + MyPoly::Poly::PolySize;
//
//	int checkx = tmpx / MyPoly::Poly::PolySize;
//	int checkz = tmpz / MyPoly::Poly::PolySize;
//
//	for (int x = checkx; x < MAP_DATA_STATIC::MapSizeX; x++)
//	{
//		for (int z = checkz; z < MAP_DATA_STATIC::MapSizeZ; z++) {
//			if (m_MapInfo[x][z] == -1) {
//				vPos->x = x * MyPoly::Poly::PolySize;
//				vPos->z = z * MyPoly::Poly::PolySize;
//				m_MapInfo[x][z] == ErrorIndex;
//			}
//		}
//	}
//
//}

bool MapData::EnemyIsNone(float Leftx, float Rightx, float Forwardz, float Backwardz, int thisindex) {
	int iLeftX = Leftx / MyPoly::Poly::PolySize;
	int iRightX = Rightx / MyPoly::Poly::PolySize;
	int iForwardZ = Forwardz / MyPoly::Poly::PolySize;
	int iBackwardZ = Backwardz / MyPoly::Poly::PolySize;


	for (int x = iLeftX; x < iRightX; x++) {
		for (int z = iBackwardZ; z < iForwardZ; z++) {
			if (x >= 0 && x < MAP_DATA_STATIC::MapSizeX
				&& z >= 0 && z < MAP_DATA_STATIC::MapSizeZ) {
				if (m_MapInfo[x][z]!= -1 && m_MapInfo[x][z] != thisindex) {
					return true;
				}
			}
		}
	}
	return false;
}


void MapData::ClearMapData() {
	//for (int x = 0; x < MAP_DATA_STATIC::MapSizeX; x++) {
	//	for (int z = 0; z < MAP_DATA_STATIC::MapSizeZ; z++) {
	//		//m_MapInfo[x][z] = -1;
	//	}
	//}
	while (!ClearPosQue.empty()) {
		m_MapInfo[ClearPosQue.front().dataposx][ClearPosQue.front().dataposz] = -1;
		ClearPosQue.pop();
	}
}

bool MapData::CanMoveRight(int index, int numcube) {
	int x = MapInfoPosIndex[index].dataposx;
	int z = MapInfoPosIndex[index].dataposz;

	for (int InfoX = x + numcube; InfoX < x + numcube * 2; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			if (InfoX >= MAP_DATA_STATIC::MapSizeX) {
				return false;
			}
			if (m_MapInfo[InfoX][InfoZ] != -1) {
				return false;
			}
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = -1;
		}
	}

	for (int InfoX = x + numcube; InfoX < x + numcube * 2; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = index;
		}
	}
	MapInfoPosIndex[index].dataposx = x + numcube;
	MapInfoPosIndex[index].dataposz = z;

	return true;
}

bool MapData::CanMoveLeft(int index, int numcube) {
	int x = MapInfoPosIndex[index].dataposx;
	int z = MapInfoPosIndex[index].dataposz;

	for (int InfoX = x - numcube; InfoX < x ; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			if (InfoX < 0) {
				return false;
			}
			if (m_MapInfo[InfoX][InfoZ] != -1) {
				return false;
			}
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = -1;
		}
	}

	for (int InfoX = x - numcube; InfoX < x; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = index;
		}
	}

	MapInfoPosIndex[index].dataposx = x - numcube;
	MapInfoPosIndex[index].dataposz = z;


	return true;
}



bool MapData::CanMoveForward(int index, int numcube) {
	int x = MapInfoPosIndex[index].dataposx;
	int z = MapInfoPosIndex[index].dataposz;

	for (int InfoX = x; InfoX < x + numcube ; InfoX++) {
		for (int InfoZ = z + numcube; InfoZ < z + numcube * 2; InfoZ++) {
			if (InfoZ >= MAP_DATA_STATIC::MapSizeZ) {
				return false;
			}
			if (m_MapInfo[InfoX][InfoZ] != -1) {
				return false;
			}
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = -1;
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z + numcube; InfoZ < z + numcube * 2; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = index;
		}
	}


	MapInfoPosIndex[index].dataposx = x;
	MapInfoPosIndex[index].dataposz = z + numcube;


	return true;
}

bool MapData::CanMoveBackward(int index, int numcube) {
	int x = MapInfoPosIndex[index].dataposx;
	int z = MapInfoPosIndex[index].dataposz;

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z - numcube; InfoZ < z ; InfoZ++) {
			if (InfoZ < 0 ) {
				return false;
			}
			if (m_MapInfo[InfoX][InfoZ] != -1) {
				return false;
			}
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z; InfoZ < z + numcube; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = -1;
		}
	}

	for (int InfoX = x; InfoX < x + numcube; InfoX++) {
		for (int InfoZ = z - numcube; InfoZ < z; InfoZ++) {
			m_MapInfo[InfoX][InfoZ] = index;
		}
	}

	MapInfoPosIndex[index].dataposx = x;
	MapInfoPosIndex[index].dataposz = z - numcube;

	return true;
}





bool MapData::SetMapData(int Index, const D3DXVECTOR3& vPos, int Size) {

	int Posx = vPos.x / MyPoly::Poly::PolySize;
	int Posz = vPos.z / MyPoly::Poly::PolySize;

	MapInfoPosIndex[Index].dataposx = Posx;
	MapInfoPosIndex[Index].dataposz = Posz;
	
	for (int x = 0; x < Size; x++) {
		for (int z = 0; z < Size; z++) {
			if (Posx + x < MAP_DATA_STATIC::MapSizeX && Posx + x >= 0
				&& Posz + z >= 0 && Posz + z < MAP_DATA_STATIC::MapSizeZ) {				
				SetDataPosition SetData;
				SetData.dataposx = Posx + x;
				SetData.dataposz = Posz + z;
				if (m_MapInfo[SetData.dataposx][SetData.dataposz] == -1)
				{
					m_MapInfo[SetData.dataposx][SetData.dataposz] = Index;
					ClearPosQue.push(SetData);
				}
			}
		}
	}
	return true;
}




bool MapData::SetInitMapData(int Index, const D3DXVECTOR3& vPos,int Size) {

	int Posx = vPos.x / MyPoly::Poly::PolySize;
	int Posz = vPos.z / MyPoly::Poly::PolySize;

	/*if (Posx >= MAP_DATA_STATIC::MapSizeX) {
		Posx = MAP_DATA_STATIC::MapSizeX - 1;
	}
	if (Posz >= MAP_DATA_STATIC::MapSizeZ) {
		Posz = MAP_DATA_STATIC::MapSizeZ - 1;
	}*/


	MapInfoPosIndex[Index].dataposx = Posx;
	MapInfoPosIndex[Index].dataposz = Posz;

	for (int x = 0; x < Size; x++) {
		for (int z = 0; z < Size; z++) {
			if (Posx + x < MAP_DATA_STATIC::MapSizeX && Posx + x >= 0
				&& Posz + z >= 0 && Posz + z < MAP_DATA_STATIC::MapSizeZ) {
				SetDataPosition SetData;
				SetData.dataposx = Posx + x;
				SetData.dataposz = Posz + z;
				m_MapInfo[SetData.dataposx][SetData.dataposz] = Index;
				ClearPosQue.push(SetData);
			}
		}
	}
	//IndexChecker.push_back(Index);
	return true;
}

void MapData::GetMapData(std::queue<int>*pOut, float LeftX, float RightX, float ForwardZ, float BackwardZ)
{
	int iLeftX = LeftX / MyPoly::Poly::PolySize;
	int iRightX = RightX / MyPoly::Poly::PolySize;
	int iForwardZ = ForwardZ / MyPoly::Poly::PolySize;
	int iBackwardZ = BackwardZ / MyPoly::Poly::PolySize;
	
	if (iLeftX < 0) {
		iLeftX = 0;
	}
	if (iRightX > MAP_DATA_STATIC::MapSizeX) {
		iRightX = MAP_DATA_STATIC::MapSizeX;
	}
	if (iBackwardZ < 0) {
		iBackwardZ = 0;
	}
	if (iForwardZ > MAP_DATA_STATIC::MapSizeZ) {
		iForwardZ = MAP_DATA_STATIC::MapSizeZ;
	}
	std::list<int> SortData;
	for (int x = iLeftX; x < iRightX; x++) {
		for (int z = iBackwardZ; z < iForwardZ; z++) {
			if (m_MapInfo[x][z] != -1) {
				SortData.push_back(m_MapInfo[x][z]);
			}
		}
	}
	SortData.sort();
	int Prev = -1;
	for (auto itr = SortData.begin(); itr != SortData.end(); itr++) {
		if (Prev != *itr) {
			pOut->push(*itr);
			Prev = *itr;
		}
	}
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
	MapInfoPosIndex.resize(m_InitEnemyDataQue.size());
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
		MapTipSizeX = 80;
		MapTipSizeZ = 80;
		//スタート地点ならちょっと変更
	}

	unsigned int NumCanSettingX = MapTipSizeX / MaxSize;//一番大きなサイズの幅をもとにそれがX方向にならいくつ設定できるか
	unsigned int NumCanSettingZ = MapTipSizeZ / MaxSize;//一番大きなサイズの幅をもとにそれがZ方向にならいくつ設定できるか

	unsigned int CanSettingMaxLVModelNum = NumCanSettingX * NumCanSettingZ;//XとZの個数をかけると、このマップサイズにセットできるマックスレベルのサイズで区切った区画がいくつあるかが求めれる

	unsigned int SumNum = LV1Num + LV2Num + LV3Num + LV4Num + LV6Num;//セットしたいモデルの数はいくつあるのか

	if (SumNum > CanSettingMaxLVModelNum)//セットできるマップチップの数よりもセットする数が多かったら　リターン
	{
		return;
	}
	std::vector<std::vector<nsModelData::EnemyModelInitData>> MapTip;//最大の大きさのモデルをもとにマップチップにデータを埋め込んでいく
																//これをシャッフルすることによって、マップチップのシャッフルを行う

	MapTip.resize(NumCanSettingX);
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		MapTip[x].resize(NumCanSettingZ);//マップチップの数だけデータを作成
	}
	unsigned int Cnt = 0;
	//int iLV = 1;

	//まずはデータを並べる
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

	for (unsigned int x = 0; x < NumCanSettingX&&Cnt<SumNum; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ&&Cnt < SumNum; z++)
		{
			//大きさによってマップチップ内の位置を調整
			MapTip[x][z].vPos.x = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);
			MapTip[x][z].vPos.z = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);//本来は横幅縦幅で調整するべきなんだろうけど
			Cnt++;
		}
	}

	//ここでシャッフル
	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			int randamx = rand() % NumCanSettingX;
			int randamz = rand() % NumCanSettingZ;

			nsModelData::EnemyModelInitData Backup = MapTip[x][z];
			MapTip[x][z] = MapTip[randamx][randamz];
			MapTip[randamx][randamz] = Backup;
		}
	}


	//次にキューをもとに実際のポジションを計算する

	for (unsigned int maptipx = 0; maptipx < NumCanSettingX; maptipx++) {
		for (unsigned int maptipz = 0; maptipz < NumCanSettingZ; maptipz++)
		{
			if (MapTip[maptipx][maptipz].iLV != 0)
			{
				D3DXVECTOR3 tmpPos(0, 0, 0);
				tmpPos.x = maptipx * MyPoly::Poly::PolySize * MaxSize;//まずはマップチップの度の位置なのかを把握
				tmpPos.z = maptipz * MyPoly::Poly::PolySize * MaxSize;
				tmpPos.x += MapTip[maptipx][maptipz].vPos.x * MyPoly::Poly::PolySize;//マップチップ内の位置を足しこんであげる
				tmpPos.z += MapTip[maptipx][maptipz].vPos.z * MyPoly::Poly::PolySize;

				//int Posx = MapTip[maptipx][maptipz].vPos.x;
				//int Posz = MapTip[maptipx][maptipz].vPos.z;

				if (MapTipNumX == 0 && MapTipNumZ == 0) {//スタート地点のマップチップの場合のみ
					tmpPos.x += 20 * MyPoly::Poly::PolySize;
					tmpPos.z += 20 * MyPoly::Poly::PolySize;
					//int SetX = 10 + Posx + maptipx * MaxSize;
					//int SetZ = 10 + Posz + maptipz * MaxSize;

					//SetMapInfo(SetX, SetZ, MapTip[maptipx][maptipz].iLV * 2 - 1, m_iObjectNum);
				}
				else {
					tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//さらに大きな全体のマップのマップチップの座標に変換
					tmpPos.z += MapTipNumZ * GroundPanel::PanelSize;
					//int SetX = Posx + maptipx * MaxSize + MapTipNumX * 100;
					//int SetZ = Posx + maptipz * MaxSize + MapTipNumZ * 100;
					//SetMapInfo(SetX, SetZ, MapTip[maptipx][maptipz].iLV * 2 - 1, m_iObjectNum);
				}
				nsModelData::EnemyModelInitData PushData;
				//PushData.vPos.x = tmpx;
				PushData.vPos = tmpPos;
				PushData.iLV = MapTip[maptipx][maptipz].iLV;
				m_InitEnemyDataQue.push(PushData);
				m_iObjectNum++;
				//m_iNumModelsCnt++;
			}
		}
	}

}
//
//void MapData::SetMapInfo(int x, int z, int size, int index) {
//
//	if (x < 0) {
//		x = 0;
//	}
//	if (x >= MAP_DATA_STATIC::MapSizeX) {
//		x = MAP_DATA_STATIC::MapSizeX - 1;
//	}
//	if (z < 0) {
//		z = 0;
//	}
//	if (z >= MAP_DATA_STATIC::MapSizeX) {
//		z = MAP_DATA_STATIC::MapSizeX - 1;
//	}
//
//	for (int sizex = 0; x < size; x++) {
//		for (int sizez = 0; z < size; z++) {
//			if (x + sizex < MAP_DATA_STATIC::MapSizeX && z + sizez < MAP_DATA_STATIC::MapSizeZ) {
//				m_MapInfo[x+sizex][z+sizez] = index;
//			}
//		}
//	}
//	IndexChecker.push_back(index);
//}
//
////
//void MapData::NoStartMapRandomizeMaptip(unsigned int LV1Num,unsigned int LV2Num,unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num, unsigned int MapTipNumX, unsigned int MapTipNumZ)
//{
//	if (MapTipNumX >= MyGround::Modelx) {
//		return;
//	}
//	if (MapTipNumZ >= MyGround::Modelz) {
//		return;
//	}
//	if (MapTipNumX == 0 && MapTipNumZ == 0) {
//		return;//スタート地点の設定はしない
//	}
//	int MaxLV = 5;
//	if (LV5Num == 0) {
//		MaxLV--;
//	}else if (LV4Num == 0) {
//		MaxLV--;
//	}else if (LV3Num == 0) {
//		MaxLV--;
//	}else if (LV2Num == 0) {
//		MaxLV--;
//	}else if (LV1Num == 0) {
//		return;
//	}
//	int MaxSize = MaxLV * 2 - 1;
//
//	int MapTipSizeX = 100;
//	int MapTipSizeZ = 100;
//
//	unsigned int NumCanSettingX = MapTipSizeX / MaxSize;//一番大きなサイズの幅をもとにそれがX方向にならいくつ設定できるか
//	unsigned int NumCanSettingZ = MapTipSizeZ / MaxSize;//一番大きなサイズの幅をもとにそれがZ方向にならいくつ設定できるか
//
//	unsigned int CanSettingMaxLVModelNum = NumCanSettingX * NumCanSettingZ;//XとZの個数をかけると、このマップサイズにセットできるマックスレベルのサイズで区切った区画がいくつあるかが求めれる
//
//	unsigned int SumNum = LV1Num + LV2Num + LV3Num + LV4Num + LV5Num;//セットしたいモデルの数はいくつあるのか
//
//	if (SumNum > CanSettingMaxLVModelNum)//セットできるマップチップの数よりもセットする数が多かったら　リターン
//	{
//		return;
//	}
//	std::vector<std::vector<nsModelData::EnemyModelInitData>> MapTip;//最大の大きさのモデルをもとにマップチップにデータを埋め込んでいく
//																//これをシャッフルすることによって、マップチップのシャッフルを行う
//
//	MapTip.resize(NumCanSettingX);
//	for (unsigned int x = 0; x < NumCanSettingX; x++) {
//		MapTip[x].resize(NumCanSettingZ);//マップチップの数だけデータを作成
//	}
//	unsigned int Cnt = 0;
//	//int iLV = 1;
//
//	//まずはデータを並べる
//	for (unsigned int x = 0; x < NumCanSettingX; x++) {
//		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
//			if (Cnt < SumNum) {
//				if (Cnt < LV1Num) {
//					MapTip[x][z].iLV = 1;
//				}
//				else if (Cnt < LV1Num + LV2Num) {
//					MapTip[x][z].iLV = 2;
//				}
//				else if (Cnt < LV1Num + LV2Num+LV3Num) {
//					MapTip[x][z].iLV = 3;
//				}
//				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num) {
//					MapTip[x][z].iLV = 4;
//				}
//				else if (Cnt < LV1Num + LV2Num + LV3Num + LV4Num + LV5Num) {
//					MapTip[x][z].iLV = 5;
//				}
//			}
//		}
//	}
//	
//
//	Cnt = 0;
//
//	for (unsigned int x = 0; x < NumCanSettingX; x++) {
//		for (unsigned int z = 0; z < NumCanSettingZ; z++)
//		{
//			//大きさによってマップチップ内の位置を調整
//			MapTip[x][z].vPos.x = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);
//			MapTip[x][z].vPos.z = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);//本来は横幅縦幅で調整するべきなんだろうけど
//			Cnt++;
//			if (Cnt >= SumNum) {
//				x = NumCanSettingX;
//				z = NumCanSettingZ;
//				//ループを抜ける
//			}
//		}
//	}
//
//	//ここでシャッフル
//	for (unsigned int x = 0; x<NumCanSettingX; x++) {
//		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
//			int randamx = rand() % NumCanSettingX;
//			int randamz = rand() % NumCanSettingZ;
//
//			nsModelData::EnemyModelInitData Backup = MapTip[x][z];
//			MapTip[x][z] = MapTip[randamx][randamz];
//			MapTip[randamx][randamz] = Backup;
//		}
//	}
//
//
//	//次にキューをもとに実際のポジションを計算する
//
//	for (unsigned int x = 0; x < NumCanSettingX; x++) {
//		for (unsigned int z = 0; z < NumCanSettingZ; z++)
//		{
//			if (MapTip[x][z].iLV != 0)
//			{
//				D3DXVECTOR3 tmpPos(0,0,0);
//				tmpPos.x = x * MyPoly::Poly::PolySize * MaxSize;//まずはマップチップの度の位置なのかを把握
//				tmpPos.z = z * MyPoly::Poly::PolySize * MaxSize;
//				tmpPos.x += MapTip[x][z].vPos.x * MyPoly::Poly::PolySize;//マップチップ内の位置を足しこんであげる
//				tmpPos.z += MapTip[x][z].vPos.z * MyPoly::Poly::PolySize;
//				tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//さらに大きな全体のマップのマップチップの座標に変換
//				tmpPos.z += MapTipNumZ * GroundPanel::PanelSize;
//				nsModelData::EnemyModelInitData PushData;
//				//PushData.vPos.x = tmpx;
//				PushData.vPos = tmpPos;
//				PushData.iLV = MapTip[x][x].iLV;
//				m_InitEnemyDataQue.push(PushData);
//				m_iObjectNum++;
//				//m_iNumModelsCnt++;
//			}
//		}
//	}
//
//}

//bool MapData::InitializeMapTip(int MapTipNumX, int MapTipNumY, int MinSize, int MaxSize, int MinModelNum, int MaxModelNum)
//{
//	//int SumModelNum = MinModelNum + MaxModelNum;
//
//	//int OneMapSet = 100 / SumModelNum;//マップチップのサイズが100だから
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


//プレイヤーのデータも保存しようかと思ったけれど
//ここで管理するのは敵のデータだけにしよう
//敵はそもそもマップ外に体が出ることすらできないようにする
//妥協する

//ちょいと考える

//この関数でまずはマップの範囲外にはでることは考慮せず
//その場所に敵を配置できるかを探すための関数にする
//これで敵の配置を少しランダムにする
//ただ、レベルの低いものをなるべく近くに置きたい
//
//bool MapData::InitCanSetPos(float fPosX,float fPosZ,int SizeX,int SizeZ) {
//	int iPosX = fPosX / MyPoly::Poly::PolySize;//どこかを探す
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
//	int iPosX = fPosX / MyPoly::Poly::PolySize;//どこかを探す
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
//			m_MapInfo[iPosX][iPosZ] = SetModelData;//受け取っていたモデル情報をここにセット
//		}
//	}
//	return true;
//}
//
////CanSetMaxSizePercentageは0~1.0の範囲の中で指定
////これはマックスサイズの大きさのボックスが配置できるうちの何パーセントを配置するかという数
////仮に一つしか配置できない場合は0パーセント以外は一つを配置する
////逆に10個配置できる場合にここのパーセンテージが0.1なら
////1つを配置する
////そういうものが造りたい
//bool InitializePosMapTip100_100(int MinSize, int MaxSize, float CanSetMaxSizePercentage, std::list<nsModelData::EnemyModelInitData>* pOutList) {
//	//int SumLV = MinSize + MaxSize;
//	int SumSize = MinSize * MinSize + MaxSize * MaxSize;
//
//	int CanSettingSize = 100 * 100 * 0.4;//ここの100は単純にモデルサイズの100＊100のサイズが実際にマップパネルの大きさになっているから
//	if (SumSize > CanSettingSize) {
//		return false;  //マップのサイズの６０％よりも大きなものは配置できない
//						//マップがあるとして全部は詰め込むつもりはないので
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
