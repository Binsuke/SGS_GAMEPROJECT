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
//PosInitを使って最初表示を行っていたが
//モデルクラスは変更を行い、LVを渡すことでモデルを作成
//PosInitは消去を行いInitLvでレベルと初期位置を渡し生成する
//
class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	
	//ポジションイニシャライズ
	MyModel();
	~MyModel();
	//レンダー関数
	
	//現状レンダリングするのはこれ
	//ほかのは使わないので削除予定
	virtual void Render(D3DXMATRIX view,D3DXMATRIX proj);

	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran);
	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation);
	//void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran,D3DXMATRIX rotation, D3DXMATRIX scale);
	

	//センターを返す
	D3DXVECTOR3 GetCenter();// { return m_vCenter; }
	//ポジションをセット
	void SetPos(D3DXVECTOR3 vPos);
	//ポジションセット
	void SetPos(float x, float y, float z);

	D3DXVECTOR3 GetPos() { return m_vPos; }

	//現状使ってない
	//D3DXVECTOR3 GetColisionPos();// { return m_vPos + m_vAnimePos; }

	//現状のワールド座標のベクトルをもらってそれに対するローカルの移動を行う
	//void Move(float deltaTime, const D3DXVECTOR3& cvForwardVec);
	//アニメーションバージョン
	bool MoveA(float deltaTime, const D3DXVECTOR3& cvForwardVec);

	//リバースアニメーション
	//bool MoveReverceA(float deltaTime, const D3DXVECTOR3& cvForwardVec);

	//モデルのレベルをセットする
	virtual void InitLv(int Lv);
	//レベル改良版

	//void InitLv()

	//レベルを1上げる
	void LVUp();

	//レベルアップ改良
	void LVUpA(MyModel* pModel);


	void ReverceOn() { m_bAnimeReverceFlg = true; }


	//レベルを１下げる
	virtual int LVDown();


	//当たり判定
	bool Colision(MyModel* pModel);



	bool Colision(MyModel* pModelA, MyModel* pModelB);


	//カメラにどのくらいカメラを下げるかのマージンを返す
	D3DXVECTOR3 GetCameraMargin();
	//カメラのターゲット場所を返す
	D3DXVECTOR3 GetCameraTarget();

	//現状のサイズを返す
	float GetSize();

	//レベルを返す
	int GetLV() { return m_iLV; }

	//コリジョンの計算（モデルが相手の）
	//bool ColisionCalc(MyModel* pModel);

	bool GroundCheck(float deltaTime);

	//void KeyInput(float deltaTime);
	//ここをポインターにしたときに問題がでるんじゃないか？と思ったのだけれど
	//コピーコンストラクターが呼び出されたときにどうする？と思ったが
	//そもそもPOSのようにモデル毎に必要なものではないため
	//コピーコンストラクターが呼ばれればもとになったデータのポインターがコピーされるはず
	//と思ったがこれはポインターにはできないな
	//コピーが行われるのでもとになったデータの情報のポインターもコピー
	//されるわけなんだけれど　コピー先のデータが消えた場合
	//元のデータになっていたm_Cubeのデータが消えてしまう
	//なのでもとに戻す；コピーを行わないの前提なら問題はないけれど
	//何があるかわからないのでポインターにするのはやめておこう
	//本当は、シーンを作った際にロードをするなどの時にメモリを確保したいので
	//ポインターにして、読み込みなどはすべてinit関数で行うようにするなどしたい
	//また、ポインターの解放もデストラクターで行うのではなくて
	//リリース関数で行うのが望ましい
	//なぜかというと、ここをポインターにした際に、コピーコンストラクタが働いてしまうと
	//ポインターの参照先がコピーされてしまうことになり
	//デストラクターでポインターを消去してしまうと
	//もしもコピーコンストラクターでデータをコピーしてしまったときに
	//コピー先のデータが消去された際に
	//コピー元になったデータまで消去されてしまうというバグが起こりかねない
	//なのでポインターにするのは避けるべきなのだとは思うけれど
	//とりあえずコピーコンストラクターをそもそもプライベートにして対応するなり
	//いろいろ対応方法はあるけれど
	//自分の経験不足でそれを試している時間もないため
	//いったんメモリは食うけれどポインターで保持するのはやめておくことにする
	//ただ、この上層のシーンクラスでこのクラスを使うデータを
	//ポインターにしてそちらをinit,release関数を用意して
	//明示的にポインターの解放を行うようにすることで
	//回避できるのかもしれない
	//正直メモリに関する知識が少し不足している部分があるので
	//勉強しなければならないなと感じる
	//ただ、この辺りはパソコンのスペックの向上などもあり
	//昔ほどメモリを切り詰めてデータを作る必要があるのかは
	//現状のゲーム制作環境をしらないのでわからない
	//ただどのくらいのメモリがあってそのうちのどのくらいのメモリを使っていいか
	//などを計算してやらないとオーバーフローを起こす可能性もあるので
	//そういったところの開発を行うことになったら　勉強するべき

	//キューブ描画用のクラス
	MyPoly::Poly m_Cube;
	//バーテックスシェーダー
	VertexShaderUtil m_VertexShader;
	//ピクセルシェーダー
	PixelShaderUtil m_PixelShader;
	//コンスタントバッファー
	MyConstantBuffer m_ConstantBuffer;


