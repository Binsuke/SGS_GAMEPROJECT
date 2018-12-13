#pragma once


#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

//include

#include <d3d11.h>
#include <vector>

#ifndef UNUSED_VAR
#define UNUSED_VAR(x) ((void*)&x)
#endif //UNUSED_VAR

//SceneNode structure

struct SceneNode
{
	SceneNode*				pParent;		//Parent pointer
	std::vector<SceneNode*>	pChildren;		//Children pointer

	//Constructor

	SceneNode()
		:pParent(NULL)
	{
		pChildren.clear();
	}

	//Destructor

	virtual ~SceneNode()
	{
		RemoveChildren();
		OnTerm();
	}

	// Add Children

	void AddChild(SceneNode* pChild)
	{
		pChildren.push_back(pChild);
	}

	// RemoveChildren
	void RemoveChildren()
	{
		//Children Call EndProcess
		for (size_t i = 0; i < pChildren.size(), i++)
		{
			pChildren[i]->RemoveChildren();
			pChildren[i]->OnTerm();
		}

		//Release Memory

		pChildren.clear();
	}

	//Initialize Process

	virtual bool OnInit(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const UINT width, const UINT height)
	{
		UNUSED_VAR(pDevice);
		UNUSED_VAR(pDeviceContext);
		UNUSED_VAR(width);
		UNUSED_VAR(height);

		return true;
	}

	//Rendering Process

	virtual void OnRender(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	{
		UNUSED_VAR(pDevice);
		UNUSED_VAR(pDeviceContext);
	}

	//Resize Process

	virtual void OnResize(ID3D11Device* pDevice,ID3D11DeviceContext* pDeviceContext,const UINT width,const UINT height)
	{
		UNUSED_VAR(pDevice);
		UNUSED_VAR(pDeviceContext);
		UNUSED_VAR(width);
		UNUSED_VAR(height);
	}

	//End Process

	virtual void OnTerm()
	{
		//DONOTHING
	}

};


#endif
