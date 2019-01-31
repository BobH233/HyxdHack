﻿#include <Windows.h>
#include <set>
#include <string>
#include <d3d11.h>
#include <D3D11Shader.h>
#include <D3Dcompiler.h>//generateshader
#include <stdlib.h>  
#include <tchar.h>  
#include <sstream>  
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")


#include "MinHook/include/MinHook.h" //detour x86&x64
#include "FW1FontWrapper/FW1FontWrapper.h" //font

#define vision4 (indesc.ByteWidth == 144 || indesc.ByteWidth == 216 || indesc.ByteWidth == 348 || indesc.ByteWidth == 1116 || indesc.ByteWidth == 5004 || indesc.ByteWidth == 7908 || indesc.ByteWidth == 13140 || indesc.ByteWidth == 3360 || indesc.ByteWidth == 1536 || indesc.ByteWidth == 2964 || indesc.ByteWidth == 3288 || indesc.ByteWidth == 3432 || indesc.ByteWidth == 2376 || indesc.ByteWidth == 2952 || indesc.ByteWidth == 16176 || indesc.ByteWidth == 12480 || indesc.ByteWidth == Wlist[pList])
#define vision5 (indesc.ByteWidth == 216 || indesc.ByteWidth == 348 || indesc.ByteWidth == 816 || indesc.ByteWidth == 1116 || indesc.ByteWidth == 1536 || indesc.ByteWidth == 2376 || indesc.ByteWidth == 2952 || indesc.ByteWidth == 2964 || indesc.ByteWidth == 3288 || indesc.ByteWidth == 3432 || indesc.ByteWidth == 4344 || indesc.ByteWidth == 4392 || indesc.ByteWidth == 4620 || indesc.ByteWidth == 4800 || indesc.ByteWidth == 5004 || indesc.ByteWidth == 5574 || indesc.ByteWidth == 7908 || indesc.ByteWidth == 12480 || indesc.ByteWidth == 13140 || indesc.ByteWidth == 13692 || indesc.ByteWidth == 16176)
#define vision5lab (indesc.ByteWidth < 1000 && indesc.ByteWidth != 1440 && indesc.ByteWidth != 6 && indesc.ByteWidth != 9 && indesc.ByteWidth != 63 && indesc.ByteWidth != 6846 && indesc.ByteWidth != 4320)
#define vision5lab1 (indesc.ByteWidth < 10000 && indesc.ByteWidth != 1440 && indesc.ByteWidth != 6 && indesc.ByteWidth != 9 && indesc.ByteWidth != 63 && indesc.ByteWidth != 6846 && indesc.ByteWidth != 4320)
#define vision6lab ((indesc.ByteWidth == 6 || indesc.ByteWidth == 9 || indesc.ByteWidth == 24 || indesc.ByteWidth == 36 || indesc.ByteWidth == 60 || indesc.ByteWidth == 63 || indesc.ByteWidth == 72 || indesc.ByteWidth == 84 || indesc.ByteWidth == 96 || indesc.ByteWidth == 108 || indesc.ByteWidth == 129 || indesc.ByteWidth == 174 || indesc.ByteWidth == 318 || indesc.ByteWidth == 330 || indesc.ByteWidth == 348 || indesc.ByteWidth == 366 || indesc.ByteWidth == 408 || indesc.ByteWidth == 414 || indesc.ByteWidth == 420 || indesc.ByteWidth == 426 || indesc.ByteWidth == 438 || indesc.ByteWidth == 453 || indesc.ByteWidth == 522 || indesc.ByteWidth == 528 || indesc.ByteWidth == 558 || indesc.ByteWidth == 600 || indesc.ByteWidth == 582 || indesc.ByteWidth == 621 || indesc.ByteWidth == 639 || indesc.ByteWidth == 690 || indesc.ByteWidth == 732 || indesc.ByteWidth == 756 || indesc.ByteWidth == 768 || indesc.ByteWidth == 801 || indesc.ByteWidth == 849 || indesc.ByteWidth == 852 || indesc.ByteWidth == 882 || indesc.ByteWidth == 900 || indesc.ByteWidth == 912 || indesc.ByteWidth == 954 || indesc.ByteWidth == 969 || indesc.ByteWidth == 1044 || indesc.ByteWidth == 216 || indesc.ByteWidth == 348 || indesc.ByteWidth == 816 || indesc.ByteWidth == 1116 || indesc.ByteWidth == 1536 || indesc.ByteWidth == 2376 || indesc.ByteWidth == 2952 || indesc.ByteWidth == 2964 || indesc.ByteWidth == 3288 || indesc.ByteWidth == 3432 || indesc.ByteWidth == 4344 || indesc.ByteWidth == 4392 || indesc.ByteWidth == 4620 || indesc.ByteWidth == 4800 || indesc.ByteWidth == 5004 || indesc.ByteWidth == 5574 || indesc.ByteWidth == 7908 || indesc.ByteWidth == 12480 || indesc.ByteWidth == 13140 || indesc.ByteWidth == 13692 || indesc.ByteWidth == 16176 || indesc.ByteWidth == 2304 || indesc.ByteWidth == 2310 || indesc.ByteWidth == 2400 || indesc.ByteWidth == 2934 || indesc.ByteWidth == 2994 || indesc.ByteWidth == 3192 || indesc.ByteWidth == 3246 || indesc.ByteWidth == 3369 || indesc.ByteWidth == 3576 || indesc.ByteWidth == 4008 || indesc.ByteWidth == 4275 || indesc.ByteWidth == 4464) && (indesc.ByteWidth != 1440 && indesc.ByteWidth != 6 && indesc.ByteWidth != 9 && indesc.ByteWidth != 63 && indesc.ByteWidth != 6846 && indesc.ByteWidth != 4320))
#define vision6lab1 ((indesc.ByteWidth>=minId && indesc.ByteWidth<=maxId) && (indesc.ByteWidth != 1440 && indesc.ByteWidth != 6 && indesc.ByteWidth != 9 && indesc.ByteWidth != 63 && indesc.ByteWidth != 6846 && indesc.ByteWidth != 4320))
// && indesc.ByteWidth != 6846
// && indesc.ByteWidth != 4320 ----must
//indesc.ByteWidth != 1440 && 
#define vision6final ((indesc.ByteWidth>=minId && indesc.ByteWidth<=maxId) && indesc.ByteWidth<=20000 && (!(indesc.ByteWidth<=4900 && indesc.ByteWidth>=4750)) && (!(indesc.ByteWidth<=2900 && indesc.ByteWidth>=2850)) && (!(indesc.ByteWidth<=3700 && indesc.ByteWidth>=3650)) && (!(indesc.ByteWidth<=6150 && indesc.ByteWidth>=6100)) && (!(indesc.ByteWidth<=4950 && indesc.ByteWidth>=4900)) && (!(indesc.ByteWidth<=1825 && indesc.ByteWidth>=1800)) && (!(indesc.ByteWidth<=3700 && indesc.ByteWidth>=3650)) && (!(indesc.ByteWidth<=1200 && indesc.ByteWidth>=1100)) && (!(indesc.ByteWidth<=5000 && indesc.ByteWidth>=4950)) && (!(indesc.ByteWidth<=850 && indesc.ByteWidth>=800)) && (indesc.ByteWidth != 1440 && indesc.ByteWidth != 6 && indesc.ByteWidth != 9 && indesc.ByteWidth != 63 && indesc.ByteWidth != 4320))

