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
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release();x=0;}
#define SAFE_DELETE(x) if(x){delete x;x=0;}
#define SAFE_DELETE_ARRAY(p){ if(p){delete[] (p); (p)=NULL;}}


struct BUFFER_PER_MESH
{
	D3DXMATRIX mW;//���[���h�s��
	D3DXMATRIX mWVP; //���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vLightDir;//���C�g����
	D3DXVECTOR4 vEye;//�J�����ʒu
};

struct BUFFER_PER_MATERIAL
{
	D3DXVECTOR4 vAmbient;//�A���r�G���g��
	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
	D3DXVECTOR4 vSpecular;//���ʔ���
};
//�I���W�i���@�}�e���A���\����
struct MY_MATERIAL
{
	CHAR szName[100];
	D3DXVECTOR4 Ambient;//�A���r�G���g
	D3DXVECTOR4 Diffuse;//�f�B�t���[�Y
	D3DXVECTOR4 Specular;//�X�y�L�����[
	CHAR szTextureName[256];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//���̃}�e���A���ł���|���S����

	MY_MATERIAL()
	{
		ZeroMemory(this, sizeof(MY_MATERIAL));
	}

	~MY_MATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};


//���_�̍\����

struct MY_VERTEX_TEX
{
	D3DXVECTOR3 vPos;//�|�W�V����
	D3DXVECTOR3 vNorm;//�@��
	D3DXVECTOR2 vTex;//UV
};


struct MY_VERTEX_NOTEX
{
	D3DXVECTOR3 vPos;//�|�W�V����
	D3DXVECTOR3 vNorm;//�@��
};
//�p�[�c���b�V���@�A�v����`���b�V���i�X�^�e�B�b�N���b�V���T���v����C3D3XMESH�N���X�Ɠ���

struct PARTS_MESH
{
	DWORD dwNumMaterial;//�}�e���A����
	ID3D11Buffer* pVertexBuffer;//�o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer** ppIndexBuffer;//�C���f�b�N�X�o�b�t�@�[
	char TextureFileName[8][256];//�e�N�X�`���[�t�@�C�����W���܂�
	MY_MATERIAL* pMaterial;//�}�e���A��
	bool Tex;//�e�N�X�`���[�����邩�ǂ���
};

struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
	PARTS_MESH* pPartsMesh;
	MYFRAME()
	{
		ZeroMemory(this, sizeof(MYFRAME));
	}
};

//���b�V���R���e�i�[�\���́@�t���[�����Ŏg�p
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9* ppTextures;
};

class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME*);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);

};




class CD3DXMESH_ANIM
{
public:
	//Data
	HWND m_hWnd;  //�E�B���h�E�n���h��
	DWORD m_dwNumMaterial; //�}�e���A���̐�
	LPD3DXMESH m_pMesh;//Directx9�̂���̃��b�V���������͂�
	D3DXVECTOR3 m_vPos;//�|�W�V����
	float m_fYaw, m_fPitch, m_fRoll;//�s�b�`�@���E�@���[��
	float m_fScale;				//�X�P�[��
	D3DXMATRIX m_View;//�r���[�s��
	D3DXMATRIX m_Proj;//�v���W�F�N�V�����s��
	D3DXVECTOR3 m_LightDir;//���C�g�̌���
	D3DXVECTOR3 m_Eye;//���_
	D3DXVECTOR3 m_AxisX;//X��
	D3DXVECTOR3 m_AxisY;//Y��
	D3DXVECTOR3 m_AxisZ;//Z��

	//�A�j���֘A
	MY_HIERARCHY* m_pHierarchy;//�K�w�\�����ׂ�z
	LPD3DXFRAME m_pFrameRoot;//�t���[���H
	LPD3DXANIMATIONCONTROLLER m_pAnimController;//�A�j���[�V�����R���g���[���[

	//Dx9
	LPDIRECT3D9 m_pD3d9;//�@
	LPDIRECT3DDEVICE9 m_pDevice9;//�f�o�C�X�X

	//Dx11
	ID3D11Device* m_pDevice11;
	ID3D11DeviceContext* m_pDeviceContext11;
	ID3D11InputLayout* m_pVertexLayout;//�e�N�X�`���[���������ꍇ�̃��C�A�E�g
	ID3D11InputLayout* m_pVertexLayout_NoTex;//�e�N�X�`���[���Ȃ������ꍇ�̃��C�A�E�g

	ID3D11VertexShader* m_pVertexShader;//�e�N�X�`���[���������ꍇ�̃o�[�e�b�N�X�V�F�[�_�[
	ID3D11VertexShader* m_pVertexShaderNoTex;//�e�N�X�`���[���Ȃ������ꍇ�̃o�[�e�b�N�X�V�F�[�_�[

	ID3D11PixelShader* m_pPixelShader;//�e�N�X�`���[���������ꍇ�̃s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pPixelShaderNoTex;//�e�N�X�`���[���Ȃ������ꍇ�̃s�N�Z���V�F�[�_�[

	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;

	ID3D11SamplerState* m_pSampleLinear;//�e�N�X�`���[�̃T���v���[

	//Method
	CD3DXMESH_ANIM();
	~CD3DXMESH_ANIM();
	HRESULT Init(HWND hWnd, ID3D11Device*, ID3D11DeviceContext*, LPSTR);
	HRESULT InitDx9();
	HRESULT InitShader();
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);
	HRESULT LoadXAnimMesh(LPSTR FileName);
	void BuildAllMesh(D3DXFRAME* pFrame);
	HRESULT CreateAppMeshFromD3DXMesh(LPD3DXFRAME pFrame);
	void DrawFrame(LPD3DXFRAME p);
	void DrawPartsMesh(PARTS_MESH* p, D3DXMATRIX World);
	void UpdateHierarchyMatrices(D3DXFRAME* p, LPD3DXMATRIX pParentMatrix);
	void MoveForward(float);
	void MoveBackward(float);
	void MoveStepLeft(float);
	void MoveStepRight(float);

};


