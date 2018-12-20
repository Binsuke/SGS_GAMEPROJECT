//#pragma once
//#include <stdio.h>
//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx10.h>
//#include <d3dx11.h>
//#include <d3dCompiler.h>
//#include <fbxsdk.h>
//#include <string.h>
//
////マクロ
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
////シェーダーに渡す値
//
//struct SHADER_GLOBAL1
//{
//	D3DXMATRIX mW;//ワールド行列
//	D3DXMATRIX mWVP;//ワールドから射影までの変換行列
//	D3DXVECTOR4 vAmbient;//アンビエント光
//	D3DXVECTOR4 vDiffuse;//ディフューズ色
//	D3DXVECTOR4 vSpecular;//鏡面反射
//};
////オリジナル　マテリアル構造体
//struct MY_MATERIAL
//{
//	CHAR szName[100];
//	D3DXVECTOR4 Ka;//アンビエント
//	D3DXVECTOR4 Kd;//ディフューズ
//	D3DXVECTOR4 Ks;//スペキュラー
//	CHAR szTextureName[100];//テクスチャーファイル名
//	ID3D11ShaderResourceView* pTexture;
//	DWORD dwNumFace;//そのマテリアルであるポリゴン数
//	MY_MATERIAL()
//	{
//		ZeroMemory(this, sizeof(MY_MATERIAL));
//	}
//	~MY_MATERIAL()
//	{
//		SAFE_RELEASE(pTexture);
//	}
//};
//
////頂点構造体
//struct MY_VERTEX
//{
//	D3DXVECTOR3 vPos;
//	D3DXVECTOR3 vNorm;
//	D3DXVECTOR2 vTex;
//};
//
////MY_MESH オリジナルメッシュクラス
//class MY_MESH
//{
//public:
//	MY_MESH();
//	~MY_MESH();
//
//	//FBX
//	KFbxSdkManager *m_pSdkManager;
//	KFbxImporter* m_pImporter;
//	KFbxScene* m_pmyScene;
//	//外部のデバイス等情報
//	ID3D11Device* m_pDevice;
//	ID3D11DeviceContext* m_pDeviceContext;
//	ID3D11SamplerState* m_pSampleLinear;
//	ID3D11Buffer* m_pConstantBuffer;
//	D3DXMATRIX m_mView;
//	D3DXMATRIX m_mProj;
//	//メッシュ関連	
//	DWORD m_dwNumVert;
//	DWORD m_dwNumFace;
//	DWORD m_dwNumUV;
//	ID3D11Buffer* m_pVertexBuffer;
//	ID3D11Buffer** m_ppIndexBuffer;
//	MY_MATERIAL* m_pMaterial;
//	DWORD m_dwNumMaterial;
//	//アニメーション関連
//	D3DXMATRIX m_mParentOrientation;//親の姿勢行列
//	D3DXMATRIX m_mMyOrientation;//自分の姿勢行列（親から見た相対姿勢）
//	D3DXMATRIX m_mFinalWorld;//最終的なワールド行列（この姿勢でレンダリングする）
//
//	KFbxNode* m_pMyFBXNode;//FBXから姿勢行列を取り出す際に使うFBXポインター
//	//メソッド
//	HRESULT InitFBX(CHAR* szFileName);
//	void DestroyFBX();
//	HRESULT CreateIndexBuffer(DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
//	void RenderMesh(D3DXMATRIX* pWorld);
//	HRESULT CreateFromFBX(CHAR* FileName);
//};