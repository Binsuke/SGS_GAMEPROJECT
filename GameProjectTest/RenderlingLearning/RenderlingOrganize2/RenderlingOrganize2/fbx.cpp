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
			{//インデックスバッファを使用せず生のデータを使用するため、動的に法線情報を格納する配列を用意する必要がある
			 //対応する場合は　Vector構造などで動的にデータを格納できる要素が必要。またその場合ここでのエレメントのモードを保存しておき
			 //描画の際にそちらのreferenceモードやマッピングモードを参照したうえでどのデータを使うかを選択する必要がある
			 //現状は未実装で進めていく。
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
	//	//UVバッファを取得
	//	FbxGeometryElement* UV = pMesh->GetElementUV(i);


	//	//マッピングモードの取得
	//	FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();
	//	//referenceモードの取得
	//	FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();

	//	//uv数を取得

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
			continue;//スキップ処理

		if (UVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
			UVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			return;

		const bool UseIndex = UVElement->GetReferenceMode != FbxGeometryElement::eDirect;
		const int IndexCount = (UseIndex) ? UVElement->GetIndexArray().GetCount() : 0;//true なら　GetCount

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

	//meshからノードを取得
	FbxNode* pnode = pMesh->GetNode();

	//マテリアルの数を取得
	int materialCount = pnode->GetMaterialCount();

	//マテリアルの数だけ繰り返す
	for (int i = 0; i < materialCount; i++) {
		//マテリアルを取得
		FbxSurfaceMaterial* pmaterial = pnode->GetMaterial(i);
		FbxProperty prop = pmaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);


		//FbxLayeredTextureの数を取得
		int layeredTextureCount = prop.GetSrcObjectCount();

		//アタッチされたテクスチャがFbxLayeredTextureの場合
		if (0 < layeredTextureCount) {
			//アタッチされたテクスチャの数だけ繰り返す
			for (int j = 0; j < layeredTextureCount; j++) {
				//テクスチャを取得
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);

				//レイヤー数を取得
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();
					
				for (int k = 0; k < textureCount; k++) {
					//テクスチャを取得
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture) {
						//テクスチャ名を取得
						std::string textureName = texture->GetRelativeFileName();
						//UVSet名を取得
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較して対応しているテクスチャなら保持

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
				//テクスチャの数だけ繰り返す
				for (int j = 0; j < fileTextureCount; j++) {
					//テクスチャを取得
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) {
						//テクスチャ名を取得
						std::string textureName = texture->GetRelativeFileName();
						//UVset名を取得
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較して対応しているテクスチャなら保持
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
			//Lambertかphongか
			if (pMaterial->GetClassId.Is(FbxSurfaceLambert::ClassId)) {
				//Lambertにダウンキャスト
				FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)pMaterial;
				//tmpMaterial = lambert->Ambient.Get();
				
			}
		}
	}
}
