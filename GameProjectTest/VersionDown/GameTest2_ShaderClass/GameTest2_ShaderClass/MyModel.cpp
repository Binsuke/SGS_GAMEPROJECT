#include "MyModel.h"

//
//void MyModel::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext, D3DXMATRIX initpos)
//{
//	m_pDevice = indevice;
//	m_pDeviceContext = indevicecontext;
//	m_World = initpos;
//}
//HRESULT MyModel::CreateConstantBuffer(D3D11_BUFFER_DESC cb) 
//{
//	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
//	{
//		return E_FAIL;
//	}
//	return S_OK;
//}
//
//void MyModel::SetConstantBuffer(D3DXMATRIX view, D3DXMATRIX proj)
//{
//	D3D11_MAPPED_SUBRESOURCE pData;
//	SIMPLESHADER_CONSTANT_BUFFER cb;
//	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
//	{
//		//ワールド　カメラ　射影行列を渡す
//		D3DXMATRIX m = m_World * view*proj;
//		D3DXMatrixTranspose(&m, &m);
//		cb.mWVP = m;
//		//mWVP = m;
//
//		////カラーを渡す
//		//D3DXVECTOR4 vColor(1, 0, 0, 1);
//		//cb.vColor = vColor;
//		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
//		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
//	}
//}
//
//void MyModel::SetCBtoVS()
//{
//	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
//}
//
//
//void MyModel::SetCBtoPS()
//{
//	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
//}