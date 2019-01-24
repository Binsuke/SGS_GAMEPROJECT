#pragma once
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

#include <string>
//シェーダーのリソース構造体
//テンプレートを使ってそれぞれのシェーダーに対応した構造体を作ることも考えたが
//複雑になりそうであったため、基盤となる構造体をここに置いておいて
//書くシェーダークラス実装の時にそこでこの構造体を継承してあげればいい
//今は識別になる変数しか入ってないが　全体に追加が必要になったときは
//こっちに追加してあげる
//struct BASE_SHADER_RESOURCE {
//	int Num;
//};    クラス化してリスト構造にしたほうがよさげ

#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H

class BASE_SHADER_CLASS{
public:
	//こちらもデバイスをいちいち受け取るのは面倒なので
	//デバイスのポインターを保持しておく
	void Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext);
	//ファイルネームはシェーダーのファイルの名前を指定する
	//バージョンに関しては　シェーダーのファイルのバージョン
	//ShaderNameはシェーダーファイル内に記載してある　PSなどのシェーダー関数名を指定
	//numは識別子になるデータを格納するためにポインターを渡してあげる
	//このnumはBASE_SHADER_RESOURCE構造体のnumと同じにする
	//これによって　識別子を受け取ったものを　適せんシェーダーとしてセットしてあげる
	//例えば　ピクセルシェーダーとバーテックスシェーダーを２種類用意していたとして
	//ピクセルシェーダーは１を　バーテックスシェーダーは２を使用するなども可能になると思う
	//ただその場合はコンスタントバッファーなどの作りを統一しておく必要があると思う
	virtual HRESULT CreateShaderFromFile(std::string FileName,std::string Version,std::string ShaderName ,int* Num)=0;
	
	//指定された識別子のシェーダーをセットする
	virtual void SetShader(int Num)=0;
protected:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

};

#endif