#include "MyModel.h"


MyModel::MyModel(): m_vForward(0,0,1),m_vUp(0,1,0),m_vRight(1,0,0),m_fPolySize(MyPoly::Poly::PolySize), m_fPolyHalfSize(MyPoly::Poly::PolyHalfSize)
{

}

void MyModel::InitAdjustment()
{
	float tmpx = (float)((m_iModelHalfSizeX -1) * m_fPolySize) + m_fPolyHalfSize;
	float tmpy = (float)((m_iModelHalfSizeY -1) * m_fPolySize) + m_fPolyHalfSize;
	float tmpz = (float)((m_iModelHalfSizeZ -1) * m_fPolySize) + m_fPolyHalfSize;

	D3DXMatrixTranslation(&m_mAdjustment, tmpx, tmpy, tmpz);
}

void MyModel::PosInit()
{

	PosInit(ModelSize);
	
}

void MyModel::PosInit(int inx,int iny,int inz)
{
	
	int tmpx,tmpy,tmpz;
	if (inx % 2 == 0){
		tmpx = (inx/2) + 1;
		m_iModelSizeX = inx + 1;

	}
	else {
		tmpx = (inx + 1) / 2 - 1;
		m_iModelSizeX = inx;
	}
	m_iModelHalfSizeX = tmpx;


	 if (iny % 2 == 0) {
		tmpy = (iny / 2) + 1;
		m_iModelSizeY = iny + 1;
	}
	else {
		tmpy = (iny + 1) / 2 - 1;
		m_iModelSizeY = iny;

	}
	 m_iModelHalfSizeY = tmpy;


	if (inz % 2 == 0) {
		tmpz = (inz / 2) + 1;
		m_iModelSizeZ = inz + 1;
	}
	else {
		tmpz = (inz + 1) / 2 - 1;
		m_iModelSizeZ = inz;
	}
	m_iModelHalfSizeZ = tmpz;



	InitAdjustment();
	for (int x = 0; x < m_iModelSizeX; x++)
	{
		for (int y = 0; y < m_iModelSizeY; y++) {
			for (int z = 0; z < m_iModelSizeZ; z++) {
				D3DXMATRIX tran;
				D3DXMatrixTranslation(&tran, (-m_fPolySize * tmpx + ((x+1)*m_fPolySize)), (-m_fPolySize*tmpy + ((y+1)*m_fPolySize)), (-m_fPolySize*tmpz + ((z+1)*m_fPolySize)));
				m_lmModelMat.push_back(tran);
			}
		}
	}
}


void MyModel::PosInit(int NumPoly)
{
	int tmpx, tmpy, tmpz;
 
	if (NumPoly % 2 == 0) {
		tmpx = (NumPoly / 2) + 1;
		m_iModelSizeX = NumPoly + 1;
		tmpy = (NumPoly / 2) + 1;
		m_iModelSizeY = NumPoly + 1;
		tmpz = (NumPoly / 2) + 1;
		m_iModelSizeZ = NumPoly + 1;
	}
	else {
		tmpx = (NumPoly + 1 / 2) - 1;
		m_iModelSizeX = NumPoly;
		tmpy = (NumPoly + 1 / 2) - 1;
		m_iModelSizeY = NumPoly;
		tmpz = (NumPoly + 1 / 2) - 1;
		m_iModelSizeZ = NumPoly;
	}

	m_iModelHalfSizeX = tmpx;
	m_iModelHalfSizeY = tmpy;
	m_iModelHalfSizeZ = tmpz;

	InitAdjustment();

	for (int x = 0; x < m_iModelSizeX; x++)
	{
		for (int y = 0; y < m_iModelSizeY; y++) {
			for (int z = 0; z < m_iModelSizeZ; z++) {
				D3DXMATRIX tran;
				D3DXMatrixTranslation(&tran, (-m_fPolySize * tmpx + ((x+1)*m_fPolySize)), (-m_fPolySize*tmpy + ((y+1)*m_fPolySize)), (-m_fPolySize*tmpz + ((z+1)*m_fPolySize)));
				m_lmModelMat.push_back(tran);
			}
		}
	}
}



void MyModel::Render(D3DXMATRIX view,D3DXMATRIX proj)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	
	for (auto itr=m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
				D3DXMATRIX tmpmatrix;
				tmpmatrix = (*itr) * m_mAdjustment;
				m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
				m_ConstantBuffer.SetCBtoPS();
				m_ConstantBuffer.SetCBtoVS();
				m_Cube.Render();
	}
}

void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran) 
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);
	
	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = (*itr) * tran * m_mAdjustment;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
	
}
void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);


	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = (*itr) * rotation * tran * m_mAdjustment;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
}


void MyModel::Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXMATRIX tran, D3DXMATRIX rotation,D3DXMATRIX scale)
{
	m_VertexShader.SetShader(0);
	m_VertexShader.SetLayout();
	m_PixelShader.SetShader(0);

	for (auto itr = m_lmModelMat.begin(); itr != m_lmModelMat.end(); ++itr)
	{
		D3DXMATRIX tmpmatrix;
		tmpmatrix = scale * (*itr) * rotation * tran * m_mAdjustment;
		m_ConstantBuffer.SetConstantBuffer(tmpmatrix, view, proj);
		m_ConstantBuffer.SetCBtoPS();
		m_ConstantBuffer.SetCBtoVS();
		m_Cube.Render();
	}
}
//
//void MyModel::MoveForward(float delta) {
//
//}

