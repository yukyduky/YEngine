#include "DeferredRenderer.h"
#include <Windows.h>
#include <cassert>

LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam);

void DeferredRenderer::initializeWindow(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed)
{
	m_WinWidth = width;
	m_WinHeight = height;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);					// Size of the windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;				// Class styles
	wc.lpfnWndProc = wndProc;						// Name of the function that we chose to process messages
	wc.cbClsExtra = NULL;							// Extra bytes after the wc structure
	wc.cbWndExtra = NULL;							// Extra bytes after the windows instance
	wc.hInstance = hInstance;						// Instance of the current program
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);		// Titlebar icon
	wc.hCursor = LoadCursor(nullptr, nullptr);	// Default mouse icon
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 4);	// Window background color
	wc.lpszMenuName = nullptr;						// Name of the menu attached to the window if we had one
	wc.lpszClassName = LPCTSTR("Project");			// Name of the windows class
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	// Taskbar icon
													// Error checking
	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		_exit(0);
	}

	m_Hwnd = CreateWindowEx(
		NULL,							// Extended style
		wc.lpszClassName,					// Name of windows class
		"Technique Project",				// Titlebar text
		WS_OVERLAPPEDWINDOW,			// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// Starting positions of window
		width,							// Window width
		height,							// Window height
		nullptr,						// In case of a parent window
		nullptr,						// In case of a menu for the window
		hInstance,						// Instance of the current program
		nullptr							// Used for an MDI client window
	);

	// Error checking
	if (!m_Hwnd)
	{
		MessageBox(nullptr, "Error creating window", "Error", MB_OK | MB_ICONERROR);
		_exit(0);
	}

	// Display and update the window
	ShowWindow(m_Hwnd, CmdShow);
	UpdateWindow(m_Hwnd);
}

void DeferredRenderer::createSwapChain()
{
	HRESULT hr;

	// Describe the SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	memset(&swapChainDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;                                  // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // use 32-bit color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how swap chain is to be used
	swapChainDesc.OutputWindow = m_Hwnd;						// the window to be used
	swapChainDesc.SampleDesc.Count = 1;                             // how many multisamples
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Create the SwapChain
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, NULL, D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, nullptr, &m_DevCon);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Swapchain - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void DeferredRenderer::setVertexBuffer(ID3D11Buffer** buffer, size_t& stride, size_t& offset)
{
	m_DevCon->IASetVertexBuffers(0, 1, buffer, &stride, &offset);
}

void DeferredRenderer::setIndexBuffer(ID3D11Buffer* buffer, int offset)
{
	m_DevCon->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}