LPCWSTR Vision = L"BobH's 荒野透视 6.0013";
typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *D3D11DrawHook) (ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation);
typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11DrawInstancedHook) (ID3D11DeviceContext* pContext, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall *D3D11DrawIndexedInstancedHook) (ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall *D3D11DrawInstancedIndirectHook) (ID3D11DeviceContext* pContext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs);
typedef void(__stdcall *D3D11DrawIndexedInstancedIndirectHook) (ID3D11DeviceContext* pContext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs);
typedef void(__stdcall *D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews);
typedef void(__stdcall *D3D11CreateQueryHook) (ID3D11Device* pDevice, const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery);
//-----------------my function------------------------
float ManuOffset = 20.0f;
time_t start, nowa;
int flitterId = 0;
int minId = 0, maxId = 0;

void OnDraw();

std::set<int> Wset;
void PrintSet();
void Add2Set(int value);
void DrawSet(float x, float y, float lineheight);
void UpdataSetting();

int Wlist[38] = { 144,216,348,816,1116,1272,1536,1680,2376,2952,2964,3288,3360,3432,4164,4320,4344,4392,4620,4800,5004,5574,7824,7908,12084,12480,13140,13692,16176,19932,29388,39300,41628,44736,84144,91872,96720,102828 };
int pList = 0;
//----------------------------------------------------
D3D11PresentHook phookD3D11Present = NULL;
D3D11DrawHook phookD3D11Draw = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11DrawInstancedHook phookD3D11DrawInstanced = NULL;
D3D11DrawIndexedInstancedHook phookD3D11DrawIndexedInstanced = NULL;
D3D11DrawInstancedIndirectHook phookD3D11DrawInstancedIndirect = NULL;
D3D11DrawIndexedInstancedIndirectHook phookD3D11DrawIndexedInstancedIndirect = NULL;
D3D11PSSetShaderResourcesHook phookD3D11PSSetShaderResources = NULL;
D3D11CreateQueryHook phookD3D11CreateQuery = NULL;

ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;

IFW1Factory *pFW1Factory = NULL;
IFW1FontWrapper *pFontWrapper = NULL;

