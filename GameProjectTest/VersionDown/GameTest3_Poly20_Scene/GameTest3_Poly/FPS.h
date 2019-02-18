#ifndef FPS_H
#define FPS_H
#include <stdio.h>

#include <Windows.h>	
//�E�B���h�E�v���O���~���O�ɕK�v�Ȃ���
#include <d3d11.h>		
//d3d11
#include <d3dx10.h>
//d3dx�n��
#include <d3dx11.h>		
//d3dx�n��
#include <d3dcompiler.h>

class FPS {
public:
	FPS();
	void Run();
	void PrintFps(HWND hWnd);
	float GetDeltaTime();
	bool DeltaReady() {
		return deltaFlg;
	}
private:
	DWORD time;
	int frame;
	int Delta;
	char str[50];
	bool fFlg;
	bool deltaFlg;
};
#endif