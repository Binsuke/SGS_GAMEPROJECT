#include "fbx.h"

bool MyFbx::MyFbx::LoadFBX(MY_MODEL_VERTEX_INFO * const pModelInfo, FbxString const &FileName, UvSet *const pUvset) {
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
		pModelInfo->Vertices[i].Pos = tmpVertex.Pos;
		//pModel->SetVertices(tmpVertex, i);
	}

	GetNormals(m_pfbxScene->GetRootNode(),pModelInfo);




	pModelInfo->numVertex = numVertex;
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
		else {
			MyFbx::MyFbx::RecursiveNode(pNode->GetChild(i));
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

void MyFbx::MyFbx::GetNormals(FbxNode* pNode, MY_MODEL_VERTEX_INFO * const pModelinfo)
{
	if (!pNode)
		return;

	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh)
	{
		FBXSDK_printf("current mesh node: %s\n", pNode->GetName());

		FbxGeometryElementNormal* pNormalElement = pMesh->GetElementNormal();

		if (pNormalElement) {

			if (pNormalElement->GetMappingMode == FbxGeometryElement::eByControlPoint)
			{
				DirectX::XMFLOAT4 NormalTmp;
				//DirectX::XMFLOAT4 *pVertextmp = new DirectX::XMFLOAT4[pMesh->GetControlPointsCount()];
				for (int VertexIndex = 0; VertexIndex < pMesh->GetControlPointsCount(); VertexIndex++)
				{
					DirectX::XMFLOAT4 Normaltmp;
					int NormalIndex = 0;
					if (pNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						NormalIndex = VertexIndex;

					if (pNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						NormalIndex = pNormalElement->GetIndexArray().GetAt(VertexIndex);

					NormalTmp.x = (float)pNormalElement->GetDirectArray().GetAt(NormalIndex)[0];
					NormalTmp.y = (float)pNormalElement->GetDirectArray().GetAt(NormalIndex)[1];
					NormalTmp.z = (float)pNormalElement->GetDirectArray().GetAt(NormalIndex)[2];
					NormalTmp.w = (float)pNormalElement->GetDirectArray().GetAt(NormalIndex)[3];


					pModelinfo->Vertices[VertexIndex].Normal = NormalTmp;
					//FbxVector4 Normal = pNormalElement->GetDirectArray().GetAt(NormalIndex);
					//Normal.
					//Normaltmp.x =
					
					
#ifdef __NORMAL_PRINT__
					FBXSDK_printf("normals for vertex[%d]: %f %f %f %f \n", VertexIndex, Normal[0], Normal[1], Normal[2], Normal[3]);
#endif
				}
			}
			else if (pNormalElement->GetMappingMode == FbxGeometryElement::eByPolygonVertex)
			{//�C���f�b�N�X�o�b�t�@���g�p�������̃f�[�^���g�p���邽�߁A���I�ɖ@�������i�[����z���p�ӂ���K�v������
			 //�Ή�����ꍇ�́@Vector�\���Ȃǂœ��I�Ƀf�[�^���i�[�ł���v�f���K�v�B�܂����̏ꍇ�����ł̃G�������g�̃��[�h��ۑ����Ă���
			 //�`��̍ۂɂ������reference���[�h��}�b�s���O���[�h���Q�Ƃ��������łǂ̃f�[�^���g������I������K�v������
			 //����͖������Ői�߂Ă����B
				//int IndexByPolygonVertex = 0;
			}
		}
	}
	int i;
	int Count = pNode->GetChildCount();
	for (i = 0; i < Count; i++) {
		GetNormals(pNode->GetChild(i),pModelinfo);
	}
}

#define __FBX_SDK_TEST__

void MyFbx::MyFbx::GetVertexUV(FbxMesh* pMesh, UvSet *const pUvset) {
	//int UVLayerCount = pMesh->GetElementUVCount();

	//for (int i = 0; i < UVLayerCount; i++) {
	//	//UV�o�b�t�@���擾
	//	FbxGeometryElement* UV = pMesh->GetElementUV(i);


	//	//�}�b�s���O���[�h�̎擾
	//	FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();
	//	//reference���[�h�̎擾
	//	FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();

	//	//uv�����擾

	//	int uvCount = 
	//}


#ifdef __FBX_SDK_TEST__
	FbxStringList UVSetNameList;
	pMesh->GetUVSetNames(UVSetNameList);

	for (int UVSetIndex = 0; UVSetIndex < UVSetNameList.GetCount();UVSetIndex++)
	{
		//get UVSetIndex
		const char *UVSetName = UVSetNameList.GetStringAt(UVSetIndex);
		const FbxGeometryElementUV* UVElement = pMesh->GetElementUV(UVSetName);

		if (!UVElement)
			continue;//�X�L�b�v����

		if (UVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
			UVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			return;

		const bool UseIndex = UVElement->GetReferenceMode != FbxGeometryElement::eDirect;
		const int IndexCount = (UseIndex) ? UVElement->GetIndexArray().GetCount() : 0;//true �Ȃ�@GetCount

		const int PolyCount = pMesh->GetPolygonCount();

		if (UVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			point2 temp;
			for (int PolyIndex = 0; PolyIndex < PolyCount; PolyIndex++)
			{
				const int PolySize = pMesh->GetPolygonSize(PolyIndex);
				for (int VertIndex = 0; VertIndex < PolySize; VertIndex++)
				{
					FbxVector2 UVValue;
					int PolyVertIndex = pMesh->GetPolygonVertex(PolyIndex, VertIndex);

					int UVIndex = UseIndex ? UVElement->GetIndexArray().GetAt(PolyVertIndex) : PolyVertIndex;

					temp.x = UVElement->GetDirectArray().GetAt(UVIndex)[0];
					temp.y = UVElement->GetDirectArray().GetAt(UVIndex)[1];
					pUvset->uvBuffer.push_back(temp);
					//UVValue = UVElement->GetDirectArray().GetAt(UVIndex);
				}
			}
			pUvset->uvSetName = UVElement->GetName();
		}
		else if (UVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int PolyIndexCounter = 0;
			for (int PolyIndex = 0; PolyIndex < PolyCount; PolyIndex++) 
			{
				const int PolySize = pMesh->GetPolygonSize(PolyIndex);

				point2 temp;
				for (int VertIndex = 0; VertIndex < PolySize; VertIndex++)
				{
					if (PolyIndexCounter < IndexCount)
					{
						FbxVector2 UVValue;
						int UVIndex = UseIndex ? UVElement->GetIndexArray().GetAt(PolyIndexCounter) : PolyIndexCounter;
						
						temp.x = UVElement->GetDirectArray().GetAt(UVIndex)[0];
						temp.y = 1.0f - UVElement->GetDirectArray().GetAt(UVIndex)[1];
						pUvset->uvBuffer.push_back(temp);
						//UVValue = UVElement->GetDirectArray().GetAt(UVIndex);

						PolyIndexCounter++;
					}
				}
				pUvset->uvSetName = UVElement->GetName();
			}

		}
	}	
#endif
}




void MyFbx::MyFbx::GetTextureName(FbxMesh* pMesh, UvSet * const pUvSet) {

	//mesh����m�[�h���擾
	FbxNode* pnode = pMesh->GetNode();

	//�}�e���A���̐����擾
	int materialCount = pnode->GetMaterialCount();

	//�}�e���A���̐������J��Ԃ�
	for (int i = 0; i < materialCount; i++) {
		//�}�e���A�����擾
		FbxSurfaceMaterial* pmaterial = pnode->GetMaterial(i);
		FbxProperty prop = pmaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);


		//FbxLayeredTexture�̐����擾
		int layeredTextureCount = prop.GetSrcObjectCount();

		//�A�^�b�`���ꂽ�e�N�X�`����FbxLayeredTexture�̏ꍇ
		if (0 < layeredTextureCount) {
			//�A�^�b�`���ꂽ�e�N�X�`���̐������J��Ԃ�
			for (int j = 0; j < layeredTextureCount; j++) {
				//�e�N�X�`�����擾
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);

				//���C���[�����擾
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();
					
				for (int k = 0; k < textureCount; k++) {
					//�e�N�X�`�����擾
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture) {
						//�e�N�X�`�������擾
						std::string textureName = texture->GetRelativeFileName();
						//UVSet�����擾
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���đΉ����Ă���e�N�X�`���Ȃ�ێ�

						if (pUvSet->uvSetName == UVSetName) {
							pUvSet->textures.push_back(textureName);
						}

					}
				}
			}
		}
		else {
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < fileTextureCount) {
				//�e�N�X�`���̐������J��Ԃ�
				for (int j = 0; j < fileTextureCount; j++) {
					//�e�N�X�`�����擾
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) {
						//�e�N�X�`�������擾
						std::string textureName = texture->GetRelativeFileName();
						//UVset�����擾
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���đΉ����Ă���e�N�X�`���Ȃ�ێ�
						if (pUvSet->uvSetName == UVSetName) {
							pUvSet->textures.push_back(textureName);
						}
					}
				}
			}
		}
	}

}

void MyFbx::MyFbx::GetMaterial(FbxMesh* pMesh, UvSet * const cUVSet,MY_MODEL_VERTEX_INFO * const pModelInfo)
{
	pModelInfo->numUV = pMesh->GetTextureUVCount();
	FbxNode* pNode = pMesh->GetNode();
	pModelInfo->numMaterial = pNode->GetMaterialCount();

	for (int i = 0; i < pModelInfo->numMaterial; i++)
	{
		MY_MATERIAL tmpMyMaterial;
		FbxDouble3 tmpMaterial;
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		//FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;
		if (pMaterial != 0) {
			//Lambert��phong��
			if (pMaterial->GetClassId.Is(FbxSurfaceLambert::ClassId)) {
				//Lambert�Ƀ_�E���L���X�g
				FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)pMaterial;
				//tmpMaterial = lambert->Ambient.Get();
				
			}
		}
	}
}
