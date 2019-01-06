#include "model.h"

//void Model::InitVertices(int const & vertexsize) {
//	m_pVertices = new VERTEX[vertexsize];
//	Initializeflg = true;
//	//m_numVerticesSize = vertexsize;
//}
//
//void Model::SetVertices(VERTEX const &vertex,int const &num) {
//	m_pVertices[num] = vertex;
//}


//bool Model::InitVertexLayout(ID3D11Device *inDevice) {
//	
//}


bool MyModel::Model::InitVertexBuffer(ID3D11Device *inDevice) {
	if (!InitVertexBufferflg) {
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(MY_VERTEX) * m_MyVertex.numVertex;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = m_MyVertex.Vertices;
		if (inDevice->CreateBuffer(&bd_vertex, &data_vertex, &m_pVerBuffer) != S_OK)
		{
			MessageBox(NULL, "InitVertexBufferError", "InitError", 0);
		}

		InitVertexBufferflg = true;
	}
	return true;
}

bool MyModel::Model::InitIndexBuffer(ID3D11Device *inDevice) {
	if (!InitIndexBufferflg) {
		D3D11_BUFFER_DESC bd_index;
		bd_index.ByteWidth = sizeof(int) * m_MyVertex.numFace;
		bd_index.Usage = D3D11_USAGE_DEFAULT;
		bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_index.CPUAccessFlags = 0;
		bd_index.MiscFlags = 0;
		bd_index.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_index;
		data_index.pSysMem = m_myFbx.GetMesh()->GetPolygonVertices();
		if (inDevice->CreateBuffer(&bd_index, &data_index, &m_pIndBuffer) != S_OK)
		{
			MessageBox(NULL, "InitIndexBufferError", "InitError", 0);
		}
		InitIndexBufferflg = true;
	}
	return true;
}

void MyModel::Model::Release() {
	//delete[] m_pVertices;
	m_pIndBuffer->Release();
	m_pVerBuffer->Release();
}

MyModel::Model::~Model() {
	Release();
	//delete m_myFbx;
}

//bool Model::Draw(ID3D11DeviceContext * inDeviceContext, ID3D11Buffer *ipConstantBuffer, ID3D11InputLayout *ipVertexLayout) {
//	
//}