ID3D11DepthStencilState *one;
D3D11_DEPTH_STENCIL_DESC oneDesc;
UINT aaa;
ID3D11Device* pD3DDevicex = 0;

#include "main.h"
//==========================================================================================================================

//init only once
bool firstTime = true;
//vertex
ID3D11Buffer *veBuffer;
UINT Stride = 0;
UINT veBufferOffset = 0;
D3D11_BUFFER_DESC vedesc;

//index
ID3D11Buffer *inBuffer;
DXGI_FORMAT inFormat;
UINT        inOffset;
D3D11_BUFFER_DESC indesc;

//rendertarget
ID3D11Texture2D* RenderTargetTexture;
ID3D11RenderTargetView* RenderTargetView = NULL;

//shader
ID3D11PixelShader* psRed = NULL;
ID3D11PixelShader* psGreen = NULL;

//pssetshaderresources
UINT pssrStartSlot;
D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
ID3D11ShaderResourceView* ShaderResourceView;

//used for logging/cycling through values
bool logger = false;
int countnum = 0;
char szString[64];
bool EnableStride = false;

//============================================================================================
using namespace std;

template<class out_type, class in_value>
out_type convert(const in_value & t)
{
	stringstream str;
	str << t;
	out_type result;
	str >> result;
	return result;
}

