#pragma once

#ifndef PIXEL_SHADER_UTILITY_H
#define PIXEL_SHADER_UTILITY_H



//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx�n��
#include <d3dx11.h>		
//d3dx�n��
#include <d3dcompiler.h>

#include <string>



//�}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;} //�n���ꂽ�I�u�W�F�N�g�̃����[�X�֐����Ăяo���Ă��̂��Ƃ�NULL�����Ă���
#endif

//�N���X�����ă��X�g�ɂ����ق����悳����
//struct PIXEL_SHADER_RESOURCE : BASE_SHADER_RESOURCE {
//	PIXEL_SHADER_RESOURCE* pPrev;
//	ID3D11PixelShader* pPixelShader;
//	PIXEL_SHADER_RESOURCE* pNext;
//};

class PixelShaderUtil{
public:
	~PixelShaderUtil();
	void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	HRESULT CreateShaderFromFile(std::string filename, std::string shadername, std::string version, int* num);

	//�w�肳�ꂽ���ʎq�̃V�F�[�_�[���Z�b�g����
	void SetShader(int Num);
	//void Release();
private:
	//std::vector<PIXEL_SHADER_RESOURCE> m_vResource;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
};

#endif