#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fbxsdk.h>

//#include "fbx.h"

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// 一つの頂点情報を格納する構造体


// GPU(シェーダ側)へ送る数値をまとめた構造体
struct CONSTANT_BUFFER {
	XMMATRIX mWVP;
};

#define WIN_STYLE WS_OVERLAPPEDWINDOW
int CWIDTH;     // クライアント領域の幅
int CHEIGHT;    // クライアント領域の高さ

HWND WHandle;
const char *ClassName = "Temp_Window";

IDXGISwapChain *pSwapChain;
ID3D11Device *pDevice;
ID3D11DeviceContext *pDeviceContext;

ID3D11RenderTargetView *pBackBuffer_RTV;

ID3D11RasterizerState *pRasterizerState;

ID3D11InputLayout *pVertexLayout;

ID3D11VertexShader *pVertexShader;		//model のシェーダーごとに必要
ID3D11PixelShader *pPixelShader;		//modelのシェーダーごとに必要
ID3D11Buffer *pConstantBuffer;			//シェーダーのコンスタントバッファーと合わせる


#define __FBX_DEBUG__

#ifndef __FBX_DEBUG__
#include "model.h"
#endif

#ifdef __FBX_DEBUG__
struct VERTEX {
	XMFLOAT3 Pos;
};
#endif


//#define __FBX_DEBUG_MY_FBX__

#ifdef __FBX_DEBUG_MY_FBX__

FbxManager *fbxManager = NULL;			//fbxの読み込みに必要
FbxScene *fbxScene = NULL;				//fbxの読み込みに必要
FbxMesh *mesh = NULL;

#endif

#ifndef __FBX_DEBUG_MY_FBX__

#include "fbx.h"

MyFbx::MyFbx dbgFbx;

#ifndef __MY_MODEL_VERTEX_INFO__
#define __MY_MODEL_VERTEX_INFO__

struct MY_VERTEX {
	DirectX::XMFLOAT3 Pos;
};

struct MY_MODEL_VERTEX_INFO {
	MY_VERTEX *Vertices;
	int numVertex;
	int numFace;
	//int numPolyVertex;
	MY_MODEL_VERTEX_INFO()
		:Vertices(NULL)
		, numVertex(0)
		, numFace(0)
		//, numPolyVertex(0){};
	{};
	~MY_MODEL_VERTEX_INFO() {
		delete[] Vertices;
	}
};

#endif

MY_MODEL_VERTEX_INFO dbgMMVertex;
#endif

#ifdef __FBX_DEBUG__
ID3D11Buffer *VerBuffer = NULL;
ID3D11Buffer *IndBuffer = NULL;
VERTEX *vertices;

#endif


#ifndef __FBX_DEBUG__
MyModel::Model DemonModel;
#endif

static float x = 0;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow) {

	// ウィンドウクラスを登録する
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = ClassName;
	RegisterClass(&wc);

	// ウィンドウの作成
	WHandle = CreateWindow(ClassName, "FBXの読み込み(モデルデータ)", WIN_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 800, NULL, NULL, hInstance, NULL);
	if (WHandle == NULL) return 0;
	ShowWindow(WHandle, nCmdShow);

	// メッセージループの実行
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ----- DXの処理 -----
			float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
			pDeviceContext->ClearRenderTargetView(pBackBuffer_RTV, clearColor);

			// パラメータの計算
			XMVECTOR eye_pos = XMVectorSet(0.0f, 70.0f, 500.0f, 1.0f);
			XMVECTOR eye_lookat = XMVectorSet(0.0f, 70.0f, 0.0f, 1.0f);
			XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
			XMMATRIX World = XMMatrixRotationY(x += 0.001f);
			XMMATRIX View = XMMatrixLookAtLH(eye_pos, eye_lookat, eye_up);
			XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)CWIDTH / (FLOAT)CHEIGHT, 0.1f, 800.0f);

			// パラメータの受け渡し
			D3D11_MAPPED_SUBRESOURCE pdata;
			CONSTANT_BUFFER cb;
			cb.mWVP = XMMatrixTranspose(World * View * Proj);
			pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
			pDeviceContext->Unmap(pConstantBuffer, 0);

			// 描画実行
