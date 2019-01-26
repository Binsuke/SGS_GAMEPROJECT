#ifndef VERTEX_SHADER_UTILITY_H
#define VERTEX_SHADER_UTILITY_H
#include "ShaderUtility.h"
//#include <vector>



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

class VertexShaderUtil{
public:
	//virtual HRESULT CreateShaderFromFile(std::string filename, std::string shadername, std::string version, int* num);
	void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	HRESULT CreateShaderFromFileV(std::string filename, std::string shadername, std::string version, int* num, D3D11_INPUT_ELEMENT_DESC layout[], UINT numelements);
	//�w�肳�ꂽ���ʎq�̃V�F�[�_�[���Z�b�g����
	void SetShader(int Num);
	void SetLayout();
	void Release();
private:
	//std::vector<PIXEL_SHADER_RESOURCE> m_vResource;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout* m_pVertexLayout;			//�o�[�e�b�N�X�̃��C�A�E�g�����ۂɎg���A���̃��C�A�E�g�����Ƃɒ��_�̌`�����߂�
	//static int Num;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
};

#endif