#pragma once
#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include "Renderer.h"
#include <d3d11.h>
#include <array>
#include "Shader.h"

constexpr int NUM_DEFERRED_OUTPUTS = 3;
constexpr int GEO_INPUT_DESC_SIZE = 3;
constexpr int LIGHT_INPUT_DESC_SIZE = 1;

class DeferredRenderer : public Renderer
{
private:
	IDXGISwapChain * m_SwapChain;
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DevCon;
	HWND m_Hwnd;
	int m_WinWidth;
	int m_WinHeight;

	std::array<ID3D11RenderTargetView*, NUM_DEFERRED_OUTPUTS> m_RTVs = {};
	std::array<ID3D11ShaderResourceView*, NUM_DEFERRED_OUTPUTS> m_SRVs = {};
	std::array<ID3D11Texture2D*, NUM_DEFERRED_OUTPUTS> m_DeferredTexs = {};
	ID3D11RenderTargetView* m_FinalRTV = nullptr;
	ID3D11DepthStencilView* m_DSV = nullptr;
	ID3D11Texture2D* m_DSB = nullptr;
	ID3D11SamplerState* m_Sampler = nullptr;
	ID3D11Buffer* m_QuadVertexBuffer = nullptr;
	D3D11_VIEWPORT m_Viewport;

	size_t m_VertBufferStride;
	size_t m_VertBufferOffset;

	Shader m_GeoShaders;
	Shader m_LightShaders;

	std::array<float, 4> m_ClearColor;

	virtual void initializeWindow(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed) override;
	virtual void createSwapChain() override;
	virtual void setVertexBuffer(ID3D11Buffer** buffer, size_t& stride, size_t& offset) override;
	virtual void setIndexBuffer(ID3D11Buffer* buffer, int offset) override;
	virtual void mapBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize) override;

	void initShaders();
	void bindTextureToRTVAndSRV(ID3D11Texture2D ** gTexure, ID3D11RenderTargetView ** gRTV, ID3D11ShaderResourceView ** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState ** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void createQuad();
	void createViewport();
	void createBackBufferRTV();
	void createDepthStencilView(int width, int height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB);
	void firstpass();
	void secondpass();
public:
	DeferredRenderer();
	virtual ~DeferredRenderer() {}
	void init(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed) override;
	void render() override;
	void cleanup() override;

	virtual bool createResource(ID3D11Resource** texture, ID3D11ShaderResourceView** srv, std::wstring filename) override;
	virtual bool createResource(ID3D11Buffer** buffer, void* data, size_t& stride, size_t& offset, size_t numVertices) override;
	virtual bool createResource(ID3D11Buffer** buffer, void* data, size_t& numIndices) override;
	virtual bool createResource(ID3D11Buffer** buffer, size_t bufferSize) override;
private:
	const D3D11_INPUT_ELEMENT_DESC m_GeoInputDesc[GEO_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC m_LightInputDesc[LIGHT_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const wchar_t* m_FileNameLightVertex = L"lightVertex.hlsl";
	const wchar_t* m_FileNameLightPixel = L"lightPixel.hlsl";

	const wchar_t* m_FileNameGeoTexVertex = L"geoVertex.hlsl";
	const wchar_t* m_FileNameGeoTexPixel = L"geoPixel.hlsl";
};

#endif // !DEFERREDRENDERER_H
