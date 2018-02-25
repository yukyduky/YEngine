#include "D3D.h"
LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam);

void D3D::initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
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
	ShowWindow(m_Hwnd, ShowWnd);
	UpdateWindow(m_Hwnd);
}

void D3D::createSwapChain()
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

void D3D::createVertexBuffer(ID3D11Buffer ** gVertexBuffer, void* v, size_t& stride, size_t& offset, int numVertices)
{
	// Describe the vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = stride * numVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Set the vertex buffer data
	D3D11_SUBRESOURCE_DATA vertexData;
	memset(&vertexData, 0, sizeof(vertexData));
	vertexData.pSysMem = v;

	HRESULT hr = m_Device->CreateBuffer(&vertexBufferDesc, &vertexData, gVertexBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Vertex buffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createIndexBuffer(ID3D11Buffer ** gIndexBuffer, void* data, int& numIndices)
{
	// Describe the index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * numIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Set the index buffer data
	D3D11_SUBRESOURCE_DATA indexData;

	indexData.pSysMem = data;
	HRESULT hr = m_Device->CreateBuffer(&indexBufferDesc, &indexData, gIndexBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Box Index Buffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::setVertexBuffer(ID3D11Buffer ** gVertexBuffer, size_t& stride, size_t& offset)
{
	m_DevCon->IASetVertexBuffers(0, 1, gVertexBuffer, &stride, &offset);
}

void D3D::setIndexBuffer(ID3D11Buffer * gIndexBuffer, int offset)
{
	m_DevCon->IASetIndexBuffer(gIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
}

void D3D::createConstantBuffer(ID3D11Buffer ** gBuffer, int bufferSize)
{
	// Describes the constant buffer
	D3D11_BUFFER_DESC cbBufferDesc;
	memset(&cbBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	cbBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbBufferDesc.ByteWidth = bufferSize;
	cbBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbBufferDesc.MiscFlags = 0;

	HRESULT hr = m_Device->CreateBuffer(&cbBufferDesc, nullptr, gBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Constant Buffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::mapBuffer(ID3D11Buffer ** gBuffer, void * cbPtr, int structSize)
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

void D3D::cleanup()
{
	m_Device->Release();
	m_DevCon->Release();
	m_SwapChain->Release();
}

int & D3D::GETwWidth()
{
	return m_WinWidth;
}

int & D3D::GETwHeight()
{
	return m_WinHeight;
}

HWND & D3D::GEThwnd()
{
	return m_Hwnd;
}

ID3D11Device *& D3D::GETgDevice()
{
	return m_Device;
}

ID3D11DeviceContext *& D3D::GETgDevCon()
{
	return m_DevCon;
}

IDXGISwapChain *& D3D::GETswapChain()
{
	return m_SwapChain;
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