template<class out_type, class in_value>
out_type convert(const in_value & t, bool bISWSring) //转wchar，wstring要用到这个  
{
	wstringstream str;
	str << t;
	out_type result;
	str >> result;
	return result;
}
//==========================================================================================================================
wstring str2;
HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (firstTime)
	{
		//get device and context
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice)))
		{
			pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
			pDevice->GetImmediateContext(&pContext);
		}

		//create depthstencilstate
		D3D11_DEPTH_STENCIL_DESC  stencilDesc;
		stencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		stencilDesc.StencilEnable = true;
		stencilDesc.StencilReadMask = 0xFF;
		stencilDesc.StencilWriteMask = 0xFF;
		stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		stencilDesc.DepthEnable = true;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::ENABLED)]);

		stencilDesc.DepthEnable = false;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::DISABLED)]);

		stencilDesc.DepthEnable = false;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		stencilDesc.StencilEnable = false;
		stencilDesc.StencilReadMask = UINT8(0xFF);
		stencilDesc.StencilWriteMask = 0x0;
		pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::NO_READ_NO_WRITE)]);

		stencilDesc.DepthEnable = true;
		stencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //
		stencilDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		stencilDesc.StencilEnable = false;
		stencilDesc.StencilReadMask = UINT8(0xFF);
		stencilDesc.StencilWriteMask = 0x0;

		stencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		stencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		stencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
		stencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
		pDevice->CreateDepthStencilState(&stencilDesc, &myDepthStencilStates[static_cast<int>(eDepthState::READ_NO_WRITE)]);

		//wireframe
		D3D11_RASTERIZER_DESC rwDesc;
		pContext->RSGetState(&rwState); // retrieve the current state
		rwState->GetDesc(&rwDesc);    // get the desc of the state
		rwDesc.FillMode = D3D11_FILL_WIREFRAME;
		rwDesc.CullMode = D3D11_CULL_NONE;
		// create a whole new rasterizer state
		pDevice->CreateRasterizerState(&rwDesc, &rwState);

		//solid
		D3D11_RASTERIZER_DESC rsDesc;
		pContext->RSGetState(&rsState); // retrieve the current state
		rsState->GetDesc(&rsDesc);    // get the desc of the state
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		// create a whole new rasterizer state
		pDevice->CreateRasterizerState(&rsDesc, &rsState);

		//create font
		HRESULT hResult = FW1CreateFactory(FW1_VERSION, &pFW1Factory);
		hResult = pFW1Factory->CreateFontWrapper(pDevice, L"微软雅黑", &pFontWrapper);
		pFW1Factory->Release();

		// use the back buffer address to create the render target
		//if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture))))
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&RenderTargetTexture)))
		{
			pDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &RenderTargetView);
			RenderTargetTexture->Release();
		}

		firstTime = false;
	}

	//shaders
	if (!psRed)
		GenerateShader(pDevice, &psRed, 1.0f, 0.0f, 0.0f);

	if (!psGreen)
		GenerateShader(pDevice, &psGreen, 0.0f, 1.0f, 0.0f);


	//call before you draw
	pContext->OMSetRenderTargets(1, &RenderTargetView, NULL);
	//draw
	if (pFontWrapper)
		OnDraw();
	

	//热键注册部分
	/*
	if ((GetAsyncKeyState(VK_MENU)) && (GetAsyncKeyState(VK_CONTROL)) && (GetAsyncKeyState(75) & 1)) { //ALT + CTRL + M toggles StrideLoger
		EnableStride = !EnableStride;
		MessageBoxA(0,"toggle","stride",MB_OK);
	}
	//Y:89
	if ((GetAsyncKeyState(89) & 1)) { //Y -> Out Set Data
		PrintSet();
		MessageBoxA(0,"PrintSet","SetPrinter",MB_OK);
	}
	//N:78
	if ((GetAsyncKeyState(78) & 1)) { //N -> toggles Wlist
		if (pList == 37) {
			pList = 0;
		}else {
			pList++;
		}
		MessageBoxA(0,"WList","Wlist",MB_OK);
		Log("Wlist Change:%d",Wlist[pList]);
	}
	*/
	/*
	if ((GetAsyncKeyState(78) & 1)) { //N -> read file to Wlist
		UpdataSetting();
		MessageBoxW(0, L"SettingUpdated", L"Update", MB_OK);
	}
	*/
	//Y:89
	/*
	if ((GetAsyncKeyState(89) & 1)) { //Y -> Out Set Data
		PrintSet();
		MessageBoxA(0, "PrintSet", "SetPrinter", MB_OK);
	}
	*/
	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer)
		veBuffer->GetDesc(&vedesc);
	if (veBuffer != NULL) { veBuffer->Release(); veBuffer = NULL; }

	//get indesc.ByteWidth
	pContext->IAGetIndexBuffer(&inBuffer, &inFormat, &inOffset);
	if (inBuffer)
		inBuffer->GetDesc(&indesc);
	if (inBuffer != NULL) { inBuffer->Release(); inBuffer = NULL; }

	//wallhack example
	
	//ByteWidth == Wlist[pList]
	// && (indesc.ByteWidth < 16100 && indesc.ByteWidth != Wlist[pList])
	pContext->GetDevice(&pD3DDevicex);
	/*
	//this is vision 4.0020
	if (Stride == 24 && vision4)
	{
		Add2Set(IndexCount);
		pContext->OMGetDepthStencilState(&one, &aaa);
		one->GetDesc(&oneDesc);
		oneDesc.DepthEnable = false;
		pD3DDevicex->CreateDepthStencilState(&oneDesc, &one);
		pContext->OMSetDepthStencilState(one, aaa);
		pContext->PSSetShader(psRed, NULL, NULL);
		phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
		oneDesc.DepthEnable = true;
		pD3DDevicex->CreateDepthStencilState(&oneDesc, &one);
		pContext->OMSetDepthStencilState(one, aaa);
		pContext->PSSetShader(psGreen, NULL, NULL);
	}
	*/
	//this is vision 6.0012
	/*
	if (Stride == 24) {
		Add2Set(IndexCount);
	}
	*/
	// && (indesc.ByteWidth != flitterId)
	if (Stride == 24 && vision6final)
	{
		pContext->OMGetDepthStencilState(&one, &aaa);
		one->GetDesc(&oneDesc);
		oneDesc.DepthEnable = false;
		pD3DDevicex->CreateDepthStencilState(&oneDesc, &one);
		pContext->OMSetDepthStencilState(one, aaa);
		pContext->PSSetShader(psRed, NULL, NULL);
		phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
		oneDesc.DepthEnable = true;
		pD3DDevicex->CreateDepthStencilState(&oneDesc, &one);
		pContext->OMSetDepthStencilState(one, aaa);
		pContext->PSSetShader(psGreen, NULL, NULL);
	}
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11PSSetShaderResources(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	pssrStartSlot = StartSlot;

	for (UINT j = 0; j < NumViews; j++)
	{
		//Resources loop
		ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[j];
		if (pShaderResView)
		{
			pShaderResView->GetDesc(&Descr);
			//Descr.Buffer.NumElements;
			//Descr.Format;

			if (
				(Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFER)
				||
				(Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFEREX)
				)
			{
				continue;//Skip buffer resources
			}

		}// if( pShaderResView )
	}// for

	 /*
	 //alternative wallhack example for f'up games
	 if (Descr.Format == 56)
	 {
	 pContext->PSSetShader(psRed, NULL, NULL);
	 SetDepthStencilState(DISABLED);
	 }
	 else
	 if(pssrStartSlot == 1) //if black screen, find correct pssrStartSlot
	 SetDepthStencilState(READ_NO_WRITE);
	 */
	return phookD3D11PSSetShaderResources(pContext, StartSlot, NumViews, ppShaderResourceViews);
}

//==========================================================================================================================

void __stdcall hookD3D11CreateQuery(ID3D11Device* pDevice, const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery)
{
	//Disable Occlusion which prevents rendering player models through certain objects (used by wallhack to see models through walls at all distances, REDUCES FPS)
	if (pQueryDesc->Query == D3D11_QUERY_OCCLUSION)
	{
		D3D11_QUERY_DESC oqueryDesc = CD3D11_QUERY_DESC();
		(&oqueryDesc)->MiscFlags = pQueryDesc->MiscFlags;
		(&oqueryDesc)->Query = D3D11_QUERY_TIMESTAMP;

		return phookD3D11CreateQuery(pDevice, &oqueryDesc, ppQuery);
	}

	return phookD3D11CreateQuery(pDevice, pQueryDesc, ppQuery);
}