protected:
	//アニメーションしない 現状使わない
	//void MoveLocalForward(float deltaTime);
	//void MoveLocalBackward(float deltaTime);
	//void MoveLocalRight(float deltaTime);
	//void MoveLocalLeft(float deltaTime);

	//作成していたが使わなくていいもの
	//bool AnimationLocalRight(float deltaTime);
//	bool AnimationLocalLeft(float deltaTime);
//	bool AnimationLocalForward(float deltaTime);
//	bool AnimationLocalBackward(float deltaTime);
	//------

	//ローカル座標のアニメーション　//リバースなし
	//bool AnimationLocalRightA(float deltaTime);
	//bool AnimationLocalLeftA(float deltaTime);
	//bool AnimationLocalForwardA(float deltaTime);
	//bool AnimationLocalBackwardA(float deltaTime);

	//アニメーションのリバース
	bool AnimationLocalRightR(float deltaTime);
	bool AnimationLocalLeftR(float deltaTime);
	bool AnimationLocalForwardR(float deltaTime);
	bool AnimationLocalBackwardR(float deltaTime);

	//これは今は使わない
	//void AnimationMargineSet();
	//これも今は使わない
	//void AnimationMargineY(float deltaTime);

	//最初のレベルをセット
	void SetLV1();

	//モデルを中心に
	void InitAdjustment();

	//モデルのセンターを更新
	void UpdateCenter();

	//モデルのサイズアップ
	void ModelSizeUp();
	//モデルのサイズダウン
	void ModelSizeDown();

	

	//現在アニメーションによって移動している量
	D3DXVECTOR3 m_vAnimePos;
	//アニメーションによる回転量
	D3DXMATRIX m_mAnimeRot;

	//右回転用のアニメーションの回転量
	float m_fAnimationRotX;
	//左回転用のアニメーションの回転量
	float m_fAnimationRotZ;
	//今は使ってない
	float m_fAnimationMargineY;

	//アニメーションする時間
	float m_fAnimTime;//second
	//アニメーションをレベルによって変更するためのディレイ設定用
	float m_fAnimTimeDelay;
	//アニメーションしてるかの設定
	bool m_bAnimeFlg;

	//アニメーションを今どのくらいしてるのかの時間
	float m_fAnimeWaitTime;

	//リバースフラグ
	bool m_bAnimeReverceFlg;

	bool m_bAnimeReverceInitFlg;

	float m_fAnimeReverceTime;

	float m_fAnimeReverceRot;

	D3DXVECTOR3 m_vAnimeRevercePos;

	//レンダリングフラグ
	bool m_bRenderflg;


	//アニメーションを行う際の最初のポジション保存用
	D3DXVECTOR3 m_vAnimationPrevPos;

	//デバイス
	ID3D11Device* m_pDevice;
	//デバイスコンテキスト
	ID3D11DeviceContext* m_pDeviceContext;

	//フォワード　（現状使ってない
	D3DXVECTOR3 m_vForward;
	//上方向　（現状使ってない
	D3DXVECTOR3 m_vUp;
	//右方向　（現状使ってない
	D3DXVECTOR3 m_vRight;

	//ローカル座標での前方向
	D3DXVECTOR3 m_vLocalForward;
	//ローカル座標での上方向
	D3DXVECTOR3 m_vLocalUp;
	//ローカル座標での右方向
	D3DXVECTOR3 m_vLocalRight;

	//現在のレベル
	int m_iLV;
	//現状使われてない
	//float m_fTransDir;
	//現状使われてない
	//float m_fRotSize;

	//現状使われてない
	//D3DXMATRIX m_mTransform;
	//現状使われてない
	//D3DXMATRIX m_mRotation;

	//キューブを真ん中にずらすための行列
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

	//モデルのサイズ
	int m_iModelSizeX;
	int m_iModelSizeY;
	int m_iModelSizeZ;

	//モデルの半分のサイズ
	int m_iModelHalfSizeX;//基本的に奇数にする、中心を計算するのがめんどくさいだけ
	int m_iModelHalfSizeY;
	int m_iModelHalfSizeZ;

	//1つのポリゴンのサイズ
	float m_fPolySize;

	//1つのポリゴンの半分のサイズ
	float m_fPolyHalfSize;

	//キューブのセンター
	D3DXVECTOR3 m_vCenter;
	//キューブのポジション
	D3DXVECTOR3 m_vPos;
	//ローカル座標の1つのキューブのマトリックス変数
	//実質これが増えれば、表示されるキューブの数が増える
	std::list<D3DXMATRIX> m_lmModelMat;

	bool m_bFallFlg;
	//void FallAnimationRight(float deltaTime);
	bool FallAnimationLeft(float deltaTime);

	bool FallAnimationRight(float deltaTime);

	bool FallAnimationBackward(float deltaTime);
	bool FallAnimationForward(float deltaTime);


};
#endif