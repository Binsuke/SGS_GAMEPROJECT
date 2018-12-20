#include "fbx.h"

bool MyFbx::MyFbx::LoadFBX(MY_MODEL_VERTEX_INFO * const pModelInfo, FbxString const &FileName) {
	m_pfbxManager = FbxManager::Create();
	if (m_pfbxManager == false) {
		//m_pfbxManager->GetLastErrorString();
		MessageBox(NULL, "FBXManeger Create: Failed", "FbxCreateError", 0);
		PostQuitMessage(0);
	}
	m_pfbxScene = FbxScene::Create(m_pfbxManager, "fbxscene");
	if (m_pfbxScene == false) {
		MessageBox(NULL, "FBXScene Create: Failed", "FbxCreateError", 0);
		PostQuitMessage(0);
	}
	
	m_pfbxImporter = FbxImporter::Create(m_pfbxManager, "imp");
	
	if (m_pfbxImporter == false) {
		MessageBox(NULL, "FBXImporter Create: Failed", "FbxCreateError", 0);
		PostQuitMessage(0);

	}

	if (!m_pfbxImporter->Initialize(FileName.Buffer(), -1, m_pfbxManager->GetIOSettings()))
	{
		MessageBox(NULL, "FbxImporterInitialize : Failed", "Importer Error", 0);
		PostQuitMessage(0);
	}


	if (!m_pfbxImporter->Import(m_pfbxScene)) {
		MessageBox(NULL, "FbxImport : Failed", "Import Error", 0);
		PostQuitMessage(0);
	}
	
	m_pfbxImporter->Destroy();

	//for (int i = 0; i < m_pfbxScene->GetRootNode()->GetChildCount(); i++) {
	RecursiveNode(m_pfbxScene->GetRootNode());

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