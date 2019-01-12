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

namespace MyPoly{
class Poly {
public:
	Poly();
	void Init();
	void Release();
	void Render(ID3D11DeviceContext* inDeviceContext,D3DXMATRIX mW);//worldの変換行列を渡すことで　そこに移動する
	HRESULT CreateVertexBuffer(ID3D11Device * inDevice);//バーテックスバッファー作成用
	HRESULT CreateTexture(ID3D11Device* inDevice);
protected:
private:
	bool InitFlg;
	SimpleVertex *m_pVertices;
	ID3D11Buffer* m_pVertexBuffer;				//バーテックスバッファー

	ID3D11SamplerState* m_pSampleLinear;			//テクスチャーのサンプラー
												//サンプラーとはテクスチャをどのように扱うか、テクスチャの画像よりも外にある端はどのように扱うか
												//例えばミラーや同じ色で塗りつぶすなどの設定をいれておいて　教えるための情報源

	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー本体　　シェーダーに渡すリソース


};
}
#endif