//#include "InputLayout.h"
//
//HRESULT MyInputLayout::CreateVertexLayout(ID3D11Device* device, ID3D11DeviceContext* devicecontext, D3D11_INPUT_ELEMENT_DESC layout[], UINT numelement)
//{
//	m_pDevice = device;
//	m_pDeviceContext = devicecontext;
//
//	//���_�C���v�b�g���C�A�E�g���쐬
//	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
//	{
//		return FALSE;
//	}
//}