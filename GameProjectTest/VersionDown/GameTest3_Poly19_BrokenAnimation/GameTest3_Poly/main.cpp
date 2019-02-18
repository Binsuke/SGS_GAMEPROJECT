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
		g_pMain->m_pCamera = new Camera;
		g_pMain->m_pFPS = new FPS;
		g_pMain->InitModel();
		g_pMain->m_pCamera->InitCamera();
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME))) //�E�B���h�E�̍쐬�@�������Ă����璆�ɓ���
		{
			if (SUCCEEDED(g_pMain->InitD3D()))//D3D�n��̏������@�������Ă����烋�[�v�ɓ���
			{
				g_pMain->Loop();	//���C�����[�v
			}
		}
		//�A�v���̏I��
		g_pMain->ReleaseModel();
		g_pMain->DestroyD3D();
		delete g_pMain;
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);//���C���̃��b�Z�[�W�v���Z�X�����s�@�����Č��ʂ�Ԃ�
}

void MAIN::InitModel()
{
	m_pTestModel = new MyModel;
	m_pTestModel->InitLv(3);
	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i] = new MyModel;
		//int LV = (m_pEnemyModel[i]->GetLV());
		m_pEnemyModel[i]->InitLv(i + 1);
		float Size = (m_pEnemyModel[i]->GetSize());
		m_pEnemyModel[i]->SetPos(0, 0, Size * (i + 10));
	}
	m_pGround = new MyGround;
	m_pMoveUI = new MoveUI;
}

void MAIN::ReleaseModel()
{
	//m_pTestModel->m_Cube.Release();

	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pFPS);
	SAFE_DELETE(m_pTestModel);

	//SAFE_DELETE_ARRAY(m_pEnemyModel);
	for (int i = 0; i < 3; i++) {
		SAFE_DELETE(m_pEnemyModel[i]);
	}

	SAFE_DELETE(m_pGround);
	SAFE_DELETE(m_pMoveUI);
}
//�R���X�g���N�^
MAIN::MAIN()
{
	ZeroMemory(this, sizeof(MAIN));
	m_eMoveVec = MAIN::eMoveVec::None;
	UI_RenderFlg = true;
	//view = -2;
}


//�f�X�g���N�^
MAIN::~MAIN()
{

}

