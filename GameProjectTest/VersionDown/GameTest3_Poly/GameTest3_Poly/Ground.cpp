#include "Ground.h"

void MyGround::PosInit()
{
	for (int x = 0; x < Modelx; x++) {
		for (int z = 0; z < Modelz; z++) {
			D3DXMATRIX tran;
			D3DXMatrixTranslation(&tran, x * 2, -1, z * 2);
			ModelPos[x][z] = tran;
		}
	}
}



void MyGround::Render(D3DXMATRIX view, D3DXMATRIX proj)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (int x = 0; x < Modelx; x++)
	{
			for (int z = 0; z < Modelz; z++)
			{
				m_ConstantBuffer.SetConstantBuffer(ModelPos[x][z], view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Ground.Render();
			}
		
	}
}

void MyGround::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (int x = 0; x < Modelx; x++)
	{
		
			for (int z = 0; z < Modelz; z++)
			{
				D3DXMATRIX tmpmatrix;
				tmpmatrix = ModelPos[x][z] * tran;
				m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Ground.Render();
			}
		
	}
}
void MyGround::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (int x = 0; x < Modelx; x++)
	{
	
			for (int z = 0; z < Modelz; z++)
			{
				D3DXMATRIX TmpMatrix;
				TmpMatrix = ModelPos[x][z] * rotation * tran;
				m_ConstantBuffer.SetConstantBuffer(TmpMatrix, view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Ground.Render();
			}
		
	}
}


void MyGround::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation, D3DXMATRIX scale)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (int x = 0; x < Modelx; x++)
	{
		
			for (int z = 0; z < Modelz; z++)
			{
				D3DXMATRIX TmpMatrix;
				TmpMatrix = scale * ModelPos[x][z] * rotation * tran;
				m_ConstantBuffer.SetConstantBuffer(TmpMatrix, view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Ground.Render();
			}
		
	}
}
