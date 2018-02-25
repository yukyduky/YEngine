#include "Shader.h"



Shader::Shader()
{
}

void Shader::SetShaders(ID3D11DeviceContext * devCon)
{
	SetVertexShader(devCon);
	SetPixelShader(devCon);
	SetInputlayout(devCon);
}

void Shader::CreateShaders(ID3D11Device* device, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	// Create Vertex Shader
	CreateVertexShader(device, fileNameVertex, inputDesc, inputDescSize);

	// Create Pixel Shader
	CreatePixelShader(device, fileNamePixel);
}

void Shader::cleanup()
{
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void Shader::CreateVertexShader(ID3D11Device* device, const wchar_t* fileName, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		fileName,		// filename
		nullptr,			// optional macros
		nullptr,			// optional include files
		"VS",				// entry point
		"vs_5_0",			// shader model (target)
		0,					// shader compile options			// here DEBUGGING OPTIONS
		0,					// effect compile options
		&pVS,				// double pointer to ID3DBlob		
		nullptr				// pointer for Error Blob messages.
							// how to use the Error blob, see here
							// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	// Create Vertex shader
	HRESULT hr = device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_VertexShader);
	if (FAILED(hr))
	{
		MessageBox(0, "Vertex Shader - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Create input layout
	CreateInputLayout(device, pVS, inputDesc, inputDescSize);

	pVS->Release();
}

void Shader::CreatePixelShader(ID3D11Device* device, const wchar_t* fileName)
{
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		fileName,			// filename
		nullptr,			// optional macros
		nullptr,			// optional include files
		"PS",				// entry point
		"ps_5_0",			// shader model (target)
		0,					// shader compile options
		0,					// effect compile options
		&pPS,				// double pointer to ID3DBlob		
		nullptr				// pointer for Error Blob messages.
							// how to use the Error blob, see here
							// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	// Create Pixel shader
	HRESULT hr = device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_PixelShader);
	if (FAILED(hr))
	{
		MessageBox(0, "Pixel Shader - Failed", "Error", MB_OK);
		_exit(0);
	}

	pPS->Release();
}

void Shader::CreateInputLayout(ID3D11Device* device, ID3DBlob* pVS, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	// Create the Input Layout
	HRESULT hr = device->CreateInputLayout(inputDesc, inputDescSize, pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_VertexLayout);
	if (FAILED(hr))
	{
		MessageBox(0, "Input Layout - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Shader::SetVertexShader(ID3D11DeviceContext * devCon) const
{
	devCon->VSSetShader(m_VertexShader, nullptr, 0);
}

void Shader::SetPixelShader(ID3D11DeviceContext* devCon) const
{
	devCon->PSSetShader(m_PixelShader, nullptr, 0);
}

void Shader::SetInputlayout(ID3D11DeviceContext* devCon) const
{
	devCon->IASetInputLayout(m_VertexLayout);
}