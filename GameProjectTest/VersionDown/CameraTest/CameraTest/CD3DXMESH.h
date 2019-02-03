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

//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release();x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}

//�\���̒�`
struct SIMPLECONSTANT_BUFFER0
{
	D3DXMATRIX mW;//���[���h�s��
	D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vLightDir;//���C�g����
	D3DXVECTOR4 vEye;//�J�����ʒu
};

struct SIMPLECONSTANT_BUFFER1
{
	D3DXVECTOR4 vAmbient;//�A���r�G���g��
	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
	D3DXVECTOR4 vSpecular;//���ʔ���
};

struct MY_MATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ambient;//�A���r�G���g
	D3DXVECTOR4 Diffuse;//�f�B�t���[�Y
	D3DXVECTOR4 Specular;//�X�y�L�����[
	CHAR szTextureName[110];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;//�e�N�X�`���[�̃��\�[�X
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
	HWND m_hWnd;//�n���h���E�B���h�E
	DWORD m_dwNumMaterial;//�}�e���A���̐�
	LPD3DXMESH m_pMesh;//���b�V���ۑ��p
	D3DXVECTOR3 m_vPos;//�|�W�V����
	float m_fYaw, m_fPitch, m_fRoll;//��]
	float m_fScale;//�g�嗦

	//Dx9
	LPDIRECT3D9 m_pD3D9;//
	LPDIRECT3DDEVICE9 m_pDevice9;//�f�o�C�X
	D3DMATERIAL9* pMeshMaterials;//���b�V���̃}�e���A�����H
	DWORD m_NumAttr;//�K�w�\���̐�
	DWORD m_AttrID[300];//300�����܂�

	//Dx11
	ID3D11Device* m_pDevice11;//�f�o�C�X
	ID3D11DeviceContext* m_pDeviceContext11;//�f�o�C�X�R���e�L�X�g
	ID3D11InputLayout* m_pVertexLayout;//�o�[�e�b�N�X���C�A�E�g
	ID3D11VertexShader* m_pVertexShader;//�o�[�e�b�N�X�V�F�[�_�[
	ID3D11PixelShader* m_pPixelShader;//�s�N�Z���V�F�[�_�[
	ID3D11Buffer* m_pConstantBuffer0;//�R���X�^���g�o�b�t�@�[
	ID3D11Buffer* m_pConstantBuffer1;//�R���X�^���g�o�b�t�@�[
	ID3D11Buffer* m_pVertexBuffer;//�o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer** m_ppIndexBuffer;//�C���f�b�N�X�o�b�t�@�[
	
	//resource
	char m_TextureFileName[8][256];//�e�N�X�`���[�t�@�C�����i�W���j
	ID3D11SamplerState* m_pSampleLinear;//�e�N�X�`���[�̃T���v���[
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



