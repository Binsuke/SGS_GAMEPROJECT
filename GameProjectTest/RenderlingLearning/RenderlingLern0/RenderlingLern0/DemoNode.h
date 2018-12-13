#pragma once

#ifndef __DEMO_NODE_H__
#define __DEMO_NODE_H__

#include <DirectXMath.h>
#include "SceneNode.h"



//DemoNodeClass

class DemoNode : public SceneNode
{

private:
	ID3D11VertexShader*			m_pVS;		//VertexShader
	ID3D11GeometryShader*		m_pGS;		//GeometryShader
	ID3D11PixelShader*			m_pPS;		//PixelShader
	ID3D11InputLayout*			m_pIL;		//InputLayout
	ID3D11Buffer*				m_pVB;		//VertexBuffer
	ID3D11Buffer*				m_pCB;		//ConstantBffer
	DirectX::XMMATRIX			m_World;	//WorldMatrix
	DirectX::XMMATRIX			m_View;		//ViewMatrix
	DirectX::XMMATRIX			m_Proj;		//ProjectionMatrix

protected:
	//NOTHING

public:
	//public variable
	// Nothing

	//PublicMethod

	//Constructor
	DemoNode();

	//Desturoctor
	virtual ~DemoNode();

	// InitializeProcess

	virtual bool OnInit(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const UINT width, const UINT height);

	//Renderling Process

	virtual void OnRender(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

	//Resize Process

	virtual void OnResize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const UINT width, const UINT height);

	//End Process

	virtual void OnTerm();

};

#endif