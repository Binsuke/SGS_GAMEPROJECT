#include "main.h"
//#include <string>
//�O���[�o���ϐ�
//extern MAIN* g_pMain = NULL;

MAIN* g_pMain = NULL;
//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wPram, LPARAM lParam);

//INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
//�A�v���P�[�V�����̃G���g���[�֐� 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN;// main�̃C���X�^���X���쐬


	if (g_pMain != NULL)//�C���X�^���X�̍쐬�ɐ������Ă��邩
	{
		
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME))) //�E�B���h�E�̍쐬�@�������Ă����璆�ɓ���
		{
			if (SUCCEEDED(g_pMain->InitD3D()))//D3D�n��̏������@�������Ă����烋�[�v�ɓ���
			{
				
				g_pMain->Loop();	//���C�����[�v
			}
		}
		//�A�v���̏I��
		g_pMain->DestroyD3D();
		delete g_pMain;
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);//���C���̃��b�Z�[�W�v���Z�X�����s�@�����Č��ʂ�Ԃ�
}




//�R���X�g���N�^
MAIN::MAIN()
{
	ZeroMemory(this, sizeof(MAIN));
	
	//view = -2;
}


//�f�X�g���N�^
MAIN::~MAIN()
{

}

void MAIN::InitScene() {
	m_pTestGameScene = new GameScene;
}

//
//std::wstring StrToWstr(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);//�m�ۂ��钷���̊m�F
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//
//	std::wstring rstr(buf);
//	delete[] buf;
//	return rstr;
//}


HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	//�E�B���h�E�̒�`

	WNDCLASSEX wc;//Window�̂��ƂɂȂ�ݒ�p�̃N���X�H
	ZeroMemory(&wc, sizeof(wc));//�[��������

	wc.cbSize = sizeof(wc); //�������g�̃T�C�Y��ݒ�
	wc.style = CS_HREDRAW | CS_VREDRAW;  //�X�^�C���ݒ�@�ǂ������ݒ肩�͂킩���Ă��Ȃ���HREDRAW��VREDRAW�Ƃ����t���O���������đ�����Ă���

	wc.lpfnWndProc = WndProc;//�悭�͂킩��Ȃ����ǁ@�R�[���o�b�N�֐���WndProc�֐��������ő�����Ă���H

	wc.hInstance = hInstance;//�C���X�^���X��n���Ă���

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//IDI_APPLICATION�Ƃ����E�B���h�E�W���̃A�C�R�������[�h���Đݒ肵�Ă���Ǝv��

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//��������E�B���h�E�W���̃J�[�\���f�[�^�����[�h���đ�����Ă���Ǝv��

	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);  //��������o�b�N�O���E���h���ǂ��������ɓh��Ԃ����̐ݒ�H

	wc.lpszClassName = (LPCSTR)WindowName;//�E�B���h�E�̖��O���N���X���ɐݒ�

	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//�A�C�R�����܂��ݒ�H

	RegisterClassEx(&wc);//���܂Őݒ肵�Ă������̂�o�^���Ă���H

	//�E�B���h�E�̍쐬
	m_hWnd = CreateWindow((LPCSTR)WindowName, (LPCSTR)WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);//�E�B���h�E�쐬


	if (!m_hWnd)//�E�B���h�E���쐬����Ă��邩
	{
		return E_FAIL;
	}

	ShowWindow(m_hWnd, SW_SHOW);//�E�B���h�E��\��
	UpdateWindow(m_hWnd);//�E�B���h�E�̃A�b�v�f�[�g

	return S_OK;
}

