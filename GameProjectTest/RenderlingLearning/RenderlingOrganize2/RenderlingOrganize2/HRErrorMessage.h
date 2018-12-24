#pragma once
#include <d3d11.h>
#include <string>

std::wstring StrToWstr(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);//確保する長さの確認
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
		//std::string tmpstr = ":ファイルが見つかりませんでした";
		tmpstr = ":ファイルが見つかりませんでした";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
		//std::string tmpstr = ":特定の種類のステートオブジェクトの一位のインスタンスが多すぎます";
		tmpstr = ":特定の種類のステートオブジェクトの一意のインスタンスが多すぎます";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
		tmpstr = ":特定の種類のビューオブジェクトの一意のインスタンスが多すぎます";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
		tmpstr = ":リソースごとの ID3D11Device::CreateDeferredContext の呼び出しまたは ID3D11DeviceContext::FinishCommandList の呼び出しの後で最初に呼び出した ID3D11DeviceContext::Map が D3D11_MAP_WRITE_DISCARD ではありませんでした。";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_FAIL:
		tmpstr = ":デバッグ レイヤーを有効にしてデバイスを作成しようとしましたが、該当するレイヤーがインストールされていません。";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_INVALIDARG:
		tmpstr = ":戻り関数に無効なパラメーターが渡されました。";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case E_OUTOFMEMORY:
		tmpstr = ":Direct3D が呼び出しを完了するうえで十分なメモリーを割り当てることができませんでした。";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	case S_FALSE:
		tmpstr = ":正常に処理されたものの、非標準の完了を示す代替成功値です";
		tmpstr = WhatCheck + tmpstr;
		MessageBox(NULL, tmpstr.c_str(), WhatCheck.c_str(), 0);
		PostQuitMessage(0);
		break;
	}
}