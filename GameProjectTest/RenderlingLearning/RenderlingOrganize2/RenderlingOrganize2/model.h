#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "fbx.h"
#include <string>
#include <list>

#ifndef __MY_VERTEX__
#define __MY_VERTEX__
struct MY_VERTEX {
	DirectX::XMFLOAT4 Pos;
	DirectX::XMFLOAT4 Normal;
};
#endif

#ifndef __MY_UV__
#define __MY_UV__

typedef struct Point2DF {
	float x, y;
	bool operator==(Point2DF& val) {
		if (this->x == val.x && this->y == val.y) {
			return true;
		}
		return false;
	}
}point2;

typedef struct __UV_SET__ {
	std::string uvSetName;
	std::list<std::string> textures;
	std::list<point2> uvBuffer;
}UvSet;

#endif

#ifndef __MY_MODEL_VERTEX_INFO__
#define __MY_MODEL_VERTEX_INFO__
struct MY_MODEL_VERTEX_INFO {
	MY_VERTEX *Vertices;
	int numVertex;
	int numFace;
	//int numPolyVertex;
	MY_MODEL_VERTEX_INFO()
		:Vertices(NULL)
		, numVertex(0)
		, numFace(0)
		//, numPolyVertex(0){};
	{};
	~MY_MODEL_VERTEX_INFO() {
		delete[] Vertices;
	}
};
#endif

namespace MyModel {
	class Model {
		//friend class my_FBX;
	private:
		MyFbx::MyFbx m_myFbx;
		MY_MODEL_VERTEX_INFO m_MyVertex;

		UvSet m_UvSet;
		/*VERTEX *m_pVertices;
		int m_numVertex;
		int m_numFace;
	*/

		bool InitVertexBufferflg;
		bool InitIndexBufferflg;
		void Release();
		//ID3D11InputLayout *pVertexLayout;
		//ID3D11VertexShader *pVertexShader;			//vertex Shader
		ID3D11Buffer *m_pVerBuffer;
		ID3D11Buffer *m_pIndBuffer;

	protected:
		//Nothing
	public:
		bool Load(FbxString const &FileName) {
			m_myFbx.LoadFBX(&m_MyVertex, FileName,m_UvSet);
			return true;
		}

		//bool Draw(ID3D11DeviceContext * inDeviceContext, ID3D11Buffer *ipConstantBuffer, ID3D11InputLayout *ipVertexLayout);
		//void InitVertices(int const &vertexsize);
		//void SetVertices(VERTEX const &vertex,int const &num);
		//void SetNumVertex(const int &numVertex) {
		//	m_numVertex = numVertex;
		//}
		//void SetNumFace(const int &numFace) {
		//	m_numFace = numFace;
		//}
		//bool InitVertexLayout(ID3D11Device *inDevice);
		bool InitVertexBuffer(ID3D11Device *inDevice);
		bool InitIndexBuffer(ID3D11Device *inDevice);

		int GetNumFace() {
			return m_MyVertex.numFace;
		}
		int GetNumVertex() {
			return m_MyVertex.numVertex;
		}

		const FbxMesh * GetPolyMesh() {
			return m_myFbx.GetMesh();
		}

		ID3D11Buffer* const* GetVertexBuffer() {
			return &m_pVerBuffer;  //privateにした意味とは？ publicにすべきか？
		}
		ID3D11Buffer** GetIndexBuffer() {
			return &m_pIndBuffer; //privateにした意味とは？
		}
		//const VERTEX* GetVertex() {//データは不変
		//	if (Initializeflg) { return m_pVertices; }
		//	else { return NULL; }
		//}

		/*const int GetVertexSize() {
			return m_numVerticesSize;
		}*/
		void Draw(ID3D11DeviceContext *pDeviceContext);

		Model()
			:InitVertexBufferflg(false)
			, InitIndexBufferflg(false) {};
		~Model();
	};
}