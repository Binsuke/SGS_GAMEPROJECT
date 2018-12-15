#pragma once
//Include 

#include "DemoApp.h"
#include <cstdio>
#include <cassert>


#ifndef DLOG
	#if defined(DEBUG) || defined(_DEBUG)
		#define DLOG(x,...)  printf_s("[File:%s, Line:%d]" x"\n".__FILE__,__LINE__,##__VA_ARGS__)
	#else
		#define DLOG(x,...)
	#endif
#endif

#ifndef ELOG
#define ELOG( x, ... );  \
        fprintf( stderr, "[File:%s, Line:%d] "x"\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
        assert( false );
#endif//ELOG

//DemoApp class

DemoApp* DemoApp::s_pThis = NULL;


// Constructor

DemoApp::DemoApp(const Config& config)
	:m_hInst(NULL)
	, m_hWnd(NULL)
	, m_DriverType(D3D_DRIVER_TYPE_NULL)
	, m_FeatureLevel(D3D_FEATURE_LEVEL_11_0)
	, m_MultiSampleCount(config.multiSampleCount)
	, m_MultiSampleQuality(config.multiSampleQuality)
	, m_SwapChainCount(config.swapChainCount)
	, m_SwapChainFormat(config.swapChainFormat)
	, m_DepthStencilFormat(config.depthStencilFormat)
	, m_pDevice(NULL)
	, m_pDeviceContext(NULL)
	, m_pSwapChain(NULL)
	, m_pRTV(NULL)
	, m_pDSV(NULL)
	, m_pRTT(NULL)
	, m_pDST(NULL)
	, m_pRTSRV(NULL)
	, m_pDSSRV(NULL)
	, m_pNode(NULL)
	, m_Width(config.width)
	, m_Height(config.height)
	, m_Title(config.title)
{
	//set clear color

	m_ClearColor[0] = config.clearColorR;
	m_ClearColor[1] = config.clearColorG;
	m_ClearColor[2] = config.clearColorB;
	m_ClearColor[3] = config.clearColorA;

	//AspectRatio

	m_AspectRatio = (FLOAT)m_Width / (FLOAT)m_Height;

}

DemoApp::~DemoApp()
{ TermApp(); }


bool DemoApp::InitWnd()
{
	//Get Instance Handle

	HINSTANCE hInst = GetModuleHandle(NULL);

	//get this
	s_pThis = this;

	//expantion window class

	WNDCLASSEXA wc;
	wc.cbSize			= sizeof(WNDCLASSEXA);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_Title.c_str();
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	// Register Window Class
	if(!RegisterClassExA(&wc))
	{
		// output error log 
		ELOG("Erro : RegisterClassEx():Failed.\n");

		//error exit
		return false;

	}

	// add instance

	m_hInst = hInst;

	//Setting Rect

	RECT rc = { 0,0,(LONG)m_Width,(LONG)m_Height };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成します.
	m_hWnd = CreateWindowA(
		m_Title.c_str(),
		m_Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		NULL,
		NULL,
		hInst,
		NULL
	);

	// 生成チェック.
	if (m_hWnd == NULL)
	{
		//　エラーログ出力.
		ELOG("Error : CreateWindow() Failed.");

		// 異常終了.
		return false;
	}

	// ウィンドウを表示します.
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// 正常終了.
	return true;


}

// exit Window Proc

void DemoApp::TermWnd()
{
	if (m_hInst != NULL)
	{
		UnregisterClassA(m_Title.c_str(), m_hInst);
	}

	m_Title.clear();
	s_pThis = NULL;


}



//Initialize D3D11

bool DemoApp::InitD3D11()
{
	HRESULT hr = S_OK;

	//window size

	RECT rc;
	GetClientRect(m_hWnd, &rc);

	UINT w = rc.right - rc.left;
	UINT h = rc.bottom - rc.top;

	//Get Size

	m_Width = w;
	m_Height = h;

	m_AspectRatio = (FLOAT)w / (FLOAT)h;

	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);


	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = m_SwapChainCount;
	sd.BufferDesc.Width = w;
	sd.BufferDesc.Height = h;
	sd.BufferDesc.Format = m_SwapChainFormat;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = m_MultiSampleCount;
	sd.SampleDesc.Quality = m_MultiSampleQuality;
	sd.Windowed = TRUE;


	for (UINT idx = 0; idx < numDriverTypes; idx++)
	{
		m_DriverType = driverTypes[idx];

		//device and swapchain create

		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			m_DriverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_pSwapChain,
			&m_pDevice,
			&m_FeatureLevel,
			&m_pDeviceContext
		);
		//succeced for end llp
		if(SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr)) 
	{
		ELOG("Error : D3D11CreateDeviceAndSwapChain() Failed.");
		return false;
	}

	hr = m_pDevice->CheckMultisampleQualityLevels(m_SwapChainFormat, m_MultiSampleCount, &m_MultiSampleMaxQuality);
	if (FAILED(hr))
	{
		ELOG("Error : D3D11DeviceCheckMultiSampleQualityLevels() Failed.");
		return false;
	}

	if (!CreateDefaultRenderTarget())
	{
		ELOG("Error : CreateDefaultRenderTarget() Failed.");
		return false;
	}

	if (!CreateDefaultDepthStencil())
	{
		ELOG("Error : CreateDefaultDepthStencil() Failed.");
		return false;
	}

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);

	//Settting View Port
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)w;
	vp.Height = (FLOAT)h;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_pDeviceContext->RSSetViewports(1, &vp);

	return OnInit();
}

