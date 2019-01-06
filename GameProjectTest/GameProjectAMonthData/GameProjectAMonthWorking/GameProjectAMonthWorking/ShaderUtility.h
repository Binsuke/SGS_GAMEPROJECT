#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>

namespace MY_SHADER_UTILITY {
	struct CONSTANT_BUFFER {
		DirectX::XMMATRIX mWVP;
	};


	class ShaderUtility {
	private:
		ID3D11VertexShader *m_pVertexShader;
		ID3D11PixelShader *m_pPixelShader;		ID3D11Buffer *pConstantBuffer;
		D3D11_INPUT_ELEMENT_DESC *m_pLayout;

		ID3D11InputLayout *m_pVertexLayout;
		ID3D11Buffer *m_pConstantBuffer;
		void Release() {
			m_pVertexShader->Release();
			m_pVertexLayout->Release();
			m_pPixelShader->Release();
			m_pConstantBuffer->Release();
		}
	protected:

	public:
		void InitPS(ID3D11Device *ipDevice, std::string Filename, std::string Entrypoint, std::string pTarget);
		void InitVSandLayout(ID3D11Device *ipDevice, std::string FileName, std::string Entrypoint, std::string pTargert, D3D11_INPUT_ELEMENT_DESC *layout, const int &SemanticNum);
		void InitConstantBuffer(ID3D11Device *ipDevice);
		//void InitLayout(D3D11_INPUT_ELEMENT_DESC *layout,const int &SemanticNum);
		void SetPS(ID3D11DeviceContext *ipDeviceContext);
		void SetVS(ID3D11DeviceContext *ipDeviceContext);
		void SetLayout(ID3D11DeviceContext *ipDeviceContext);

		void SetConstantBuff(ID3D11DeviceContext *ipDeviceContext, const CONSTANT_BUFFER& cb);
		~ShaderUtility() {
			Release();
		}
	};
}