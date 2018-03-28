#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <d3d11.h>
#include <WICTextureLoader.h>
#include <string>

class Renderer
{
private:
	virtual void initializeWindow(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed) = 0;
	virtual void createSwapChain() = 0;
	virtual void setVertexBuffer(ID3D11Buffer** buffer, size_t& stride, size_t& offset) = 0;
	virtual void setIndexBuffer(ID3D11Buffer* buffer, int offset) = 0;
	virtual void mapBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize) = 0;
public:
	virtual ~Renderer() {}

	virtual void init(HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed) = 0;
	virtual void render() = 0;
	virtual void cleanup() = 0;

	virtual bool createResource(ID3D11Resource** texture, ID3D11ShaderResourceView** srv, std::wstring filename) = 0;
	virtual bool createResource(ID3D11Buffer** buffer, void* data, size_t& stride, size_t& offset, size_t numVertices) = 0;
	virtual bool createResource(ID3D11Buffer** buffer, void* data, size_t& numIndices) = 0;
	virtual bool createResource(ID3D11Buffer** buffer, size_t bufferSize) = 0;
};

#endif // RENDERER_H