//Exit D3D11
void DemoApp::TermD3D11()
{
	if (m_pDeviceContext)
	{
		m_pDeviceContext->ClearState();
		m_pDeviceContext->Flush();
	}
	//Apllication end

	OnTerm();

	ReleaseDefaultRenderTarget();

	ReleaseDefaultDepthStencil();
	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}
	if (m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = NULL;
	}

	// デバイスを解放します.
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

}

//Initialize Application
bool DemoApp::InitApp()
{ 
	// ウィンドウの初期化.
	if (!InitWnd())
	{
		ELOG("Error : InitWnd() Failed.");
		return false;
	}

	// D3D11の初期化.
	if (!InitD3D11())
	{
		ELOG("Error : InitD3D11() Failed.");
		return false;
	}

	// 正常終了.
	return true;
}

// Exit Application proc
void DemoApp::TermApp()
{
	// D3D11の終了処理.
	TermD3D11();

	// ウィンドウの終了処理.
	TermWnd();

}

//Create RenderTarget
bool DemoApp::CreateDefaultRenderTarget()
{
	HRESULT hr = S_OK;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pRTT);
	if (FAILED(hr))
	{
		ELOG("Error : IDXFISwapChain::Getbuffer() Failed");
		return false;
	}

	hr = m_pDevice->CreateRenderTargetView(m_pRTT, NULL, &m_pRTV);
	if (FAILED(hr))
	{
		ELOG("Error : ID3D11Device::CreateRenderTargetView() Failed.");
		return false;
	}

	hr = m_pDevice->CreateShaderResourceView(m_pRTT, NULL, &m_pRTSRV);
	if (FAILED(hr))
	{
		ELOG("Error * ID3D11Device::CreateShaderResourceView() Failed.");
		return false;
	}
	return true;
}

//Default RenderTaget Release

void DemoApp::ReleaseDefaultRenderTarget()
{
	// レンダーターゲットのシェーダリソースビューを解放.
		if (m_pRTSRV)
		{
			m_pRTSRV->Release();
			m_pRTSRV = NULL;
		}

	// レンダーターゲットビューを解放.
	if (m_pRTV)
	{
		m_pRTV->Release();
		m_pRTV = NULL;
	}

	// レンダーターゲットのテクスチャを解放.
	if (m_pRTT)
	{
		m_pRTT->Release();
		m_pRTT = NULL;
	}
}

