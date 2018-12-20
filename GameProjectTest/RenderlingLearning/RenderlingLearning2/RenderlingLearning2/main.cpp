////�K�v�ȃw�b�_�[�t�@�C���̃C���N���[�h
//#include <stdio.h>
//#include <windows.h>
//#include <d3d11.h>
//#include <d3dx10.h>
//#include <d3dx11.h>
//#include <d3dCompiler.h>
//#include "MyMesh.h"
////�K�v�ȃ��C�u�����t�@�C���̃��[�h
//#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"d3dx10.lib")
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"d3dx11.lib")
//#pragma comment(lib,"d3dCompiler.lib")
//
//#pragma comment(lib,"libfbxsdk_md.lib")
//#pragma comment(lib,"libfbxml2_md.lib")
//#pragma comment(lib,"zlib_md.lib")
//
////�萔
//#define WINDOW_WIDTH 640
//#define WINDOW_HEIGHT 480
////�}�N��
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
////�O���[�o��
//HWND g_hWnd;
//ID3D11Device* g_pDevice;
//IDXGISwapChain*			g_pSwapChain;
//ID3D11RenderTargetView* g_pRenderTargetView;
//ID3D11DepthStencilView* g_pDepthStencilView;
//ID3D11InputLayout*      g_pVertexLayout;
//ID3D11Texture2D*		g_pDepthStencil;
//
//ID3D11DeviceContext	 *g_pDeviceContext = NULL;
//ID3D11VertexShader *g_pVertexShader = NULL;//effect�ł͂Ȃ��A�ʂɃo�[�e�b�N�X�V�F�[�_�[
//ID3D11PixelShader *g_pPixelShader = NULL;//effect�ł͂Ȃ��A�ʂɃs�N�Z���V�F�[�_�[
//
//ID3D11Buffer* g_pConstantBuffer0 = NULL;//�A�v�������V�F�[�_�[�˂����@�R���X�^���g�o�b�t�@�[ 
//ID3D11Buffer* g_pConstantBuffer1 = NULL;//�A�v�������V�F�[�_�[�˂����@�R���X�^���g�o�b�t�@�[�@
//
//ID3D11SamplerState* g_pSampleLinear = NULL;//�e�N�X�`���[�̃T���v���[ �S�}�e���A���e�N�X�`���[����
//
////�V�F�[�_�[�ɓn���l
//struct SHADER_GLOBAL0
//{
//	D3DXVECTOR4 vLightDir;//���C�g����
//	D3DXVECTOR4 vEye;//�J�����ʒu
//};
//
//D3DXVECTOR3 g_vLightDir(-1, 1, -1);
//MY_MESH* g_pMesh;
//
////�֐��v���g�^�C�v�̐錾
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HRESULT InitD3d(HWND);
//void Render();
//
////
////INT WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR szStr,INT iCmdShow)
////�A�v���P�[�V�����̃G���g���[�֐�
//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
//{
//	//���b�V���̃C���X�^���X����
//	g_pMesh = new MY_MESH;
//	// �E�B���h�E�̏�����
//	static WCHAR szAppName[] = L"D3D11�@FBX����X�^�e�B�b�N���b�V��";
//	WNDCLASSEX  wndclass;
//
//	wndclass.cbSize = sizeof(wndclass);
//	wndclass.style = CS_HREDRAW | CS_VREDRAW;
//	wndclass.lpfnWndProc = WndProc;
//	wndclass.cbClsExtra = 0;
//	wndclass.cbWndExtra = 0;
//	wndclass.hInstance = hInst;
//	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wndclass.lpszMenuName = NULL;
//	wndclass.lpszClassName = szAppName;
//	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
//	RegisterClassEx(&wndclass);
//
//	g_hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
//		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL);
//	ShowWindow(g_hWnd, SW_SHOW);
//	UpdateWindow(g_hWnd);
//	// �_�C���N�g�RD�̏������֐����Ă�
//	if (FAILED(InitD3d(g_hWnd)))
//	{
//		return 0;
//	}
//	// ���b�Z�[�W���[�v
//	MSG msg;
//	ZeroMemory(&msg, sizeof(msg));
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			Render();
//		}
//	}
//	//�A�v���P�[�V�������I�����鎞�ɂ́ADirect3D�I�u�W�F�N�g�������[�X����
//	delete g_pMesh;
//	SAFE_RELEASE(g_pSampleLinear);
//	SAFE_RELEASE(g_pDepthStencilView);
//	SAFE_RELEASE(g_pDepthStencil);
//	SAFE_RELEASE(g_pVertexShader);
//	SAFE_RELEASE(g_pPixelShader);
//	SAFE_RELEASE(g_pConstantBuffer0);
//	SAFE_RELEASE(g_pConstantBuffer1);
//	SAFE_RELEASE(g_pSwapChain);
//	SAFE_RELEASE(g_pRenderTargetView);
//	SAFE_RELEASE(g_pVertexLayout);
//	SAFE_RELEASE(g_pDeviceContext);
//	SAFE_RELEASE(g_pDevice);
//
//	return (INT)msg.wParam;
//}
////
////LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
//// �E�B���h�E�v���V�[�W���[�֐�
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hWnd, iMsg, wParam, lParam);
//}
////
////HRESULT InitD3d(HWND hWnd)
////�_�C���N�g3D�̏�����
//HRESULT InitD3d(HWND hWnd)
//{
//	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
//	DXGI_SWAP_CHAIN_DESC sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.BufferCount = 1;
//	sd.BufferDesc.Width = WINDOW_WIDTH;
//	sd.BufferDesc.Height = WINDOW_HEIGHT;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = 60;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.OutputWindow = g_hWnd;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.Windowed = TRUE;
//
//	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
//	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;
//
//	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
//		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pDevice,
//		pFeatureLevel, &g_pDeviceContext)))
//	{
//		return FALSE;
//	}
//	//�����_�[�^�[�Q�b�g�r���[�̍쐬
//	ID3D11Texture2D *pBackBuffer;
//	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
//	g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
//	pBackBuffer->Release();
//
//	//�[�x�X�e���V���r���[�̍쐬
//	D3D11_TEXTURE2D_DESC descDepth;
//	descDepth.Width = WINDOW_WIDTH;
//	descDepth.Height = WINDOW_HEIGHT;
//	descDepth.MipLevels = 1;
//	descDepth.ArraySize = 1;
//	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
//	descDepth.SampleDesc.Count = 1;
//	descDepth.SampleDesc.Quality = 0;
//	descDepth.Usage = D3D11_USAGE_DEFAULT;
//	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	descDepth.CPUAccessFlags = 0;
//	descDepth.MiscFlags = 0;
//	g_pDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);
//
//	g_pDevice->CreateDepthStencilView(g_pDepthStencil, NULL, &g_pDepthStencilView);
//	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h	
//	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
//
//	//�r���[�|�[�g�̐ݒ�
//	D3D11_VIEWPORT vp;
//	vp.Width = WINDOW_WIDTH;
//	vp.Height = WINDOW_HEIGHT;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//	g_pDeviceContext->RSSetViewports(1, &vp);
//
//	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
//	ID3DBlob *pCompiledShader = NULL;
//	ID3DBlob *pErrors = NULL;
//	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
//	if (FAILED(D3DX11CompileFromFile(L"Geometry_Material_Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
//	{
//		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pErrors);
//
//	if (FAILED(g_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &g_pVertexShader)))
//	{
//		SAFE_RELEASE(pCompiledShader);
//		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
//		return E_FAIL;
//	}
//	//���_�C���v�b�g���C�A�E�g���`	
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//	UINT numElements = sizeof(layout) / sizeof(layout[0]);
//
//	//���_�C���v�b�g���C�A�E�g���쐬
//	if (FAILED(g_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &g_pVertexLayout)))
//		return FALSE;
//	//���_�C���v�b�g���C�A�E�g���Z�b�g
//	g_pDeviceContext->IASetInputLayout(g_pVertexLayout);
//
//	//�u���u����s�N�Z���V�F�[�_�[�쐬
//	if (FAILED(D3DX11CompileFromFile(L"Geometry_Material_Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
//	{
//		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pErrors);
//	if (FAILED(g_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &g_pPixelShader)))
//	{
//		SAFE_RELEASE(pCompiledShader);
//		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pCompiledShader);
//	//���X�^���C�Y�ݒ�
//	D3D11_RASTERIZER_DESC rdc;
//	ZeroMemory(&rdc, sizeof(rdc));
//	rdc.CullMode = D3D11_CULL_NONE;
//	rdc.FillMode = D3D11_FILL_SOLID;
//
//	ID3D11RasterizerState* pIr = NULL;
//	g_pDevice->CreateRasterizerState(&rdc, &pIr);
//	g_pDeviceContext->RSSetState(pIr);
//	SAFE_RELEASE(pIr);
//	//�R���X�^���g�o�b�t�@�[0�쐬
//	D3D11_BUFFER_DESC cb;
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.ByteWidth = sizeof(SHADER_GLOBAL0);
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//
//	if (FAILED(g_pDevice->CreateBuffer(&cb, NULL, &g_pConstantBuffer0)))
//	{
//		return E_FAIL;
//	}
//	//�R���X�^���g�o�b�t�@�[1�쐬  
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.ByteWidth = sizeof(SHADER_GLOBAL1);
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//
//	if (FAILED(g_pDevice->CreateBuffer(&cb, NULL, &g_pConstantBuffer1)))
//	{
//		return E_FAIL;
//	}
//	//�e�N�X�`���[�p�T���v���[�쐬
//	D3D11_SAMPLER_DESC SamDesc;
//	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
//
//	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//	g_pDevice->CreateSamplerState(&SamDesc, &g_pSampleLinear);
//
//	//	���b�V���N���X�Ƀf�o�C�X�֘A����n��
//	g_pMesh->m_pDevice = g_pDevice;
//	g_pMesh->m_pDeviceContext = g_pDeviceContext;
//	g_pMesh->m_pSampleLinear = g_pSampleLinear;
//	g_pMesh->m_pConstantBuffer = g_pConstantBuffer1;
//
//	//FBX�t�@�C���ǂݍ���
//	g_pMesh->CreateFromFBX("chips.fbx");
//
//	return S_OK;
//}
//
////
////void Render()
////�����_�����O����֐�
//void Render()
//{
//	float ClearColor[4] = { 0,0,1,1 }; // �N���A�F�쐬�@RGBA�̏�
//	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);//��ʃN���A 
//	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);//�[�x�o�b�t�@�N���A
//
//	D3DXMATRIX mView;
//	D3DXMATRIX mProj;
//	//�r���[�s��
//	D3DXVECTOR3 Eye(0.0f, 0.0f, -0.5f);
//	D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
//	D3DXMatrixLookAtLH(&mView, &Eye, &At, &Up);
//	g_pMesh->m_mView = mView;
//
//	//�v���W�F�N�V�����s��
//	D3DXMatrixPerspectiveFovLH(&mProj, (float)D3DX_PI / 4, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1100.0f);
//	g_pMesh->m_mProj = mProj;
//
//	//���C�g�x�N�g�����V�F�[�_�[�ɓn��	
//	//�J�����ʒu���V�F�[�_�[�ɓn��
//	D3D11_MAPPED_SUBRESOURCE pData;
//	if (SUCCEEDED(g_pDeviceContext->Map(g_pConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
//	{
//		SHADER_GLOBAL0 sg;
//		sg.vLightDir = D3DXVECTOR4(g_vLightDir.x, g_vLightDir.y, g_vLightDir.z, 0.0f);
//		sg.vEye = D3DXVECTOR4(Eye.x, Eye.y, Eye.z, 0);
//		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL0));
//		g_pDeviceContext->Unmap(g_pConstantBuffer0, 0);
//	}
//	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer0);
//	g_pDeviceContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer0);
//	//�g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
//	g_pDeviceContext->VSSetShader(g_pVertexShader, NULL, 0);
//	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);
//	//�����_�[
//	D3DXMATRIX mWorld;
//	static float fAngle = 0;
//	fAngle += 0.0003f;
//	D3DXMatrixRotationY(&mWorld, fAngle);
//	g_pMesh->RenderMesh(&mWorld);
//
//	g_pSwapChain->Present(0, 0);//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj	
//}