#include "ShaderUtility.h"

void BASE_SHADER_CLASS::Init(ID3D11Device* indevice, ID3D11DeviceContext* indevicecontext)
{
	m_pDevice = indevice;
	m_pDeviceContext = indevicecontext;
}