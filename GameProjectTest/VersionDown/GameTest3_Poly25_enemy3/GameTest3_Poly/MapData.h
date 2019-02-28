#include "MyModel.h"
#include "Ground.h"

#include <list>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <queue>
#include "main.h"

#include <math.h>
//マップ上のデータをここに置いておいて
//移動の際に範囲内に敵がいるかをデータを参照して
//渡してあげるみたいなことを考えていたのだけれど
//とりあえず今はアルファを作るほうが先だと考えるので
//軽量化は後回しにしよう


//結局AI作るのに　ある程度の情報がないと話にならないということで
//簡単に情報を保存できるものを作る

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
	//1移動分のパネルサイズ
	static const int MapSizeX = MyGround::Modelx * GroundPanel::PanelSize / MyPoly::Poly::PolySize;//一枚のマップサイズを一つのポリーサイズで割ってそれをマップチップ分だけ用意
	static const int MapSizeZ = MyGround::Modelz * GroundPanel::PanelSize / MyPoly::Poly::PolySize;
}

class MapData {

public:	

	MapData();
	void Init();

	int GetNumModels();
	bool GetInitEnemyData(nsModelData::EnemyModelInitData*const pOut);//ポインターの参照先を変えない

	
	bool SetInitMapData(int Index, const D3DXVECTOR3& vPos,int Size);
	
	
	//bool GetMapData()

	void GetMapData(std::queue<int> *pOut, float LeftX, float RightX, float ForwardZ, float BackwardZ);


	bool SortAndIndexCheck(int* IndexNum);

	//void isErrorNotIndextoRePositioningResize(D3DXVECTOR3*const vPos,int ErrorIndex);
	//1つのマップチップがあるとして、その中で割合を渡して、実際にいくつのものが渡せるかわからないけれど　配置できる個数を計算したい
	//これが1つのマップチップには基本的にレベルが違う種類を2つから3つ配置するようにする
	//bool InitializePosMapTip100_100(int MinSize,int MaxSize,float MinPercentage,std::list<nsModelData::EnemyModelInitData>* pOutList);
	//bool InitializePosMapTip100_100(int MinSize, int CenterSize,int MaxSize, float MinPercentage, std::list<nsModelData::EnemyModelInitData>* pOutList);

	//bool InitializeMapTip(int MapTipNumX, int MapTipNumY, int MinSize, int MaxSize, int MinModelNum, int MaxModelNum);
	//まずはこの関数で配置できるのかを調べる
	//bool InitCanSetPos(float fPosxX, float fPosZ, int SizeX, int SizeZ);
	//その後配置、ただし念のために本当にデータがないのかはチェックをする
	//bool InitSetPos(float fPosX, float fPosZ, int SizeX, int SizeZ,const nsModelData::ModelData& SetModelData);
private:
	
	//動的配列で確保したベクター配列にリストを入れてありそのリストデータ自体がModelDataを保有する
	//やりたいことを考えた際にこれが一番ベストだと思った
	//ただ複雑にならないか心配
	//std::vector< std::vector<std::list<nsModelData::ModelData>>> m_MapInfoList;
	std::vector< std::vector<int>> m_MapInfo;


	std::queue<nsModelData::EnemyModelInitData> m_InitEnemyDataQue;
	//unsigned int m_iNumModelsCnt;


	//void SetMapInfo(int x, int z, int size, int index);

	//マップの配置数を本来はテキストデータなどから読み込んで
	//それをもとにいじれるようにしておきたいが
	//動作確認と、そこまでを作る時間があるかわからないので
	//とりあえず、動作確認ようにデータを作る
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
	//4次元配列になるで
	//std::vector< std::vector<nsModelData::ModelData>> m_MapTip[MyGround::Modelx][MyGround::Modelz];

	//現状　キングのレベルを5と設定するとして、ランダマイズするものを作ろう

	//改造して
	//void NoStartMapRandomizeMaptip(unsigned int LV1Num,unsigned int LV2Num,unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num,unsigned int MapTipNumX,unsigned int MapTipNumZ);

	void MapRandomizeMaptip(unsigned int LV1Num, unsigned int LV2Num, unsigned int LV3Num, unsigned int LV4Num, unsigned int LV5Num, unsigned int MapTipNumX, unsigned int MapTipNumZ);

	
	std::list<int> IndexChecker;

	int m_iObjectNum;
	//void StartMapRandamizeMaptip(unsigned int LV1Num,unsigned int )
	//初期位置
	//enum InitMapTip0_0 {
	//	LV1Num = 12,
	//};
	//void InitMapTip0_0();
};
#endif