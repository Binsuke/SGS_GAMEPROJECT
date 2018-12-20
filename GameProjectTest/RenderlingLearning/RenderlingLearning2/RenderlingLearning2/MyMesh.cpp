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
////�f�ށiFBX)�̂ق��́A�O�p�|���S���ɂ��邱��
//HRESULT MY_MESH::CreateFromFBX(CHAR* FileName)
//{
//	//�w��̃t�@�C����FBX������
//	if (FAILED(InitFBX(FileName)))
//	{
//		MessageBox(0, L"FBX���[�_�[���������s", NULL, MB_OK);
//		return E_FAIL;
//	}
//
//	//�ǂݍ���
//	KFbxNode* pRootNode = m_pmyScene->GetRootNode();
//	KFbxMesh* pFbxMesh = 0;
//	KFbxNodeAttribute::EAttributeType type;
//
//	KFbxNodeAttribute *pAttr = pRootNode->GetNodeAttribute();
//	if (pAttr != NULL)
//	{
//		type = pAttr->GetAttributeType();
//		if (type == KFbxNodeAttribute::eMESH)//�^�C�v�����b�V���̏ꍇ�@���ʂ̓��[�g�����b�V�����̂��̂ł��邱�Ƃ͏��Ȃ�
//		{
//			pFbxMesh = pRootNode->GetMesh();
//		}
//	}
//	else//�q�����b�V���̉\������
//	{
//		int iNumChild = pRootNode->GetChildCount();
//		KFbxNode* pChildNode = pRootNode->GetChild(0);
//		pAttr = pChildNode->GetNodeAttribute();
//		type = pAttr->GetAttributeType();
//		if (type == KFbxNodeAttribute::eMESH)//�^�C�v�����b�V���̏ꍇ�@���ʂ̓��[�g�����b�V�����̂��̂ł��邱�Ƃ͏��Ȃ�
//		{
//			pFbxMesh = pChildNode->GetMesh();
//		}
//		else
//		{
//			MessageBox(0, L"���b�V���̓ǂݍ��ݎ��s", NULL, MB_OK);
//		}
//	}
//	//���O�ɒ��_���A�|���S�������𒲂ׂ�
//	m_dwNumVert = pFbxMesh->GetControlPointsCount();
//	m_dwNumUV = pFbxMesh->GetTextureUVCount();
//	m_dwNumFace = pFbxMesh->GetPolygonCount();
//
//	if (m_dwNumVert < m_dwNumUV)//Direct3D�ł�UV�̐��������_���K�v
//	{
//		//���L���_���ŁA���_��������Ȃ���
//		MessageBox(0, L"Direct3D�́AUV�̐��������_���K�v�ł��iUV��u���ꏊ���K�v�ł��j�e�N�X�`���[�͐������\���Ȃ��Ǝv���܂�", NULL, MB_OK);
//		//return E_FAIL;
//	}
//	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
//	MY_VERTEX* pvVB = new MY_VERTEX[m_dwNumVert];
//	int* piFaceBuffer = new int[m_dwNumFace * 3];//�R���_�|���S���Ȃ̂ŁA1�t�F�C�X=3���_(3�C���f�b�N�X)
//
//	//���_�ǂݍ���
//	KFbxVector4* pCoord = pFbxMesh->GetControlPoints();
//
//	for (DWORD i = 0; i < m_dwNumVert; i++)
//	{
//		pvVB[i].vPos.x = -pCoord[i][0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
//		pvVB[i].vPos.y = pCoord[i][1];
//		pvVB[i].vPos.z = pCoord[i][2];
//	}
//	//�|���S�����i���_�C���f�b�N�X�j�ǂݍ���	
//	int* piIndex = pFbxMesh->GetPolygonVertices();
//	memcpy(piFaceBuffer, piIndex, sizeof(int)*m_dwNumFace * 3);
//
//	//�@���ǂݍ���
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
//		pvVB[iVert0Index].vNorm.x = -Normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
//		pvVB[iVert0Index].vNorm.y = Normal[1];
//		pvVB[iVert0Index].vNorm.z = Normal[2];
//
//		pFbxMesh->GetPolygonVertexNormal(i, 1, Normal);
//		pvVB[iVert1Index].vNorm.x = -Normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
//		pvVB[iVert1Index].vNorm.y = Normal[1];
//		pvVB[iVert1Index].vNorm.z = Normal[2];
//
//		pFbxMesh->GetPolygonVertexNormal(i, 2, Normal);
//		pvVB[iVert2Index].vNorm.x = -Normal[0];//FBX�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
//		pvVB[iVert2Index].vNorm.y = Normal[1];
//		pvVB[iVert2Index].vNorm.z = Normal[2];
//	}
//	//�e�N�X�`���[���W�ǂݍ���
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
//	//�}�e���A���ǂݍ���
//	KFbxNode* pNode = pFbxMesh->GetNode();
//	m_dwNumMaterial = pNode->GetMaterialCount();
//
//	m_pMaterial = new MY_MATERIAL[m_dwNumMaterial];
//
//	//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
//	m_ppIndexBuffer = new ID3D11Buffer*[m_dwNumMaterial];
//
//	for (int i = 0; i < m_dwNumMaterial; i++)
//	{
//		//�t�H�����f����z��
//		KFbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
//		KFbxSurfacePhong* pPhong = (KFbxSurfacePhong*)pMaterial;
//
//		//����
//		KFbxPropertyDouble3 d3Ambient = pPhong->GetAmbientColor();
//		m_pMaterial[i].Ka.x = (float)d3Ambient.Get()[0];
//		m_pMaterial[i].Ka.y = (float)d3Ambient.Get()[1];
//		m_pMaterial[i].Ka.z = (float)d3Ambient.Get()[2];
//		//�g�U���ˌ�
//		KFbxPropertyDouble3 d3Diffuse = pPhong->GetDiffuseColor();
//		m_pMaterial[i].Kd.x = (float)d3Diffuse.Get()[0];
//		m_pMaterial[i].Kd.y = (float)d3Diffuse.Get()[1];
//		m_pMaterial[i].Kd.z = (float)d3Diffuse.Get()[2];
//		//���ʔ��ˌ�
//		KFbxPropertyDouble3 d3Specular = pPhong->GetDiffuseColor();
//		m_pMaterial[i].Ks.x = (float)d3Specular.Get()[0];
//		m_pMaterial[i].Ks.y = (float)d3Specular.Get()[1];
//		m_pMaterial[i].Ks.z = (float)d3Specular.Get()[2];
//		//�e�N�X�`���[�i�f�B�t���[�Y�e�N�X�`���[�̂݁j
//		KFbxProperty lProperty;
//		lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
//		KFbxTexture* texture = KFbxCast<KFbxTexture>(lProperty.GetSrcObject(KFbxTexture::ClassId, 0));
//		if (texture)
//		{
//			strcpy_s(m_pMaterial[i].szTextureName, texture->GetName());
//			//�e�N�X�`���[���쐬
//			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice, m_pMaterial[i].szTextureName, NULL, NULL, &m_pMaterial[i].pTexture, NULL)))//��΃p�X�t�@�C�����́A�܂����s����Ǝv�����A�A�A
//			{
//				char ext[11];
//				_splitpath(m_pMaterial[i].szTextureName, 0, 0, m_pMaterial[i].szTextureName, ext);
//				strcat_s(m_pMaterial[i].szTextureName, ext);
//
//				if (FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice, m_pMaterial[i].szTextureName, NULL, NULL, &m_pMaterial[i].pTexture, NULL)))//�t�@�C�����݂̂Ńg���C
//				{
//					MessageBox(0, L"�e�N�X�`���[�ǂݍ��ݎ��s", NULL, MB_OK);
//					return E_FAIL;
//				}
//			}
//		}
//		//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
//		int iCount = 0;
//		int* pIndex = new int[m_dwNumFace * 3];//�Ƃ肠�����A���b�V�����̃|���S�����Ń������m�ہi�X�̃|���S���O���[�v�͂��Ȃ炸����ȉ��ɂȂ邪�j
//
//		//���̃}�e���A���ł���C���f�b�N�X�z����̊J�n�C���f�b�N�X�𒲂ׂ�@����ɃC���f�b�N�X�̌������ׂ�		
//		iCount = 0;
//		for (int k = 0; k < m_dwNumFace; k++)
//		{
//			KFbxLayerElementMaterial* mat = pFbxMesh->GetLayer(0)->GetMaterials();//���C���[��1��������z��
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
//		m_pMaterial[i].dwNumFace = iCount / 3;//���̃}�e���A�����̃|���S����
//
//		delete pIndex;
//	}
//	//�o�[�e�b�N�X�o�b�t�@�[���쐬
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
//	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
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
//	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g�i�o�[�e�b�N�X�o�b�t�@�[�͈�ł����j
//	UINT stride = sizeof(MY_VERTEX);
//	UINT offset = 0;
//	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
//
//	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
//	for (int i = 0; i < m_dwNumMaterial; i++)
//	{
//		//�g�p����Ă��Ȃ��}�e���A���΍�
//		if (m_pMaterial[i].dwNumFace == 0)
//		{
//			continue;
//		}
//		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
//		stride = sizeof(int);
//		offset = 0;
//		m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);
//
//		//�v���~�e�B�u�E�g�|���W�[���Z�b�g
//		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//		//�}�e���A���̊e�v�f�ƕϊ��s����V�F�[�_�[�ɓn��			
//
//		//���[���h�s����V�F�[�_�[�ɓn��
//		//���[���h�E�r���[�E�v���W�F�N�V�����s����V�F�[�_�[�ɓn��
//		//�f�B�t���[�Y�J���[���V�F�[�_�[�ɓn��
//		//�X�y�L�����[���V�F�[�_�[�ɓn��
//		//�X�y�L�����[�̃p���[���V�F�[�_�[�ɓn��
//		//�A���r�G���g���V�F�[�_�[�ɓn��
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
//		//�e�N�X�`���[���V�F�[�_�[�ɓn��
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