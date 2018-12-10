//�w�b�_�[�t�@�C���̃C���N���[�h
#include <windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dCompiler.h>
#include <fbxsdk.h>
#include <string>
using namespace DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
//�萔��`
#define WINDOW_WIDTH 640 //�E�B���h�E��
#define WINDOW_HEIGHT 480 //�E�B���h�E����
int CWIDTH = WINDOW_WIDTH;
int CHEIGHT = WINDOW_HEIGHT;


//�P�̒��_�����i�[����\����
struct VERTEX {
	XMFLOAT3 Pos;
};

//GPU(�V�F�[�_���֑��鐔�l���܂Ƃ߂��\����
struct CONSTANT_BUFFER {
	XMMATRIX mWVP;
};

//�O���[�o���ϐ�
HWND g_hWnd = NULL;



//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//
//�G���g���[�֐�
//
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	// �E�B���h�E�̏�����
	static char szAppName[] = "FBX�̓ǂݍ��݁i���o�C���f�[�^�j";

	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	g_hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInst, 0);

	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);

	// ���b�Z�[�W���[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//�A�v���P�[�V�����̏����͂����ōs���B

		}
	}

	//�I��
	return (INT)msg.wParam;
}

//
//�E�B���h�E�v���V�[�W���[�֐�
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
	{

		return 0;
	}
	case WM_KEYDOWN:
	{
		switch ((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}
	case WM_DESTROY:
	{

		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}