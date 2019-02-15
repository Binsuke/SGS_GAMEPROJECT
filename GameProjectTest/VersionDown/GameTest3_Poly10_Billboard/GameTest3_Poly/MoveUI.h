#ifndef MOVEUI_H
#define MOVEUI_H

#include "VertexShaderUtility.h"

#include "PixelShaderUtility.h"

#include "ConstantBuffer.h"
#include "MoveUIPanel.h"
#include <list>

class MoveUI {
public:
	//void Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext);
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos);;
	
	void MovePanelInit(ID3D11Device* indevice,ID3D11DeviceContext* indevicecontext);
	
	void Render(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 center,float length,D3DXVECTOR3 vForward);;



	VertexShaderUtil m_VertexShader;
	PixelShaderUtil m_PixelShader;
	MyConstantBuffer m_ConstantBuffer;

private:

	void RenderW(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos);;
	void RenderA(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos);;
	void RenderS(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos);;
	void RenderD(D3DXMATRIX view, D3DXMATRIX proj, D3DXVECTOR3 pos);;

	enum eWASD{
		eW=0,
		eA=1,
		eS=2,
		eD=3,
	};

	void Sort(std::list<eWASD>*lepOut, float fWz, float fAz, float fSz, float fDz);
	
	//void Sort(std::list<eWASD>*lepOut, const D3DXVECTOR3& cvW, const D3DXVECTOR3& cvA,  const D3DXVECTOR3& cvS, const D3DXVECTOR3& cvD, const D3DXVECTOR3& cvForward);

	/*D3DXVECTOR3 m_vLocalForward;
	D3DXVECTOR3 m_vLocalRight;
*/
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	
	MoveUIPanel m_PanelW;
	MoveUIPanel m_PanelA;
	MoveUIPanel m_PanelS;
	MoveUIPanel m_PanelD;


};

#endif