//==========================================================================================================================

void __stdcall hookD3D11Draw(ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation)
{
	if (GetAsyncKeyState(VK_F9) & 1)
		Log("Draw called");

	return phookD3D11Draw(pContext, VertexCount, StartVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawInstanced(ID3D11DeviceContext* pContext, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	if (GetAsyncKeyState(VK_F9) & 1)
		Log("DrawInstanced called");

	return phookD3D11DrawInstanced(pContext, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawIndexedInstanced(ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	if (GetAsyncKeyState(VK_F9) & 1)
		Log("DrawIndexedInstanced called");

	return phookD3D11DrawIndexedInstanced(pContext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawInstancedIndirect(ID3D11DeviceContext* pContext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	if (GetAsyncKeyState(VK_F9) & 1)
		Log("DrawInstancedIndirect called");

	return phookD3D11DrawInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawIndexedInstancedIndirect(ID3D11DeviceContext* pContext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	if (GetAsyncKeyState(VK_F9) & 1)
		Log("DrawIndexedInstancedIndirect called");

	return phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
}

//==========================================================================================================================

const int MultisampleCount = 1; // Set to 1 to disable multisampling
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall InitializeHook(LPVOID)
{
	//Sleep(5000);

	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandleA("dxgi.dll");
		Sleep(8000);
	} while (!hDXGIDLL);
	Sleep(100);

	//HMODULE hD3D11DLL = 0;
	//do
	//{
	//hD3D11DLL = GetModuleHandle("d3d11.dll");
	//Sleep(100);
	//} while (!hD3D11DLL);
	//Sleep(1000);

	IDXGISwapChain* pSwapChain;

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = MultisampleCount;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	// LibOVR 0.4.3 requires that the width and height for the backbuffer is set even if
	// you use windowed mode, despite being optional according to the D3D11 documentation.
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createFlags = 0;
#ifdef _DEBUG
	// This flag gives you some quite wonderful debug text. Not wonderful for performance, though!
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBoxA(hWnd, "Failed to create directX device and swapchain!", "Error", MB_ICONERROR);
		return NULL;
	}


	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];

	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[12], hookD3D11DrawIndexed, reinterpret_cast<void**>(&phookD3D11DrawIndexed)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[12]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[24], hookD3D11CreateQuery, reinterpret_cast<void**>(&phookD3D11CreateQuery)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[24]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[39], hookD3D11DrawIndexedInstancedIndirect, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstancedIndirect)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[39]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[20], hookD3D11DrawIndexedInstanced, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstanced)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[20]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[21], hookD3D11DrawInstanced, reinterpret_cast<void**>(&phookD3D11DrawInstanced)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[21]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[40], hookD3D11DrawInstancedIndirect, reinterpret_cast<void**>(&phookD3D11DrawInstancedIndirect)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[40]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[13], hookD3D11Draw, reinterpret_cast<void**>(&phookD3D11Draw)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[13]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[8], hookD3D11PSSetShaderResources, reinterpret_cast<void**>(&phookD3D11PSSetShaderResources)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[8]) != MH_OK) { return 1; }

	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	while (true) {
		Sleep(10);
	}

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	return NULL;
}

//==========================================================================================================================

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		DisableThreadLibraryCalls(hModule);
		GetModuleFileNameA(hModule, dlldir, 512);
		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
		CreateThread(NULL, 0, InitializeHook, NULL, 0, NULL);
		InitLog();
		Log("DLL被载入");
		time(&start);
		break;

	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		if (MH_Uninitialize() != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[12]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pDeviceVTable[24]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[39]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[20]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[21]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[40]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[13]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[8]) != MH_OK) { return 1; }
		break;
	}
	return TRUE;
}
wstring str3;
double cost;
void OnDraw() {
	time(&nowa);
	pFontWrapper->DrawString(pContext, Vision, 16, 16.0f, ManuOffset + 50.0f, 0xff0000ff, FW1_RESTORESTATE);
	pFontWrapper->DrawString(pContext, L"QQ:1795498748", 16, 16.0f, ManuOffset + 80.0f, 0xff0000ff, FW1_RESTORESTATE);
	pFontWrapper->DrawString(pContext, L"For Only Zendee Used", 16, 16.0f, ManuOffset + 110.0f, 0xffffff00, FW1_RESTORESTATE);
	pFontWrapper->DrawString(pContext, L"仅Zendee内部使用", 16, 16.0f, ManuOffset + 140.0f, 0xffffff00, FW1_RESTORESTATE);
	cost = difftime(nowa, start);
	str3 = convert<wstring>(cost, 1);
	if ((int)cost < 60) {
		str3 = L"已稳定运行:" + str3 + L" 秒";
	}else {
		str3 = L"已稳定运行:" + convert<wstring>((int)cost / 60, 1) + L"分" + convert<wstring>((int)cost % 60, 1) + L"秒";
	}
	pFontWrapper->DrawString(pContext, str3.c_str(), 16, 16.0f, ManuOffset + 170.0f, 0xffFFFFFF, FW1_RESTORESTATE);
	UpdataSetting();
	str3 = L"min: " + convert<wstring>(minId, 1) + L" min: " + convert<wstring>(maxId, 1);
	pFontWrapper->DrawString(pContext, str3.c_str(), 16, 16.0f, ManuOffset + 200.0f, 0xffFFFFFF, FW1_RESTORESTATE);
	DrawSet(16.0f, ManuOffset + 200.0f,30.0f);
}
wstring str4;
void DrawSet(float x,float y,float lineheight) {
	for (set<int>::iterator it = Wset.begin(); it != Wset.end(); it++) {
		str4 = convert<wstring>((*it),1);
		pFontWrapper->DrawString(pContext, str4.c_str(), 16, x, y, 0xffFF8C00, FW1_RESTORESTATE);
		y += lineheight;
	}
}