#ifdef __FBX_DEBUG_MY_FBX__
			pDeviceContext->DrawIndexed(mesh->GetPolygonVertexCount(), 0, 0);
#endif

#ifdef __FBX_DEBUG_MY_FBX__
			pDeviceContext->DrawIndexed(dbgMMVertex.numFace, 0, 0);
#endif
#ifndef __FBX_DEBUG__
			pDeviceContext->DrawIndexed(DemonModel.GetNumFace(), 0, 0);
#endif
			pSwapChain->Present(0, 0);
		}
	}

	return 0;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
	case WM_CREATE:
	{

		// ----- パイプラインの準備 -----
		RECT csize;
		GetClientRect(hwnd, &csize);
		CWIDTH = csize.right;
		CHEIGHT = csize.bottom;

		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.BufferCount = 1;
		scd.BufferDesc.Width = CWIDTH;
		scd.BufferDesc.Height = CHEIGHT;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = hwnd;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = TRUE;
		D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &fl, 1, D3D11_SDK_VERSION, &scd, &pSwapChain, &pDevice, NULL, &pDeviceContext);

		ID3D11Texture2D *pbbTex;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbbTex);
		pDevice->CreateRenderTargetView(pbbTex, NULL, &pBackBuffer_RTV);
		pbbTex->Release();

		// ビューポートの設定
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)CWIDTH;
		vp.Height = (FLOAT)CHEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		// シェーダの設定
		ID3DBlob *pCompileVS = NULL;
		ID3DBlob *pCompilePS = NULL;
		D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
		D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);

		// 頂点レイアウト
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
		pCompileVS->Release();
		pCompilePS->Release();

		// 定数バッファの設定
		D3D11_BUFFER_DESC cb;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		cb.Usage = D3D11_USAGE_DYNAMIC;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;
		pDevice->CreateBuffer(&cb, NULL, &pConstantBuffer);

#ifndef __FBX_DEBUG__
		DemonModel.Load("demonwalking.fbx");
		
#endif
#ifdef __FBX_DEBUG_MY_FBX__

		// FBXの読み込み
		fbxManager = FbxManager::Create();
		fbxScene = FbxScene::Create(fbxManager, "fbxscene");
		FbxString FileName("demonwalking.fbx");
		FbxImporter *fbxImporter = FbxImporter::Create(fbxManager, "imp");
		fbxImporter->Initialize(FileName.Buffer(), -1, fbxManager->GetIOSettings());
		fbxImporter->Import(fbxScene);
		fbxImporter->Destroy();

		// 頂点データの取り出し
		for (int i = 0; i < fbxScene->GetRootNode()->GetChildCount(); i++) {
			if (fbxScene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
				mesh = fbxScene->GetRootNode()->GetChild(i)->GetMesh();
				break;
			}
		}
		vertices = new VERTEX[mesh->GetControlPointsCount()];
		for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
			vertices[i].Pos.x = (FLOAT)mesh->GetControlPointAt(i)[0];
			vertices[i].Pos.y = (FLOAT)mesh->GetControlPointAt(i)[1];
			vertices[i].Pos.z = (FLOAT)mesh->GetControlPointAt(i)[2];
		}
#endif

#ifndef __FBX_DEBUG_MY_FBX__
		dbgFbx.LoadFBX(&dbgMMVertex, "demonwalking.fbx");

#endif

#ifndef __FBX_DEBUG__
		DemonModel.InitVertexBuffer(pDevice);
#endif



#ifdef __FBX_DEBUG_MY_FBX__

		//// 頂点データ用バッファの設定 debug on
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(VERTEX) * mesh->GetControlPointsCount();
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = vertices;
		pDevice->CreateBuffer(&bd_vertex, &data_vertex, &VerBuffer);