//Create DefaultDeptth
bool DemoApp::CreateDefaultDepthStencil()
{
	HRESULT hr = S_OK;
	DXGI_FORMAT textureFormat = m_DepthStencilFormat;
	DXGI_FORMAT resourceFormat = m_DepthStencilFormat;


	switch (m_DepthStencilFormat)
	{
	case DXGI_FORMAT_D16_UNORM:
		{
			textureFormat = DXGI_FORMAT_R16_TYPELESS;
			resourceFormat = DXGI_FORMAT_R16_UNORM;
		}
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		{
			textureFormat = DXGI_FORMAT_R24G8_TYPELESS;
			resourceFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		}
		break;
	case DXGI_FORMAT_D32_FLOAT:
		{
			textureFormat = DXGI_FORMAT_R32_TYPELESS;
			resourceFormat = DXGI_FORMAT_R32_FLOAT;
		}
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	{
		textureFormat = DXGI_FORMAT_R32G8X24_TYPELESS;
		resourceFormat = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
	}
	break;

	}

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width	= m_Width;
	td.Height	= m_Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = textureFormat;
	td.SampleDesc.Count = m_MultiSampleCount;
	td.SampleDesc.Quality = m_MultiSampleQuality;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	// 深度ステンシルテクスチャの生成.
	hr = m_pDevice->CreateTexture2D(&td, NULL, &m_pDST);
	if (FAILED(hr))
	{
		ELOG("Error : ID3D11Device::CreateTexture2D() Failed.");
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = m_DepthStencilFormat;
	if (m_MultiSampleCount == 0)
	{
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;
	}
	else {
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}

	hr = m_pDevice->CreateDepthStencilView(m_pDST, &dsvd, &m_pDSV);
	if (FAILED(hr))
	{
		ELOG("Error : ID3D11Device::CreateDepthStencilView() Failed.");
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = resourceFormat;

	if (m_MultiSampleCount == 0)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	}

	hr = m_pDevice->CreateShaderResourceView(m_pDST, &srvd, &m_pDSSRV);
	if (FAILED(hr))
	{
		ELOG("Error : ID3D11Device::CreateShaderResourceView() Failed.");
		return false;
	}


	return true;
}
//ReleaseDefualtDepth
void DemoApp::ReleaseDefaultDepthStencil()
{
	// 深度ステンシルバッファのシェーダリソースビューを解放します.
	if (m_pDSSRV)
	{
		m_pDSSRV->Release();
		m_pDSSRV = NULL;
	}

	// 深度ステンシルビューを解放します.
	if (m_pDSV)
	{
		m_pDSV->Release();
		m_pDSV = NULL;
	}

	// 深度ステンシルテクスチャを解放します.
	if (m_pDST)
	{
		m_pDST->Release();
		m_pDST = NULL;
	}

}
//Initialize
bool DemoApp::OnInit()
{
	if (m_pNode)
	{
		if (!m_pNode->OnInit(m_pDevice, m_pDeviceContext, m_Width, m_Height))
		{
			ELOG("Error: SceneNode::OnInit() Failed.");
			return false;
		}

		for (UINT i = 0; i < m_pNode->pChildren.size(); i++)
		{
			if (!m_pNode->pChildren[i]->OnInit(m_pDevice, m_pDeviceContext, m_Width, m_Height)) 
			{
				ELOG("Error : SceneNode::OnInit() Failed.chiled index = %d", i);
				return false;
			}
		}

	}
	return true;
}


void DemoApp::OnTerm()
{
	if (m_pNode)
	{
		for (UINT i = 0; i < m_pNode->pChildren.size(); i++)
		{
			m_pNode->pChildren[i]->OnTerm();
		}
		m_pNode->OnTerm();
	}
}


void DemoApp::OnRender()
{
	assert(m_pRTV != NULL);
	assert(m_pDSV != NULL);

	m_pDeviceContext->ClearRenderTargetView(m_pRTV, m_ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	if (m_pNode)
	{
		//call parent renderin process
		m_pNode->OnRender(m_pDevice, m_pDeviceContext);

		//call children render process
		for (UINT i = 0; i < m_pNode->pChildren.size(); i++)
		{
			m_pNode->pChildren[i]->OnRender(m_pDevice, m_pDeviceContext);
		}
	}

	//render result
	m_pSwapChain->Present(0, 0);

}


void DemoApp::OnResize(const UINT w, const UINT h)
{
	if (m_pSwapChain && m_pDeviceContext)
	{
		//setting windows size
		m_Width = w;
		m_Height = h;

		//calc aspect
		m_AspectRatio = (FLOAT)w / (FLOAT)h;

		//setting render target to NULL
		ID3D11RenderTargetView* pNull = NULL;
		m_pDeviceContext->OMSetRenderTargets(1, &pNull, NULL);

		//release render target
		ReleaseDefaultRenderTarget();

		//release depth target
		ReleaseDefaultRenderTarget();

		HRESULT hr = S_OK;

		//Resize SwapChain

		hr = m_pSwapChain->ResizeBuffers(m_SwapChainCount, 0, 0, m_SwapChainFormat, 0);

		if (FAILED(hr))
		{
			ELOG("Error : IDXGISwapChain::ResizeBuffer() Failed.");
		}

		if (!CreateDefaultRenderTarget())
		{
			ELOG("Error : CreateDeaultRenderTarget() Failed.");
		}

		if (!CreateDefaultDepthStencil())
		{
			ELOG("Error : CreateDefaultDepthStencil() Failed.");
		}

		//Setting RenderTarget to DeviceContext
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);



		//setting viewport
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)w;
		vp.Height = (FLOAT)h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		//setting viewport to devicecontext
		m_pDeviceContext->RSSetViewports(1, &vp);

	}

	if (m_pNode)
	{
		//Call Resize Process
		m_pNode->OnResize(m_pDevice, m_pDeviceContext, w, h);

		for (UINT i = 0; i < m_pNode->pChildren.size(); ++i)
		{
			m_pNode->pChildren[i]->OnResize(m_pDevice, m_pDeviceContext, w, h);
		}
	}

}


