#include "main.h"
//#include <string>
//�O���[�o���ϐ�
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
		g_pMain->m_Camera = new Camera;
		g_pMain->m_FPS = new FPS;
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
	view = -2;
}


//�f�X�g���N�^
MAIN::~MAIN()
{

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
			view += 0.001;
			break;
		case VK_DOWN:
			view -= 0.001;
			break;
		}
		break;
	case WM_DESTROY://�E�B���h�E�̔j�����b�Z�[�W���͂�����@�I��������R�[���o�b�N���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);//���̂ق��̓f�t�H���g�̃E�B���h�E�̃v���Z�X���s��
}

void MAIN::Loop()
{
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	
	
	while (msg.message != WM_QUIT)//�I�����b�Z�[�W���͂��Ă��Ȃ���΁@���[�v
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //���b�Z�[�W�����Ƃɏ�����I��
		{
			TranslateMessage(&msg);			//�҂��s����̃E�B���h�E�̗D�揇�ʂ̍����v���Z�X������
			DispatchMessage(&msg);
		}
		else {
			//�A�v���P�[�V�������������鎞�Ԃ�������A�v���P�[�V�����̏���

			App();
		}
	}
	//�A�v���P�[�V�����̏I��

}

//void MAIN::App()
//�A�v���P�[�V���������B�A�v���̃��C���֐�

void MAIN::App()
{
	g_pMain->m_FPS->Run();
	Render();//�A�v���P�[�V�����̒��g�͌��󃌃��_�[�̂�
}


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

	//�V�F�[�_�[���������s���@�@

	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}

	//�|���S���쐬
	if (FAILED(InitPolygon()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT MAIN::InitShader()
{

	
	//hlsl�t�@�C���ǂݍ��݁@�u���u�쐬�@
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[���쐬

	int tmpnum;
	
	m_TestModel.m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	}

	m_Ground.m_VertexShader.Init(m_pDevice, m_pDeviceContext);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //���̍�Ƃ��s���̂́@�{���̓V�F�[�_�[�̏������ƂɃ��C�A�E�g�����K�v���łĂ��邽�߁A�V�F�[�_�[���Ƃ�

	//m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);

	for (int i = 0; i < 3; i++) {
		m_EnemyModel[i].m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	}
	m_TestModel.m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_Ground.m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	


	////���_�C���v�b�g���C�A�E�g���`
	////���񂱂��� VS_OUTPUT�̃��C�A�E�g�����ƂɁ@�@POSITION �� UV�ɂȂ�TEXCOORD��ݒ�
	

	
	//�u���u����s�N�Z���V�F�[�_�[�쐬

	m_TestModel.m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_TestModel.m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_PixelShader.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);
	}

	m_Ground.m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	m_TestModel.m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);

	
	//�R���X�^���g�o�b�t�@�[�쐬�@�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;//������
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU�ɃA�N�Z�X����t���O�ݒ�
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//�g�p�@

	m_TestModel.m_ConstantBuffer.CreateConstantBuffer(cb);

	for (int i = 0; i < 3; i++)
	{
		m_EnemyModel[i].m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_ConstantBuffer.CreateConstantBuffer(cb);
	}

	m_Ground.m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_ConstantBuffer.CreateConstantBuffer(cb);

	return S_OK;
}


HRESULT MAIN::InitPolygon()
{
	m_TestModel.PosInit();
	m_TestModel.m_Cube.Init(m_pDevice, m_pDeviceContext);
	m_TestModel.m_Cube.CreateVertexBuffer();
	m_TestModel.m_Cube.CreateTexture("white.jpg");

	for (int i = 0; i < 3; i++) {
		m_EnemyModel[i].PosInit();
		m_EnemyModel[i].m_Cube.Init(m_pDevice, m_pDeviceContext);
		m_EnemyModel[i].m_Cube.CreateVertexBuffer();
		m_EnemyModel[i].m_Cube.CreateTexture("red.jpg");
	}

	m_Ground.PosInit();
	m_Ground.m_Ground.Init(m_pDevice, m_pDeviceContext);
	m_Ground.m_Ground.CreateVertexBuffer();
	m_Ground.m_Ground.CreateTexture("white.jpg");

	return S_OK;
}