bool MAIN::Colision2(MyModel* pModelA, MyModel* pModelB)
{
	D3DXVECTOR3 vLength = pModelB->GetCenter() - pModelA->GetCenter();
	float fLength = D3DXVec3Length(&vLength);
	float fModelArad = pModelA->GetSize() *0.5;//sqrt(pow(pModelA->GetSize(), 2) + pow(pModelA->GetSize(), 2))*0.49;
	float fModelBrad = sqrt(pow(pModelB->GetSize(), 2) + pow(pModelB->GetSize(), 2))*0.49;
	if (fLength < fModelArad + fModelBrad)
	{
		return true;
	}
	return false;
}
bool MAIN::Colision(MyModel* pModelA, MyModel* pModelB)
{
		//D3DXVECTOR3 vLength = pModelB->GetCenter() - pModelA->GetCenter();
		//float fLength = D3DXVec3Length(&vLength);
		//float fModelArad = pModelA->GetSize() *0.49;//sqrt(pow(pModelA->GetSize(), 2) + pow(pModelA->GetSize(), 2))*0.49;
		//float fModelBrad = sqrt(pow(pModelB->GetSize(), 2) + pow(pModelB->GetSize(), 2))*0.49;
		//if (fLength < fModelArad + fModelBrad)
		//{
		//	return true;
		//}

			D3DXVECTOR3 vModelA = pModelA->GetCenter();
			D3DXVECTOR3 vModelB = pModelB->GetCenter();

			D3DXVECTOR2 vTopRightA;

			float SizeA = pModelA->GetSize() * 0.98;
			float SizeB = pModelB->GetSize() * 0.98;

			vTopRightA.x = vModelA.x + SizeA / 2.0f;
			vTopRightA.y = vModelA.z + SizeA / 2.0f;
			D3DXVECTOR2 vTopLeftA;
			vTopLeftA.x = vModelA.x - SizeA / 2.0f;
			vTopLeftA.y = vModelA.z + SizeA / 2.0f;
			D3DXVECTOR2 vUnderRightA;
			vUnderRightA.x = vModelA.x + SizeA / 2.0f;
			vUnderRightA.y = vModelA.z - SizeA / 2.0f;
			D3DXVECTOR2 vUnderLeftA;
			vUnderLeftA.x = vModelA.x - SizeA / 2.0f;
			vUnderLeftA.y = vModelA.z - SizeA / 2.0f;


			D3DXVECTOR2 vTopRightB;
			vTopRightB.x = vModelB.x + SizeB / 2.0f;
			vTopRightB.y = vModelB.z + SizeB / 2.0f;
			D3DXVECTOR2 vTopLeftB;
			vTopLeftB.x = vModelB.x - SizeB / 2.0f;
			vTopLeftB.y = vModelB.z + SizeB / 2.0f;
			D3DXVECTOR2 vUnderRightB;
			vUnderRightB.x = vModelB.x + SizeB / 2.0f;
			vUnderRightB.y = vModelB.z - SizeB / 2.0f;
			D3DXVECTOR2 vUnderLeftB;
			vUnderLeftB.x = vModelB.x - SizeB; // 2.0f;
			vUnderLeftB.y = vModelB.z - SizeB; // 2.0f;

			if (vTopLeftA.x < vUnderRightB.x && vTopLeftA.y > vUnderRightB.y
				&& vTopRightA.x > vUnderLeftB.x && vTopRightA.y > vUnderLeftB.y
				&& vUnderLeftA.x < vTopRightB.x && vUnderLeftA.y < vTopRightB.y
				&& vUnderRightA.x > vTopLeftB.x && vUnderRightA.y < vTopLeftB.y
				)
			{
				return true;
			}


		

	return false;
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
	g_pMain->m_pFPS->Run();

	for (int i = 0; i < 3; i++) {
		//if (g_pMain->m_pTestModel->GetLV() > g_pMain->m_pEnemyModel[i]->GetLV())
		//{
		if (g_pMain->m_pEnemyModel[i]->GetLV() > 0) {
			//if (g_pMain->m_pTestModel->GetLV() > m_pEnemyModel[i]->GetLV()) {
				if (Colision(g_pMain->m_pTestModel, g_pMain->m_pEnemyModel[i]))
				{
					g_pMain->m_pEnemyModel[i]->LVDown();
				}
			//}
			//else if (g_pMain->m_pTestModel->GetLV() == 1 && m_pEnemyModel[i]->GetLV() == 1)
			//{
				//if (Colision(g_pMain->m_pTestModel, g_pMain->m_pEnemyModel[i])) {
				//	g_pMain->m_pEnemyModel[i]->LVDown();
				//}
			//}

		}
		//}
	}
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

	m_pTestModel->m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	}

	m_pGround->m_VertexShader.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_VertexShader.Init(m_pDevice, m_pDeviceContext);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]); //���̍�Ƃ��s���̂́@�{���̓V�F�[�_�[�̏������ƂɃ��C�A�E�g�����K�v���łĂ��邽�߁A�V�F�[�_�[���Ƃ�

	//m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);

	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i]->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	}
	m_pTestModel->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pGround->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);
	m_pMoveUI->m_VertexShader.CreateShaderFromFileV("SimpleTexture.hlsl", "VS", "vs_5_0", &tmpnum, layout, numElements);


	////���_�C���v�b�g���C�A�E�g���`
	////���񂱂��� VS_OUTPUT�̃��C�A�E�g�����ƂɁ@�@POSITION �� UV�ɂȂ�TEXCOORD��ݒ�



	//�u���u����s�N�Z���V�F�[�_�[�쐬

	m_pTestModel->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pTestModel->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);
	}

	m_pGround->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);

	m_pMoveUI->m_PixelShader.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_PixelShader.CreateShaderFromFile("SimpleTexture.hlsl", "PS", "ps_5_0", &tmpnum);


	m_pTestModel->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);


	//�R���X�^���g�o�b�t�@�[�쐬�@�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;//������
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU�ɃA�N�Z�X����t���O�ݒ�
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;//�g�p�@

	m_pTestModel->m_ConstantBuffer.CreateConstantBuffer(cb);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_ConstantBuffer.CreateConstantBuffer(cb);
	}

	m_pGround->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_ConstantBuffer.CreateConstantBuffer(cb);

	m_pMoveUI->m_ConstantBuffer.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_ConstantBuffer.CreateConstantBuffer(cb);


	return S_OK;
}