int DemoApp::MainLoop()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			OnRender();
		}
	}
	return (int)msg.wParam;
}


int DemoApp::Run()
{
	int retcode = -1;

	if (InitApp())
	{
		retcode = MainLoop();
	}
	TermApp();

	return retcode;
}



LRESULT CALLBACK DemoApp::WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT	ps;
	HDC			hdc;
	switch (uMsg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	case WM_SIZE:
	{
		UINT w = (UINT)LOWORD(lp);
		UINT h = (UINT)HIWORD(lp);
		s_pThis->OnResize(w, h);
	}break;
	default:
	{//Notthing
	}break;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

void DemoApp::SetNode( SceneNode* pNode)
{
	m_pNode = pNode;
}

SceneNode* DemoApp::GetNode() const
{
	return m_pNode;
}

//Get Device 

ID3D11Device* DemoApp::GetDevice() const
{
	return m_pDevice;
}

//DeviceContext
ID3D11DeviceContext* DemoApp::GetDeviceContext() const
{
	return m_pDeviceContext;
}

IDXGISwapChain* DemoApp::GetSwapChain() const 
{
	return m_pSwapChain;
}

ID3D11RenderTargetView* DemoApp::GetRenderTargetView() const
{
	return m_pRTV;
}

ID3D11DepthStencilView* DemoApp::GetDepthStencilView() const
{
	return m_pDSV;
}

ID3D11ShaderResourceView* DemoApp::GetDepthStencilShaderResourceView() const
{
	return m_pDSSRV;
}

// get window Width
UINT DemoApp::GetWidth() const
{
	return m_Width;
}

//-----------------------------------------------------------------------------------
//     window height
//-----------------------------------------------------------------------------------
UINT DemoApp::GetHeight() const
{
	return m_Height;
}

//-----------------------------------------------------------------------------------
//     get active application
//-----------------------------------------------------------------------------------
DemoApp* DemoApp::GetActive()
{
	return s_pThis;
}

