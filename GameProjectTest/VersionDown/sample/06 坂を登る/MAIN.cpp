#include "MAIN.h"
//�O���[�o���ϐ�
MAIN* g_pMain=NULL;
//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//
//
//�A�v���P�[�V�����̃G���g���[�֐� 
INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
{
	g_pMain=new MAIN;
	if(g_pMain != NULL)
	{
		if(SUCCEEDED(g_pMain->InitWindow(hInstance,0,0,WINDOW_WIDTH,
			WINDOW_HEIGHT,APP_NAME)))
		{
			if(SUCCEEDED(g_pMain->InitD3D()))
			{
				g_pMain->Loop();
			}
		}
		//�A�v���I��
		g_pMain->DestroyD3D();
		delete g_pMain;
	}
	return 0;
}
//
//
//OS���猩���E�B���h�E�v���V�[�W���[�i���ۂ̏�����MAIN�N���X�̃v���V�[�W���[�ŏ����j
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd,uMsg,wParam,lParam);
}
//
//
//�E�B���h�E�쐬
HRESULT MAIN::InitWindow(HINSTANCE hInstance,
		INT iX,INT iY,INT iWidth,INT iHeight,LPCWSTR WindowName)
 {
	 // �E�B���h�E�̒�`
	WNDCLASSEX  wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(&wc);

	//�E�B���h�E�̍쐬
	m_hWnd=CreateWindow(WindowName,WindowName,WS_OVERLAPPEDWINDOW,
		0,0,iWidth,iHeight,0,0,hInstance,0);
	 if(!m_hWnd) 
	 {
		 return E_FAIL;
	 }
	 //�E�C���h�E�̕\��
	 ShowWindow(m_hWnd,SW_SHOW);
	 UpdateWindow(m_hWnd) ;

	 return S_OK;
 }
//
//
//�E�B���h�E�v���V�[�W���[
 LRESULT MAIN::MsgProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_KEYDOWN:
		switch((char)wParam)
		{
			case VK_ESCAPE://ESC�L�[�ŏC��
			PostQuitMessage(0);
			break;
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc (hWnd, iMsg, wParam, lParam);
 }
//
//
//���b�Z�[�W���[�v�ƃA�v���P�[�V���������̓����
void MAIN::Loop()
{
	//���b�V���쐬
	m_pRobotMesh=new CD3DXMESH;
	m_pRobotMesh->Init(m_hWnd,m_pDevice,m_pDeviceContext,"robotB.x");
	m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,1);
	m_pRobotMesh->m_vPos=D3DXVECTOR3(0,0.5,-10);

	m_pSlopeMesh=new CD3DXMESH;
	m_pSlopeMesh->Init(m_hWnd,m_pDevice,m_pDeviceContext,"slope.x");

	 // ���b�Z�[�W���[�v
	 MSG msg={0};
	 ZeroMemory(&msg,sizeof(msg));
	 while(msg.message!=WM_QUIT)
	 {
		 if( PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		 {
			 TranslateMessage(&msg);
			 DispatchMessage(&msg);
		 }
		 else
		 {
			 //�A�v���P�[�V�����̏����͂��������ԁB
			 App();			 
		 }
	 }
	 //�A�v���P�[�V�����̏I��
 }
//
//
//�A�v���P�[�V���������B�A�v���̃��C���֐��B
 void MAIN::App()
 {
	 Render();
 }
