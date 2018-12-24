#pragma once
#include <d3d11.h>
#include <string>

std::wstring StrToWstr(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);//�m�ۂ��钷���̊m�F
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);

	std::wstring rstr(buf);
	delete[] buf;
	return rstr;
}

void D3D11ErrorCheck(HRESULT hr,std::string WhatCheck) {
	std::string tmpstr;
	switch (hr) {
	case S_OK:
		break;
	case D3D11_ERROR_FILE_NOT_FOUND:
		//std::string tmpstr = ":�t�@�C����������܂���ł���";
		tmpstr = ":�t�@�C����������܂���ł���";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
		//std::string tmpstr = ":����̎�ނ̃X�e�[�g�I�u�W�F�N�g�̈�ʂ̃C���X�^���X���������܂�";
		tmpstr = ":����̎�ނ̃X�e�[�g�I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂�";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
		tmpstr = ":����̎�ނ̃r���[�I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂�";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
		tmpstr = ":���\�[�X���Ƃ� ID3D11Device::CreateDeferredContext �̌Ăяo���܂��� ID3D11DeviceContext::FinishCommandList �̌Ăяo���̌�ōŏ��ɌĂяo���� ID3D11DeviceContext::Map �� D3D11_MAP_WRITE_DISCARD �ł͂���܂���ł����B";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_FAIL:
		tmpstr = ":�f�o�b�O ���C���[��L���ɂ��ăf�o�C�X���쐬���悤�Ƃ��܂������A�Y�����郌�C���[���C���X�g�[������Ă��܂���B";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_INVALIDARG:
		tmpstr = ":�߂�֐��ɖ����ȃp�����[�^�[���n����܂����B";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_OUTOFMEMORY:
		tmpstr = ":Direct3D ���Ăяo�����������邤���ŏ\���ȃ������[�����蓖�Ă邱�Ƃ��ł��܂���ł����B";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case S_FALSE:
		tmpstr = ":����ɏ������ꂽ���̂́A��W���̊�����������֐����l�ł�";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	}
}