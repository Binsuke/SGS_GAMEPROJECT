#ifndef POLY_H
#define POLY_H
//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
//�w�b�_�[�t�@�C���̃C���N���[�h
#include <Windows.h>	
//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx�n��
#include <d3dx11.h>		
//d3dx�n��
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
	void Render(ID3D11DeviceContext* inDeviceContext,D3DXMATRIX mW);//world�̕ϊ��s���n�����ƂŁ@�����Ɉړ�����
	HRESULT CreateVertexBuffer(ID3D11Device * inDevice);//�o�[�e�b�N�X�o�b�t�@�[�쐬�p
	HRESULT CreateTexture(ID3D11Device* inDevice);
protected:
private:
	bool InitFlg;
	SimpleVertex *m_pVertices;
	ID3D11Buffer* m_pVertexBuffer;				//�o�[�e�b�N�X�o�b�t�@�[

	ID3D11SamplerState* m_pSampleLinear;			//�e�N�X�`���[�̃T���v���[
												//�T���v���[�Ƃ̓e�N�X�`�����ǂ̂悤�Ɉ������A�e�N�X�`���̉摜�����O�ɂ���[�͂ǂ̂悤�Ɉ�����
												//�Ⴆ�΃~���[�⓯���F�œh��Ԃ��Ȃǂ̐ݒ������Ă����ā@�����邽�߂̏��

	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�{�́@�@�V�F�[�_�[�ɓn�����\�[�X


};
}
#endif