HRESULT MAIN::InitPolygon()
{
	m_pTestModel->m_Cube.Init(m_pDevice, m_pDeviceContext);
	m_pTestModel->m_Cube.CreateVertexBuffer();
	m_pTestModel->m_Cube.CreateTexture("white.png");

	for (int i = 0; i < 3; i++) {
		m_pEnemyModel[i]->m_Cube.Init(m_pDevice, m_pDeviceContext);
		m_pEnemyModel[i]->m_Cube.CreateVertexBuffer();
		m_pEnemyModel[i]->m_Cube.CreateTexture("red.jpg");
	}

	m_pGround->PosInit();
	m_pGround->m_Ground.Init(m_pDevice, m_pDeviceContext);
	m_pGround->m_Ground.CreateVertexBuffer();
	m_pGround->m_Ground.CreateTexture("white.jpg");

	/*m_pMoveUI->m_PanelW.Init(m_pDevice, m_pDeviceContext);
	m_pMoveUI->m_PanelW.CreateVertexBuffer();
	m_pMoveUI->m_PanelW.CreateTexture("UI_W.png");
*/
	m_pMoveUI->MovePanelInit(m_pDevice, m_pDeviceContext);
	return S_OK;
}

void MAIN::Render()
{
	Camera* MainCamera = g_pMain->m_pCamera;	//Main Camera Pointer
	FPS* DeltaFPS = g_pMain->m_pFPS;
	float ClearColor[4] = { 0,0,0.0,1 }; //�N���A�F�@RGBA

	//��ʃN���A
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//�J���[
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//�f�v�X�X�e���V��

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProjection;


	//Inputs
	//static MAIN::eMoveVec Vec = MAIN::eMoveVec;;None;

	int KeyStateCnt = 4;

	if (DeltaFPS->DeltaReady())
	{
		if (GetKeyState('A') & 0x80) {
			if (m_eMoveVec == eMoveVec::None || m_eMoveVec == eMoveVec::Left)
			{
				m_eMoveVec = eMoveVec::Left;
				UI_RenderFlg = false;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Left) {
				//m_eMoveVec = eMoveVec::None;
				//UI_RenderFlg = true;
			}
			KeyStateCnt--;
		}

		if (GetKeyState('D') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Right)
			{
				m_eMoveVec = MAIN::eMoveVec::Right;
				UI_RenderFlg = false;
			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Right) {
				//m_eMoveVec = eMoveVec::None;
				//UI_RenderFlg = true;
			}
			KeyStateCnt--;
		}
		if (GetKeyState('W') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Forward)
			{
				m_eMoveVec = MAIN::eMoveVec::Forward;
				UI_RenderFlg = false;
			}
			
		}
		else {
			if (m_eMoveVec == eMoveVec::Forward) {
				//m_eMoveVec = eMoveVec::None;
				//UI_RenderFlg = true;

			}
			KeyStateCnt--;
		}
		if (GetKeyState('S') & 0x80) {
			if (m_eMoveVec == MAIN::eMoveVec::None || m_eMoveVec == MAIN::eMoveVec::Backward)
			{
				m_eMoveVec = MAIN::eMoveVec::Backward;
				UI_RenderFlg = false;

			}
		}
		else {
			if (m_eMoveVec == eMoveVec::Backward) {
				//m_eMoveVec = eMoveVec::None;
				//UI_RenderFlg = true;
			}
			KeyStateCnt--;
		}


		//�����Ɍ����悤�ɂ��邩�@���̃^�[�Q�b�g�܂Ŗ߂����̏���
		MainCamera->UpDateLook(DeltaFPS->GetDeltaTime(), m_pTestModel->GetSize());
		if (GetKeyState(VK_UP) & 0x80) {
			MainCamera->LookUp(DeltaFPS->GetDeltaTime(), m_pTestModel->GetSize());
			
			//MainCamera->MoveUp(DeltaFPS->GetDeltaTime());
		}
		if (GetKeyState(VK_DOWN) & 0x80) {
			MainCamera->LookDown(DeltaFPS->GetDeltaTime(), m_pTestModel->GetSize());
			//MainCamera->MoveDown(DeltaFPS->GetDeltaTime());
		}

		static bool bR = false;
		static bool bL = false;
		if (GetKeyState(VK_RIGHT) & 0x80) {
			//MainCamera->RotRight(DeltaFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				MainCamera->RotRight(DeltaFPS->GetDeltaTime());
				bR = true;
			}
		}
		else {
			if (m_eMoveVec == None)
			{
				bR = false;
			}
		}

		if (GetKeyState(VK_LEFT) & 0x80) {
			//MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
			if (m_eMoveVec == None)
			{
				MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
				bL = true;
			}
		}
		else {
			if (m_eMoveVec == None) 
			{
				bL = false;
			}
		}

		bool check = MoveUpdateA(m_eMoveVec);
		if (check) {
			m_eMoveVec = eMoveVec::None;
		}

		if (bL || bR ) {
			UI_RenderFlg = false;
		}
		else if(KeyStateCnt == 0 && check){
			UI_RenderFlg = true;
		}

		
		static bool flg = false;//���x���A�b�v�m�F�p

		if (GetKeyState('E') & 0x80) {
			//MainCamera->RotRight(DeltaFPS->GetDeltaTime());
			if (!flg) {
				if (m_eMoveVec == None) {
					m_pTestModel->LVUp();
					flg = true;
				}
			}
		}
		else if (flg) {
			flg = false;
		}
		static bool flg2 = false;

		if (GetKeyState('Q') & 0x80) {
			//MainCamera->RotLeft(DeltaFPS->GetDeltaTime());
			if (!flg2) {
				if (m_eMoveVec == None)
				{
					if (m_pTestModel->GetLV() >= 2) {
						m_pTestModel->LVDown();
						flg2 = true;
					}
				}
			}
		}
		else if (flg2) {
			flg2 = false;
		}
	}

	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, 0.0f, 0.0f, 0.0f);
	MainCamera->SetCameraA(&mView, &mProjection, m_pTestModel->GetCameraTarget(), m_pTestModel->GetCameraMargin());

	


	m_pGround->Render(mView, mProjection);

	for (int i = 0; i < 3; i++)
	{
		m_pEnemyModel[i]->Render(mView, mProjection);
	}

	m_pTestModel->Render(mView, mProjection);
	
	if (UI_RenderFlg) {
		m_pMoveUI->Render(mView, mProjection, m_pTestModel->GetCenter(), m_pTestModel->GetSize() * 1.1, MainCamera->GetWorldForward(), m_pTestModel->GetLV());
	}
	g_pMain->m_pFPS->PrintFps(m_hWnd);

	m_pSwapChain->Present(0, 0);//��ʍX�V

}