//
//
//
HRESULT MAIN::InitD3D()
{
	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0; 
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

    if( FAILED( D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL, 
		0,&pFeatureLevels,1,D3D11_SDK_VERSION,&sd,&m_pSwapChain,&m_pDevice,
		pFeatureLevel,&m_pDeviceContext )) )
	{
		return FALSE;
	}
	//�e��e�N�X�`���[�ƁA����ɕt�т���e��r���[���쐬

	//�o�b�N�o�b�t�@�[�e�N�X�`���[���擾�i���ɂ���̂ō쐬�ł͂Ȃ��j
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ),(LPVOID*)&pBackBuffer_Tex);
	//���̃e�N�X�`���[�ɑ΂������_�[�^�[�Q�b�g�r���[(RTV)���쐬
	m_pDevice->CreateRenderTargetView( pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV );
	SAFE_RELEASE(pBackBuffer_Tex);	

	//�f�v�X�X�e���V���r���[�p�̃e�N�X�`���[���쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pDevice->CreateTexture2D( &descDepth, NULL, &m_pBackBuffer_DSTex );
	//���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬
	m_pDevice->CreateDepthStencilView( m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV,m_pBackBuffer_DSTexDSV);
	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports( 1, &vp );
	//���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc,sizeof(rdc));
	rdc.CullMode=D3D11_CULL_NONE;
	rdc.FillMode=D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr=NULL;
	m_pDevice->CreateRasterizerState(&rdc,&pIr);
	m_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	return S_OK;
}
//
//
//
void MAIN::DestroyD3D()
{
	SAFE_DELETE(m_pRobotMesh);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDevice);
}
//
//
//�V�[������ʂɃ����_�����O
void MAIN::Render()
{	
	//���{�b�g����
	m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,0);
	if(GetKeyState('W') & 0x80)
	{
		m_pRobotMesh->m_Dir=m_pRobotMesh->m_AxisZ*0.05;
	}
	if(GetKeyState('S') & 0x80)
	{
		m_pRobotMesh->m_Dir=-m_pRobotMesh->m_AxisZ*0.05;
	}
	if(GetKeyState('A') & 0x80)
	{
		m_pRobotMesh->m_Dir=-m_pRobotMesh->m_AxisX*0.05;
	}
	if(GetKeyState('D') & 0x80)
	{
		m_pRobotMesh->m_Dir=m_pRobotMesh->m_AxisX*0.05;
	}
	if(GetKeyState(VK_LEFT) & 0x80)
	{
		m_pRobotMesh->m_fYaw-=0.05;
	}
	if(GetKeyState(VK_RIGHT) & 0x80)
	{
		m_pRobotMesh->m_fYaw+=0.05;
	}

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = {0,0,1,1};// �N���A�F�쐬�@RGBA�̏�
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV,ClearColor);//��ʃN���A
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV,D3D11_CLEAR_DEPTH,1.0f,0);//�[�x�o�b�t�@�N���A

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vEyePt; 
	D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	//�J���������{�b�g�̌��ɔz�u�B
	D3DXVECTOR3 v(0,1,-3);
	D3DXVec3TransformCoord(&v,&v,&m_pRobotMesh->m_World);
	vEyePt=v;
	vLookatPt=m_pRobotMesh->m_vPos+D3DXVECTOR3(0,0.5,0);//���{�b�g�̕��������悤�ɂ���

	D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookatPt, &vUpVec );
	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH( &mProj, D3DX_PI/4, (FLOAT)WINDOW_WIDTH/(FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f );
	//�����_�����O
	m_pRobotMesh->Render(mView,mProj,D3DXVECTOR3(1,1,-1),vEyePt);
	m_pSlopeMesh->Render(mView,mProj,D3DXVECTOR3(1,1,-1),vEyePt);
	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pSwapChain->Present(0,0);
	
	//�d�́i�������̃x�N�g�������Z�j
	m_pRobotMesh->m_Dir+=D3DXVECTOR3(0,-0.02,0);

	//�����蔻��
	float fDistance=0;
	D3DXVECTOR3 vNormal;
	if( RayIntersect(m_pRobotMesh,m_pRobotMesh->m_Dir,m_pSlopeMesh,&fDistance,&vNormal) && fDistance<=0.3)	
	{
		//�������ԂȂ̂ŁA���点��
		m_pRobotMesh->m_Dir=Slip(m_pRobotMesh->m_Dir,vNormal);//����x�N�g�����v�Z

		//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
		if( RayIntersect(m_pRobotMesh,m_pRobotMesh->m_Dir,m_pSlopeMesh,&fDistance,&vNormal)&& fDistance<=0.2)			
		{				
			m_pRobotMesh->m_Dir=D3DXVECTOR3(0,0,0);//�~�߂�
		}		
	}	
	
	//���{�b�g�@�ʒu�X�V
	m_pRobotMesh->m_vPos+=m_pRobotMesh->m_Dir;
	if(m_pRobotMesh->m_vPos.y-0.5<=0) m_pRobotMesh->m_vPos.y=0.5;

	//60FPS���
	static int time=0;
	time=timeGetTime();
	while(timeGetTime()-time<16.667);
}

