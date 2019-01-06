#pragma once
#include <fbxsdk.h>
#include <DirectXMath.h>
#include <Windows.h>
//#include <d3d11.h>
#include "model.h"


//#ifndef __MY_VERTEX__
//#define __MY_VERTEX__
//struct MY_VERTEX {
//	DirectX::XMFLOAT4 Pos;
//	DirectX::XMFLOAT4 Normal;
//};
//#endif
//
//#ifndef __MY_MODEL_VERTEX_INFO__
//#define __MY_MODEL_VERTEX_INFO__
//struct MY_MODEL_VERTEX_INFO {
//	MY_VERTEX *Vertices;
//	int numVertex;
//	int numFace;
//	//int numPolyVertex;
//	MY_MODEL_VERTEX_INFO()
//		:Vertices(NULL)
//		, numVertex(0)
//		, numFace(0)
//		//, numPolyVertex(0){};
//	{};
//	~MY_MODEL_VERTEX_INFO() {
//		delete[] Vertices;
//	}
//};
//#endif

namespace MyFbx {

	class MyFbx {
	private:
		FbxManager	*m_pfbxManager;
		FbxScene	*m_pfbxScene;
		FbxImporter *m_pfbxImporter;
		FbxMesh		*m_pMesh;

		bool RecursiveNode(FbxNode *pNode);
		void GetNormals(FbxNode* pNode, MY_MODEL_VERTEX_INFO * const pModelinfo);
		void GetVertexUV(FbxMesh* pmesh, UvSet * const pUvset);
		void GetTextureName(FbxMesh* pMesh, UvSet * const pUvSet);
		void GetMaterial(FbxMesh* pMesh, UvSet * const pUvSet, MY_MODEL_VERTEX_INFO * const pModelInfo, ID3D11Device *inDevice);
		//bool Init();
		void Release();
	protected:
		//none
	public:
		bool LoadFBX(MY_MODEL_VERTEX_INFO * const pModelInfo, FbxString const &FileName, UvSet *const pUvset);
		const FbxMesh* GetMesh() {
			return m_pMesh;
		}
		MyFbx()
			:m_pfbxManager(NULL)
			, m_pfbxScene(NULL)
			, m_pMesh(NULL)
		{/*notthing*/
		};
		~MyFbx();
	};

}