void MAIN::MoveUpdate(eMoveVec eVec)
{
	m_pCamera->UpDateWorldVec();
	D3DXVECTOR3 vLocalVec;
	switch (eVec)
	{
		//case eMoveVec::None:
			//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);

	case eMoveVec::Forward:
		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalVec);
		break;
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		m_pTestModel->Move(m_pFPS->GetDeltaTime(), vLocalLeftVec);
		break;
	}
}



bool MAIN::MoveUpdateA(eMoveVec eVec)
{
	m_pCamera->UpDateWorldVec();
	D3DXVECTOR3 vLocalVec;
	switch (eVec)
	{
	case eMoveVec::None:
		//m_pCamera->GetMoveLocalVec(&vLocalVec, Camera::eGetForward);
		//UI_RenderFlg = true;
		return true;
	case eMoveVec::Forward:
		//D3DXVECTOR3 vLocalForwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetForward);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Backward:
		//D3DXVECTOR3 vLocalBackwardVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetBackward);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case eMoveVec::Right:
		//D3DXVECTOR3 vLocalRightVec(0,0,0);
		m_pCamera->GetMoveLocalVecA(&vLocalVec, Camera::eGetRight);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalVec);
	case Left:
		D3DXVECTOR3 vLocalLeftVec;
		m_pCamera->GetMoveLocalVecA(&vLocalLeftVec, Camera::eGetLeft);
		return m_pTestModel->MoveA(m_pFPS->GetDeltaTime(), vLocalLeftVec);
	}

	return false;
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