void MAIN::Render()
{
	Camera* MainCamera = g_pMain->m_Camera;	//Main Camera Pointer
	FPS* DeltaFPS = g_pMain->m_FPS;
	float ClearColor[4] = { 0,0,0.0,1 }; //�N���A�F�@RGBA

	//��ʃN���A
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//�J���[
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//�f�v�X�X�e���V��

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;


	//Inputs

	//getting delta position by inputs
	D3DXVECTOR3 deltaPosition(0, 0, 0);
	deltaPosition = MainCamera->m_Pos;
	D3DXVECTOR3 deltaRot(0,0,0);
	deltaRot = MainCamera->m_Rot;
	if (DeltaFPS->DeltaReady())
	{
		if (GetKeyState('A') & 0x80) {
			MainCamera->m_Pos += 1.0f * -MainCamera->m_vRight * DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('D') & 0x80) {
			MainCamera->m_Pos += 1.0f * MainCamera->m_vRight* DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('W') & 0x80) {
			MainCamera->m_Pos += 1.0f * MainCamera->m_vForward* DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState('S') & 0x80) {
			MainCamera->m_Pos += 1.0f * -MainCamera->m_vForward* DeltaFPS->GetDeltaTime();
		}

		//getting delta rotation by inputs
		if (GetKeyState(VK_RIGHT) & 0x80) {
			MainCamera->m_Rot.y += 1.0f * DeltaFPS->GetDeltaTime();
		}
		if (GetKeyState(VK_LEFT) & 0x80) {
			MainCamera->m_Rot.y -= 1.0f * DeltaFPS->GetDeltaTime();
		}
	}


	
	deltaPosition = (MainCamera->m_Pos - deltaPosition);
	//deltaRot = (MainCamera->m_Rot - deltaRot);
	//popup message
	if (GetKeyState(VK_SPACE))
	{
		char testString[256];
		sprintf_s(testString, "%f", MainCamera->m_Pos.x);
		MessageBox(m_hWnd, testString, "test", 0);
	}

	if (GetKeyState('E') & 0x80)
	{
		char testString[256];
		sprintf_s(testString, "%f", DeltaFPS->GetDeltaTime());
		MessageBox(m_hWnd, testString, "test", 0);
	}

	//���[���h�g�����X�t�H�[��
	//Rotate and Translate main camera
	D3DXMatrixTranslation(&MainCamera->m_Transform, deltaPosition.x, deltaPosition.y, deltaPosition.z);

	D3DXVECTOR3 vRotTmp(MainCamera->m_PoseMat._21, MainCamera->m_PoseMat._22, MainCamera->m_PoseMat._23);
	D3DXMatrixRotationAxis(&MainCamera->m_DeltaMat, &vRotTmp, MainCamera->m_Rot.y);

	D3DXVECTOR3 vRight(1, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vForward(0, 0, 1);
	D3DXVec3TransformCoord(&MainCamera->m_vRight, &vRight, &MainCamera->m_DeltaMat);
	D3DXVec3TransformCoord(&MainCamera->m_vUp, &vUp, &MainCamera->m_DeltaMat);
	D3DXVec3TransformCoord(&MainCamera->m_vForward, &vForward, &MainCamera->m_DeltaMat);


	D3DXMATRIX mTransform = MainCamera->m_DeltaMat * MainCamera->m_Transform;

	//D3DXVec3TransformCoord(&MainCamera->m_vLookat, &MainCamera->m_vLookat, &MainCamera->m_Transform);
	//D3DXVec3TransformCoord(&MainCamera->m_vEyePt, &MainCamera->m_vEyePt, &MainCamera->m_Transform);


	//D3DXVec3TransformCoord(&MainCamera->m_vLookat, &MainCamera->m_vLookat, &mTransform);
	//D3DXVec3TransformCoord(&MainCamera->m_vEyePt, &MainCamera->m_vEyePt, &mTransform);

	D3DXVECTOR3 vEyePt = MainCamera->m_Pos;
	D3DXVECTOR3 vLookAtPt = vEyePt + MainCamera->m_vForward;

	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookAtPt, &MainCamera->m_vUp); //getting view matrix

	
	//�v���W�F�N�V�����g�����X�t�H�[��
	D3DXMatrixPerspectiveFovLH(&mProjection, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


	
	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, 0.0f, 0.0f, 0.0f);
	m_TestModel.Render(mView, mProjection,Tran);
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&Tran, (i+1)*1, 0, (i+1)*1);

		m_EnemyModel[i].Render(mView, mProjection, Tran);
	}
	
	m_Ground.Render(mView, mProjection);

	g_pMain->m_FPS->PrintFps(m_hWnd);

	m_pSwapChain->Present(0, 0);//��ʍX�V

}


void MAIN::DestroyD3D()
{
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
}