#pragma once
#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <d3d11.h>
#include <array>
#include "Shader.h"

enum class SHADERTYPE { COLOR, TEXTURE };

constexpr int NUM_DEFERRED_OUTPUTS = 3;
constexpr int GEOTEX_INPUT_DESC_SIZE = 3;
constexpr int GEOCOLOR_INPUT_DESC_SIZE = 3;
constexpr int LIGHT_INPUT_DESC_SIZE = 1;

class DeferredRenderer
{
private:
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

	Shader* m_CurrentGeoShaders = nullptr;
	Shader m_GeoColorShaders;
	Shader m_GeoTexShaders;
	Shader m_LightShaders;

	std::array<float, 4> m_ClearColor;

	void initShaders();
	void bindTextureToRTVAndSRV(ID3D11Texture2D ** gTexure, ID3D11RenderTargetView ** gRTV, ID3D11ShaderResourceView ** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState ** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void createQuad();
	void createViewport();
	void createBackBufferRTV();
	void createDepthStencilView(int width, int height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB);
public:
	void init();
	void firstpass();
	void secondpass();
	void cleanup();
	void setShaderType(SHADERTYPE type);
private:
	const D3D11_INPUT_ELEMENT_DESC m_GeoTexInputDesc[GEOTEX_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC m_GeoColorInputDesc[GEOCOLOR_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC m_LightInputDesc[LIGHT_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const wchar_t* m_FileNameLightVertex = L"lightVertex.hlsl";
	const wchar_t* m_FileNameLightPixel = L"lightPixel.hlsl";

	const wchar_t* m_FileNameGeoColorVertex = L"geoVertexColor.hlsl";
	const wchar_t* m_FileNameGeoColorPixel = L"geoPixelColor.hlsl";

	const wchar_t* m_FileNameGeoTexVertex = L"geoVertexTexture.hlsl";
	const wchar_t* m_FileNameGeoTexPixel = L"geoPixelTexture.hlsl";
};

#endif // !DEFERREDRENDERER_H
