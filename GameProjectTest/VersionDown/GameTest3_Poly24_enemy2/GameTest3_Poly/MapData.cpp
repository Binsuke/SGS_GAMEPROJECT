#include "MapData.h"

void MapData::Init() {
	//まずはベクタークラスによって動的に配列を確保
	//2次元配列を作る。ベクタークラスだが
	//実際には2次元配列のように扱うことができる
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

	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++)
		{
			//大きさによってマップチップ内の位置を調整
			MapTip[x][z].vPos.x = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);
			MapTip[x][z].vPos.z = rand() % ((MaxLV * 2 - MapTip[x][z].iLV * 2)+1);//本来は横幅縦幅で調整するべきなんだろうけど
			Cnt++;
			if (Cnt >= SumNum) {
				x = NumCanSettingX;
				z = NumCanSettingZ;
				//ループを抜ける
			}
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
				if (MapTipNumX == 0 && MapTipNumZ == 0) {//スタート地点のマップチップの場合のみ
					tmpPos.x += 10 * MyPoly::Poly::PolySize;
					tmpPos.z += 10 * MyPoly::Poly::PolySize;
				}
				else {
					tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//さらに大きな全体のマップのマップチップの座標に変換
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
		return;//スタート地点の設定はしない
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

	unsigned int NumCanSettingX = MapTipSizeX / MaxSize;//一番大きなサイズの幅をもとにそれがX方向にならいくつ設定できるか
	unsigned int NumCanSettingZ = MapTipSizeZ / MaxSize;//一番大きなサイズの幅をもとにそれがZ方向にならいくつ設定できるか

	unsigned int CanSettingMaxLVModelNum = NumCanSettingX * NumCanSettingZ;//XとZの個数をかけると、このマップサイズにセットできるマックスレベルのサイズで区切った区画がいくつあるかが求めれる

	unsigned int SumNum = LV1Num + LV2Num + LV3Num + LV4Num + LV5Num;//セットしたいモデルの数はいくつあるのか

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
			//大きさによってマップチップ内の位置を調整
			MapTip[x][z].vPos.x = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);
			MapTip[x][z].vPos.z = rand() % (MaxLV * 2 - MapTip[x][z].iLV * 2);//本来は横幅縦幅で調整するべきなんだろうけど
			Cnt++;
			if (Cnt >= SumNum) {
				x = NumCanSettingX;
				z = NumCanSettingZ;
				//ループを抜ける
			}
		}
	}

	//ここでシャッフル
	for (unsigned int x = 0; x<NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++) {
			int randamx = rand() % NumCanSettingX;
			int randamz = rand() % NumCanSettingZ;

			nsModelData::EnemyModelInitData Backup = MapTip[x][z];
			MapTip[x][z] = MapTip[randamx][randamz];
			MapTip[randamx][randamz] = Backup;
		}
	}


	//次にキューをもとに実際のポジションを計算する

	for (unsigned int x = 0; x < NumCanSettingX; x++) {
		for (unsigned int z = 0; z < NumCanSettingZ; z++)
		{
			if (MapTip[x][z].iLV != 0)
			{
				D3DXVECTOR3 tmpPos(0,0,0);
				tmpPos.x = x * MyPoly::Poly::PolySize * MaxSize;//まずはマップチップの度の位置なのかを把握
				tmpPos.z = z * MyPoly::Poly::PolySize * MaxSize;
				tmpPos.x += MapTip[x][z].vPos.x * MyPoly::Poly::PolySize;//マップチップ内の位置を足しこんであげる
				tmpPos.z += MapTip[x][z].vPos.z * MyPoly::Poly::PolySize;
				tmpPos.x += MapTipNumX * GroundPanel::PanelSize;//さらに大きな全体のマップのマップチップの座標に変換
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
