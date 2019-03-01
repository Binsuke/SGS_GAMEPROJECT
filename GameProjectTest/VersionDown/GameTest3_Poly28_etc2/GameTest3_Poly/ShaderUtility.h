#pragma once
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

#include <string>
//�V�F�[�_�[�̃��\�[�X�\����
//�e���v���[�g���g���Ă��ꂼ��̃V�F�[�_�[�ɑΉ������\���̂���邱�Ƃ��l������
//���G�ɂȂ肻���ł��������߁A��ՂƂȂ�\���̂������ɒu���Ă�����
//�����V�F�[�_�[�N���X�����̎��ɂ����ł��̍\���̂��p�����Ă�����΂���
//���͎��ʂɂȂ�ϐ����������ĂȂ����@�S�̂ɒǉ����K�v�ɂȂ����Ƃ���
//�������ɒǉ����Ă�����
//struct BASE_SHADER_RESOURCE {
//	int Num;
//};    �N���X�����ă��X�g�\���ɂ����ق����悳��

#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H

class BASE_SHADER_CLASS{
public:
	//��������f�o�C�X�����������󂯎��͖̂ʓ|�Ȃ̂�
	//�f�o�C�X�̃|�C���^�[��ێ����Ă���
	void Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext);
	//�t�@�C���l�[���̓V�F�[�_�[�̃t�@�C���̖��O���w�肷��
	//�o�[�W�����Ɋւ��Ắ@�V�F�[�_�[�̃t�@�C���̃o�[�W����
	//ShaderName�̓V�F�[�_�[�t�@�C�����ɋL�ڂ��Ă���@PS�Ȃǂ̃V�F�[�_�[�֐������w��
	//num�͎��ʎq�ɂȂ�f�[�^���i�[���邽�߂Ƀ|�C���^�[��n���Ă�����
	//����num��BASE_SHADER_RESOURCE�\���̂�num�Ɠ����ɂ���
	//����ɂ���ā@���ʎq���󂯎�������̂��@�K����V�F�[�_�[�Ƃ��ăZ�b�g���Ă�����
	//�Ⴆ�΁@�s�N�Z���V�F�[�_�[�ƃo�[�e�b�N�X�V�F�[�_�[���Q��ޗp�ӂ��Ă����Ƃ���
	//�s�N�Z���V�F�[�_�[�͂P���@�o�[�e�b�N�X�V�F�[�_�[�͂Q���g�p����Ȃǂ��\�ɂȂ�Ǝv��
	//�������̏ꍇ�̓R���X�^���g�o�b�t�@�[�Ȃǂ̍��𓝈ꂵ�Ă����K�v������Ǝv��
	virtual HRESULT CreateShaderFromFile(std::string FileName,std::string Version,std::string ShaderName ,int* Num)=0;
	
	//�w�肳�ꂽ���ʎq�̃V�F�[�_�[���Z�b�g����
	virtual void SetShader(int Num)=0;
protected:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

};

#endif