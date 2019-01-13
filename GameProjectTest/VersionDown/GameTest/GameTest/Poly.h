#ifndef POLY_H
#define POLY_H
//ウィンドウプログラミングに必要なもの
//ヘッダーファイルのインクルード
#include <Windows.h>	
//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>

struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 vTex;
};

struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;   //world * view * projection の行列を渡す
						//このWVPによってモデルの座標をローカル座標から変換する
						//ワールド座標　ビュー行列　プロジェクション行列を合成したものをモデルの行列にかけ合わせることで
						//行列の計算処理を少なくしている。例えば移動スケール回転という行列があった場合に
						//移動成分　スケールに使う成分　回転に使う成分は　行列内で見事に分かれているため
						//4*4行列においてうまいこと合成したものを一括でかけて計算処理を減らすことができる
						//１つの頂点に対して　移動、スケール、回転を毎回やるよりも
						//まとめてやることによって計算回数を３分の１？にできるはず
						//mWVPにおいてもあらかじめ合成しておくことで計算回数を減らしていたはず
						//頂点の数が膨大になるモデルになればなるほどこういった細かな計算回数を減らすことが実行速度に直結してくるらしい

	D3DXVECTOR4 vColor;

};

namespace MyPoly{
class Poly {
public:
	Poly();
	void Init(ID3D11Device* inDevice,ID3D11DeviceContext* inDeviceContext);
	void Release();
	//void SetConstantBuffer();
	void Render(D3DXMATRIX mWVP);//worldの変換行列を渡すことで　そこに移動する
	HRESULT CreateVertexBuffer();//バーテックスバッファー作成用
	HRESULT CreateTexture();
protected:
private:
	void SetConstantBuffer(D3DXMATRIX WVP);
	void InitConstantBuffer();
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	bool InitFlg;
	SimpleVertex *m_pVertices;
	ID3D11Buffer* m_pVertexBuffer;				//バーテックスバッファー

	ID3D11SamplerState* m_pSampleLinear;			//テクスチャーのサンプラー
												//サンプラーとはテクスチャをどのように扱うか、テクスチャの画像よりも外にある端はどのように扱うか
												//例えばミラーや同じ色で塗りつぶすなどの設定をいれておいて　教えるための情報源

	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー本体　　シェーダーに渡すリソース

	ID3D11Buffer* m_pConstantBuffer;			//コンスタントバッファーを作るためのバッファ

};
}
#endif