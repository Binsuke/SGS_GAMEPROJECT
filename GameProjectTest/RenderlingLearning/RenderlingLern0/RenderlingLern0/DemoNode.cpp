//Include

#include <cassert>
#include "DemoNode.h"
#include "ShaderUtil.h"


struct CustomVertex
{
	DirectX::XMFLOAT3 position;		//postion
};


//ConstantBuffeForPerFrame

struct ConstantBufferForPerFrame
{
	DirectX::XMMATRIX world;		//world
	DirectX::XMMATRIX view;			//view
	DirectX::XMMATRIX proj;			//projection
};



DemoNode::DemoNode()
	:m_pVS(NULL)
	, m_pGS(NULL)
	, m_pPS(NULL)
	, m_pIL(NULL)
	, m_pVB(NULL)
	, m_pCB(NULL)
{
	m_World		= DirectX::XMMatrixIdentity();
	m_View		= DirectX::XMMatrixIdentity();
	m_Proj		= DirectX::XMMatrixIdentity();
}


// Destructor

DemoNode::~DemoNode()
{
	OnTerm();
}


//Initialize

bool DemoNode::OnInit
(
	ID3D11Device*			pDevice,
	ID3D11DeviceContext*	pDeviceContext,
	const UINT				width,
	const UINT				height
) 
{
	HRESULT hr = S_OK;

	// compile the Vertex Shader
	ID3DBlob* pVSBlob = NULL;

	// file pass
	hr = CompileShaderFromFile((WCHAR*)".Simple,fx", "VSFunc", "vs_4_0", &pVSBlob);

	if (FAILED(hr))
	{
		assert(false && "CompileShaderFromFile()VS Failed");
		return false;
	}

	// Vertex Shader
	hr = pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVS);

	if (FAILED(hr))
	{
		assert(false && "ID3D11Device::CreateVertexShader() Failed.");
		pVSBlob->Release();
		pVSBlob = NULL;
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	UINT numElements = ARRAYSIZE(layout);

	//Create Input Layout
	hr = pDevice->CreateInputLayout(
		layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&m_pIL
	);

	pVSBlob->Release();
	pVSBlob = NULL;

	if (FAILED(hr))
	{
		assert(false && "ID3D11Device::CreateInputLayout() Failed.");
		return false;
	}

	pDeviceContext->IASetInputLayout(m_pIL);

	//Compile the Geometry Shader
	{
		ID3DBlob* pGSBlob = NULL;
		// filepass

		hr = CompileShaderFromFile((WCHAR*)"../res/Simple.fx","GSFunc","gs_4_0", &pGSBlob);

		if (FAILED(hr))
		{
			assert(false && "CompleteShaderFromFile() GS Failed");
			return false;
		}

		//Create Geometry Shader

		hr = pDevice->CreateGeometryShader(
			pGSBlob->GetBufferPointer(),
			pGSBlob->GetBufferSize(),
			NULL,
			&m_pGS
		);

		pGSBlob->Release();
		pGSBlob = NULL;

		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateGeometryShader() Failed.");
			return false;
		}
	}

	//CompilePixelShader
	{
		ID3DBlob* pPSBlob = NULL;

		hr = CompileShaderFromFile((WCHAR*)"../res/Simple.fx", "PSFunc", "ps_4_0", &pPSBlob);

		if (FAILED(hr)) 
		{
			assert(false && "CompileShaderFromFile() PS Failed");
			return false;
		}

		//create pixel shader
		hr = pDevice->CreatePixelShader(
			pPSBlob->GetBufferPointer(),
			pPSBlob->GetBufferSize(),
			NULL,
			&m_pPS
		);

		pPSBlob->Release();
		pPSBlob = NULL;

		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreatePixelShader() Failed");
			return false;
		}
	}

	// Vertex Buffer Setting
	{
		//Vertex　Difine
		CustomVertex vertices[] = {
			DirectX::XMFLOAT3(0.0f,0.5f,0.0f),
			DirectX::XMFLOAT3(0.5f,-0.5f,0.0f),
			DirectX::XMFLOAT3(-0.5f,-0.5f,0.0f),
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CustomVertex) * 3;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		//subresource setting
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = vertices;

		//create vertex buffer
		hr = pDevice->CreateBuffer(&bd, &initData, &m_pVB);

		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateBuffer() Failed.");
			return false;
		}

		//vertex buffer setting input asembla
		UINT stride = sizeof(CustomVertex);
		UINT offset = 0;

		pDeviceContext->IASetVertexBuffers(0, 1, &m_pVB, &stride, &offset);

		//setting primitive type

		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//create constant buffer
	{
		//setting Constant buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

	}
	return true;
}

void DemoNode::OnTerm()
{
	//Vertex Shader Release
	if (m_pVS)
	{
		m_pVS->Release();
		m_pVS = NULL;
	}

	//Geometry Shader Release
	
	if (m_pGS)
	{
		m_pGS->Release();
		m_pGS = NULL;
	}

	//Pixel Shader Release
	if (m_pPS)
	{
		m_pPS->Release();
		m_pPS = NULL;
	}

	if (m_pVB)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}

	// 入力レイアウトを解放.
	if (m_pIL)
	{
		m_pIL->Release();
		m_pIL = NULL;
	}

	// 定数バッファを解放.
	if (m_pCB)
	{
		m_pCB->Release();
		m_pCB = NULL;
	}


}

void DemoNode::OnRender(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	//setting shader
	pDeviceContext->VSSetShader(m_pVS, NULL, 0);
	pDeviceContext->GSSetShader(m_pGS, NULL, 0);
	pDeviceContext->PSSetShader(m_pPS, NULL, 0);

	//setting constant buffer

	ConstantBufferForPerFrame cb;
	cb.world = m_World;
	cb.view = m_View;
	cb.proj = m_Proj;

	//update subresource 
	pDeviceContext->UpdateSubresource(m_pCB, 0, NULL, &cb, 0, 0);

	//setting constanto bufffer to geometory
	pDeviceContext->GSSetConstantBuffers(0, 1, &m_pCB);

	//Render

	pDeviceContext->Draw(3, 0);

}

void DemoNode::OnResize
(
	ID3D11Device*           pDevice,
	ID3D11DeviceContext*    pDeviceContext,
	const UINT              width,
	const UINT              height
)
{
	// setting projction matrix.
	{
		// calc aspect
		FLOAT aspectRatio = (FLOAT)width / (FLOAT)height;

		//calc projection matrix
		m_Proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, aspectRatio, 0.01f, 1000.0f);
	}
}
