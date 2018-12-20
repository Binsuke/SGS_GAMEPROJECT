#include "fbx.h"

bool MyFbx::MyFbx::LoadFBX(MY_MODEL_VERTEX_INFO * const pModelInfo, FbxString const &FileName) {
	m_pfbxManager = FbxManager::Create();
	if (m_pfbxManager == NULL) {
		return false;
	}
	m_pfbxScene = FbxScene::Create(m_pfbxManager, "fbxscene");
	if (m_pfbxScene == NULL) {
		return false;
	}
	
	m_pfbxImporter = FbxImporter::Create(m_pfbxManager, "imp");
	
	if (m_pfbxImporter == NULL) {
		return false;
	}

	m_pfbxImporter->Initialize(FileName.Buffer(), -1, m_pfbxManager->GetIOSettings());
	m_pfbxImporter->Import(m_pfbxScene);
	m_pfbxImporter->Destroy();

	//for (int i = 0; i < m_pfbxScene->GetRootNode()->GetChildCount(); i++) {
	if (!RecursiveNode(m_pfbxScene->GetRootNode())) {
		return false;
	}
	//pModel->InitVertices(m_pMesh->GetControlPointsCount());
	int numVertex = m_pMesh->GetControlPointsCount();
	int numFace = m_pMesh->GetPolygonVertexCount();
	pModelInfo->Vertices = new MY_VERTEX[numVertex];
	//VERTEX *tmpVertex = new VERTEX[numVertex];
	for (int i = 0; i < m_pMesh->GetControlPointsCount(); i++) {
		MY_VERTEX tmpVertex;
		tmpVertex.Pos.x = (float)m_pMesh->GetControlPointAt(i)[0];
		tmpVertex.Pos.y = (float)m_pMesh->GetControlPointAt(i)[1];
		tmpVertex.Pos.z = (float)m_pMesh->GetControlPointAt(i)[2];
		pModelInfo->Vertices[i] = tmpVertex;
		//pModel->SetVertices(tmpVertex, i);
	}


	pModelInfo->numVertex	= numVertex;
	pModelInfo->numFace = numFace;
	/*pModel->SetNumVertex(numVertex);
	pModel->SetNumFace(numFace);
*/
		/*if (m_pfbxScene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {

		}*/
	//}

	return true;

}


bool MyFbx::MyFbx::RecursiveNode(FbxNode *pNode) {
	//for (int i = 0; i < pNode->GetChildCount(); i++) {
	//	if (pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
	//		m_pMesh = pNode->GetMesh();
	//		return true;
	//	}
	//	FbxNode *pChild = pNode->GetChild(i);
	//	if (RecursiveNode(pChild)) {
	//		return true;
	//	}
	//}

	for (int i = 0; i < pNode->GetChildCount(); i++) {
			if (pNode->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
				m_pMesh = pNode->GetChild(i)->GetMesh();
				break;
			}
		}

	return false;
}

void MyFbx::MyFbx::Release() {
	m_pfbxScene->Destroy();
	m_pfbxManager->Destroy();
}

MyFbx::MyFbx::~MyFbx() {
	Release();
}