//LRESULT MAIN::MsgProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
//�E�B���h�E�v���V�[�W���[
LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://�G�X�P�[�v�L�[��������Ă�����@�I��������R�[���o�b�N�߁[�����[���𑗂�v���O�������I������
			PostQuitMessage(0);
			break;
		case VK_UP:
			//view += 0.001;
			break;
		case VK_DOWN:
			//view -= 0.001;
			break;
		}
		break;
	case WM_DESTROY://�E�B���h�E�̔j�����b�Z�[�W���͂�����@�I��������R�[���o�b�N���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);//���̂ق��̓f�t�H���g�̃E�B���h�E�̃v���Z�X���s��
}


//������Ăяo����邱�Ƃ��l����Ƃ��[��
//D3D�̏������Ƃ����@�ڂ����ق��������񂾂낤����
//�^�C�g���Ƃ����Ăяo�����т�D3D�̏�����������Ă����܂�񂾂�Ȃ�
//����DirectX�̏������Ƃ�DirectX�̖{�͕̂ʂ̃N���X�ɕ��������ق��������C������
//�Ƃ肠�������͂�����
//�O���[�o���ϐ���g_pMain���Ăяo���Ȃ��悤�ɋC��t���Ă�����
//���Ԃ������DirectX�͕���������

void MAIN::Loop()
{
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	InitScene();

	while (msg.message != WM_QUIT)//�I�����b�Z�[�W���͂��Ă��Ȃ���΁@���[�v
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //���b�Z�[�W�����Ƃɏ�����I��
		{
			TranslateMessage(&msg);			//�҂��s����̃E�B���h�E�̗D�揇�ʂ̍����v���Z�X������
			DispatchMessage(&msg);
		}
		else {
			//�A�v���P�[�V�������������鎞�Ԃ�������A�v���P�[�V�����̏���

			m_pFPS->PrintFps(m_hWnd);
			m_pFPS->Run();
			m_pTestGameScene->App();
		}
	}
	//�A�v���P�[�V�����̏I��

}

//void MAIN::App()
//�A�v���P�[�V���������B�A�v���̃��C���֐�



//HRESULT MAIN::InitD3D()
//Direct3D������

