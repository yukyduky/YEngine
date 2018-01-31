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
	std::array<ID3D11RenderTargetView*, NUM_DEFERRED_OUTPUTS> gRTVs;
	std::array<ID3D11ShaderResourceView*, NUM_DEFERRED_OUTPUTS> gSRVs;
	std::array<ID3D11Texture2D*, NUM_DEFERRED_OUTPUTS> gDeferredTexs;
	ID3D11RenderTargetView* gFinalRTV;
	ID3D11DepthStencilView* gDSV;
	ID3D11Texture2D* gDSB;
	ID3D11SamplerState* gSampler;
	ID3D11Buffer* gQuadVertexBuffer;
	D3D11_VIEWPORT viewport;

	size_t vertBufferStride;
	size_t vertBufferOffset;

	Shader* currentGeoShaders;
	Shader geoColorShaders;
	Shader geoTexShaders;
	Shader lightShaders;

	std::array<float, 4> clearColor;

	void initShaders();
	void bindTextureToRTVAndSRV(ID3D11Texture2D ** gTexure, ID3D11RenderTargetView ** gRTV, ID3D11ShaderResourceView ** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState ** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void createQuad();
	void createViewport();
	void createBackBufferRTV();
	void createDepthStencilView(size_t width, size_t height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB);
public:
	void init();
	void firstpass();
	void secondpass();
	void setShaderType(SHADERTYPE type);
private:
	const D3D11_INPUT_ELEMENT_DESC geoTexInputDesc[GEOTEX_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC geoColorInputDesc[GEOCOLOR_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC lightInputDesc[LIGHT_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const wchar_t* fileNameLightVertex = L"lightVertex.hlsl";
	const wchar_t* fileNameLightPixel = L"lightPixel.hlsl";

	const wchar_t* fileNameGeoColorVertex = L"geoVertexColor.hlsl";
	const wchar_t* fileNameGeoColorPixel = L"geoPixelColor.hlsl";

	const wchar_t* fileNameGeoTexVertex = L"geoVertexTexture.hlsl";
	const wchar_t* fileNameGeoTexPixel = L"geoPixelTexture.hlsl";
};

#endif // !DEFERREDRENDERER_H
