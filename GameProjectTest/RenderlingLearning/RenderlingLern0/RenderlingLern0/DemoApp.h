#pragma once

#ifndef __DEMO_APP_H__
#define __DEMO_APP_H__

//------------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "SceneNode.h"


//DemoApp Class

class DemoApp
{
private:

protected:
	//protected variables

	static const UINT			SWAPCHAIN_BUFFER_COUNT		= 2;
	static const DXGI_FORMAT	SWAPCHAIN_BUFFER_FORMAT		= DXGI_FORMAT_R8G8B8A8_UNORM;
	static const DXGI_FORMAT	DEPTHSTENCIL_TEXTURE_FORMAT = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	static const DXGI_FORMAT	DEPTHSTENCIL_VIEW_FORMAT	= DXGI_FORMAT_D24_UNORM_S8_UINT;
	static const DXGI_FORMAT	DEPTHSTENCIL_RESOURCE_FORMAT = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;

	static DemoApp*				s_pThis;					//this pointer
	HINSTANCE					m_hInst;					//Instance Handle
	HWND						m_hWnd;						//WindowHandle
	D3D_DRIVER_TYPE				m_DriverType;				//DriverType
	D3D_FEATURE_LEVEL			m_FeatureLevel;				//function Level
	UINT						m_MulitiSampleCount;		//MultiSample Count
	UINT						m_MulitiSampleQuality;		//MultiSample Quality
	UINT						m_MulltiSampeleMaxQuality;	//MultiSample Max Quality
	UINT						m_SwapChainCount;			//SwapChain Count
	DXGI_FORMAT					m_SwapChainFormat;			//SwapChain Format
	DXGI_FORMAT					m_DepthStencilFormat;		//DepthStencil Format
	ID3D11Device*				m_pDevice;					//Device
	ID3D11DeviceContext*		m_pDeviceContext;			//DeviceContext
	IDXGISwapChain*				m_pSwapChain;				//SwapChain
	ID3D11RenderTargetView*		m_pRTV;						//RenderTaegetView
	ID3D11DepthStencilView*		m_pDSV;						//DepthStencilView
	ID3D11Texture2D*			m_pRTT;						//RenderTargetTexture
	ID3D11Texture2D*			m_pDST;						//DepsStencilTexture
	ID3D11ShaderResourceView*	m_pRTSRV;					//RenderTargetShaderResourceVIew
	ID3D11ShaderResourceView*	m_pDSSRV;					//DepthStensilShaderResourceView
	SceneNode*					m_pNode;					//SceneRootNode
	FLOAT						m_ClearColor[4];			//クリアカラー
	UINT						m_Width;					//WindowWidth
	UINT						m_Height;					//WindowHeight
	std::string					m_Title;					//TitleName

	//protected Method

	//Window Initialize

	bool InitWnd();

	//Window Endfunc

	void TermWnd();

	//D3D11 Initialize

	bool InitD3D11();

	//D3D11 Endfunc

	void TermD3D11();

	//Aplu Original End func

	void TermApp();

	//MainLoop func
	
	int MainLoop();

	//Initialize Called Func
	
	bool OnInit();

	//Rendering Called Func

	void OnRender();

	//EndProc Called Func

	void OnTerm();

	//Resize Called Func

	void OnResize(const UINT w, const UINT h);

	//Create Default Render Target

	bool CreateDefaultRenderTarget();

	//Create Default Depth Stensil Buffer

	bool CreateDefaultDepthStencil();

	//ReleaseDefaultDepthStencilBuffer

	void ReleaseDefaultDepthStencil();

	// Window Proc
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

public:
	// public variables

	struct Config
	{
		UINT			swapChainCount;
		DXGI_FORMAT		swapChainFormat;
		DXGI_FORMAT		depthStencilFormat;
		UINT			multiSampleCount;
		UINT			multiSampleQuality;
		UINT			width;
		UINT			height;
		LPSTR			title;
		FLOAT			clearColorR;
		FLOAT			clearColorG;
		FLOAT			clearColorB;
		FLOAT			clearColorA;

		Congif()
			:swapChainCount(2)
			, swapChainFormat(DXGI_FORMAT_R8G8B8A8_UNORM)
			, depthStencilFormat(DXGI_FORMAT_D24_UNORM_S8_UINT)
			, multiSampleCount(1)
			, multiSampleQuality(0)
			, width(960)
			, height(540)
			, title("DemoApp")
			, clearColorR(0.392f)
			, clearColorG(0.584f)
			, clearColorB(0.929f)
			, clearColorA(1.0f)
		{ /* DO NOTHING*/}
	};

	//public methods

	// constructor

	DemoApp(const Config& config);

	//destructor

	virtual ~DemoApp();

	// Aplication Execution

	int Run();

	// node Config

	void SetNode(SceneNode* pNode);

	// get node

	SceneNode* GetNode() const;

	// get device interface

	ID3D11Device* GetDevice() const;

	// get DeviceContextInterface

	ID3D11DeviceContext* GetDeviceContext() const;

	// get RenderTargetView

	ID3D11RenderTargetView* GetRenderTargetView() const;

	// get DepthStencilView

	ID3D11DepthStencilView* GetDepthStencilView() const;

	//get SwapChain

	IDXGISwapChain* GetSwapChain() const;

	//get window width
	UINT GetWidth() const;

	//get window height

	UINT GetHeight() const;

	// GetAspectRtion

	FLOAT GetAspectRatio() const;

	// Get Active App0lication

	static DemoApp* GetActive();
};


#endif //__DEMO_APP_H