void DeferredRenderer::mapBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize)
{
	// Map constant buffer so that we can write to it.
	D3D11_MAPPED_SUBRESOURCE dataPtr;
	HRESULT hr = m_DevCon->Map(*gBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
	if (FAILED(hr))
	{
		MessageBox(0, "Buffer mapping - Failed", "Error", MB_OK);
		_exit(0);
	}
	// copy memory from CPU to GPU the entire struct
	memcpy(dataPtr.pData, cbPtr, structSize);
	// UnMap constant buffer so that we can use it again in the GPU
	m_DevCon->Unmap(*gBuffer, 0);
}

void DeferredRenderer::initShaders()
{
	m_GeoShaders.CreateShaders(m_Device, m_FileNameGeoTexVertex, m_FileNameGeoTexPixel, m_GeoInputDesc, GEO_INPUT_DESC_SIZE);

	m_LightShaders.CreateShaders(m_Device, m_FileNameLightVertex, m_FileNameLightPixel, m_LightInputDesc, LIGHT_INPUT_DESC_SIZE);
}

void DeferredRenderer::bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format)
{
	HRESULT hr;

	// Describe the texture
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Format = format;
	texDesc.CPUAccessFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	// Create one texture per rendertarget
	hr = m_Device->CreateTexture2D(&texDesc, nullptr, gTexure);
	if (FAILED(hr))
	{
		MessageBox(0, "Create texture (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Rendertargetview
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	// Create one rtv per output from the pixel shader
	hr = m_Device->CreateRenderTargetView(*gTexure, &rtvDesc, gRTV);
	if (FAILED(hr))
	{
		MessageBox(0, "Create RTV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Shaderresourceview
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// Create one srv per texture to be loaded into the next pixel shader
	hr = m_Device->CreateShaderResourceView(*gTexure, &srvDesc, gSRV);
	if (FAILED(hr))
	{
		MessageBox(0, "Create SRV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void DeferredRenderer::initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc)
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sampDesc;
	memset(&sampDesc, 0, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = filter;
	sampDesc.AddressU = texAdressModeU;
	sampDesc.AddressV = texAdressModeV;
	sampDesc.AddressW = texAdressModeW;
	sampDesc.ComparisonFunc = compFunc;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = m_Device->CreateSamplerState(&sampDesc, gSampler);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Samplerstate - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void DeferredRenderer::createQuad()
{
	struct Vertex
	{
		float x, y, z, w;
	};

	// Vertices
	Vertex v[] =
	{
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
	};
	// Stride and offset
	m_VertBufferStride = sizeof(Vertex);
	m_VertBufferOffset = 0;

	// Create the vertex buffer
	this->createResource(&m_QuadVertexBuffer, &v, m_VertBufferStride, m_VertBufferOffset, 4);
}

void DeferredRenderer::createViewport()
{
	memset(&m_Viewport, 0, sizeof(D3D11_VIEWPORT));

	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = static_cast<FLOAT>(m_WinWidth);
	m_Viewport.Height = static_cast<FLOAT>(m_WinHeight);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
}

void DeferredRenderer::createBackBufferRTV()
{
	HRESULT hr;

	// Describe the Buffer
	DXGI_MODE_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = m_WinWidth;
	bufferDesc.Height = m_WinHeight;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Create the BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Swapchain backbuffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Create the Render Target
	hr = m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_FinalRTV);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Render Target View - Failed", "Error", MB_OK);
		_exit(0);
	}
	BackBuffer->Release();
}

void DeferredRenderer::createDepthStencilView(int width, int height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB)
{
	HRESULT hr;

	// Describe the Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	memset(&depthStencilDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));

	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// Creates the Depth/Stencil View
	hr = m_Device->CreateTexture2D(&depthStencilDesc, nullptr, gDSB);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Depth Texture - Failed", "Error", MB_OK);
		_exit(0);
	}

	hr = m_Device->CreateDepthStencilView(*gDSB, nullptr, gDSV);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Depth Stencil - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void DeferredRenderer::firstpass()
{
	// Clear the final RenderTargetView
	m_DevCon->ClearRenderTargetView(m_FinalRTV, m_ClearColor.data());
	// Clear the deferred RenderTargetViews
	for (auto &i : m_RTVs)
	{
		m_DevCon->ClearRenderTargetView(i, m_ClearColor.data());
	}
	// Clear the DepthStencilView
	m_DevCon->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set the geo shaders to the current shaders
	m_GeoShaders.SetShaders(m_DevCon);
	m_DevCon->RSSetViewports(1, &m_Viewport);

	// Set the rendertarget to the deferred RenderTargetViews
	m_DevCon->OMSetRenderTargets(NUM_DEFERRED_OUTPUTS, m_RTVs.data(), m_DSV);
}

void DeferredRenderer::secondpass()
{
	// Set the light shaders as the current shaders
	m_LightShaders.SetShaders(m_DevCon);

	// Set the vertexbuffer to the quad vertices
	m_DevCon->IASetVertexBuffers(0, 1, &m_QuadVertexBuffer, &m_VertBufferStride, &m_VertBufferOffset);
	m_DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Unbind the RenderTargetViews
	ID3D11RenderTargetView* gNullRTV[NUM_DEFERRED_OUTPUTS] = { nullptr, nullptr, nullptr };
	m_DevCon->OMSetRenderTargets(NUM_DEFERRED_OUTPUTS, gNullRTV, nullptr);

	// Bind the ShaderResourceVies
	m_DevCon->PSSetShaderResources(0, NUM_DEFERRED_OUTPUTS, m_SRVs.data());

	// Set the rendertarget to the final rendertarget
	m_DevCon->OMSetRenderTargets(1, &m_FinalRTV, nullptr);

	// Draw the final texture over the whole screen
	m_DevCon->Draw(4, 0);
	// Present the backbuffer to the screen
	m_SwapChain->Present(0, 0);

	// Unbind the ShaderResourceViews
	ID3D11ShaderResourceView* gNullSRV[NUM_DEFERRED_OUTPUTS] = { nullptr, nullptr, nullptr };
	m_DevCon->PSSetShaderResources(0, NUM_DEFERRED_OUTPUTS, gNullSRV);
}

DeferredRenderer::DeferredRenderer()
{
	// Set the clear color
	m_ClearColor[0] = 255.0f;
	m_ClearColor[1] = 0.0f;
	m_ClearColor[2] = 255.0f;
	m_ClearColor[3] = 255.0f;
}

void DeferredRenderer::init(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed)
{
	this->initializeWindow(hInstance, CmdShow, width, height, windowed);
	this->createSwapChain();

	// Create the backbuffer RenderTargetView (gFinalRTV)
	this->createBackBufferRTV();

	// Create the DepthStencilView
	this->createDepthStencilView(m_WinWidth, m_WinHeight, &m_DSV, &m_DSB);

	// Initialize all shaders
	this->initShaders();

	// Bind the deferred RTVs and SRVs to eachother
	for (int i = 0; i < NUM_DEFERRED_OUTPUTS; i++)
	{
		this->bindTextureToRTVAndSRV(&m_DeferredTexs[i], &m_RTVs[i], &m_SRVs[i], m_WinWidth, m_WinHeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
	}

	// Create the quad to draw on
	this->createQuad();

	// Initialize the sampler
	this->initSampler(&m_Sampler, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_ALWAYS);

	// Create the viewport
	this->createViewport();
}

void DeferredRenderer::render()
{
	this->firstpass();
	this->secondpass();
}

void DeferredRenderer::cleanup()
{
	m_SwapChain->Release();
	m_Device->Release();
	m_DevCon->Release();

	for (auto &i : m_RTVs)
	{
		i->Release();
	}
	for (auto &i : m_SRVs)
	{
		i->Release();
	}
	for (auto &i : m_DeferredTexs)
	{
		i->Release();
	}

	m_FinalRTV->Release();
	m_DSV->Release();
	m_DSB->Release();
	m_Sampler->Release();
	m_QuadVertexBuffer->Release();
	m_GeoShaders.cleanup();
	m_LightShaders.cleanup();
}

bool DeferredRenderer::createResource(ID3D11Resource** texture, ID3D11ShaderResourceView** srv, std::wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(m_Device, filename.c_str(), texture, srv);
	assert(!FAILED(hr) && "Failed to create texture from file - Deferred Renderer");
	return FAILED(hr) ? false : true;
}

bool DeferredRenderer::createResource(ID3D11Buffer** buffer, void* data, size_t& stride, size_t& offset, size_t numVertices)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = stride * numVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	memset(&vertexData, 0, sizeof(vertexData));
	vertexData.pSysMem = data;

	HRESULT hr = m_Device->CreateBuffer(&vertexBufferDesc, &vertexData, buffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Vertex buffer - Failed", "Error", MB_OK);
	}
	return FAILED(hr) ? false : true ;
}

bool DeferredRenderer::createResource(ID3D11Buffer** buffer, void* data, size_t& numIndices)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * numIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	memset(&indexData, 0, sizeof(indexData));
	indexData.pSysMem = data;

	HRESULT hr = m_Device->CreateBuffer(&indexBufferDesc, &indexData, buffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Box Index Buffer - Failed", "Error", MB_OK);
	}
	return FAILED(hr) ? false : true;
}

bool DeferredRenderer::createResource(ID3D11Buffer** buffer, size_t bufferSize)
{
	D3D11_BUFFER_DESC cbBufferDesc;
	memset(&cbBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	cbBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbBufferDesc.ByteWidth = bufferSize;
	cbBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbBufferDesc.MiscFlags = 0;

	HRESULT hr = m_Device->CreateBuffer(&cbBufferDesc, nullptr, buffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Constant Buffer - Failed", "Error", MB_OK);
	}
	return FAILED(hr) ? false : true;
}

LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
