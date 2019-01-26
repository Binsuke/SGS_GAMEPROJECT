#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

//ウィンドウプログラミングに必要なもの
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx系列
#include <d3dx11.h>		
//d3dx系列
#include <d3dcompiler.h>

//マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //渡されたオブジェクトのリリース関数を呼び出してそのあとにNULLを入れている
													//マクロで行っているけど、テンプレートで行うほうがいいとは思う
#endif SAFE_RELEASE

#ifndef SIMPLESHADER_CONSTANT_BUFFER_DEF
#define SIMPLESHADER_CONSTANT_BUFFER_DEF
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
#endif

class MyConstantBuffer {
public:
	void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	HRESULT CreateConstantBuffer(D3D11_BUFFER_DESC cb);
	void SetConstantBuffer(D3DXMATRIX world,D3DXMATRIX view, D3DXMATRIX proj);
	void SetCBtoVS();
	void SetCBtoPS();
	void Release();
private:
	ID3D11Buffer* m_pConstantBuffer;			//コンスタントバッファーを作るためのバッファ
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	//static int Num;
};
#endif