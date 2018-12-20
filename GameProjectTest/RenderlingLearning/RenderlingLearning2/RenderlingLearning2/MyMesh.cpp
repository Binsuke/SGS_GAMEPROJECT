//#include <stdlib.h>
//#include "MyMesh.h"
//
//#pragma comment(lib,"libfbxsdk_md.lib")
//#pragma comment(lib,"libfbxml2_md.lib")
//#pragma comment(lib,"zlib_md.lib")
//
//
////
////
////
//MY_MESH::MY_MESH()
//{
//	ZeroMemory(this, sizeof(MY_MESH));
//	D3DXMatrixIdentity(&m_mMyOrientation);
//}
//
////
////
////
//MY_MESH::~MY_MESH()
//{
//	delete[] m_pMaterial;
//	SAFE_RELEASE(m_pVertexBuffer);
//	for (int i = 0; i < m_dwNumMaterial; i++)
//	{
//		SAFE_RELEASE(m_ppIndexBuffer[i]);
//	}
//	delete[] m_ppIndexBuffer;
//
//	DestroyFBX();
//}
////
////
////
//HRESULT MY_MESH::InitFBX(CHAR* szFileName)
//{
//	m_pSdkManager = KFbxSdkManager::Create();
//
//	m_pImporter = KFbxImporter::Create(m_pSdkManager, "my importer");
//
//	int iFormat = -1;
//	m_pImporter->Initialize((const char*)szFileName, iFormat);
//
//	m_pmyScene = KFbxScene::Create(m_pSdkManager, "my scene");
//
//	m_pImporter->Import(m_pmyScene, 0);
//
//	return S_OK;
//}
////
////
////
//void MY_MESH::DestroyFBX()
//{
//	IOSREF.FreeIOSettings();
//	if (m_pSdkManager) m_pSdkManager->Destroy();
//}
////
////
////素材（FBX)のほうは、三角ポリゴンにすること
//HRESULT MY_MESH::CreateFromFBX(CHAR* FileName)
//{
//	//指定のファイルでFBX初期化
//	if (FAILED(InitFBX(FileName)))
//	{
//		MessageBox(0, L"FBXローダー初期化失敗", NULL, MB_OK);
//		return E_FAIL;
//	}
//
//	//読み込み
//	KFbxNode* pRootNode = m_pmyScene->GetRootNode();
//	KFbxMesh* pFbxMesh = 0;
//	KFbxNodeAttribute::EAttributeType type;
//
//	KFbxNodeAttribute *pAttr = pRootNode->GetNodeAttribute();
//	if (pAttr != NULL)
//	{
//		type = pAttr->GetAttributeType();
//		if (type == KFbxNodeAttribute::eMESH)//タイプがメッシュの場合　普通はルートがメッシュそのものであることは少ない
//		{
//			pFbxMesh = pRootNode->GetMesh();
//		}
//	}
//	else//子がメッシュの可能性あり
//	{
//		int iNumChild = pRootNode->GetChildCount();
//		KFbxNode* pChildNode = pRootNode->GetChild(0);
//		pAttr = pChildNode->GetNodeAttribute();
//		type = pAttr->GetAttributeType();
//		if (type == KFbxNodeAttribute::eMESH)//タイプがメッシュの場合　普通はルートがメッシュそのものであることは少ない
//		{
//			pFbxMesh = pChildNode->GetMesh();
//		}
//		else
//		{
//			MessageBox(0, L"メッシュの読み込み失敗", NULL, MB_OK);
//		}
//	}
//	//事前に頂点数、ポリゴン数等を調べる
//	m_dwNumVert = pFbxMesh->GetControlPointsCount();
//	m_dwNumUV = pFbxMesh->GetTextureUVCount();
//	m_dwNumFace = pFbxMesh->GetPolygonCount();
//
//	if (m_dwNumVert < m_dwNumUV)//Direct3DではUVの数だけ頂点が必要
//	{
//		//共有頂点等で、頂点数が足りない時
//		MessageBox(0, L"Direct3Dは、UVの数だけ頂点が必要です（UVを置く場所が必要です）テクスチャーは正しく貼られないと思われます", NULL, MB_OK);
//		//return E_FAIL;
//	}
//	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
//	MY_VERTEX* pvVB = new MY_VERTEX[m_dwNumVert];
//	int* piFaceBuffer = new int[m_dwNumFace * 3];//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)
//
//	//頂点読み込み
//	KFbxVector4* pCoord = pFbxMesh->GetControlPoints();
//
//	for (DWORD i = 0; i < m_dwNumVert; i++)
//	{
//		pvVB[i].vPos.x = -pCoord[i][0];//FBXは右手座標系なのでxあるいはｚを反転
//		pvVB[i].vPos.y = pCoord[i][1];
//		pvVB[i].vPos.z = pCoord[i][2];
//	}
//	//ポリゴン情報（頂点インデックス）読み込み	
//	int* piIndex = pFbxMesh->GetPolygonVertices();
//	memcpy(piFaceBuffer, piIndex, sizeof(int)*m_dwNumFace * 3);
//
//	//法線読み込み
//	KFbxVector4 Normal;
//	for (i = 0; i < m_dwNumFace; i++)
//	{
//		int iStartIndex = pFbxMesh->GetPolygonVertexIndex(i);
//
//		int iVert0Index = piFaceBuffer[iStartIndex];
//		int iVert1Index = piFaceBuffer[iStartIndex + 1];
//		int iVert2Index = piFaceBuffer[iStartIndex + 2];
//
//		if (iVert0Index <= 0) continue;
//
//		pFbxMesh->GetPolygonVertexNormal(i, 0, Normal);
//		pvVB[iVert0Index].vNorm.x = -Normal[0];//FBXは右手座標系なのでxあるいはｚを反転
//		pvVB[iVert0Index].vNorm.y = Normal[1];
//		pvVB[iVert0Index].vNorm.z = Normal[2];
//
//		pFbxMesh->GetPolygonVertexNormal(i, 1, Normal);
//		pvVB[iVert1Index].vNorm.x = -Normal[0];//FBXは右手座標系なのでxあるいはｚを反転
//		pvVB[iVert1Index].vNorm.y = Normal[1];
//		pvVB[iVert1Index].vNorm.z = Normal[2];
//
//		pFbxMesh->GetPolygonVertexNormal(i, 2, Normal);
//		pvVB[iVert2Index].vNorm.x = -Normal[0];//FBXは右手座標系なのでxあるいはｚを反転
//		pvVB[iVert2Index].vNorm.y = Normal[1];
//		pvVB[iVert2Index].vNorm.z = Normal[2];
//	}
//	//テクスチャー座標読み込み
//	KFbxLayerElementUV* pUV = 0;
//	pUV = pFbxMesh->GetLayer(0)->GetUVs();
//	for (i = 0; i < m_dwNumUV; i++)
//	{
//		KFbxVector2 v2;
//		v2 = pUV->GetDirectArray().GetAt(i);
//		pvVB[i].vTex.x = v2.GetAt(0);
//		pvVB[i].vTex.y = 1.0f - v2.GetAt(1);
//	}
//
//	//マテリアル読み込み
//	KFbxNode* pNode = pFbxMesh->GetNode();
//	m_dwNumMaterial = pNode->GetMaterialCount();
//
//	m_pMaterial = new MY_MATERIAL[m_dwNumMaterial];
//
//	//マテリアルの数だけインデックスバッファーを作成
//	m_ppIndexBuffer = new ID3D11Buffer*[m_dwNumMaterial];
//
//	for (int i = 0; i < m_dwNumMaterial; i++)
//	{
//		//フォンモデルを想定
//		KFbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
//		KFbxSurfacePhong* pPhong = (KFbxSurfacePhong*)pMaterial;
//
//		//環境光
//		KFbxPropertyDouble3 d3Ambient = pPhong->GetAmbientColor();
//		m_pMaterial[i].Ka.x = (float)d3Ambient.Get()[0];
//		m_pMaterial[i].Ka.y = (float)d3Ambient.Get()[1];
//		m_pMaterial[i].Ka.z = (float)d3Ambient.Get()[2];
//		//拡散反射光
//		KFbxPropertyDouble3 d3Diffuse = pPhong->GetDiffuseColor();
//		m_pMaterial[i].Kd.x = (float)d3Diffuse.Get()[0];
//		m_pMaterial[i].Kd.y = (float)d3Diffuse.Get()[1];
//		m_pMaterial[i].Kd.z = (float)d3Diffuse.Get()[2];
//		//鏡面反射光
//		KFbxPropertyDouble3 d3Specular = pPhong->GetDiffuseColor();
//		m_pMaterial[i].Ks.x = (float)d3Specular.Get()[0];
//		m_pMaterial[i].Ks.y = (float)d3Specular.Get()[1];
//		m_pMaterial[i].Ks.z = (float)d3Specular.Get()[2];
//		//テクスチャー（ディフューズテクスチャーのみ）
//		KFbxProperty lProperty;
//		lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
//		KFbxTexture* texture = KFbxCast<KFbxTexture>(lProperty.GetSrcObject(KFbxTexture::ClassId, 0));
//		if (texture)
//		{
//			strcpy_s(m_pMaterial[i].szTextureName, texture->GetName());
//			//テクスチャーを作成
//			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice, m_pMaterial[i].szTextureName, NULL, NULL, &m_pMaterial[i].pTexture, NULL)))//絶対パスファイル名は、まず失敗すると思うが、、、
//			{
//				char ext[11];
//				_splitpath(m_pMaterial[i].szTextureName, 0, 0, m_pMaterial[i].szTextureName, ext);
//				strcat_s(m_pMaterial[i].szTextureName, ext);
//
//				if (FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice, m_pMaterial[i].szTextureName, NULL, NULL, &m_pMaterial[i].pTexture, NULL)))//ファイル名のみでトライ
//				{
//					MessageBox(0, L"テクスチャー読み込み失敗", NULL, MB_OK);
//					return E_FAIL;
//				}
//			}
//		}
//		//マテリアルの数だけインデックスバッファーを作成
//		int iCount = 0;
//		int* pIndex = new int[m_dwNumFace * 3];//とりあえず、メッシュ内のポリゴン数でメモリ確保（個々のポリゴングループはかならずこれ以下になるが）
//
//		//そのマテリアルであるインデックス配列内の開始インデックスを調べる　さらにインデックスの個数も調べる		
//		iCount = 0;
//		for (int k = 0; k < m_dwNumFace; k++)
//		{
//			KFbxLayerElementMaterial* mat = pFbxMesh->GetLayer(0)->GetMaterials();//レイヤーが1枚だけを想定
//			int matId = mat->GetIndexArray().GetAt(k);
//			if (matId == i)
//			{
//				pIndex[iCount] = pFbxMesh->GetPolygonVertex(k, 0);
//				pIndex[iCount + 1] = pFbxMesh->GetPolygonVertex(k, 1);
//				pIndex[iCount + 2] = pFbxMesh->GetPolygonVertex(k, 2);
//				iCount += 3;
//			}
//		}
//		CreateIndexBuffer(iCount * sizeof(int), pIndex, &m_ppIndexBuffer[i]);
//		m_pMaterial[i].dwNumFace = iCount / 3;//そのマテリアル内のポリゴン数
//
//		delete pIndex;
//	}
//	//バーテックスバッファーを作成
//	D3D11_BUFFER_DESC bd;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(MY_VERTEX) *m_dwNumVert;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	D3D11_SUBRESOURCE_DATA InitData;
//	InitData.pSysMem = pvVB;
//	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
//		return FALSE;
//
//	//一時的な入れ物は、もはや不要
//	delete[] piFaceBuffer;
//	if (pvVB) delete[] pvVB;
//
//	return S_OK;
//}
////
////
////
//HRESULT MY_MESH::CreateIndexBuffer(DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer)
//{
//	D3D11_BUFFER_DESC bd;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = dwSize;
//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	D3D11_SUBRESOURCE_DATA InitData;
//	InitData.pSysMem = pIndex;
//	InitData.SysMemPitch = 0;
//	InitData.SysMemSlicePitch = 0;
//	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, ppIndexBuffer)))
//	{
//		return FALSE;
//	}
//
//	return S_OK;
//}
////
////
////
//void MY_MESH::RenderMesh(D3DXMATRIX* pWorld)
//{
//	m_mFinalWorld = *pWorld;
//
//	//バーテックスバッファーをセット（バーテックスバッファーは一つでいい）
//	UINT stride = sizeof(MY_VERTEX);
//	UINT offset = 0;
//	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
//
//	//マテリアルの数だけ、それぞれのマテリアルのインデックスバッファ－を描画
//	for (int i = 0; i < m_dwNumMaterial; i++)
//	{
//		//使用されていないマテリアル対策
//		if (m_pMaterial[i].dwNumFace == 0)
//		{
//			continue;
//		}
//		//インデックスバッファーをセット
//		stride = sizeof(int);
//		offset = 0;
//		m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);
//
//		//プリミティブ・トポロジーをセット
//		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//		//マテリアルの各要素と変換行列をシェーダーに渡す			
//
//		//ワールド行列をシェーダーに渡す
//		//ワールド・ビュー・プロジェクション行列をシェーダーに渡す
//		//ディフューズカラーをシェーダーに渡す
//		//スペキュラーをシェーダーに渡す
//		//スペキュラーのパワーをシェーダーに渡す
//		//アンビエントをシェーダーに渡す
//		D3D11_MAPPED_SUBRESOURCE pData;
//		if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
//		{
//			SHADER_GLOBAL1 sg;
//			sg.mW = m_mFinalWorld;
//			D3DXMatrixTranspose(&sg.mW, &sg.mW);
//			sg.mWVP = m_mFinalWorld * m_mView*m_mProj;
//			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
//			sg.vAmbient = m_pMaterial[i].Ka;
//			sg.vDiffuse = m_pMaterial[i].Kd;
//			sg.vSpecular = m_pMaterial[i].Ks;
//			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL1));
//			m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
//		}
//		m_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
//		m_pDeviceContext->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
//		//テクスチャーをシェーダーに渡す
//		if (m_pMaterial[i].szTextureName[0] != NULL)
//		{
//			m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
//			m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMaterial[i].pTexture);
//		}
//		//Draw
//		m_pDeviceContext->DrawIndexed(m_pMaterial[i].dwNumFace * 3, 0, 0);
//
//	}
//}