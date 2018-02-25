#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <d3d11.h>
#include <d3dcompiler.h>

class Shader
{
public:
	Shader();

	void SetShaders(ID3D11DeviceContext* devCon);
	void CreateShaders(ID3D11Device* device, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void cleanup();

private:
	void CreateVertexShader(ID3D11Device* device, const wchar_t* fileName, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void CreatePixelShader(ID3D11Device* device, const wchar_t* fileName);
	void CreateInputLayout(ID3D11Device* device, ID3DBlob* pVS, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	void SetVertexShader(ID3D11DeviceContext* devCon) const;
	void SetPixelShader(ID3D11DeviceContext* devCon) const;
	void SetInputlayout(ID3D11DeviceContext* devCon) const;

	// COMs
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout * m_VertexLayout;
};

#endif
