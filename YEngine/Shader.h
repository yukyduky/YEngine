#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <d3d11.h>
#include <d3dcompiler.h>

class Shader
{
public:
	Shader();

	void SetShaders(ID3D11DeviceContext* gDevCon);
	void CreateShaders(ID3D11Device* gDevice, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void cleanup();

private:
	void CreateVertexShader(ID3D11Device* gDevice, const wchar_t* fileName, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void CreatePixelShader(ID3D11Device* gDevice, const wchar_t* fileName);
	void CreateInputLayout(ID3D11Device* gDevice, ID3DBlob* pVS, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void SetVertexShader(ID3D11DeviceContext* gDevCon) const;
	void SetPixelShader(ID3D11DeviceContext* gDevCon) const;
	void SetInputlayout(ID3D11DeviceContext* gDevCon) const;

	// COMs
	ID3D11VertexShader* gVertexShader;
	ID3D11PixelShader* gPixelShader;
	ID3D11InputLayout * gVertexLayout;

	// Error handling
	HRESULT hr;
};

#endif