void PrintSet() {
	Log("-----------------SetDate-----------------");
	int p = 0;
	for (std::set<int>::iterator it = Wset.begin(); it != Wset.end(); it++) {
		Log("[%d]%d",p,(*it));
		p++;
	}
	Log("-----------------------------------------");
}

void Add2Set(int value) {
	Wset.insert(value);
}

void UpdataSetting() {
	flitterId = ReadSettingFile();
	str2 = convert<wstring>(flitterId, 1);
	minId = ReadNumMin();
	maxId = ReadNumMax();
}

/*
Model Stride:
	24
	36
	32
	28
	20
*/
/*
dx11 vtable CONTEXT index
Index: 0 | QueryInterface
Index: 1 | Addref
Index: 2 | Release
Index: 3 | GetDevice
Index: 4 | GetPrivateData
Index: 5 | SetPrivateData
Index: 6 | SetPrivateDataInterface
Index: 7 | VSSetConstantBuffers
Index: 8 | PSSetShaderResources
Index: 9 | PSSetShader
Index: 10 | SetSamplers
Index: 11 | SetShader
Index: 12 | DrawIndexed
Index: 13 | Draw
Index: 14 | Map
Index: 15 | Unmap
Index: 16 | PSSetConstantBuffer
Index: 17 | IASetInputLayout
Index: 18 | IASetVertexBuffers
Index: 19 | IASetIndexBuffer
Index: 20 | DrawIndexedInstanced
Index: 21 | DrawInstanced
Index: 22 | GSSetConstantBuffers
Index: 23 | GSSetShader
Index: 24 | IASetPrimitiveTopology
Index: 25 | VSSetShaderResources
Index: 26 | VSSetSamplers
Index: 27 | Begin
Index: 28 | End
Index: 29 | GetData
Index: 30 | GSSetPredication
Index: 31 | GSSetShaderResources
Index: 32 | GSSetSamplers
Index: 33 | OMSetRenderTargets
Index: 34 | OMSetRenderTargetsAndUnorderedAccessViews
Index: 35 | OMSetBlendState
Index: 36 | OMSetDepthStencilState
Index: 37 | SOSetTargets
Index: 38 | DrawAuto
Index: 39 | DrawIndexedInstancedIndirect
Index: 40 | DrawInstancedIndirect
Index: 41 | Dispatch
Index: 42 | DispatchIndirect
Index: 43 | RSSetState
Index: 44 | RSSetViewports
Index: 45 | RSSetScissorRects
Index: 46 | CopySubresourceRegion
Index: 47 | CopyResource
Index: 48 | UpdateSubresource
Index: 49 | CopyStructureCount
Index: 50 | ClearRenderTargetView
Index: 51 | ClearUnorderedAccessViewUint
Index: 52 | ClearUnorderedAccessViewFloat
Index: 53 | ClearDepthStencilView
Index: 54 | GenerateMips
Index: 55 | SetResourceMinLOD
Index: 56 | GetResourceMinLOD
Index: 57 | ResolveSubresource
Index: 58 | ExecuteCommandList
Index: 59 | HSSetShaderResources
Index: 60 | HSSetShader
Index: 61 | HSSetSamplers
Index: 62 | HSSetConstantBuffers
Index: 63 | DSSetShaderResources
Index: 64 | DSSetShader
Index: 65 | DSSetSamplers
Index: 66 | DSSetConstantBuffers
Index: 67 | DSSetShaderResources
Index: 68 | CSSetUnorderedAccessViews
Index: 69 | CSSetShader
Index: 70 | CSSetSamplers
Index: 71 | CSSetConstantBuffers
Index: 72 | VSGetConstantBuffers
Index: 73 | PSGetShaderResources
Index: 74 | PSGetShader
Index: 75 | PSGetSamplers
Index: 76 | VSGetShader
Index: 77 | PSGetConstantBuffers
Index: 78 | IAGetInputLayout
Index: 79 | IAGetVertexBuffers
Index: 80 | IAGetIndexBuffer
Index: 81 | GSGetConstantBuffers
Index: 82 | GSGetShader
Index: 83 | IAGetPrimitiveTopology
Index: 84 | VSGetShaderResources
Index: 85 | VSGetSamplers
Index: 86 | GetPredication
Index: 87 | GSGetShaderResources
Index: 88 | GSGetSamplers
Index: 89 | OMGetRenderTargets
Index: 90 | OMGetRenderTargetsAndUnorderedAccessViews
Index: 91 | OMGetBlendState
Index: 92 | OMGetDepthStencilState
Index: 93 | SOGetTargets
Index: 94 | RSGetState
Index: 95 | RSGetViewports
Index: 96 | RSGetScissorRects
Index: 97 | HSGetShaderResources
Index: 98 | HSGetShader
Index: 99 | HSGetSamplers
Index: 100 | HSGetConstantBuffers
Index: 101 | DSGetShaderResources
Index: 102 | DSGetShader
Index: 103 | DSGetSamplers
Index: 104 | DSGetConstantBuffers
Index: 105 | CSGetShaderResources
Index: 106 | CSGetUnorderedAccessViews
Index: 107 | CSGetShader
Index: 108 | CSGetSamplers
Index: 109 | CSGetConstantBuffers
Index: 110 | ClearState
Index: 111 | Flush
Index: 112 | GetType
Index: 113 | GetContextFlags
Index: 114 | FinishCommandList


// ID3D11 DEVICE virtuals
*QueryInterface 						0
*AddRef 								1
*Release 								2
*CreateBuffer 							3
*CreateTexture1D 						4
*CreateTexture2D 						5
*CreateTexture3D 						6
*CreateShaderResourceView				7
*CreateUnorderedAccessView 				8
*CreateRenderTargetView 				9
*CreateDepthStencilView 				10
*CreateInputLayout 						11
*CreateVertexShader 					12
*CreateGeometryShader 					13
*CreateGeometryShaderWithStreamOutput	14
*CreatePixelShader 						15
*CreateHullShader 						16
*CreateDomainShader						17
*CreateComputeShader					18
*CreateClassLinkage 					19
*CreateBlendState 						20
*CreateDepthStencilState 				21
*CreateRasterizerState 					22
*CreateSamplerState						23
*CreateQuery 							24
*CreatePredicate 						25
*CreateCounter 							26
*CreateDeferredContext 					27
*OpenSharedResource 					28
*CheckFormatSupport 					29
*CheckMultisampleQualityLevels 			30
*CheckCounterInfo 						31
*CheckCounter 							32
*CheckFeatureSupport 					33
*GetPrivateData 						34
*SetPrivateData 						35
*SetPrivateDataInterface 				36
*GetFeatureLevel 						37
*GetCreationFlags 						38
*GetDeviceRemovedReason 				39
*GetImmediateContext 					40
*SetExceptionMode 						41
*GetExceptionMode 						42


// IDXGI SWAPCHAIN virtuals
[0]    7405CADA    (CMTUseCountedObject<CDXGISwapChain>::QueryInterface)
[1]    7405C9A7    (CMTUseCountedObject<CDXGISwapChain>::AddRef)
[2]    7405C9D8    (CMTUseCountedObject<CDXGISwapChain>::Release)
[3]    7405D6BF    (CDXGISwapChain::SetPrivateData)
[4]    7405F6FC    (CDXGISwapChain::SetPrivateDataInterface)
[5]    7405D6AF    (CDXGISwapChain::GetPrivateData)
[6]    7406106A    (CDXGISwapChain::GetParent)
[7]    7405EFDE    (CDXGISwapChain::GetDevice)
[8]    74061BD1    (CDXGISwapChain::Present)
[9]    740617A7    (CDXGISwapChain::GetBuffer)
[10]    74065CD6    (CDXGISwapChain::SetFullscreenState)
[11]    740662DC    (CDXGISwapChain::GetFullscreenState)
[12]    74061146    (CDXGISwapChain::GetDesc)
[13]    740655ED    (CDXGISwapChain::ResizeBuffers)
[14]    74065B8D    (CDXGISwapChain::ResizeTarget)
[15]    7406197B    (CDXGISwapChain::GetContainingOutput)
[16]    74066524    (CDXGISwapChain::GetFrameStatistics)
[17]    74066A58    (CDXGISwapChain::GetLastPresentCount)
[18]    740612C6    (CDXGISwapChain::GetDesc1)
[19]    740613E0    (CDXGISwapChain::GetFullscreenDesc)
[20]    740614F9    (CDXGISwapChain::GetHwnd)
[21]    7406156D    (CDXGISwapChain::GetCoreWindow)
[22]    74061D0D    (CDXGISwapChain[::IDXGISwapChain1]::Present1)
[23]    74062069    (CDXGISwapChain::IsTemporaryMonoSupported)
[24]    740615BB    (CDXGISwapChain::GetRestrictToOutput)
[25]    740615FB    (CDXGISwapChain::SetBackgroundColor)
[26]    740616F1    (CDXGISwapChain::GetBackgroundColor)
[27]    7406173F    (CDXGISwapChain::SetRotation)
[28]    74061770    (CDXGISwapChain::GetRotation)
[29]    7405CC1A    (CMTUseCountedObject<CDXGISwapChain>::`vector deleting destructor')
[30]    7405181E    (CMTUseCountedObject<CDXGISwapChain>::LUCCompleteLayerConstruction)
[31]    7405CBA5    (DXGID3D10ETWRundown)


// DXGI VTable:
[0]	6ED3F979	(CMTUseCountedObject<CDXGISwapChain>::QueryInterface)
[1]	6ED3F84D	(CMTUseCountedObject<CDXGISwapChain>::AddRef)
[2]	6ED3F77D	(CMTUseCountedObject<CDXGISwapChain>::Release)
[3]	6ED6A6D7	(CDXGISwapChain::SetPrivateData)
[4]	6ED6A904	(CDXGISwapChain::SetPrivateDataInterface)
[5]	6ED72BC9	(CDXGISwapChain::GetPrivateData)
[6]	6ED6DCDD	(CDXGISwapChain::GetParent)
[7]	6ED69BF4	(CDXGISwapChain::GetDevice)
[8]	6ED3FAAD	(CDXGISwapChain::Present)
[9]	6ED40209	(CDXGISwapChain::GetBuffer)
[10]	6ED47C1C	(CDXGISwapChain::SetFullscreenState)
[11]	6ED48CD9	(CDXGISwapChain::GetFullscreenState)
[12]	6ED40CB1	(CDXGISwapChain::GetDesc)
[13]	6ED48A3B	(CDXGISwapChain::ResizeBuffers)
[14]	6ED6F153	(CDXGISwapChain::ResizeTarget)
[15]	6ED47BA5	(CDXGISwapChain::GetContainingOutput)
[16]	6ED6D9B5	(CDXGISwapChain::GetFrameStatistics)
[17]	6ED327B5	(CDXGISwapChain::GetLastPresentCount)
[18]	6ED43400	(CDXGISwapChain::GetDesc1)
[19]	6ED6D9D0	(CDXGISwapChain::GetFullscreenDesc)
[20]	6ED6DA90	(CDXGISwapChain::GetHwnd)
[21]	6ED6D79F	(CDXGISwapChain::GetCoreWindow)
[22]	6ED6E352	(?Present1@?QIDXGISwapChain2@@CDXGISwapChain@@UAGJIIPBUDXGI_PRESENT_PARAMETERS@@@Z)
[23]	6ED6E240	(CDXGISwapChain::IsTemporaryMonoSupported)
[24]	6ED44146	(CDXGISwapChain::GetRestrictToOutput)
[25]	6ED6F766	(CDXGISwapChain::SetBackgroundColor)
[26]	6ED6D6B9	(CDXGISwapChain::GetBackgroundColor)
[27]	6ED4417B	(CDXGISwapChain::SetRotation)
[28]	6ED6DDE3	(CDXGISwapChain::GetRotation)
[29]	6ED6FF85	(CDXGISwapChain::SetSourceSize)
[30]	6ED6DF4F	(CDXGISwapChain::GetSourceSize)
[31]	6ED6FCBD	(CDXGISwapChain::SetMaximumFrameLatency)
[32]	6ED6DBE5	(CDXGISwapChain::GetMaximumFrameLatency)
[33]	6ED6D8CD	(CDXGISwapChain::GetFrameLatencyWaitableObject)
[34]	6ED6FB45	(CDXGISwapChain::SetMatrixTransform)
[35]	6ED6DAD0	(CDXGISwapChain::GetMatrixTransform)
[36]	6ED6C155	(CDXGISwapChain::CheckMultiplaneOverlaySupportInternal)
[37]	6ED6E82D	(CDXGISwapChain::PresentMultiplaneOverlayInternal)
[38]	6ED4397A	(CMTUseCountedObject<CDXGISwapChain>::`vector deleting destructor')
[39]	6ED4EAE0	(CSwapBuffer::AddRef)
[40]	6ED46C81	(CMTUseCountedObject<CDXGISwapChain>::LUCBeginLayerDestruction)
*/