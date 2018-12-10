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


};


#endif //__DEMO_APP_H