//
//
//���C�ɂ��Փ˔���@���C�����胁�b�V���ƌ�������ꍇ�́ApfDistance�ɋ���������true��Ԃ�
//�������Ă���|���S�����Ԃ�
bool MAIN::RayIntersect(CD3DXMESH* pMeshA,D3DXVECTOR3& Dir,CD3DXMESH* pMeshB,float* pfDistance,D3DXVECTOR3* pvNormal)
{
	BOOL boHit=false;
	D3DXMATRIX Inv;
	D3DXVECTOR3 vStart,vEnd,vDirection;
	//���C���o�����b�V���̈ʒu�E��]�����C�ɓK�p
	vStart=pMeshA->m_vPos+D3DXVECTOR3(0,-0.4,0);
	//���C�𓖂Ă郁�b�V���������Ă������]���Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
	D3DXMatrixInverse(&Inv,NULL,&pMeshB->m_World);
	D3DXVec3TransformCoord(&vStart,&vStart,&Inv);

	D3DXVECTOR3 Direction=Dir;
	D3DXVec3Normalize(&Direction,&Direction);
	DWORD dwIndex=0;
	D3DXIntersect(pMeshB->m_pMesh,&vStart,&Direction,&boHit,&dwIndex,NULL,NULL, pfDistance,NULL,NULL);
	if(boHit)
	{
		//�������Ă���|���S���̒��_��������
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pMeshB->m_pMesh,dwIndex,vVertex);
		D3DXPLANE p;
		//���̒��_���畽�ʕ������𓾂�
		D3DXPlaneFromPoints(&p,&vVertex[0],&vVertex[1],&vVertex[2]);
		//���ʕ������̌W�����@���̐���
		pvNormal->x=p.a;
		pvNormal->y=p.b;
		pvNormal->z=p.c;

		return true;
	}
	return false;
}
//
//
// L:���˃x�N�g���i���C�j N:�|���S���̖@��
D3DXVECTOR3 MAIN::Slip(D3DXVECTOR3 L,D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S=L-((D3DXVec3Dot(&N,&L))/(pow(D3DXVec3Length(&N),2)))*N;

	return S;
}
//
//
//���̃|���S���̒��_��������
HRESULT MAIN::FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvVertices)
{
	DWORD i,k;
	DWORD dwStride=pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum=pMesh->GetNumVertices();
	DWORD dwPolyNum=pMesh->GetNumFaces();
	DWORD* pwPoly=NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY,(VOID**)&pwPoly);	

	BYTE *pbVertices=NULL;
	FLOAT* pfVetices=NULL;
	LPDIRECT3DVERTEXBUFFER9 VB=NULL;
	pMesh->GetVertexBuffer(&VB);
	if(SUCCEEDED(VB->Lock(0,0,(VOID**)&pbVertices,0)))
	{
		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex* 3] ];
		pvVertices[0].x=pfVetices[0];
		pvVertices[0].y=pfVetices[1];
		pvVertices[0].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+1] ];
		pvVertices[1].x=pfVetices[0];
		pvVertices[1].y=pfVetices[1];
		pvVertices[1].z=pfVetices[2];

		pfVetices=(FLOAT*)&pbVertices[dwStride*pwPoly[ dwPolyIndex * 3+2] ];
		pvVertices[2].x=pfVetices[0];
		pvVertices[2].y=pfVetices[1];
		pvVertices[2].z=pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
	}
	return S_OK;
}
