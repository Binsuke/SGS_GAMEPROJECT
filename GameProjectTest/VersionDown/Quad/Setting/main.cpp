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

	if ( FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel,&m_pDeviceContext)))
	{
		return FALSE;
	}

	//�e��e�N�X�`���[�Ƃ���ɕt������e��r���[���쐬

	//�o�b�N�o�b�t�@�[�ƃe�N�X�`���[���擾 (���łɂ���̂ł��쐬�ł͂Ȃ�

	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);//�X���b�v�`�F�[������e�N�X�`���[���擾
	
	//���̃e�N�X�`���[�ɑ΂��ă����_�[�^�[�Q�b�g�r���[���쐬

	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL,&m_pBackBuffer_TexRTV); //��قǎ擾�����e�N�X�`�������ƂɃ����_�[�^�[�Q�b�g�r���[���쐬

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

	//hlsl�t�@�C���ǂݍ��݁@�u���u�쐬
	ID3DBlob* pCompileShader = NULL;//�������قǂ�D3D11�n��̐������ō���Ă����p�^�[���Ɠ����悤�Ȃ��̂��Ǝv��

	//�o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(MakeShader((LPSTR)"Point3D.hlsl", (LPSTR)"VS", (LPSTR)"vs_5_0", (void**)&m_pVertexShader, &pCompileShader)))
	{
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���쐬
	//��������Ƃɒ��_�̃��C�A�E�g���V�F�[�_�[���ɒm�点�Ă���͂�
	//���_�̃��C�A�E�g���ς��΂������ς��
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);//���_���C�A�E�g�͂��̓s�x�ς��\��������̂Ł@
															//�S�̂̃T�C�Y����̃T�C�Y�Ŋ��邱�Ƃ�
															//�G�������g�������߂Ă���

	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompileShader->GetBufferPointer(), pCompileShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return FALSE;
	}

	SAFE_RELEASE(pCompileShader);

	//�s�N�Z���V�F�[�_�[�쐬
	if (FAILED(MakeShader((LPSTR)"Point3D.hlsl", (LPSTR)"PS", (LPSTR)"ps_5_0", (void**)&m_pPixelShader, &pCompileShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompileShader);

	//�R���X�^���g�o�b�t�@�[���쐬�@�ϊ��s��n���悤

	D3D11_BUFFER_DESC cb;//�����p�̃o�b�t�@
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�ǂ������������Ȃ̂�
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);//�o�b�t�@�[�̃T�C�Y
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	
	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer))) //�����p�̃o�b�t�@�����ƂɃR���X�^���g�o�b�t�@�[�̐ݒ�
	{
		return E_FAIL;
	}
	
	//�_�Ƃ��Ẵo�[�e�b�N�X�o�b�t�@�[�쐬
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//HRESULT MAIN::MakeShader(LPSTR szFileName,LPSTR szFuncName,LPSTR szProfileName,void** ppShader,ID3DBlob** ppBlob)
//hlsl�t�@�C����ǂݍ��݃V�F�[�_�[���쐬����
HRESULT MAIN::MakeShader(LPSTR szFileName, LPSTR szFuncName, LPSTR szProfileName, void** ppShader, ID3DBlob** ppBlob)
{
	ID3DBlob *pErrors = NULL;
	if (FAILED(D3DX11CompileFromFileA(szFileName, NULL, NULL, szFuncName, szProfileName, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, NULL, ppBlob, &pErrors, NULL)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	char szProfile[3] = { 0 };
	memcpy(szProfile, szProfileName, 2);//�v���t�@�C���l�[���Q�������R�s�[

	if (strcmp(szProfile, "vs") == 0)//vertexshader
	{
		if (FAILED(m_pDevice->CreateVertexShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11VertexShader**)ppShader)))
		{
			return E_FAIL;
		}
	}

	if (strcmp(szProfile, "ps") == 0)//pixel Shader
	{
		if (FAILED(m_pDevice->CreatePixelShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11PixelShader**)ppShader)))
		{
			return E_FAIL;
		}
	}

	if (strcmp(szProfile, "gs") == 0) //GeometryShader
	{
		if (FAILED(m_pDevice->CreateGeometryShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11GeometryShader**)ppShader)))
		{
			return E_FAIL;
		}
	}


	if (strcmp(szProfile, "hs") == 0) //HullShader
	{
		if (FAILED(m_pDevice->CreateHullShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11HullShader**)ppShader)))
		{
			return E_FAIL;
		}
	}

	if (strcmp(szProfile, "ds") == 0)//Domain Shader
	{
		if (FAILED(m_pDevice->CreateDomainShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11DomainShader**)ppShader)))
		{
			return E_FAIL;
		}
	}
	if (strcmp(szProfile, "cs") == 0)//Compute Shader
	{
		if (FAILED(m_pDevice->CreateComputeShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11ComputeShader**)ppShader)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//HRESULT MAIN::InitModel()
//�|���S���A���b�V���Ȃǂ̃W�I���g���֘A���������i�����ł́h�_�h�p

HRESULT MAIN::InitModel()
{
	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(-0.5f,-0.5f,0.0f),
		D3DXVECTOR3(-0.5f,0.5f,0.0f),
		D3DXVECTOR3(0.5f,-0.5f,0.0f),	//���ɕύX���邽�߃|�C���g��ǉ�

		D3DXVECTOR3(0.5f,0.5f,0.0f),
	};
	D3D11_BUFFER_DESC bd; //����
	bd.Usage = D3D11_USAGE_DEFAULT;//�g�p�@
	bd.ByteWidth = sizeof(SimpleVertex) * 4;//�T�C�Y��3�ɂȂ������ߐ���ύX
											//�����Ɋւ��Ă�sizeof(vertices) / sizeof(simpleVertex)�̂悤�ɂ���̂���������
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData; //�f�[�^����邽�߂ɂ��낢��l�ߍ��ނ��߂̔�

	InitData.pSysMem = vertices;

	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}


	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	return S_OK;

}

void MAIN::Render()
{
	//��ʃN���A
	float ClearColor[4] = { 0,0,0.5,1 }; //�N���A�F�@RGBA

	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//�J���[
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//�f�v�X�X�e���V��

	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Proj;

	//���[���h�g�����X�t�H�[��
	static float x = 0;

	//x += 0.00001;
	D3DXMATRIX Tran;
	D3DXMatrixTranslation(&Tran, x, 0, 0);
	World = Tran;

	//�r���[�g�����X�t�H�[��
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -2.0f); //���_�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	D3DXMatrixLookAtLH(&View, &vEyePt, &vLookatPt, &vUpVec);

	//�v���W�F�N�V�����g�����X�t�H�[��
	D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI / 4,(FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�@�J�����@�ˉe�s���n��
		D3DXMATRIX m = World * View*Proj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�v���~�e�B�u�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//���ɂ��邽�߂ɕύX

	//�v���~�e�B�u�������_�����O
	m_pDeviceContext->Draw(4, 0);//�o�[�e�b�N�X��3�ɂȂ������炱�����ύX

	m_pSwapChain->Present(0, 0);//��ʍX�V

}


void MAIN::DestroyD3D()
{
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
}