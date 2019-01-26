#include "Poly.h"
#include "PixelShaderUtility.h"
#include "VertexShaderUtility.h"
#include "ConstantBuffer.h"

class MyModel {
public:
	//void Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext);
	void PosInit();
	void Render(D3DXMATRIX view,D3DXMATRIX proj);

	MyPoly::Poly m_Cube;
	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	MyConstantBuffer m_ConstantBuffer;
private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	

	D3DXMATRIX m_World;
	enum {
		Modelx = 3,
		Modely = 3,
		Modelz = 3,
	};
	D3DXMATRIX ModelPos[Modelx][Modely][Modelz];
};