HRESULT MAIN::InitD3D()
{
	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd;  //�X���b�v�`�F�[�������ۂɐݒ������\����

	ZeroMemory(&sd, sizeof(sd));;//�܂��̓��������N���A

	sd.BufferCount = 1; //�o�b�t�@�[���������邩
	sd.BufferDesc.Width = WINDOW_WIDTH;//�X���b�v�`�F�[���̕��@��{�I�ɃE�B���h�Eb�̃T�C�Y�Ɠ����ł���
	sd.BufferDesc.Height = WINDOW_HEIGHT;//������͍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�t�H�[�}�b�g�̐ݒ�
	sd.BufferDesc.RefreshRate.Numerator = 60;//���t���b�V�����[�g�̐ݒ�@����͂U�O
	sd.BufferDesc.RefreshRate.Denominator = 1;//Denominator�Ƃ͕���Ƃ����Ӗ��炵���@�Ȃ̂Ł@60/1���t���b�V�����[�g�Ƃ������ƂɂȂ�̂��H

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//Usage�Ƃ͎g�p�@�Ƃ����Ӗ��Ȃ̂Ł@������ǂ̂悤�Ɏg�p���邩�ɂ��Đݒ肵�Ă���Ǝv��
	sd.OutputWindow = m_hWnd;//�ǂ̃E�B���h�E��\������̂�
	sd.SampleDesc.Count = 1;//Desc�Ƃ͐����A�T���v���̐�������������ۂ��Ǝv��
	sd.SampleDesc.Quality = 0;//����͉𑜓x�ׂ̍����Ƃ��Ɋ֌W������̂��ȁH

	sd.Windowed = TRUE; //�E�B���h�E���[�h���ǂ���

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;//FEATURE�Ƃ͓���
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel, &m_pDeviceContext)))
	{
		return FALSE;
	}

	//�e��e�N�X�`���[�Ƃ���ɕt������e��r���[���쐬

	//�o�b�N�o�b�t�@�[�ƃe�N�X�`���[���擾 (���łɂ���̂ł��쐬�ł͂Ȃ�

	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);//�X���b�v�`�F�[������e�N�X�`���[���擾

	//���̃e�N�X�`���[�ɑ΂��ă����_�[�^�[�Q�b�g�r���[���쐬

	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV); //��قǎ擾�����e�N�X�`�������ƂɃ����_�[�^�[�Q�b�g�r���[���쐬

	SAFE_RELEASE(pBackBuffer_Tex);//�s�v�ɂȂ������ߔj���H

	//�f�v�X�X�e���V���r���[�p�̃e�N�X�`���[���쐬

	D3D11_TEXTURE2D_DESC descDepth; //�e�N�X�`���QD�̐���

	descDepth.Width = WINDOW_WIDTH;//�[�x�e�N�X�`�����E�B���h�E�𓯂��傫���ɂ���ق����悢
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;		//Mip�Ƃ́H
	descDepth.ArraySize = 1;		//�z��̃T�C�Y
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;//��������̂�
	descDepth.SampleDesc.Quality = 0;//�N�I���e�B�͂ǂ̒��x�ɂ���̂�
	descDepth.Usage = D3D11_USAGE_DEFAULT;//�g�p�@

	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;//�ǂ̂悤�Ȃ��̂Ȃ̂�

	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);//���������ƂɃf�b�v�X�e�N�X�`���[���쐬

	//���̃e�N�X�`���[�ɑ΂��ăf�v�X�X�e���V���r���[���쐬

	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h����
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV);

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp; //��������ݒ�Ɋւ��Đ����̂悤�Ȃ��̂���
	vp.Width = WINDOW_WIDTH;//�r���[�|�[�g����{�I�ɃE�B���h�E�̃T�C�Y�Ɠ����ł����H
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f; //�r���[�����ۂɁA����p�����Ƃɕ`��͈͂����߂�ۂɁ@�[�x�̈�ԏ������Ƃ���Ƒ傫���Ƃ���̕������߂�
						//��{�I�ɂ́@���̐[�x�Ȃǂ����ƂɁA����p�Ƃ��v�Z���ĕ`�悷��T�C�Y��ς���
						//���̕�Ԍv�Z�ɂ���ăp�[�X��������
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp); //�r���[�|�[�g���������@�����Đ�قǂ̐ݒ肵��������n���Đݒ�

	//���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rdc;//���X�^���C�Y�Ɋւ�������@���̕ӂ͌��\���񓯂��p�^�[���̂悤�ȋC������
								//������ݒ肷��ꍇ�́@�܂��͐��������쐬����������Ƃɐݒ肷��

	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE; //�J���Ɋւ��Ă͉��������C�����邪�o���ĂȂ�
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;

	m_pDevice->CreateRasterizerState(&rdc, &pIr);//��قǐݒ肵�������������ƂɁ@pIr�ɍ쐬�������̂��Ƃ肠���������

	m_pDeviceContext->RSSetState(pIr);//��قǐ����������Ƃɍ�������X�^���C�U�[�����ۂɐݒ肵�Ă����Ă���

	SAFE_RELEASE(pIr);

	//�A���t�@�u�����h�p�u�����h�X�e�[�g�쐬
	//png�t�@�C�����ɃA���t�@��񂪂���B�A���t�@�ɂ�蓧�߂���悤�w�肵�Ă���
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&bd, &m_pBlendState)))
	{
		return E_FAIL;
	}

	UINT mask = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, mask);


	//�V�F�[�_�[���������s���@�@

	//if (FAILED(InitShader()))
	//{
	//	return E_FAIL;
	//}

	////�|���S���쐬
	//if (FAILED(InitPolygon()))
	//{
	//	return E_FAIL;
	//}

	m_pFPS = new FPS;


	return S_OK;
}







void MAIN::DestroyD3D()
{
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
	SAFE_DELETE(m_pFPS);

}