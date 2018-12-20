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
////�}�N��
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
////�V�F�[�_�[�ɓn���l
//
//struct SHADER_GLOBAL1
//{
//	D3DXMATRIX mW;//���[���h�s��
//	D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
//	D3DXVECTOR4 vAmbient;//�A���r�G���g��
//	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
//	D3DXVECTOR4 vSpecular;//���ʔ���
//};
////�I���W�i���@�}�e���A���\����
//struct MY_MATERIAL
//{
//	CHAR szName[100];
//	D3DXVECTOR4 Ka;//�A���r�G���g
//	D3DXVECTOR4 Kd;//�f�B�t���[�Y
//	D3DXVECTOR4 Ks;//�X�y�L�����[
//	CHAR szTextureName[100];//�e�N�X�`���[�t�@�C����
//	ID3D11ShaderResourceView* pTexture;
//	DWORD dwNumFace;//���̃}�e���A���ł���|���S����
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
////���_�\����
//struct MY_VERTEX
//{
//	D3DXVECTOR3 vPos;
//	D3DXVECTOR3 vNorm;
//	D3DXVECTOR2 vTex;
//};
//
////MY_MESH �I���W�i�����b�V���N���X
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
//	//�O���̃f�o�C�X�����
//	ID3D11Device* m_pDevice;
//	ID3D11DeviceContext* m_pDeviceContext;
//	ID3D11SamplerState* m_pSampleLinear;
//	ID3D11Buffer* m_pConstantBuffer;
//	D3DXMATRIX m_mView;
//	D3DXMATRIX m_mProj;
//	//���b�V���֘A	
//	DWORD m_dwNumVert;
//	DWORD m_dwNumFace;
//	DWORD m_dwNumUV;
//	ID3D11Buffer* m_pVertexBuffer;
//	ID3D11Buffer** m_ppIndexBuffer;
//	MY_MATERIAL* m_pMaterial;
//	DWORD m_dwNumMaterial;
//	//�A�j���[�V�����֘A
//	D3DXMATRIX m_mParentOrientation;//�e�̎p���s��
//	D3DXMATRIX m_mMyOrientation;//�����̎p���s��i�e���猩�����Ύp���j
//	D3DXMATRIX m_mFinalWorld;//�ŏI�I�ȃ��[���h�s��i���̎p���Ń����_�����O����j
//
//	KFbxNode* m_pMyFBXNode;//FBX����p���s������o���ۂɎg��FBX�|�C���^�[
//	//���\�b�h
//	HRESULT InitFBX(CHAR* szFileName);
//	void DestroyFBX();
//	HRESULT CreateIndexBuffer(DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer);
//	void RenderMesh(D3DXMATRIX* pWorld);
//	HRESULT CreateFromFBX(CHAR* FileName);
//};