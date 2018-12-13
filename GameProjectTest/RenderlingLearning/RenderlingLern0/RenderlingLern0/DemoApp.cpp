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
