#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//マクロ
#define SAFE_RELEASE(x) if(x){x->Release();x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}

//構造体定義
struct SIMPLECONSTANT_BUFFER0
{
	D3DXMATRIX mW;//ワールド行列
	D3DXMATRIX mWVP;//ワールドから射影までの変換行列
	D3DXVECTOR4 vLightDir;//ライト方向
	D3DXVECTOR4 vEye;//カメラ位置
};

struct SIMPLECONSTANT_BUFFER1
{
	D3DXVECTOR4 vAmbient;//アンビエント光
	D3DXVECTOR4 vDiffuse;//ディフューズ色
	D3DXVECTOR4 vSpecular;//鏡面反射
};

struct MY_MATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ambient;//アンビエント
	D3DXVECTOR4 Diffuse;//ディフューズ
	D3DXVECTOR4 Specular;//スペキュラー
	CHAR szTextureName[110];//テクスチャーファイル名
	ID3D11ShaderResourceView* pTexture;//テクスチャーのリソース
	DWORD dwNumFace;//そのマテリアルであるポリゴン数

	MY_MATERIAL()
	{
		ZeroMemory(this, sizeof(MY_MATERIAL));
	}
	~MY_MATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};

struct MY_VERTEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

class CD3DXMESH
{
public:
	//Data
	HWND m_hWnd;//ハンドルウィンドウ
	DWORD m_dwNumMaterial;//マテリアルの数
	LPD3DXMESH m_pMesh;//メッシュ保存用
	D3DXVECTOR3 m_vPos;//ポジション
	float m_fYaw, m_fPitch, m_fRoll;//回転
	float m_fScale;//拡大率

	//Dx9
	LPDIRECT3D9 m_pD3D9;//
	LPDIRECT3DDEVICE9 m_pDevice9;//デバイス
	D3DMATERIAL9* pMeshMaterials;//メッシュのマテリアル数？
	DWORD m_NumAttr;//階層構造の数
	DWORD m_AttrID[300];//300属性まで

	//Dx11
	ID3D11Device* m_pDevice11;//デバイス
	ID3D11DeviceContext* m_pDeviceContext11;//デバイスコンテキスト
	ID3D11InputLayout* m_pVertexLayout;//バーテックスレイアウト
	ID3D11VertexShader* m_pVertexShader;//バーテックスシェーダー
	ID3D11PixelShader* m_pPixelShader;//ピクセルシェーダー
	ID3D11Buffer* m_pConstantBuffer0;//コンスタントバッファー
	ID3D11Buffer* m_pConstantBuffer1;//コンスタントバッファー
	ID3D11Buffer* m_pVertexBuffer;//バーテックスバッファー
	ID3D11Buffer** m_ppIndexBuffer;//インデックスバッファー
	
	//resource
	char m_TextureFileName[8][256];//テクスチャーファイル名（８枚）
	ID3D11SamplerState* m_pSampleLinear;//テクスチャーのサンプラー
	MY_MATERIAL* m_pMaterial;

	//Method
	CD3DXMESH();
	~CD3DXMESH();
	HRESULT Init(HWND hWnd, ID3D11Device*,ID3D11DeviceContext*, LPSTR);
	HRESULT InitDx9();
	HRESULT LoadXMesh(LPSTR FileName);
	HRESULT InitShader();
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);
};



