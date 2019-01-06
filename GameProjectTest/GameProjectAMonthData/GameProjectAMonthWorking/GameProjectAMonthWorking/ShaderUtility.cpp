#include "ShaderUtility.h"
#include "HRErrorMessage.h"

void MY_SHADER_UTILITY::ShaderUtility::InitPS(ID3D11Device *ipDevice, std::string Filename, std::string Entrypoint, std::string Target) {
	ID3DBlob *pCompilePS = NULL;
	HRESULT hr = S_OK;
	std::wstring tmp = StrToWstr(Filename);
	LPCWSTR pwsFilename = tmp.c_str();

	//std::string s = "a";
	//LPCSTR ps = s.c_str();
	/*std::string str = "a";
	LPCWSTR tmp = str.c_str();*/
	//std::string tmpstr = Filename;
	hr = D3DCompileFromFile(pwsFilename, NULL, NULL, Entrypoint.c_str(), Target.c_str(), NULL, 0, &pCompilePS, NULL);
	std::string ErrorStr = "D3DCompileFromFile PS:";
	ErrorStr = ErrorStr + Filename;
	D3D11ErrorCheck(hr, ErrorStr);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "D3DCompileFromFile PS :Failed", "D3DCompileFromFile error", 0);
	//	PostQuitMessage(0);
	//}
	hr = ipDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &m_pPixelShader);
	ErrorStr = "CreatePixelShader:";
	ErrorStr = ErrorStr + Filename;
	D3D11ErrorCheck(hr, ErrorStr);

	pCompilePS->Release();
}

void MY_SHADER_UTILITY::ShaderUtility::InitVSandLayout(ID3D11Device *ipDevice, std::string Filename, std::string Entrypoint, std::string Target, D3D11_INPUT_ELEMENT_DESC *layout, const int &SemanticNum) {

	ID3DBlob *pCompileVS = NULL;
	HRESULT hr = S_OK;
	std::wstring tmp = StrToWstr(Filename);
	LPCWSTR pwsFilename = tmp.c_str();
	hr = D3DCompileFromFile(pwsFilename, NULL, NULL, Entrypoint.c_str(), Target.c_str(), NULL, 0, &pCompileVS, NULL);
	std::string ErrorStr = "D3DCompileFromFile VS:";
	ErrorStr = ErrorStr + Filename;
	D3D11ErrorCheck(hr, ErrorStr);

	hr = ipDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &m_pVertexShader);

	D3D11ErrorCheck(hr, "CreateVertexShader:");
	m_pLayout = new D3D11_INPUT_ELEMENT_DESC[SemanticNum];

	for (int i = 0; i < SemanticNum; i++) {
		m_pLayout[i] = layout[i];
	}

	hr = ipDevice->CreateInputLayout(m_pLayout, SemanticNum, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &m_pVertexLayout);
	D3D11ErrorCheck(hr, "CreateInputLayout");
	pCompileVS->Release();
}

void MY_SHADER_UTILITY::ShaderUtility::InitConstantBuffer(ID3D11Device *ipDevice) {
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	HRESULT hr = S_OK;
	hr = ipDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	D3D11ErrorCheck(hr, "CreateBuffer:Constant Buffer");
}

void MY_SHADER_UTILITY::ShaderUtility::SetLayout(ID3D11DeviceContext *ipDeviceContext) {

	ipDeviceContext->IASetInputLayout(m_pVertexLayout);
	ipDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void MY_SHADER_UTILITY::ShaderUtility::SetVS(ID3D11DeviceContext * ipDeviceContext) {

	ipDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	ipDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);

}

void MY_SHADER_UTILITY::ShaderUtility::SetPS(ID3D11DeviceContext *ipDeviceContext) {
	ipDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	ipDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}

void MY_SHADER_UTILITY::ShaderUtility::SetConstantBuff(ID3D11DeviceContext *ipDeviceContext, const CONSTANT_BUFFER &cb) {

	D3D11_MAPPED_SUBRESOURCE pdata;
	HRESULT hr = S_OK;
	hr = ipDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	D3D11ErrorCheck(hr, "DeviceContext ConstantaBuffer Map");
	errno_t error;
	error = memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));

	if (error) {
		MessageBox(NULL, "memcpy_s error", "error", 0);
		PostQuitMessage(0);
	}

	ipDeviceContext->Unmap(m_pConstantBuffer, 0);
}