#include "MyModel.h"

void MyModel::PosInit()
{
	for (int x = 0; x < Modelx; x++) {
		for (int y = 0; y < Modely; y++) {
			for (int z = 0; z < Modelz; z++) {
				D3DXMatrixTranslation(&ModelPos[x][y][z], 0, 0, 0);
			}
		}
	}
	for (int x = 0; x < Modelx; x++)
	{
		for (int y = 0; y < Modely; y++)
		{
			for (int z = 0; z < Modelz; z++)
			{
				if (x == 0) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, -0.2f, 0.0f, 0.0f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}
				if (x == 2) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, 0.2f, 0.0f, 0.0f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}

				if (y == 0)	{
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, 0.0f, -0.2f, 0.0f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}
				if (y == 2) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, 0.0f, 0.2f, 0.0f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}

				if (z == 0) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, 0.0f, 0.0f, -0.2f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}
				if (z == 2) {
					D3DXMATRIX tran;
					D3DXMatrixTranslation(&tran, 0.0f, 0.0f, 0.2f);
					ModelPos[x][y][z] = ModelPos[x][y][z] * tran;
				}
			}
		}
	}
}


//void MyModel::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext)
//{
//	m_pDevice = indevice;
//	m_pDeviceContext = indevicecontext;
//}

void MyModel::Render(D3DXMATRIX view,D3DXMATRIX proj)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (int x = 0; x < Modelx; x++)
	{
		for (int y = 0; y < Modely; y++)
		{
			for (int z = 0; z < Modelz; z++)
			{
				m_ConstantBuffer.SetConstantBuffer(ModelPos[x][y][z], view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Cube.Render();
			}
		}
	}
}


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