#endif

#ifndef __FBX_DEBUG_MY_FBX__

		//// 頂点データ用バッファの設定 debug off
		D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(VERTEX) * dbgMMVertex.numVertex;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_vertex;
		data_vertex.pSysMem = dbgMMVertex.Vertices;
		pDevice->CreateBuffer(&bd_vertex, &data_vertex, &VerBuffer);
#endif



#ifndef __FBX_DEBUG__
			//// 頂点データ用バッファの設定 debug off
	
		DemonModel.InitIndexBuffer(pDevice);
#endif



#ifdef __FBX_DEBUG_MY_FBX__

		//// インデックスデータの取り出しとバッファの設定
		D3D11_BUFFER_DESC bd_index;
		bd_index.ByteWidth = sizeof(int) * mesh->GetPolygonVertexCount();
		bd_index.Usage = D3D11_USAGE_DEFAULT;
		bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_index.CPUAccessFlags = 0;
		bd_index.MiscFlags = 0;
		bd_index.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_index;
		data_index.pSysMem = mesh->GetPolygonVertices();
		pDevice->CreateBuffer(&bd_index, &data_index, &IndBuffer);
#endif

#ifndef __FBX_DEBUG_MY_FBX__

		//// インデックスデータの取り出しとバッファの設定 debugoff
		D3D11_BUFFER_DESC bd_index;
		bd_index.ByteWidth = sizeof(int) * dbgMMVertex.numFace;
		bd_index.Usage = D3D11_USAGE_DEFAULT;
		bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_index.CPUAccessFlags = 0;
		bd_index.MiscFlags = 0;
		bd_index.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA data_index;
		data_index.pSysMem = dbgFbx.GetMesh()->GetPolygonVertices();
		pDevice->CreateBuffer(&bd_index, &data_index, &IndBuffer);

#endif


		// ラスタライザの設定
		D3D11_RASTERIZER_DESC rdc = {};
		rdc.CullMode = D3D11_CULL_BACK;
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.FrontCounterClockwise = TRUE;
		pDevice->CreateRasterizerState(&rdc, &pRasterizerState);

		// オブジェクトの反映
#ifndef __FBX_DEBUG__
		UINT stride = sizeof(MY_VERTEX); //Debugoff
#endif

#ifdef __FBX_DEBUG__
		UINT stride = sizeof(VERTEX);	//Debugon
#endif



		UINT offset = 0;
#ifdef __FBX_DEBUG__	//debugonn

		pDeviceContext->IASetVertexBuffers(0, 1, &VerBuffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(IndBuffer, DXGI_FORMAT_R32_UINT, 0);
		
#endif


#ifndef __FBX_DEBUG__		//debugoff
		pDeviceContext->IASetVertexBuffers(0, 1, DemonModel.GetVertexBuffer(), &stride, &offset);
		pDeviceContext->IASetIndexBuffer(DemonModel.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
#endif

		pDeviceContext->IASetInputLayout(pVertexLayout);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		pDeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);


		pDeviceContext->VSSetShader(pVertexShader, NULL, 0);
		pDeviceContext->PSSetShader(pPixelShader, NULL, 0);
		pDeviceContext->RSSetState(pRasterizerState);


		pDeviceContext->OMSetRenderTargets(1, &pBackBuffer_RTV, NULL);
		pDeviceContext->RSSetViewports(1, &vp);

		return 0;
	}
	case WM_DESTROY:

		pSwapChain->Release();
		pDeviceContext->Release();
		pDevice->Release();

		pBackBuffer_RTV->Release();

		pRasterizerState->Release();
		pVertexShader->Release();
		pVertexLayout->Release();
		pPixelShader->Release();
		pConstantBuffer->Release();
		
#ifdef __FBX_DEBUG__
		VerBuffer->Release();
#endif

#ifdef __FBX_DEBUG_MY_FBX__

		
		fbxScene->Destroy();
		fbxManager->Destroy();

		delete[] vertices;
#endif
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}